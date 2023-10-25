# graphics-openGL
One interesting computer graphics project written in C++ using OpenGL library.

System configuration
  OS: Ubuntu 18.04.4 LTS (Bionic Beaver)
  CPU: Intel Core i3-8145U 2.10 GHz
	RAM: 2 GB
	GPU: Intel UHD Graphics 620
	IDE: -
	Programming language: C/C++

Graphical effects
  First-order particles' system
  Object animation
  Environmental maps
  Fog
  Program-defined non-trvially shaped object (torus)
  User can move his/hers viewpoint
  Music theme

Controls
  WASD - moving the viewpoint
  LMB + cursor - adjusting the angle view
  F/G - increase/decrease fog density

Libraries used
  <iostream>
	<cmath>
	<GL/glut.h>
	<stb_image.h>
	<irrKlang/irrKlang.h>

Compilation instructions
  stb folder:
    stb_image.h header file must be placed in the standard library directory (/user/include)
  IrrKlang folder:
    libIrrKlang.so must be placed in the comiler directory (e.g. /user/lib/x86_64-linux-gnu)
    the entire 'irrKlang' folder (first lowercase! it's the one inside the ambient 'IrrKlang') must be placed in the standard
    library directory (/user/include)
  .ogg and .jpg files must be in the same directory with the source code

Terminal command:
  g++ sphere3.0.2.cpp -lglut -lGLU -lGL -lIrrKlang
