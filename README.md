# graphics-openGL
One interesting computer graphics project written in C++ using OpenGL library.

Compilation instructions
1. Download and extract the file 'Soyfer-OpenGL-Task-3.0.3.7z'
2. libIrrKlang.so must be placed in the compiler directory (e.g. /user/lib/x86_64-linux-gnu).
   I recommend simply copying and pasting this library under Root permissions.
3. Execute the following command in Terminal: "g++ sphere3.0.3.cpp -lglut -lGLU -lGL -lIrrKlang"
4. Then open 'a.out' file and enjoy!

System configuration
1. OS: Ubuntu 18.04.4 LTS (Bionic Beaver); also successfully tested on Debian GNU/Linux 12 (BookWorm)
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
