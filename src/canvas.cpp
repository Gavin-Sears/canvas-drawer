#include "canvas.h"
#include <cassert>

using namespace std;
using namespace agl;

// Constructor
Canvas::Canvas(int w, int h) : _canvas(w, h)
{
   _canvas = Image(w, h);
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

// 
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

   _shape = 0;
   _vertices.clear();
}

// 
void Canvas::vertex(int x, int y)
{
   if(x > _canvas.width()) 
   {
         x = _canvas.width();
      }
   if (y > _canvas.height()) 
   {
         y = _canvas.height();
   }
   if (_shape == 1 || _shape == 2 || _shape == 3) 
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
void Canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
   for (int row = 0; row < (_canvas.height()); ++row) {
      for (int c = 0; c < (_canvas.width()); ++c) {
         _canvas.set(row, c, {(unsigned char)r, (unsigned char)g, (unsigned char)b});
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
   else {
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

         triC.r = (unsigned char)(alp * (int)a.color.r + bet * (int)b.color.r + gam * (int)c.color.r);
         triC.g = (unsigned char)(alp * (int)a.color.g + bet * (int)b.color.g + gam * (int)c.color.g);
         triC.b = (unsigned char)(alp * (int)a.color.b + bet * (int)b.color.b + gam * (int)c.color.b);

         if ((gam <= 1.1f && gam >= -0.001f) && (bet <= 1.01f && bet >= -0.001f) && (alp <= 1.1f && alp >= -0.001f))
         {
            _canvas.set(y, x, triC);
         }
      }
   }
   
}

