#include "canvas.h"
#include <cassert>
#include <math.h>

using namespace std;
using namespace agl;

// Constructor
Canvas::Canvas(int w, int h) : _canvas(w, h)
{
   _canvas = Image(w, h);
   _grad = false;
   _gradColort = {0, 0, 0};
   _gradColorb = {255, 255, 255};
}

void Canvas::gradC(bool g, Pixel top, Pixel bottom)
{
   _grad = g;
   _gradColort = top;
   _gradColorb = bottom;
}

// Destructor
Canvas::~Canvas()
{
   _vertices.clear();
   _triangles.clear();
}

// Saves image
void Canvas::save(const std::string& filename)
{
   _canvas.save(filename);
}

// Sets shape type
void Canvas::begin(PrimitiveType type)
{
   _vertices.clear();
   if (type == UNDEFINED) 
   {
      _shape = 1;
   } 
   else if (type == LINES) 
   {
      _shape = 2;
   } 
   else if (type == TRIANGLES) 
   {
      _shape = 3;
   } 
   else if (type == ISOCUBES)
   {
      _shape = 4;
   }
   else if (type == ISOTETS)
   {
      _shape = 5;
   }
   else if (type == CIRCLES)
   {
      _shape = 6;
   }
   else 
   {
      std::cout << "ERROR. Invalid drawing type selected" << std::endl;
      _shape = 0;
   }

}

// 
void Canvas::end()
{
   Vertex a;
   Vertex b;
   Vertex c;

   // If we are drawing lines, we do so this way
   if (_shape == 2) 
   {
      for (unsigned int i = 0; i < _vertices.size(); ++i) 
      {
         if ((i + 1) % 2 == 0) 
         {
            a = _vertices[i - 1];
            b = _vertices[i];
            bresenham(a, b);
         }
      }
   }
   else if (_shape == 3)
   {
      for (unsigned int i = 0; i < _vertices.size(); ++i)
      {
         if ((i + 1) % 3 == 0)
         {
            a = _vertices[i - 2];
            b = _vertices[i - 1];
            c = _vertices[i];
            triangle(a, b, c);
         }
      }
   }
   else if (_shape == 4)
   {
      for (unsigned int i = 0; i < _vertices.size(); ++i)
      {
         isoCube(10, _vertices[i]);
      }
   }
   else if (_shape == 5)
   {
      for (unsigned int i = 0; i < _vertices.size(); ++i)
      {
         isoTet(12, _vertices[i]);
      }
   }
   else if (_shape == 6)
   {
      for (unsigned int i = 0; i < _vertices.size(); ++i)
      {
         circle(_vertices[i], 10);
      }
   }
   _shape = 0;
   _vertices.clear();
}

// 
void Canvas::vertex(int x, int y)
{
   if(x > (_canvas.width() - 1)) 
   {
         x = _canvas.width() - 1;
      }
   if (y > (_canvas.height() - 1)) 
   {
         y = _canvas.height() - 1;
   }
   if (_shape == 1 || _shape == 2 || _shape == 3 || _shape == 4 || _shape == 5 || _shape == 6) 
   {
      _vertices.push_back(Vertex{_curColor, (unsigned char)x, (unsigned char)y});
   }
   else 
   {
      std::cout << "ERROR. Invalid drawing type selected" << std::endl;
   }
}

// Changes current vertex to a given color
void Canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
   _curColor = {r, g, b};
}

// Changes background to given color
void Canvas::background(unsigned char r, unsigned char g, unsigned char b, unsigned char r2, unsigned char g2, unsigned char b2)
{
   float t;
   Pixel tempColor;
   for (int row = 0; row < (_canvas.height()); ++row) 
   {
      for (int c = 0; c < (_canvas.width()); ++c) 
      {
         t = (float)row / (_canvas.height());
         tempColor = {
            (unsigned char)(int)(r * (1 - t) + r2 * (t)),
            (unsigned char)(int)(g * (1 - t) + g2 * (t)),
            (unsigned char)(int)(b * (1 - t) + b2 * (t))
         };
         _canvas.set(row, c, tempColor);
      }
   }
}

// Bresenham line drawing
void Canvas::bresenham(Vertex a, Vertex b) 
{
   
   int x = 0;
   int y = 0;
   int W = b.x - a.x; 
   int H = b.y - a.y; 
   int F; // equals 2 * H - W for horizontal, 2 * W - H for vertical
   float m = (float)H / W; 
   float t = 0.0f;
   int tempR = 0;
   int tempG = 0;
   int tempB = 0;
   Pixel c = _curColor;

   // Octant I
   if ((a.x < b.x) && ((0 <= m) && (m <= 1)))
   {
      y = a.y;
      F = 2 * H - W;
      for (unsigned int Ix = a.x; Ix <= (b.x - 1); ++Ix)
      {
         t = (float)Ix / (W);
         tempR = (int)(a.color.r * (1 - t) + b.color.r * (t));
         tempG = (int)(a.color.g * (1 - t) + b.color.g * (t));
         tempB = (int)(a.color.b * (1 - t) + b.color.b * (t));
         c = {(unsigned char)tempR, (unsigned char)tempG, (unsigned char)tempB};
         _canvas.set(y, Ix, c);
         if (F > 0)
         {
            y++;
            F += 2 * (H - W);
         }
         else 
         {
            F += 2 * H;
         }
      }
   }
   // Octant II
   else if (((a.y < b.y) && (1 < m)) || ((H >= 0 && W == 0) && (a.y < b.y)))
   {
      x = a.x;
      F = 2 * W - H;
      for (unsigned int IIy = a.y; IIy <= (b.y); ++IIy)
      {
         t = (float)IIy / (H);
         tempR = (int)(a.color.r * (1 - t) + b.color.r * (t));
         tempG = (int)(a.color.g * (1 - t) + b.color.g * (t));
         tempB = (int)(a.color.b * (1 - t) + b.color.b * (t));
         c = {(unsigned char)tempR, (unsigned char)tempG, (unsigned char)tempB};
         _canvas.set(IIy, x, c);
         if (F > 0)
         {
            x++;
            F += 2 * (W - H);
         }
         else
         {
            F += 2 * W;
         }
      }
   }
   // Octant III
   else if ((a.y < b.y) && (-1 > m)) 
   {

   }
   // Octant IV
   else if ((b.x < a.x) && ((0 >= m) && (m >= -1)))
   {

   }
   // Octant V
   else if ((b.x < a.x) && ((0 < m) && (m <= 1)))
   {

   }
   // Octant VI
   else if ((b.y < a.y) && (1 < m))
   {

   }
   // Octant VII
   else if ((b.y < a.y) && (-1 > m))
   {
      x = a.x;
      H = H * -1;
      F = 2 * W - H;
      for (unsigned int IIy = a.y; IIy >= (b.y); IIy--)
      {
         t = (float)IIy / (H);
         tempR = (int)(a.color.r * (1 - t) + b.color.r * (t));
         tempG = (int)(a.color.g * (1 - t) + b.color.g * (t));
         tempB = (int)(a.color.b * (1 - t) + b.color.b * (t));
         c = {(unsigned char)tempR, (unsigned char)tempG, (unsigned char)tempB};
         _canvas.set(IIy, x, c);
         if (F > 0)
         {
            x++;
            F += 2 * (W - H);
         }
         else
         {
            F += 2 * W;
         }
      }
   }
   // Octant VIII
   else if ((a.x < b.x) && ((0 >= m) && (m >= -1)))
   {
      y = a.y;
      H = H * -1;
      F = 2 * H - W;
      for (unsigned int Ix = a.x; Ix <= (b.x - 1); ++Ix)
      {
         t = (float)Ix / (W);
         tempR = (int)(a.color.r * (1 - t) + b.color.r * (t));
         tempG = (int)(a.color.g * (1 - t) + b.color.g * (t));
         tempB = (int)(a.color.b * (1 - t) + b.color.b * (t));
         c = {(unsigned char)tempR, (unsigned char)tempG, (unsigned char)tempB};
         _canvas.set(y, Ix, c);
         if (F > 0)
         {
            y--;
            F += 2 * (H - W);
         }
         else 
         {
            F += 2 * H;
         }
      }
   }
   else
   {
      std::cout << "ERROR. Invalid coordinates received " << (int)a.x << "," << (int)a.y << " and " << (int)b.x << "," << (int)b.y << " with slope of " << m << std::endl;
   }
   
}

void Canvas::triangle(Vertex a, Vertex b, Vertex c)
{
   int maxx = 99;
   if (a.x >= b.x && a.x >= c.x)
   {
      maxx = a.x;
   }
   else if (b.x >= c.x)
   {
      maxx = b.x;
   }
   else 
   {
      maxx = c.x;
   }

   int minx = 99;
   if (a.x <= b.x && a.x <= c.x)
   {
      minx = a.x;
   }
   else if (b.x <= c.x)
   {
      minx = b.x;
   }
   else
   {
      minx = c.x;
   }

   int maxy = 99;
   if (a.y >= b.y && a.y >= c.y)
   {
      maxy = a.y;
   }
   else if (b.y >= c.y)
   {
      maxy = b.y;
   }
   else
   {
      maxy = c.y;
   }

   int miny = 99;
   if (a.y <= b.y && a.y <= c.y)
   {
      miny = a.y;
   }
   else if (b.y <= c.y)
   {
      miny = b.y;
   }
   else
   {
      miny = c.y;
   }

   float gam;
   float bet;
   float alp;
   float t;
   Pixel triC;
   for (int x = minx; x < maxx; x++) 
   {
      for (int y = miny; y < maxy; y++) 
      {
         gam = (float)( (b.y - a.y) * (x - a.x) - (b.x - a.x) * (y - a.y) ) / 
         ( (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y) );

         bet = (float)( (c.y - a.y) * (x - a.x) - (c.x - a.x) * (y - a.y) ) / 
         ( (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y) );
         alp = 1.0f - bet - gam;

         if (_grad == false)
         {
            triC.r = (unsigned char)(alp * (int)a.color.r + bet * (int)b.color.r + gam * (int)c.color.r);
            triC.g = (unsigned char)(alp * (int)a.color.g + bet * (int)b.color.g + gam * (int)c.color.g);
            triC.b = (unsigned char)(alp * (int)a.color.b + bet * (int)b.color.b + gam * (int)c.color.b);
         }
         else
         {
            t = (float)y / (_canvas.height());
            triC.r = (unsigned char)(int)
            (((_gradColort.r * (1 - t) + _gradColorb.r * (t)) / pow(3.0f, t) + 
            (alp * (int)a.color.r + bet * (int)b.color.r + gam * (int)c.color.r) / pow(3.0f, t)) / 2.0f);

            triC.g = (unsigned char)(int)
            (((_gradColort.g * (1 - t) + _gradColorb.g * (t)) / pow(3.0f, t) + 
            (alp * (int)a.color.g + bet * (int)b.color.g + gam * (int)c.color.g) / pow(3.0f, t)) / 2.0f);

            triC.b = (unsigned char)(int)
            (((_gradColort.b * (1 - t) + _gradColorb.b * (t)) / pow(3.0f, t) + 
            (alp * (int)a.color.b + bet * (int)b.color.b + gam * (int)c.color.b) / pow(3.0f, t)) / 2.0f);
         }

         if ((gam <= 1.0f && gam >= -0.003125) && (bet <= 1.0f && bet >= -0.003125) && (alp <= 1.0f && alp >= -0.003125))
         {
            _canvas.set(y, x, triC);
         }
      }
   }
   
}

void Canvas::isoCube(float height, Vertex pos)
{
   // Top quad
   Vertex c1 = pos;
   Vertex tl1 = {pos.color, (unsigned char)((int)pos.x - height), 
               (unsigned char)((int)pos.y - (height / 2.0f))};
   Vertex tr1 = {pos.color, (unsigned char)((int)pos.x + height), 
               (unsigned char)((int)pos.y - (height / 2.0f))};
   Vertex t = {pos.color, pos.x, (unsigned char)((int)pos.y - height)};

   // Bottom Right quad
   float scale = 222.0f / 254.0f;
   Vertex b1 = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
                pos.x, (unsigned char)((float)pos.y + height)};
   Vertex br = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
               (unsigned char)((int)pos.x + height),
               (unsigned char)((int)pos.y + (height / 2.0f))};
   Vertex c2 = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
               pos.x, pos.y};
   Vertex tr2 = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
               (unsigned char)((int)pos.x + height), 
               (unsigned char)((int)pos.y - (height / 2.0f))};

   // Bottom Left quad
   scale = 183.0f / 254.0f;
   Vertex b2 = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
                pos.x, (unsigned char)((float)pos.y + height)};
   Vertex bl = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
               (unsigned char)((int)pos.x - height),
               (unsigned char)((int)pos.y + (height / 2.0f))};
   Vertex c3 = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)},
               pos.x, pos.y};
   Vertex tl2 = {{(unsigned char)((int)pos.color.r * scale), 
               (unsigned char)((int)pos.color.g * scale), 
               (unsigned char)((int)pos.color.b * scale)}, 
               (unsigned char)((int)pos.x - height), 
               (unsigned char)((int)pos.y - (height / 2.0f))};

   // Top quad construction
   triangle(c1, tl1, t);
   triangle(c1, t, tr1);

   // Bottom right quad construction
   triangle(c2, tr2, br);
   triangle(c2, br, b1);

   // Bottom left quad construction
   triangle(tl2, c3, bl);
   triangle(bl, c3, b2);
}

void Canvas::isoTet(float height, Vertex pos)
{

   // Finding tricky position of top point
   int txpos = (pos.x - (height / 2.0f)) + (1.0f / 3.0f) * height;
   int typos = pos.y - height * (4.0f / 3.0f);

   // Left triangle
   float scale = 183.0f / 254.0f;
   Vertex b1 = {{(unsigned char)((int)pos.color.r * scale), 
         (unsigned char)((int)pos.color.g * scale), 
         (unsigned char)((int)pos.color.b * scale)},
         (unsigned char)((int)pos.x + (1.0f / 3.0f) * height), 
         pos.y};
   Vertex l = {{(unsigned char)((int)pos.color.r * scale), 
         (unsigned char)((int)pos.color.g * scale), 
         (unsigned char)((int)pos.color.b * scale)},
         (unsigned char)((int)pos.x - height + (1.0f / 3.0f) * height), 
         (unsigned char)((int)pos.y - (height / 2.0f))};
   Vertex t1 = {{(unsigned char)((int)pos.color.r * scale), 
         (unsigned char)((int)pos.color.g * scale), 
         (unsigned char)((int)pos.color.b * scale)},
         (unsigned char)(txpos + (1.0f / 3.0f) * height), 
         (unsigned char)typos};
   // Right triangle
   scale = 222.0f / 254.0f;
   Vertex b2 = {{(unsigned char)((int)pos.color.r * scale), 
         (unsigned char)((int)pos.color.g * scale), 
         (unsigned char)((int)pos.color.b * scale)},
         (unsigned char)((int)pos.x + (1.0f / 3.0f) * height), 
         pos.y};
   Vertex t2 = {{(unsigned char)((int)pos.color.r * scale), 
         (unsigned char)((int)pos.color.g * scale), 
         (unsigned char)((int)pos.color.b * scale)},
         (unsigned char)(txpos + (1.0f / 3.0f) * height),
         (unsigned char)typos};
   Vertex r = {{(unsigned char)((int)pos.color.r * scale), 
         (unsigned char)((int)pos.color.g * scale), 
         (unsigned char)((int)pos.color.b * scale)},
         (unsigned char)((int)pos.x + (height / 2.0f) + (1.0f / 3.0f) * height), 
         (unsigned char)((int)pos.y - (height * 0.75f))};

   // Drawing right Triangle
   triangle(b2, t2, r);

   // Drawing left Triangle
   triangle(b1, l, t1);
}

// Circle 
void Canvas::circle(Vertex center, float radius)
{
   int maxy = (int)((int)center.y + (radius));
   int maxx = (int)((int)center.x + (radius));
   int miny = (int)((int)center.x - (radius));
   int minx = (int)((int)center.x - (radius));
   float d = 0;
   
   for (int x = minx; x < maxx; x++) 
   {
      for (int y = miny; y < maxy; y++) 
      {
         d = abs(sqrt(pow((x - center.x), 2) + pow((y - center.y), 2)));
         if (d <= abs(radius))
         {
            _canvas.set(y, x, center.color);
         }
      }
   }
}