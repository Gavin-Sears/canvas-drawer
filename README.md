# canvas-drawer

Implements a simple drawing api

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake -G "Visual Studio 16 2019" ..
canvas-drawer/build $ start Draw-2D.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
canvas-drawer/build $ ../bin/Debug/draw_test
canvas-drawer/build $ ../bin/Debug/draw_art
```

*macOS*

Open terminal to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake ..
canvas-drawer/build $ make
```

To run each program from build, you would type

```
canvas-drawer/build $ ../bin/draw_test
canvas-drawer/build $ ../bin/draw_art
```

## Supported primitives

Isometric Cube

<img src="Examples/Cube.png" width="200" height="200">

Isometric Tetrahedron

<img src="Examples/Tet.png" width="200" height="200">

Circle

<img src="Examples/CircleEx.png" width="200" height="200">

## Results

Various circles with a gradient

<img src="Examples/Circle.png" width="400" height="400">

These three variations of the image "dungeon," demonstrate how the different gradient specification work.

Background gradient from white to black, and matching block gradient

<img src="Examples/Dungeon.png" width-"400" height="400">

Background gradient from black to white, and block gradient from white to green

<img src="Examples/DungeonThree.png" width-"400" height="400">

Background gradient from magenta to (0, 100, 100), and block gradient affected by background, with a gradient from white to black applied as well.

<img src="Examples/DungeonTwo.png" width-"400" height="400">

"Tarski's World"

uses isometric tetradhedron, cubes, and a background gradient![Tarski's World](/Users/stephensears/cs313/canvas-drawer/Examples/Tarski's_World.png)

<img src="Examples/Tarski's_World.png" width="400" height="400">

<img src="Examples/Tarski's_World.png" width-"400" height="400">
