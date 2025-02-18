//Wenxuan.Xu
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vector"
using namespace std;

#pragma region parameters

float rs = 5;
float speed = 10;
int time_interval = 5;
//rotating camera

GLfloat pi = 3.1415926f;
GLfloat Rangle = 0;//this is for the rot
//These are used to set the scale size
GLfloat landx = 2000.0;
GLfloat landY = 10.0;
GLfloat landZ = 1200.0;
// camera
typedef struct point { GLfloat x, y, z; };

GLfloat fltFOV = 100; //Field Of View
GLfloat fltZoom = 1.1; //Zoom amount
GLfloat fltX0 = 0.0; //Camera position
GLfloat fltY0 = 500.0;
GLfloat fltZ0 = -700.0;
//reference point
GLfloat fltXRef = 0.0;
GLfloat fltYRef = 550.0;
GLfloat fltZRef = 0.0;
GLfloat fltXUp = 0.0;
GLfloat fltYUp = 1.0;
GLfloat fltZUp = 0.0;
float fltCarX = 0;
float fltWheelRof = 0;
float fltWheelRofTimeout = 0;
GLint imagewidth0, imageheight0, pixellength0;
GLint imagewidth1, imageheight1, pixellength1;
GLint imagewidth2, imageheight2, pixellength2;
GLint imagewidth3, imageheight3, pixellength3;
GLint imagewidth4, imageheight4, pixellength4;
GLint imagewidth5, imageheight5, pixellength5;
GLint imagewidth6, imageheight6, pixellength6;
GLint imagewidth7, imageheight7, pixellength7;
GLint imagewidth8, imageheight8, pixellength8;
GLint imagewidth9, imageheight9, pixellength9;
GLint imagewidth10, imageheight10, pixellength10;
GLint imagewidth11, imageheight11, pixellength11;
GLint imagewidth12, imageheight12, pixellength12;
GLuint textures[13];
vector <GLubyte*>p;

// lighting
GLfloat lightX = 0.0;
GLfloat lightY = 1800.0;
GLfloat lightZ = 0.0;
GLfloat lightR = 0.86;
GLfloat lightG = 0.84;
GLfloat lightB = 0.83;
GLfloat lightA = 0.85;
GLfloat lightPosition[] = { lightX, lightY, lightZ, 1.0 };
GLfloat sun_intensity[] = { 1.0, 1.0, 0, 1.0 };

bool isNight = false;

// Window size
GLint winWidth = 1600;
GLint winHeight = 900;
#pragma endregion
void block(float x, float z, float u, float l, float w, float h, float c1, float c2, float c3);
void drawFrame();
void drawPlant1(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0.0, 100.0, 0.0);
	glScalef(60.0, 65.0, 60.0);
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

void lightingInitNight(GLfloat intensity_red, GLfloat intensity_green, GLfloat intensity_blue, GLfloat intensity_alpha) {
	GLfloat ambient_intensity[] = { intensity_red, intensity_green, intensity_blue, intensity_alpha };
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);
	GLfloat mat_ambient[] = { 1,1,1,1.0 };
	GLfloat mat_di[] = { 0.9,0.9,0.9,1.0 };
	GLfloat mat_sp[] = { 0.5,0.8,0.4,1.0 };
	GLfloat mat_shine[] = { 20.0 };
	//These are mat light
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_di);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sp);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void lightingInit(GLfloat intensity_red, GLfloat intensity_green, GLfloat intensity_blue, GLfloat intensity_alpha) {
	GLfloat ambient_intensity[] = { intensity_red, intensity_green, intensity_blue, intensity_alpha };
	glEnable(GL_LIGHTING);              // Set up ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	glEnable(GL_LIGHT0);                // Set up sunlight.
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);
	GLfloat mat_ambient[] = { 1,1,1,1.0 };
	GLfloat mat_di[] = { 1,1,1,1.0 };
	GLfloat mat_sp[] = { 1,1,11,1.0 };
	GLfloat mat_shine[] = { 20.0 };
	//These are mat light
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_di);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sp);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
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
	p.push_back(pixeldata);
	fclose(pfile);
}

void textureInit() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	ReadImage("lol.bmp", imagewidth0, imageheight0, pixellength0);
	ReadImage("mc.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("grass.bmp", imagewidth2, imageheight2, pixellength2);
	ReadImage("build.bmp", imagewidth3, imageheight3, pixellength3);
	ReadImage("road.bmp", imagewidth4, imageheight4, pixellength4);
	ReadImage("skyboxtop.bmp", imagewidth5, imageheight5, pixellength5);
	ReadImage("skyboxnorth.bmp", imagewidth6, imageheight6, pixellength6);
	ReadImage("skyboxeast.bmp", imagewidth7, imageheight7, pixellength7);
	ReadImage("skyboxwest.bmp", imagewidth8, imageheight8, pixellength8);
	ReadImage("skyboxsouth.bmp", imagewidth9, imageheight9, pixellength9);
	ReadImage("water.bmp", imagewidth10, imageheight10, pixellength10);
	ReadImage("brick.bmp", imagewidth11, imageheight11, pixellength11);
	ReadImage("sunmap.bmp", imagewidth12, imageheight12, pixellength12);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(13, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth2, imageheight2, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth3, imageheight3, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[3]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth4, imageheight4, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[4]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth5, imageheight5, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth6, imageheight6, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth7, imageheight7, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[7]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth8, imageheight8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[8]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth9, imageheight9, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[9]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth10, imageheight10, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[10]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textures[11]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth11, imageheight11, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[11]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textures[12]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth12, imageheight12, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[12]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void adv(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-300, 150, 0);
	glScalef(10, 270, 10);
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(305, 150, 0);
	glScalef(10, 300, 10);
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 260, 0);
	glScalef(600, 10, 10);
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 200, 0);
	glScalef(600, 10, 10);
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 250, 10);
	glScalef(400, 200, 5);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.6);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.6);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.6);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.6);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}

void twinTower() {
	block(-1000.0, -10, 75, 200, 1400, 200, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(-1000.0, -10, 850, 150, 150, 150, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(-1000.0, -10, 975, 90, 100, 90, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(-1000.0, -10, 1060, 50, 70, 50, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(-1000.0, -10, 1130, 10, 70, 10, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	glPushMatrix();
	glTranslatef(0, 1230, -10);
	glRotatef(180, 1, 0, 0);
	glScalef(1790, 600, 5);
	glColor3ub(220, 220, 220);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.505, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.505, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.505, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.505, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.505, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.505, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.505, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.505, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.505, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.505, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.505, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.505, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, 0.505);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, 0.505);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, 0.505);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.505);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, -0.505);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, -0.505);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, -0.505);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, -0.505);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glPopMatrix();
	block(1000.0, -10, 75, 200, 1400, 200, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(1000.0, -10, 850, 150, 150, 150, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(1000.0, -10, 975, 90, 100, 90, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(1000.0, -10, 1060, 50, 70, 50, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
	block(1000.0, -10, 1130, 10, 70, 10, 220, 220, 220);//Chocolate2(0.93, 0.46, 0.13)
}

void drawBrickBuilding(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0, 350, 0);
	glScalef(150, 1100, 400);
	glColor3f(1, 0.88, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.505, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.505, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.505, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.505, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.505, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.505, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.505, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.505, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.505, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.505, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.505, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.505, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, 0.505);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, 0.505);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, 0.505);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.505);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, -0.505);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, -0.505);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, -0.505);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, -0.505);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSolidCube(1);
	glPopMatrix();
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			glPushMatrix();
			glTranslatef(-75, i * 100 + 125, j * 100 - 150);
			glScalef(10, 50, 50);
			glColor3f(1, 1, 1);
			glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(75, i * 100 + 125, j * 100 - 150);
			glScalef(10, 50, 50);
			glColor3f(1, 1, 1);
			glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
		}
		glTranslatef(0, i * 100 + 125, -200);
		glScalef(50, 50, 10);
		glColor3f(1, 1, 1);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, i * 100 + 125, 200);
		glScalef(50, 50, 10);
		glColor3f(1, 1, 1);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
}

void block(float x, float z, float u, float l, float w, float h, float c1, float c2, float c3) {
	glPushMatrix();
	glTranslatef(x, 0.0, 0 + z);
	glPushMatrix();
	glTranslatef(0.0, u, 0.0);
	glScalef(l, w, h);
	glColor3ub(c1, c2, c3);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[11]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.505, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.505, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.505, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.505, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.505, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.505, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.505, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.505, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.505, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.505, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.505, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.505, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, 0.505);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, 0.505);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, 0.505);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.505);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, -0.505);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, -0.505);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, -0.505);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, -0.505);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glPopMatrix();
	glPopMatrix();
}

void sun(GLfloat r)
{
	glPushMatrix();
	glTranslatef(-600, 1500, -500);
	glScalef(5, 5, 5);
	glRotatef(rs, 0, 1, 0);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textures[12]);
	GLUquadric* quadricObj = gluNewQuadric();
	// Create a quadric surface object
	gluQuadricTexture(quadricObj, GL_TRUE); // Set textures mode to true
	gluSphere(quadricObj, r, 50, 20);
	glPopMatrix();

}

void drawPlainRoad(GLfloat x, GLfloat y, GLfloat z, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scaleX, scaleY, scaleZ);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.6, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.6, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.6, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.6, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0, 0.39, 0);
	glutSolidCube(1);
	glColor3f(0, 0.39, 0);
	glutWireCube(1);
	glPopMatrix();
}

void drawRiver(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0, 8, 0);
	glScalef(300, 10.5, landZ);
	glColor3f(0.5, 1, 0.83);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.6, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.6, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.6, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.6, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
}

void drawZebraLine(GLfloat x, GLfloat y, GLfloat z) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0, 1.2, 0);
	glScalef(15, 5, 175);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}

void environment() {
	for (int i = 0; i < landZ; i += 250)
	{
		drawPlant1(0, 0, i - (landZ / 2) + 70);
	}
}

void drawConstructions() {

	twinTower();
	drawBrickBuilding(1050, 100, -350);
	drawBrickBuilding(1050, 100, 350);
	drawBrickBuilding(-1050, 100, 350);
	drawBrickBuilding(-1050, 100, -350);


}

void drawFrame() {
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	glScalef(landx, landY, landZ);
	glColor3ub(220, 220, 220);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.6, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.6, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.6, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.6, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glutSolidCube(1);//除了中间人行道以外的地
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -2, -20);
	glScalef(landx, 10, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1230, 10, 0);
	glScalef(160, 10, landZ);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1230, 10, 0);
	glScalef(160, 10, landZ);


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 30, 0);

	glPopMatrix();
    drawPlainRoad(0, 0, 0, 330, 10, landZ);
	drawRiver(-landx + 500, 15, 0);
	drawRiver(landx - 500, 10, 0);
	environment();
    drawPlainRoad(-1150, 0, 0, 750, 10, landZ);
    drawPlainRoad(1150, 0, 0, 750, 10, landZ);

	for (int j = 0; j < 26; j++) {
		drawZebraLine(0 + 30 * j, 10, -20);
	}
	for (int i = 0; i < 26; i++) {
		drawZebraLine(-(0 + 30 * i), 10, -20);
	}

	adv(-500, 0, -300);
	drawConstructions();
}

void drawWheel(float x, float y, float z, float rof) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rs, 1, 0, 0);
	glRotatef(88 + rof, 0, 1, 0);
	glColor3f(0.3, 0.8, 0.6);
	glutSolidCylinder(60, 5, 40, 1);
	glColor3f(0, 0, 0);
	glutWireCylinder(60, 5, 40, 1);
	glPopMatrix();
}

void drawViewMirror(float x) {
	glPushMatrix();
	glTranslatef(x, 120.0, -10.0);
	glScalef(25.0, 8, 10.0);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glColor3f(1, 1, 1);
	glutSolidCube(1);
	glPopMatrix();
}

void drawCarGlass(float y, float rof) {
	glPushMatrix();
	glTranslatef(0, 120, y);
	glRotatef(rof, 1, 0, 0);
	glScalef(1.38, 0.7, 1);
	glTranslatef(-150, -150, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(100, 100, 0);
	glVertex3f(200, 100, 0);
	glVertex3f(200, 200, 0);
	glVertex3f(100, 200, 0);
	glEnd();
	glPopMatrix();
}

void drawTaillight(float x) {

}

// Using Hierarchical Modelling to design a car
void car() {
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(-500, 30.0, -500.0 + speed);
	glScalef(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(0, 30.0, -60.0);
	glScalef(150.0, 10.0, 450.0);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glColor3f(0.6, 0.6, 0.6);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 60.0, -60.0);
	glScalef(150.0, 50, 450.0);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glColor3f(1, 1, 0.6);
	glutSolidCube(1);
	glPopMatrix();
	// Middle body of the car
	glPushMatrix();
	glTranslatef(0, 100.0, -70.0);
	glScalef(150.0, 50, 130.0);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glColor3f(1, 1, 0.6);
	glutSolidCube(1);
	glPopMatrix();
	// Glass
	drawCarGlass(10, 120);
	drawCarGlass(-175, 55);
	// Rear view mirror
	drawViewMirror(80);
	drawViewMirror(-80);
	// Taillight
	// 4 wheels
	drawWheel(80, 30, 50, 0);
	drawWheel(80, 30, -150, 0);
	drawWheel(-80, 30, 50, 0);
	drawWheel(-80, 30, -150, 0);

	glPopMatrix();
}

void OnTimer1(int value)
{
	if (speed < 1000) {
		speed += 10;
	}
	if (speed >= 1000) {
		speed = 0;
	}
	glutTimerFunc(time_interval, OnTimer1, 1);
}
void OnTimer2(int value)
{
	rs += 5;
	if (rs >= 360)
		rs = 0;
	else if (rs <= 0)
		rs = 359;
	glutTimerFunc(time_interval, OnTimer2, 2);
}


void display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, winWidth / winHeight, 5, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(fltX0 * fltZoom, fltY0 * fltZoom, fltZ0 * fltZoom, fltXRef, fltYRef, fltZRef, fltXUp, fltYUp, fltZUp);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 1, 1, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sun(20);
	car();
    drawFrame();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(landx / 2 + 2000, 2000, landZ / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-landx / 2 - 2000, 2000, landZ / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-landx / 2 - 2000, 0, landZ / 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(landx / 2 + 2000, 0, landZ / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(landx - 350, 0, landZ / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(landx - 350, 0, -landZ / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(landx - 350, 2000, -landZ / 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(landx - 350, 2000, landZ / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-landx + 350, 0, landZ / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-landx + 350, 0, -landZ / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-landx + 350, 2000, -landZ / 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-landx + 350, 2000, landZ / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(landx / 2 + 760, 2000, landZ / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(landx / 2 + 760, 2000, -landZ / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-landx / 2 - 760, 2000, -landZ / 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-landx / 2 - 760, 2000, landZ / 2);
	glEnd();
	glutSwapBuffers();
}

void displayNight() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, winWidth / winHeight, 5, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(fltX0 * fltZoom, fltY0 * fltZoom, fltZ0 * fltZoom, fltXRef, fltYRef, fltZRef, fltXUp, fltYUp, fltZUp);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sun(20);
	car();


    drawFrame();
	glutSwapBuffers();
}

void lightChange() {
	if (isNight)
	{
		isNight = false;
		lightR = 0.8;
		lightG = 0.8;
		lightB = 0.8;
		lightA = 0.8;
		lightingInitNight(lightR, lightG, lightB, lightA);
		glutDisplayFunc(display);
	}
	else
	{
		isNight = true;
		lightR = 0.5;
		lightG = 0.5;
		lightB = 0.5;
		lightA = 1;
		lightingInitNight(lightR, lightG, lightB, lightA);
		glutDisplayFunc(displayNight);
	}
	glutPostRedisplay();
}

void reshapeWindow(GLint newWinWidth, GLint newWinHeight) {
	winWidth = newWinWidth;
	winHeight = newWinHeight;
}

void keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		exit(0);
	if (key == 'z' || key == 'Z')
		if (fltZoom < 3.5)
			fltZoom += 0.1;
	if (key == 'x' || key == 'X')
		if (fltZoom > 0.2)
			fltZoom -= 0.1;
	if (key == 'a' || key == 'A') {
		Rangle += (pi / 90);
		fltX0 = 500 * cos(Rangle);
		fltZ0 = 500 * sin(Rangle);
	}
	if (key == 'd' || key == 'D') {
		Rangle -= (pi / 90);
		fltX0 = 500 * cos(Rangle);
		fltZ0 = 500 * sin(Rangle);
	}
	if (key == 'w' || key == 'W') {
		fltY0 += 20;
		if (fltY0 > 800) fltY0 = 800;
	}
	if (key == 's' || key == 'S') {
		fltY0 -= 20;
		if (fltY0 < 20) fltY0 = 20;
	}

	if (key == 'c' || key == 'C')
		lightChange();
	glutPostRedisplay();
}

void when_in_mainloop()
{ // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CPT2053D");
	lightingInit(lightR, lightG, lightB, lightA);
	textureInit();
	glutDisplayFunc(display);
	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer1, 1);
	glutTimerFunc(time_interval, OnTimer2, 2);
	glutReshapeFunc(reshapeWindow);
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();
	system("pause");
}