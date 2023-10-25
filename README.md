# graphics-openGL
One interesting computer graphics project written in C++ using OpenGL library.

System configuration
1. OS: Ubuntu 18.04.4 LTS (Bionic Beaver)
2. CPU: Intel Core i3-8145U 2.10 GHz
3. RAM: 2 GB
4. GPU: Intel UHD Graphics 620
5. Programming language: C/C++

Graphical effects
1. First-order particles' system
2. Object animation
3. Environmental maps
4. Fog
5. Program-defined non-trvially shaped object (torus)
6. User can move his/hers viewpoint
7. Music theme

Controls
1. WASD - moving the viewpoint
2. LMB + cursor - adjusting the angle view
3. F/G - increase/decrease fog density

Libraries used: iostream, cmath, GL/glut.h, stb_image.h, irrKlang/irrKlang.h

Compilation instructions
1. 'stb' folder: stb_image.h header file must be placed in the standard library directory (/user/include)
2. 'irrKlang_general' folder:
   a) libIrrKlang.so must be placed in the comiler directory (e.g. /user/lib/x86_64-linux-gnu)
   b) the entire 'irrKlang' folder (first lowercase! it's the one inside the ambient 'IrrKlang') must be placed in the standard library directory (/user/include)
   c) .ogg and .jpg files must be in the same directory with the source code

Terminal command: g++ sphere3.0.2.cpp -lglut -lGLU -lGL -lIrrKlang
