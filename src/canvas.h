/*-----------------------------------------------
 * Author: Gavin Sears
 * Date: Fri, Feb 24
 * Description: Image drawing tool. Supports the use of lines, triangles,
 * isometric cubes, isometric tetrahedrons, and circles, and also allows
 * for various specifications regarding gradients
 ----------------------------------------------*/

#ifndef canvas_H_
#define canvas_H_

#include <string>
#include <vector>
#include "image.h"

namespace agl
{
   enum PrimitiveType {UNDEFINED, LINES, TRIANGLES, ISOCUBES, ISOTETS, CIRCLES};

   /**
   * @brief Holder for a triangle
   * 
   */
   struct Triangle {
      unsigned char v1;
      unsigned char v2;
      unsigned char v3;
   };

   /**
   * @brief Holder for a vertex
   * 
   */
   struct Vertex {
      Pixel color;

      unsigned char x;
      unsigned char y;
   };

   class Canvas
   {
   public:
      Canvas(int w, int h);

      // Specify gradient colors or if you want a gradient
      void gradC(bool g, Pixel top, Pixel bottom);

      virtual ~Canvas();

      // Save to file
      void save(const std::string& filename);

      // Draw primitives with a given type (either LINES or TRIANGLES)
      // For example, the following draws a red line followed by a green line
      // begin(LINES);
      //    color(255,0,0);
      //    vertex(0,0);
      //    vertex(100,0);
      //    color(0,255,0);
      //    vertex(0, 0);
      //    vertex(0,100);
      // end();
      void begin(PrimitiveType type);
      void end();

      // Specifiy a vertex at raster position (x,y)
      // x corresponds to the column; y to the row
      void vertex(int x, int y);

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b, unsigned char r2, unsigned char g2, unsigned char b2);

      // Bresenham formula, assume your octant is to the right of the y axis
      void bresenham(Vertex a, Vertex b);

      // Triangle formula
      void triangle(Vertex a, Vertex b, Vertex c);

      // Isometric Cube
      void isoCube(float height, Vertex pos);

      // Isometric Tetrahedron
      void isoTet(float height, Vertex pos);

      // Circle
      void circle(Vertex center, float radius);

   private:
      std::vector<Vertex> _vertices;
      std::vector<Triangle> _triangles;
      Image _canvas;
      Pixel _curColor;
      int _shape;
      Pixel _gradColort;
      Pixel _gradColorb;
      bool _grad;
   };
}

#endif


