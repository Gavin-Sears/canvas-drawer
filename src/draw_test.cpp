#include <iostream>
#include "canvas.h"

using namespace agl;
using namespace std;

void test_line(Canvas& drawer, int ax, int ay, int bx, int by, const std::string& savename)
{
   drawer.background(0, 0, 0, 0, 0, 0);
   drawer.begin(LINES);
   drawer.vertex(ax, ay);
   drawer.vertex(bx, by);
   drawer.end();
   drawer.save(savename);
}

int main(int argc, char** argv)
{
   Canvas drawer(100, 100);

   drawer.color(255, 255, 255);
   test_line(drawer, 0, 50, 100, 50, "horizontal-line.png");
   test_line(drawer, 50, 0, 50, 100, "vertical-line.png");
   test_line(drawer, 0, 0, 100, 100, "diagonal-line-1.png"); // slope = 1
   test_line(drawer, 25, 10, 75, 25,  "h-lessthan-w-line-1.png"); // slope H < W
   test_line(drawer, 25, 25, 75, 75,  "w-lessthan-h-line-1.png"); // slope W < H
   test_line(drawer, 0, 100, 100, 0, "diagonal-line-2.png"); // slope H < W
   test_line(drawer, 25, 90, 75, 75,  "h-lessthan-w-line-2.png"); // slope H < W
   test_line(drawer, 25, 90, 75, 25,  "w-lessthan-h-line-2.png"); // slope W < H

   // test line interpolation
   drawer.background(0, 0, 0, 0, 0, 0);
   drawer.begin(LINES);
   drawer.color(255, 0, 255);
   drawer.vertex(0, 0);
   drawer.color(0, 255, 255);
   drawer.vertex(100, 100);
   drawer.end();
   drawer.save("line-color-interpolation.png");

   // test triangle with interpolation
   drawer.background(0, 0, 0, 0, 0, 0);
   drawer.begin(TRIANGLES);
   drawer.color(255, 0, 255);
   drawer.vertex(10, 0);
   drawer.color(0, 255, 255);
   drawer.vertex(90, 50);
   drawer.color(255, 255, 0);
   drawer.vertex(10, 90);
   drawer.end();
   drawer.save("triangle.png");

   // test triangle with interpolation
   drawer.background(0, 0, 0, 0, 0, 0);
   drawer.begin(TRIANGLES);
   drawer.color(255, 0, 255);
   drawer.vertex(10, 10);
   drawer.vertex(10, 90);
   drawer.vertex(90, 90);

   drawer.color(255, 255, 0);
   drawer.vertex(90, 90);
   drawer.vertex(90, 10);
   drawer.vertex(10, 10);
   drawer.end();
   drawer.save("quad.png");

   // test isometric cubes
   Canvas drawerTwo(200, 200);
   drawerTwo.background(255, 255, 255, 129, 152, 188);
   drawerTwo.begin(ISOCUBES);

   // Making a chessboard
   int posx = 100;
   int posy = 70;
   int count = 0;
   Pixel curColor = {0, 0, 0};
   for (int i = 0; i < 8; i++)
   {
      for (int n = 0; n < 8; n++)
      {
         if (count % 2 == 1)
         {
            curColor = {255, 255, 255};
         }
         else 
         {
            curColor = {0, 0, 0};
         }

         drawerTwo.color(curColor.r, curColor.g, curColor.b);
         drawerTwo.vertex(posx + (n * 10), posy + (n * 5));
         count++;
      }
      count++;
      posx = posx - 10;
      posy = posy + 5;
   }

   drawerTwo.color(89, 180, 183);
   drawerTwo.vertex(60, 110);
   drawerTwo.vertex(120, 70);
   drawerTwo.end();

   drawerTwo.begin(ISOTETS);
   drawerTwo.color(238, 97, 250);
   drawerTwo.vertex(130, 115);
   drawerTwo.end();

   drawerTwo.save("Tarski's_World.png");

   Canvas drawerCube(40, 40);
   drawerCube.background(255, 255, 255, 255, 255, 255);
   drawerCube.begin(ISOCUBES);
   drawerCube.color(255, 0, 0);
   drawerCube.vertex(20, 20);
   drawerCube.end();
   drawerCube.save("Cube.png");

   Canvas drawerTet(40, 40);
   drawerTet.background(255, 255, 255, 255, 255, 255);
   drawerTet.begin(ISOTETS);
   drawerTet.color(0, 0, 255);
   drawerTet.vertex(18, 28);
   drawerTet.end();
   drawerTet.save("Tet.png");

   Canvas drawerDung(200, 200);
   drawerDung.background(255, 255, 255, 0, 0, 0);
   drawerDung.gradC(true, {255, 255, 255}, {0, 0, 0});
   drawerDung.begin(ISOCUBES);
   drawerDung.color(0, 0, 255);
   for (int i = 0; i < 10; i++)
   {
      drawerDung.vertex(110 - (i * 10), 3 + (i * 15));
   }
   drawerDung.color(255, 0, 0);
   for (int i = 0; i < 14; i++)
   {
      drawerDung.vertex(30 + (i * 10), 3 + (i * 15));
   }
   drawerDung.color(0, 255, 0);
   for (int i = 0; i < 6; i++)
   {
      drawerDung.vertex(190 - (i * 10), 123 + (i * 15));
   }
   drawerDung.end();
   drawerDung.save("Dungeon.png");

   drawerDung.background(255, 0, 255, 0, 100, 100);
   drawerDung.gradC(true, {255, 0, 255}, {0, 100, 100});
   drawerDung.begin(ISOCUBES);
   drawerDung.color(0, 0, 255);
   for (int i = 0; i < 10; i++)
   {
      drawerDung.vertex(110 - (i * 10), 3 + (i * 15));
   }
   drawerDung.color(255, 0, 0);
   for (int i = 0; i < 14; i++)
   {
      drawerDung.vertex(30 + (i * 10), 3 + (i * 15));
   }
   drawerDung.color(0, 255, 0);
   for (int i = 0; i < 6; i++)
   {
      drawerDung.vertex(190 - (i * 10), 123 + (i * 15));
   }
   drawerDung.end();
   drawerDung.save("DungeonTwo.png");

   drawerDung.background(0, 0, 0, 255, 255, 255);
   drawerDung.gradC(true, {0, 0, 0}, {0, 255, 0});
   drawerDung.begin(ISOCUBES);
   drawerDung.color(0, 0, 255);
   for (int i = 0; i < 10; i++)
   {
      drawerDung.vertex(110 - (i * 10), 3 + (i * 15));
   }
   drawerDung.color(255, 0, 0);
   for (int i = 0; i < 14; i++)
   {
      drawerDung.vertex(30 + (i * 10), 3 + (i * 15));
   }
   drawerDung.color(0, 255, 0);
   for (int i = 0; i < 6; i++)
   {
      drawerDung.vertex(190 - (i * 10), 123 + (i * 15));
   }
   drawerDung.end();
   drawerDung.save("DungeonThree.png");

   Canvas drawerCirc(100, 100);
   drawerCirc.background(255, 255, 0, 0, 0, 255);
   drawerCirc.begin(CIRCLES);
   drawerCirc.color(255, 0, 255);
   drawerCirc.vertex(25, 25);
   drawerCirc.color(0, 255, 255);
   drawerCirc.vertex(25, 75);
   drawerCirc.color(255, 255, 0);
   drawerCirc.vertex(75, 75);
   drawerCirc.end();
   drawerCirc.save("Circle.png");

   drawerCirc.background(255, 255, 255, 255, 255, 255);
   drawerCirc.begin(CIRCLES);
   drawerCirc.color(0, 255, 0);
   drawerCirc.vertex(50, 50);
   drawerCirc.end();
   drawerCirc.save("Circle.png");

   return 0;
}
