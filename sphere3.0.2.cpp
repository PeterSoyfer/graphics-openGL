#include<iostream>
#include<cmath>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<irrKlang/irrKlang.h>

static void load_texture()
{
	GLuint texture_sphere;
	int w,h,nch;
	unsigned char *data = stbi_load("grob-tex-1024-inv-sph.jpg", &w, &h, &nch, 0);

	if(!data)
	{
		std::cout << "\nFailed to load texture.\n" << std::endl;
		exit(1);
	}

	glGenTextures(1,&texture_sphere);
	glBindTexture(GL_TEXTURE_2D, texture_sphere);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid*)data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

static GLUquadric *sphere;

const GLfloat sphere_radius=20;

static void init_sphere()
{
	sphere = gluNewQuadric();
	load_texture();
}

static void draw_sphere()
{
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluSphere(sphere, sphere_radius, 48, 48);
}

#define MAX_PARTICLES 50

const float flux_size = 2.5;
const float particle_size = 0.25;
const float lifetime = 8;

const float xpos = 0;
const float ypos = 10;
const float zpos = 0;

const float vx = 0;
const float vy = -40;
const float vz = 0;

const float grav_x = 0;
const float grav_y = 0;
const float grav_z = 0;

static GLuint loop;

typedef struct
{
	float life;
	float fade;
	
	float x,y,z;
	float xi,yi,zi;
	float xg,yg,zg;
}
particles;

static particles particle[MAX_PARTICLES];

static void init_particles()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	
	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		particle[loop].life = (float)rand()/RAND_MAX;
		particle[loop].fade = 0.005;
		
		float angle = ((float)rand()/RAND_MAX)*2*M_PI;
		float radius = flux_size*(float)rand()/RAND_MAX;

		particle[loop].xi = vx;
		particle[loop].yi = vy;
		particle[loop].zi = vz;
		
		particle[loop].xg = grav_x;
		particle[loop].yg = grav_y;
		particle[loop].zg = grav_z;

		particle[loop].x = xpos+radius*cos(angle);
		particle[loop].y = ypos;
		particle[loop].z = zpos+radius*sin(angle);
	}
}

static void draw_particles()
{
	float slowdown=4e-4;

	glPushMatrix();
	
	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		float x = particle[loop].x;
		float y = particle[loop].y;
		float z = particle[loop].z;
			
		glBegin(GL_TRIANGLE_STRIP);
		
		glTexCoord2d(1,1); glVertex3f(x+particle_size,y+particle_size,z);
		glTexCoord2d(0,1); glVertex3f(x-particle_size,y+particle_size,z);
		glTexCoord2d(1,0); glVertex3f(x+particle_size,y-particle_size,z);
		glTexCoord2d(0,0); glVertex3f(x-particle_size,y-particle_size,z);
			
		glEnd();
		
		particle[loop].x += particle[loop].xi*slowdown;
		particle[loop].y += particle[loop].yi*slowdown;
		particle[loop].z += particle[loop].zi*slowdown;
		
		particle[loop].xi += particle[loop].xg;
		particle[loop].yi += particle[loop].yg;
		particle[loop].zi += particle[loop].zg;
		
		particle[loop].life -= particle[loop].fade*(1/lifetime);
		
		if (particle[loop].life < 0)
		{
			float angle = ((float)rand()/RAND_MAX)*2*M_PI;
			float radius = flux_size*(float)rand()/RAND_MAX;
			
			particle[loop].life = (float)rand()/RAND_MAX;
			particle[loop].fade = 0.005;

			particle[loop].x = xpos+radius*cos(angle);
			particle[loop].y = ypos;
			particle[loop].z = zpos+radius*sin(angle);

			particle[loop].xi = vx;
			particle[loop].yi = vy;
			particle[loop].zi = vz;
		}
	}
	glPopMatrix();
}

#define TORUS_MAJOR 1.5
#define TORUS_MINOR 0.8
#define TORUS_MAJOR_RES 32
#define TORUS_MINOR_RES 32
#define FOUNTAIN_HEIGHT 3.f

static GLfloat oscill=0, move=0.1, amplitude=3;

static void draw_torus(void)
{
	static GLuint torus_list = 0;
	int i, j, k;
	double s, t, x, y, z, nx, ny, nz, scale, twopi;

	glTranslatef(0,amplitude*sin(oscill),0);

	if (!torus_list)
	{
		torus_list = glGenLists(1);
		glNewList(torus_list, GL_COMPILE_AND_EXECUTE);
		twopi = 2.0 * M_PI;
		for (i = 0;  i < TORUS_MINOR_RES;  i++)
		{
			glBegin(GL_QUAD_STRIP);
			for (j = 0;  j <= TORUS_MAJOR_RES;  j++)
			{
				for (k = 1;  k >= 0;  k--)
				{
					s = (i + k) % TORUS_MINOR_RES + 0.5;
					t = j % TORUS_MAJOR_RES;
					x = (TORUS_MAJOR + TORUS_MINOR * cos(s * twopi / TORUS_MINOR_RES)) * cos(t * twopi / TORUS_MAJOR_RES);
					z = FOUNTAIN_HEIGHT + TORUS_MINOR * sin(s * twopi / TORUS_MINOR_RES);
					y = (TORUS_MAJOR + TORUS_MINOR * cos(s * twopi / TORUS_MINOR_RES)) * sin(t * twopi / TORUS_MAJOR_RES);
					nx = x - TORUS_MAJOR * cos(t * twopi / TORUS_MAJOR_RES);
					ny = y;
					nz = z - TORUS_MAJOR * sin(t * twopi / TORUS_MAJOR_RES);
					scale = 1.0 / sqrt(nx*nx + ny*ny + nz*nz);
					nx *= scale;
					ny *= scale;
					nz *= scale;
					glNormal3f((float) nx, (float) ny, (float) nz);
					glVertex3f((float) x, (float) y, (float) z);
				}
			}      
			glEnd();
		}
		glEndList();
	}
	else
	{
		glCallList(torus_list);
	}
}

const GLfloat fogColor[4]= {0.5, 0, 0.5, 1}; //purple haze

static GLfloat fog_density=0.06;

static void render_fog()
{
	glFogi(GL_FOG_MODE,GL_EXP2); //LINEAR,EXP,EXP2
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, fog_density);
	glFogf(GL_FOG_START, 0);
	glFogf(GL_FOG_END, 5);
	glHint(GL_FOG_HINT, GL_NICEST);
}

static GLfloat camx = 0, camy = 11, camz = 15.5;
static GLfloat viewx = 0, viewy = -0.6, viewz = -0.8;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(camx, camy, camz, camx+viewx, camy+viewy, camz+viewz, 0, 1, 0);
	
	glEnable(GL_DEPTH_TEST);

	draw_sphere();

	draw_particles();
	
	draw_torus();

	glutPostRedisplay();

	render_fog();
	
	glDisable(GL_DEPTH_TEST);
	
	glFlush();
	glutSwapBuffers();
}

const GLfloat fraction = 0.15;

void movecam(GLfloat fwd, GLfloat strafe)
{
	GLfloat spd = 1/sqrt(viewx * viewx + viewy * viewy + viewz * viewz);

	camx += (viewx * fwd - viewz * strafe) * spd;
	camy += (viewy * fwd) * spd;
	camz += (viewz * fwd + viewx * strafe) * spd;
}

int mousex = -0x10000, mousey;

void mouse(int button, int state, int x, int y)
{
  mousex = -0x10000;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mousex = x;
    mousey = y;
  }
}

void rotate2d(GLfloat ang, GLfloat& x, GLfloat& y)
{
  double cos_a = cos(ang), sin_a = sin(ang);
  double xr = x * cos_a - y * sin_a;
  double yr = x * sin_a + y * cos_a;
  x = xr;
  y = yr;
}

void motion(int x, int y)
{
  if (mousex != -0x10000)
  {
    GLfloat mdx = (x - mousex) * -0.01;
    GLfloat mdy = (y - mousey) * -0.01;
    GLfloat xang = atan2(viewx, viewz);
    rotate2d(xang, viewx, viewz);
    rotate2d(mdy, viewz, viewy);
    rotate2d(-xang - mdx, viewx, viewz);
  }
  mousex = x;
  mousey = y;
}

void keyboard(unsigned char key, int xx, int yy)
{
	switch(key)
	{
		case 27: glutDestroyWindow(glutGetWindow()); exit(0); break;
    case 'w':
    	if(camx*camx+camy*camy+camz*camz<0.95*sphere_radius*sphere_radius)
    		movecam(fraction,0);
    	else camx=camy=camz=0;
    	break;
    case 's':
    	if(camx*camx+camy*camy+camz*camz<0.95*sphere_radius*sphere_radius)
    		movecam(-fraction,0);
    	else camx=camy=camz=0;
    	break;
    case 'a':
    	if(camx*camx+camy*camy+camz*camz<0.95*sphere_radius*sphere_radius)
    		movecam(0,-fraction);
    	else camx=camy=camz=0;
    	break;
    case 'd':
    	if(camx*camx+camy*camy+camz*camz<0.95*sphere_radius*sphere_radius)
    		movecam(0,fraction);
    	else camx=camy=camz=0;
    	break;
    case 'f': if(fog_density<=0.06) fog_density+=0.04; break;
		case 'g': if(fog_density>=0.04) fog_density-=0.04; break;
	}
}

static void idle()
{
	if(oscill < 360) oscill+=move;
	else oscill=0;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	if (h == 0) h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45, (float)w/h, 1, 1000);
}

void init()
{
	glClearColor(0.6,0,0.6,0); //deep purple
	glClearDepth(1.0f);
	
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	
	if(!engine) exit(-1);
	
	engine->play2D("tuman.ogg",true);

	init_sphere();
	
	init_particles();

	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_FOG);
}

#define WIN_W 800
#define WIN_H 600

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIN_W, WIN_H);
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("");

	init();

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	
	glutIdleFunc(idle);
	
	glutMainLoop();
	exit(EXIT_SUCCESS);
}


