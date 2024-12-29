#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector"
#include <functional>

GLfloat lightX = 0.0;
GLfloat lightY = 500.0;
GLfloat lightZ = 500.0;
GLfloat intensity = 0.6;
GLfloat intensity_alpha = 0.1;
GLfloat diffuseMaterial[4] = { intensity, intensity,intensity, intensity_alpha };

int time_interval = 60;

GLfloat Rangle = 0;
GLfloat eyeX = 0; //Camera position
GLfloat eyeY = 0;
GLfloat eyeZ = 500;
//reference point
GLfloat centerX = 0.0;
GLfloat centerY = 0.0;
GLfloat centerZ = 0.0;
GLfloat upX = 0.0;
GLfloat upY = 1.0;
GLfloat upZ = 0.0;

float delTrainZ = 0;
float delTrainZ2 = 0;
float delWindmill = 0;
float delCar1 = 0;
float delCar2 = 0;
float px = 0;
float planeX = 0;
float deltaY = 50;
float trainZ = -1100;
int scene = 1;
int view = 1;
int m = 1;

using namespace std;
GLint imagewidth0, imagewidth1, imagewidth2, imagewidth3, imagewidth4, imagewidth5, imagewidth6, imagewidth7, imagewidth8, imagewidth9;
GLint imageheight0, imageheight1, imageheight2, imageheight3, imageheight4, imageheight5, imageheight6, imageheight7, imageheight8, imageheight9;
GLint pixellength0, pixellength1, pixellength2, pixellength3, pixellength4, pixellength5, pixellength6, pixellength7, pixellength8, pixellength9;
vector<GLubyte*>p; // Similar to GLubyte* for program 3 but for 2 images (so a vector)
GLuint textures[11];

#define checkStationWidth 64
#define checkStationHeight 64
GLubyte stationImage[checkStationWidth][checkStationHeight][3];

/* Both A and B are function pointers.
These function pointers are defined for pointing to the various shape functions, i.e. sphere(), cube()
and cone(). */
using FunctionPtr = std::function<void(void)>;
FunctionPtr A;
FunctionPtr B;
FunctionPtr C;

void when_in_mainloop()
{
	if (view == 1) {
		if (scene == 1) {
			if (delTrainZ <= 400 + eyeZ)
			{
				delTrainZ = delTrainZ + 1;
			}
			else {
				delTrainZ = 0;
			}
		}
		else if (scene == 2) {
			if (delTrainZ <= 400 + eyeZ)
			{
				delTrainZ = delTrainZ + 0.4;
			}
			else {
				delTrainZ = 0;
			}
		}
	}
	else if (view == 2) {
		if (scene == 1) {
			if (m == 1) {
				if (delTrainZ < 1000)
				{
					trainZ = -1100;
					delTrainZ = delTrainZ + 1;
				}
				else {
					m = 2;
					delTrainZ = 0;
				}
			}
			else if (m == 2) {
				if (delTrainZ2 < 1200)
				{
					trainZ = -100;
					delTrainZ2 = delTrainZ2 + 1;
				}
				else if (delTrainZ2 >= 1200) {
					m = 1;
					delTrainZ2 = 0;
				}
			}
		}
		else if (scene == 2) {
			if (m == 1) {
				if (delTrainZ < 1000)
				{
					trainZ = -1100;
					delTrainZ = delTrainZ + 0.4;
				}
				else {
					m = 2;
					delTrainZ = 0;
				}
			}
			else if (m == 2) {
				if (delTrainZ2 < 1200)
				{
					trainZ = -100;
					delTrainZ2 = delTrainZ2 + 0.4;
				}
				else if (delTrainZ2 >= 1200) {
					m = 1;
					delTrainZ2 = 0;
				}
			}
		}
	}



	if (delWindmill < 360) {
		delWindmill += 0.1;
	}
	else {
		delWindmill = 0;
	}

	if (delCar1 < 300) {
		delCar1 += 0.2;
	}
	else {
		delCar1 = -500;
	}

	if (delCar2 > -700) {
		delCar2 -= 0.25;
	}
	else {
		delCar2 = 300;
	}

	if (px < 2000) {
		px += 1;
	}
	else {
		px = -2000;
	}

	if (planeX < 360) {
		planeX += 1;
	}
	else {
		planeX = 0;
	}
	glutPostRedisplay();
}

void OnTimer(int value)
{
	if (view == 1) {
		if (scene == 1) {
			if (delTrainZ <= 500 + eyeZ)
			{
				delTrainZ = delTrainZ + 1;
			}
			else {
				delTrainZ = 0;
			}
		}
		else if (scene == 2) {
			if (delTrainZ <= 500 + eyeZ)
			{
				delTrainZ = delTrainZ + 0.4;
			}
			else {
				delTrainZ = 0;
			}
		}
	}
	else if (view == 2) {
		if (scene == 1) {
			if (m == 1) {
				if (delTrainZ < 1000)
				{
					trainZ = -1100;
					delTrainZ = delTrainZ + 1;
				}
				else {
					m = 2;
					delTrainZ = 0;
				}
			}
			else if (m == 2) {
				if (delTrainZ2 < 2000)
				{
					trainZ = -100;
					delTrainZ2 = delTrainZ2 + 1;
				}
				else if (delTrainZ2 == 2000) {
					m = 1;
					delTrainZ2 = 0;
				}
			}
		}
		else if (scene == 2) {
			if (m == 1) {
				if (delTrainZ < 1000)
				{
					trainZ = -1100;
					delTrainZ = delTrainZ + 0.4;
				}
				else {
					m = 2;
					delTrainZ = 0;
				}
			}
			else if (m == 2) {
				if (delTrainZ2 < 2000)
				{
					trainZ = -100;
					delTrainZ2 = delTrainZ2 + 0.4;
				}
				else if (delTrainZ2 == 2000) {
					m = 1;
					delTrainZ2 = 0;
				}
			}
		}
	}



	if (delWindmill < 360) {
		delWindmill += 0.1;
	}
	else {
		delWindmill = 0;
	}

	if (delCar1 < 300) {
		delCar1 += 0.2;
	}
	else {
		delCar1 = -500;
	}

	if (delCar2 > -700) {
		delCar2 -= 0.25;
	}
	else {
		delCar2 = 300;
	}

	if (px < 2000) {
		px += 1;
	}
	else {
		px = -2000;
	}

	if (planeX < 360) {
		planeX += 1;
	}
	else {
		planeX = 0;
	}
	glutTimerFunc(time_interval, OnTimer, 1);

}

void ReadImage(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
	GLubyte* pixeldata;
	FILE* pfile;
	fopen_s(&pfile, path, "rb");
	if (pfile == 0) exit(0);
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);
	p.push_back(pixeldata); // Similar to glDrawPixels for program 3
	fclose(pfile);
}

//use checkboard way to draw a textures of station
void makeStationImage(void) {
	int i, j;
	for (i = 0; i < checkStationWidth; i++) {
		for (j = 0; j < checkStationHeight; j++) {
			if ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) {
				stationImage[i][j][0] = (GLubyte)79;
				stationImage[i][j][1] = (GLubyte)79;
				stationImage[i][j][2] = (GLubyte)79;
			}
			else
			{
				stationImage[i][j][0] = (GLubyte)208;
				stationImage[i][j][1] = (GLubyte)226;
				stationImage[i][j][2] = (GLubyte)255;
			}
		}
	}
}

//Initialise the light
void lightinit() {
	GLfloat mat_specular[] = { 0.5,0.5,0.5,1 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1, -1, 1, 1 }; // Directional light
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseMaterial);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glDepthFunc(GL_LEQUAL);
}

//the initialize of all textures
void textureinit(void) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	ReadImage("sky.bmp", imagewidth0, imageheight0, pixellength0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
	glGenTextures(1, &textures[0]); // number of textures names to be generated and an array of textures names
	glBindTexture(GL_TEXTURE_2D, textures[0]); // target to which textures is bound and name of a textures
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	makeStationImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(2, &textures[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, checkStationWidth, checkStationHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, &stationImage[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	ReadImage("wood.bmp", imagewidth1, imageheight1, pixellength1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(3, &textures[2]);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("roof.bmp", imagewidth2, imageheight2, pixellength1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(4, &textures[3]);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth2, imageheight2, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("window.bmp", imagewidth3, imageheight3, pixellength3);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(5, &textures[4]);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth3, imageheight3, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[3]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("grass.bmp", imagewidth4, imageheight4, pixellength4);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(6, &textures[5]);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth4, imageheight4, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[4]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("sign.bmp", imagewidth5, imageheight5, pixellength5);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(7, &textures[6]);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth5, imageheight5, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("road.bmp", imagewidth6, imageheight6, pixellength6);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(8, &textures[7]);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth6, imageheight6, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("sign1.bmp", imagewidth7, imageheight7, pixellength7);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(9, &textures[8]);
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth7, imageheight7, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[7]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("sign2.bmp", imagewidth8, imageheight8, pixellength8);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(10, &textures[9]);
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth8, imageheight8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[8]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	ReadImage("sign3.bmp", imagewidth9, imageheight9, pixellength9);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textures[10]);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth9, imageheight9, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[9]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glShadeModel(GL_FLAT);
}

// functions
// one()
// draw a single object
void one(FunctionPtr a) // pointer as parameter
{
	glEnable(GL_DEPTH_TEST);
	a();
	glDisable(GL_DEPTH_TEST);
}
// inside()
// sets stencil buffer to show the part of A (front or back face according to 'face') that is inside of B.
void inside(FunctionPtr a, FunctionPtr b, GLenum face, GLenum test)
{
	// draw A into depth buffer, but not into color buffer
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glCullFace(face); //back is culled
	a();
	// use stencil buffer to find the parts of A that are inside of B by first incrementing the stencil buffer wherever B's front faces are
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glCullFace(GL_BACK);
	b();
	// then decrement the stencil buffer wherever B's back faces are
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	glCullFace(GL_FRONT);
	b();
	// now draw the part of A that is inside of B
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(test, 0, 1);
	glDisable(GL_DEPTH_TEST);
	glCullFace(face);
	a();
	// reset stencil test
	glDisable(GL_STENCIL_TEST);
}
// fixup()
// fixes up the depth buffer with A's depth values
void fixup(FunctionPtr a)
{
	// fix up the depth buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDepthFunc(GL_ALWAYS);
	a();
	// reset depth func
	glDepthFunc(GL_LESS);
}
// and()
// Boolean A and B (draw wherever A intersects B) algorithm: find where A is inside B, and then find where B is inside A
void And(FunctionPtr a, FunctionPtr b)
{
	inside(a, b, GL_BACK, GL_NOTEQUAL);
#if 1 // set to 0 for faster, but incorrect results
	fixup(b);
#endif
	inside(b, a, GL_BACK, GL_NOTEQUAL);
}

// sphere()
// draw a sphere
void sphere(float tx, float ty, float tz, float rangle, float rx, float ry, float rz, float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glRotatef(rangle, rx, ry, rz);
	glScalef(sx, sy, sz);
	glutSolidSphere(100.0, 100, 100);
	glPopMatrix();
}
// cube()
// draw a cube
void cube(float tx, float ty, float tz, float rangle, float rx, float ry, float rz, float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glRotatef(rangle, rx, ry, rz);
	glScalef(sx, sy, sz);
	glutSolidCube(100.0);
	glPopMatrix();
}
// cone()
// draw a cone
void cone(float tx, float ty, float tz, float rangle, float rx, float ry, float rz, float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glRotatef(rangle, rx, ry, rz);
	glScalef(sx, sy, sz);
	glutSolidCone(49.0, 100.0, 100, 100);
	glPopMatrix();
}

// complex()
// draw a cone conbined with shpere
void complex(float tx, float ty, float tz, float rangle, float rx, float ry, float rz, float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glRotatef(rangle, rx, ry, rz);
	glScalef(sx, sy, sz);
	glutSolidSphere(28, 100, 100);
	glutSolidCone(30.0, 100.0, 100, 100);
	glPopMatrix();
}

//use CSG techniques to draw the plane
void drawPlane() {
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	GLfloat mat_diffuse[] = { 0.7, 0.8, 0.85, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 30.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslatef(px, 50, 0);

	//tail of the plane
	glPushMatrix();
	glTranslatef(300, 260, 0);
	glRotatef(30, 0, 0, 1);
	complex(-440, 500, -500, 90, 0, 1, 0, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, -105, 0);
	glRotatef(-30, 0, 0, 1);
	complex(-440, 500, -500, 90, 0, 1, 0, 1, 1, 1);
	glPopMatrix();

	//body of plane
	B = []() {cube(-125, 502, -500, 0, 0, 0, 0, 3, 1.5, 1.5); };
	C = []() {cone(65, 502, -500, -90, 0, 1, 0, 1.5, 1.5, 5); };
	And(B, C);

	//head of plane
	A = []() {sphere(0, 500, -500, 0, 0, 0, 0, 1.2, 1, 1); };
	B = []() {cube(75, 500, -500, 0, 0, 0, 0, 1, 1, 1); };
	/*one(A);
	one(B);*/
	And(A, B);

	//use hierarchical to draw propeller of plane
	glPushMatrix();
	glTranslatef(130, 500, -500);
	glRotatef(planeX, 1, 0, 0);
	glutSolidSphere(20, 100, 100);

	glPushMatrix();
	glTranslatef(0, 0, -100);
	glScalef(1, 1, 1);
	glutSolidCone(25, 100, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 100);
	glScalef(1, 1, 1);
	glRotatef(180, 1, 0, 0);
	glutSolidCone(25, 100, 100, 100);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}

//a isolation belt to divide track and highway
void drawIsolation() 
{   
	for (int i = -600; i < 600; i += 300) {
		glPushMatrix();
		glTranslatef(350, -60, i);
		glScalef(0.8, 0.8, 0.8);
		glPushMatrix();
		glTranslatef(0.0, 20, 70);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-50, -10, 40);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-30, 26, 0);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(30, 30, 10);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(60, -20, 30);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(60, 0, -30);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 20, -40);
		glColor3ub(255, 27, 68);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -40, 0.0);
		glScalef(85, 85, 85);
		glColor3ub(255, 88, 224);
		glutSolidIcosahedron();
		glScalef(1.005, 1.005, 1.005);
		glColor3f(0.0, 0.0, 0.0);
		glutWireIcosahedron();
		glPopMatrix();

		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-50, -200, 51);
		glVertex3f(50, -200, 51);
		glVertex3f(50, -245, 51);
		glVertex3f(-50, -245, 51);
		glEnd();
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-51, -200, 51);
		glVertex3f(-51, -200, -51);
		glVertex3f(-51, -245, -51);
		glVertex3f(-51, -245, 51);
		glEnd();
		glPushMatrix();
		glTranslatef(0, -220, 0);
		glScalef(1, 0.6, 1);
		glColor3f(0.83f, 0.4f, 0.1f);
		glutSolidCube(100);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -182.5, 0);
		glScalef(1, 0.1, 1);
		glColor3f(0.83f, 0.4f, 0.1f);
		glutSolidCube(150);
		glPopMatrix();

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		glVertex3f(-91, -40, 76);
		glVertex3f(-91, -40, -76);
		glVertex3f(-91, -190, -76);
		glVertex3f(-91, -190, 76);
		glEnd();
		glPushMatrix();
		glTranslatef(82.5, -115, 0);
		glScalef(0.1, 1, 1);
		glColor3f(0.83f, 0.4f, 0.1f);
		glutSolidCube(150);
		glPopMatrix();

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		glVertex3f(-91, -40, 76);
		glVertex3f(91, -40, 76);
		glVertex3f(91, -190, 76);
		glVertex3f(-91, -190, 76);
		glEnd();

		glPushMatrix();
		glTranslatef(-82.5, -115, 0);
		glScalef(0.1, 1, 1);
		glColor3f(0.83f, 0.4f, 0.1f);
		glutSolidCube(150);
		glPopMatrix();

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		glVertex3f(-91, -40, 76);
		glVertex3f(91, -40, 76);
		glVertex3f(91, -40, -76);
		glVertex3f(-91, -40, -76);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		glVertex3f(-74, -40, 60);
		glVertex3f(74, -40, 60);
		glVertex3f(74, -40, -60);
		glVertex3f(-74, -40, -60);
		glEnd();

		glPushMatrix();
		glTranslatef(0, -115, -67.5);
		glScalef(1, 1, 0.1);
		glColor3f(0.83f, 0.4f, 0.1f);
		glutSolidCube(150);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -115, 67.5);
		glScalef(1, 1, 0.1);
		glColor3f(0.83f, 0.4f, 0.1f);
		glutSolidCube(150);
		glPopMatrix();
		glPopMatrix();
	}
	glDisable(GL_LIGHTING);
}

//the temporary house of train
void drawHouse() {
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glPushMatrix();
	glTranslatef(-700, 0, -50);
	glColor3f(0.5f, 0.3f, 0.1f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-150, -30, -100);
	glTexCoord2f(0, 0); glVertex3f(0, 80, -100);
	glTexCoord2f(1, 0); glVertex3f(0, 80, -400);
	glTexCoord2f(1, 1); glVertex3f(-150, -30, -400);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-150, -230, -100);
	glTexCoord2f(0.0, 0.64); glVertex3f(-150, -30, -100);
	glTexCoord2f(0, 1.0); glVertex3f(0, 80, -100);
	glTexCoord2f(1, 0.64); glVertex3f(150, -30, -100);
	glTexCoord2f(1, 0); glVertex3f(150, -230, -100);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(150, -230, -100);
	glTexCoord2f(0, 1); glVertex3f(150, -30, -100);
	glTexCoord2f(1, 1); glVertex3f(150, -30, -400);
	glTexCoord2f(1, 0); glVertex3f(150, -230, -400);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(0, 80, -100);
	glTexCoord2f(0, 1); glVertex3f(150, -30, -100);
	glTexCoord2f(1, 1); glVertex3f(150, -30, -400);
	glTexCoord2f(1, 0); glVertex3f(0, 80, -400);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//window
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 180; ++i) {
		float theta = i * (3.1415 / 180.0);
		float x = 50 * cos(theta);
		float y = 50 * sin(theta);
		glTexCoord2f((0.5 + x / 100) * 0.5, 0.5 * y / 100); glVertex3f(x, y - 70, -99);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-50, -150, -99);
	glTexCoord2f(0, 1); glVertex3f(-50, -70, -99);
	glTexCoord2f(1, 1); glVertex3f(50, -70, -99);
	glTexCoord2f(1, 0); glVertex3f(50, -150, -99);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3ub(100, 100, 100);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 180; ++i) {
		float theta = i * (3.1415 / 180.0);
		float x = 50 * cos(theta);
		float y = 50 * sin(theta);
		glVertex3f(x, y - 70, -99);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-50, -150, -99);
	glVertex3f(-50, -70, -99);
	glVertex3f(50, -70, -99);
	glVertex3f(50, -150, -99);
	glEnd();
	glPopMatrix();
}

//the title of train station
void drawTitle() {
	glEnable(GL_LIGHTING);
	GLfloat mat_diffuse[] = { 0.1,0.1,0.1, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 30.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glColor3ub(20, 28, 31);
	glPushMatrix();
	glTranslatef(-900, 0, -100);
	glScalef(1, 50, 1);
	glutSolidCube(10);
	glPopMatrix();

	glColor3ub(20, 28, 31);
	glPushMatrix();
	glTranslatef(-600, 0, -100);
	glScalef(1, 50, 1);
	glutSolidCube(10);
	glPopMatrix();

	glColor3ub(20, 28, 31);
	glPushMatrix();
	glTranslatef(-750, 200, -100);
	glScalef(40, 1, 1);
	glutSolidCube(10);
	glPopMatrix();

	glColor3ub(20, 28, 31);
	glPushMatrix();
	glTranslatef(-750, 100, -100);
	glScalef(40, 1, 1);
	glutSolidCube(10);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-900, 100, -100);
	glTexCoord2f(0.0, 1.0); glVertex3f(-900, 200, -100);
	glTexCoord2f(1.0, 1.0); glVertex3f(-600, 200, -100);
	glTexCoord2f(1.0, 0.0); glVertex3f(-600, 100, -100);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

//use cosahedron to draw the tree
void drawTree() {
	glDisable(GL_LIGHTING);
	for (int i = -500; i < 600; i += 100) {
		glPushMatrix();
		glTranslatef(-1000, -210, i);
		glScalef(1.5, 2, 1.5);
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glScalef(60.0, 65.0, -30.0);
		glColor3f(0.0, 0.7, 0.1);
		glutSolidIcosahedron();
		glColor3f(0.0, 0.0, 0.0);
		glutWireIcosahedron();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 25.0, 0.0);
		glScalef(15.0, 50.0, 15.0);
		glColor3f(0.7, 0.3, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
}

//track of train
void drawTrack() {
	glDisable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3ub(105, 58, 18);
	glPushMatrix();
	glTranslatef(0, -250, 300);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -250, 200);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -250, 100);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -250, 0);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -250, -100);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(105, 58, 18);
	glTranslatef(0, -250, -200);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(105, 58, 18);
	glTranslatef(0, -250, -300);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(105, 58, 18);
	glTranslatef(0, -250, -400);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(105, 58, 18);
	glTranslatef(0, -250, -500);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(105, 58, 18);
	glTranslatef(0, -250, -600);
	glScalef(2.5f, 0.05f, 0.25f);
	glutSolidCube(200.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(101, 96, 105);
	glTranslatef(-180, -230, -250);
	glScalef(0.1f, 0.1f, 3);
	glutSolidCube(400.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(101, 96, 105);
	glTranslatef(180, -230, -250);
	glScalef(0.1f, 0.1f, 3);
	glutSolidCube(400.0);
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

//use hierarchical modelling to draw a weathercock
void drawWeathercock() {
	glEnable(GL_LIGHTING);
	GLfloat mat_diffuse[] = { 0.31,0.34,0.54, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 30.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glColor3ub(195, 195, 195);
	glTranslatef(1300, -300, -600);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(50, 200, 100, 100);

	glPushMatrix();
	glTranslatef(0, 0, 200);
	GLfloat mat_diffuse2[] = { 0.85,0.8,0.6, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);
	glRotatef(delWindmill, 0, 0, 1);
	glColor3ub(242, 255, 14);
	glutSolidSphere(10, 20, 100);
	glPushMatrix();
	GLfloat mat_diffuse3[] = { 0.85,0.2,0.4, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse3);
	glTranslatef(100, 0, 0);
	glScalef(1, 0.2, 1.3);
	glRotatef(-90, 0, 1, 0);
	glColor3ub(195, 16, 23);
	glutSolidCone(25, 100, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 0, 0);
	glScalef(1, 0.2, 0.5);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(25, 100, 100, 100);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

//a traffic light can be control by both keyboard and mouse
void drawLight() {
	glEnable(GL_LIGHTING);
	GLfloat mat_diffuse[] = { 0.1,0.1,0.1, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 30.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glColor3ub(20, 28, 31);
	glPushMatrix();
	glTranslatef(-300, -100, -100);
	glScalef(10.0, 300.0, 10.0);
	glutSolidCube(1);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glScalef(5, 0.5, 1);
	glutSolidCube(1);
	glDisable(GL_LIGHTING);

	//green light
	if (scene == 1) {
		glPushMatrix();
		glColor3ub(0, 0, 0);
		glTranslatef(0, 0.3, 0.5);
		glScalef(0.5, 0.25, 0.5);
		glutSolidSphere(0.5, 100, 100);
		glTranslatef(0, -1.2, 0);
		glColor3ub(0, 0, 0);
		glutSolidSphere(0.5, 100, 100);
		glTranslatef(0, -1.2, 0);
		glColor3ub(23, 199, 80);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
	}
	//yellow light
	else if (scene == 2) {
		glPushMatrix();
		glColor3ub(0, 0, 0);
		glTranslatef(0, 0.3, 0.5);
		glScalef(0.5, 0.25, 0.5);
		glutSolidSphere(0.5, 100, 100);
		glTranslatef(0, -1.2, 0);
		glColor3ub(234, 197, 50);
		glutSolidSphere(0.5, 100, 100);
		glTranslatef(0, -1.2, 0);
		glColor3ub(0, 0, 0);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
	}
	//red light
	else if (scene == 3) {
		glPushMatrix();
		glColor3ub(234, 28, 31);
		glTranslatef(0, 0.3, 0.5);
		glScalef(0.5, 0.25, 0.5);
		glutSolidSphere(0.5, 100, 100);
		glTranslatef(0, -1.2, 0);
		glColor3ub(0, 0, 0);
		glutSolidSphere(0.5, 100, 100);
		glTranslatef(0, -1.2, 0);
		glColor3ub(0, 0, 0);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
}

//use hierarchical modelling to draw a car
void drawCar() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(875, -250, delCar1);

	//body of car
	glScalef(0.5, 0.5, 0.3);
	glPushMatrix();
	glTranslatef(0, 30.0, -60.0);
	glScalef(150.0, 10.0, 450.0);

	glColor3ub(49, 49, 59);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 70.0, -60.0);
	glScalef(150.0, 70, 450.0);
	glColor3ub(255, 253, 125);
	glutSolidCube(1);
	glPopMatrix();

	//top of the car
	glPushMatrix();
	glTranslatef(0, 130.0, -50.0);
	glScalef(150.0, 50, 200.0);
	glColor3f(1, 1, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	// wheels of car
	glPushMatrix();
	glTranslatef(80, 30, 50);
	glRotatef(88, 0, 1, 0);
	glColor3ub(48, 45, 105);
	glutSolidCylinder(60, 5, 40, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 30, -150);
	glRotatef(88, 0, 1, 0);
	glutSolidCylinder(60, 5, 40, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 30, -150);
	glRotatef(88, 0, 1, 0);
	glutSolidCylinder(60, 5, 40, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 30, 50);
	glRotatef(88, 0, 1, 0);
	glutSolidCylinder(60, 5, 40, 1);
	glPopMatrix();
	glPopMatrix();
}

//draw a lorry use hierarchical modelling to draw a lorry
void drawLorry() {
	glDisable(GL_LIGHTING);
	glPushMatrix();

	//body of the lorry
	glTranslatef(630, -250, delCar2);
	glScalef(0.7, 0.6, 0.4);
	glPushMatrix();
	glTranslatef(0, 30.0, -60.0);
	glScalef(150.0, 10.0, 450.0);
	glColor3ub(124, 128, 87);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 70.0, -60.0);
	glScalef(150.0, 70, 450.0);
	glColor3ub(178, 206, 255);
	glutSolidCube(1);
	glPopMatrix();

	//top of the lorry
	glPushMatrix();
	glTranslatef(0, 150.0, -200.0);
	glScalef(100.0, 80, 350.0);
	glColor3ub(255, 255, 255);
	glutSolidCylinder(1, 1, 100, 100);
	glPopMatrix();

	//wheels of the lorry
	glPushMatrix();
	glTranslatef(80, 30, 0);
	glRotatef(90, 0, 1, 0);
	glColor3ub(128, 128, 128);
	glutSolidCylinder(100, 5, 40, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 30, -100);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(70, 5, 40, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 30, -150);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(70, 5, 40, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 30, 50);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(70, 5, 40, 1);
	glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawSign() {
	glEnable(GL_LIGHTING);
	GLfloat mat_diffuse[] = { 0.5,0.5,0.5, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 30.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	//frame of signs
	glPushMatrix();
	glTranslatef(500, 0, -500);
	glScalef(1, 50, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1000, 0, -500);
	glScalef(1, 50, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(750, 200, -500);
	glScalef(70, 1, 1);
	glutSolidCube(10);
	glPopMatrix();

	//triangle sign
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(525, 160, -494);
	glTexCoord2f(1.0, 0.0); glVertex3f(625, 160, -494);
	glTexCoord2f(0.5, 1.0); glVertex3f(575, 260, -494);
	glEnd();

	//rectangle sign
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0); glVertex3f(725, 300, -494);
	glTexCoord2f(1.0, 1.0); glVertex3f(975, 300, -494);
	glTexCoord2f(1.0, 0.0); glVertex3f(975, 120, -494);
	glTexCoord2f(0.0, 0.0); glVertex3f(725, 120, -494);
	glEnd();

	//circle sign
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10) {
		float angle = i * 3.14159265 / 180.0;
		float x = 50 * cos(angle) + 670;
		float y = 50 * sin(angle) + 200;
		glTexCoord2f((cos(angle) + 1) / 2, (sin(angle) + 1) / 2); glVertex3f(x, y, -494);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}
void drawTrain() {
	//use a hierarchical modelling to draw a train
	glEnable(GL_LIGHTING);
	GLfloat mat_diffuse[] = { 0.08, 0.6, 0.08, 1.0 };
	GLfloat mat_specular[] = { 0.5,0.5,0.5, 1.0 };
	GLfloat mat_shininess[] = { 30.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	GLfloat emissionColor2[] = { 0.15, 0.5, 0.03,1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor2);
	glPushMatrix();
	glTranslatef(0, -50, trainZ + delTrainZ + delTrainZ2);

	glPushMatrix();
	glScalef(1.6, 1.6, 5);
	glColor3ub(44, 112, 52);
	glutSolidCube(200.0);
	glPopMatrix();
	GLfloat emissionColor3[] = { 0.3,0.2,0.14,1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor3);

	//top of train
	glPushMatrix();
	glTranslatef(0, 175, 0);
	glScalef(1.2, 0.15, 5);
	glColor3ub(77, 50, 36);
	glutSolidCube(200.0);
	glPopMatrix();
	//screen of train
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-115, 0, 500.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-115, 120, 500.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(115, 120, 500.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(115, 0, 500.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//lights of train
	glPushMatrix();
	glTranslatef(-110, -50, 500);
	GLfloat emissionColor[] = { 1.0,1.0,0.5,1.0 };// emission
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	glColor3ub(253, 255, 188);
	glutSolidSphere(25, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(110, -50, 500);
	glColor3ub(253, 255, 188);
	glutSolidSphere(25, 25, 25);
	glPopMatrix();
	GLfloat defaultEmission[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, defaultEmission);

	//tyres of train
	glPushMatrix();
	glTranslatef(-170, -160, 500);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1, 1);
	glColor3ub(0, 0, 0);
	GLfloat mat_diffuse2[] = { 0.3,0.5,0.7,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);
	glutSolidCylinder(20, 20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150, -160, 500);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1, 1);
	glColor3ub(0, 0, 0);
	glutSolidCylinder(20, 20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150, -160, -500);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1, 1);
	glColor3ub(0, 0, 0);
	glutSolidCylinder(20, 20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-170, -160, -500);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1, 1);
	glColor3ub(0, 0, 0);
	glutSolidCylinder(20, 20, 20, 20);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

void drawRoad()
{
	//draw a highway with textures
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(500, -249, -700);
	glTexCoord2f(1, 1); glVertex3f(1000, -249, -700);
	glTexCoord2f(1, 0); glVertex3f(1000, -249, 700);
	glTexCoord2f(0, 0); glVertex3f(500, -249, 700);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
void drawSky()
{
	//sky textures to a volumn
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-3000, -250, -600);
	glTexCoord2f(0.0, 1.0); glVertex3f(-3000, 1500, -600);
	glTexCoord2f(1.0, 1.0); glVertex3f(3000.0, 1500, -600);
	glTexCoord2f(1.0, 0.0); glVertex3f(3000.0, -250, -600);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-3000, -250, -600);
	glTexCoord2f(0.0, 1.0); glVertex3f(-3000, 1500, -600);
	glTexCoord2f(1.0, 1.0); glVertex3f(-3000, 1500, 600);
	glTexCoord2f(1.0, 0.0); glVertex3f(-3000, -250, 600);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(3000, -250, -600);
	glTexCoord2f(0.0, 1.0); glVertex3f(3000, 1500, -600);
	glTexCoord2f(1.0, 1.0); glVertex3f(3000, 1500, 600);
	glTexCoord2f(1.0, 0.0); glVertex3f(3000, -250, 600);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(3000, 1500, -600);
	glTexCoord2f(0.0, 1.0); glVertex3f(-3000, 1500, -600);
	glTexCoord2f(1.0, 1.0); glVertex3f(-3000, 1500, 600);
	glTexCoord2f(1.0, 0.0); glVertex3f(3000, 1500, 600);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawGrass() {
	//grass textures
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1.0); glVertex3f(-3000, -250, -600);
	glTexCoord2f(0.0, 0.0); glVertex3f(-3000, -250, 600);
	glTexCoord2f(1.0, 0); glVertex3f(3000.0, -250, 600);
	glTexCoord2f(1.0, 1.0); glVertex3f(3000.0, -250, -600);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawStation()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-900, -210, 0);
	glTexCoord2f(0.0, 1); glVertex3f(-900, -210, -500);
	glTexCoord2f(1.0, 1); glVertex3f(-500, -210, -500);
	glTexCoord2f(1.0, 0.0); glVertex3f(-500, -210, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3ub(66, 66, 66);
	glBegin(GL_QUADS);
	glVertex3f(-500, -210, 0);
	glVertex3f(-500, -210, -500);
	glVertex3f(-500, -250, -500);
	glVertex3f(-500, -250, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-900, -210, 0);
	glVertex3f(-500, -210, 0);
	glVertex3f(-500, -250, 0);
	glVertex3f(-900, -250, 0);
	glEnd();
}

void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY + deltaY, eyeZ, centerX, centerY, centerZ - 500, upX, upY, upZ);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSky();
	drawPlane();
	drawGrass();
	drawRoad();
	drawTree();
	drawTrack();
	drawSign();
	drawCar();
	drawLorry();
	drawWeathercock();
	drawIsolation();
	glPushMatrix();
	glTranslatef(0, 0, 100);
	glScalef(1, 1, 1);
	drawStation();
	drawHouse();
	drawTitle();
	glPopMatrix();
	drawTrain();
	drawLight();
	glFlush();
}

//keyboard input to control the display
void keyboard_input(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		exit(0);
	if (key == 'a' || key == 'A') {
		if (eyeX < 130) {
			eyeX += 5;
		}
	}
	if (key == 'd' || key == 'D') {
		if (eyeX >= -130) {
			eyeX -= 5;
		}
	}
	if (key == 'w' || key == 'W') {
		if (eyeZ >= 400) {
			eyeZ -= 5;
		}
	}
	if (key == 's' || key == 'S') {
		if (eyeZ <= 600) {
			eyeZ += 5;
		}
	}
	if (key == '1') {
		scene = 1;
	}
	if (key == '2') {
		scene = 2;
	}
	if (key == '3') {
		scene = 3;
	}
	if (key == ' ')
	{
		if (deltaY == 50) {
			deltaY = 500;
		}
		else {
			deltaY = 50;
		}

		if (view == 1) {
			view = 2;
			trainZ = -1100;
			delTrainZ = 0;
			delTrainZ2 = 0;
			m = 1;
		}
		else {
			view = 1;
			trainZ = -1100;
			delTrainZ = 0;
			delTrainZ2 = 0;
			m = 1;
		}
	}
	glutPostRedisplay();
}

//This will be called when the viewport is changed
void myReshape(GLsizei w, GLsizei h) {
	GLfloat fAspect;
	if (h == 0) // Avoid division by zero
		h = 1;
	glViewport(0, 0, w, h); // Set viewport to window dimensions
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION); // Reset coordinate system
	glLoadIdentity();
	gluPerspective(90, fAspect, 100, 10000); // Set viewing volume
}

void menu(int item) //mouse and keyboard can control the display altogether
{
	keyboard_input((unsigned char)item, 0, 0);
}

int main(int argc, char** argv) {
	int opt;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	if (glutCreateWindow("cw2") == GL_FALSE)
		exit(0);
	glutReshapeFunc(myReshape);
	lightinit();
	textureinit();
	glutDisplayFunc(display);
	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer, 1);
	glutKeyboardFunc(keyboard_input);
	opt = glutCreateMenu(menu);
	glutAddMenuEntry("green     (1)", '1');
	glutAddMenuEntry("yellow     (2)", '2');
	glutAddMenuEntry("red     (3)", '3');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}