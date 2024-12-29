 //File ID: myCard.cpp
 //Title: My holy work
 //Author: Hongbin Zhang
#define FREEGLUT_STATIC
#include "GL/freeglut.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
//Hide the terminal windows
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
const int GL_MULTISAMPLE = 0x809D;
void define_to_OpenGL();

GLfloat w = 600;
GLfloat h = 800;
GLfloat coverStep = 0; 
GLfloat flagStep = 0;
GLfloat rotateStep = 4; // step of the planet
GLfloat rotation = 0; // initial rotate of star;
GLfloat downStep = 0; // 
GLfloat SolarRotate = 0, MercuryRotate = 0, VenusRotate = 0, EarthRotate = 0;
GLfloat starX, starY, Rs, rs = 0;

int rdm = 0; // random color value
bool downFlag = 0; // state Flag
bool starFlag = 0; // rise when a star drawn

typedef struct { GLfloat x, y; } point; // define a 2D point
point p0 = { 0, 0 }; // Inner origin
point pr = { 0, 290 }; // planet
point pCoverUp = { 0, h };
point pCoverDown = { 0, 0 };

int time_interval = 16; // declare refresh interval in ms

int starNum = 0;
typedef GLfloat star2[100];
star2 randomX = {};
star2 randomY = {};
star2 randomR = {};
star2 randomr = {};

GLint scale = 1;
GLint stepx = 0;
GLint stepy = 0;
void selectColor(int type)
{ // 1: (0, 61, 153) ultramarine 2: (28, 38, 82) supernova violet 3: (30, 44, 128) van Gogh violet
// 4: (249,104,70) Halo (dark) 5: (252,193,88) Halo (bright) 6: (42,12,88) Magenta (dark) 7: (179,0,124) Magenta (bright)
// 8: (234,139,89) Yellow (bright) 9: (255,243,127) Yellow (dark) [Change order] 10: (0,94,255) Blue (dark) 11: (44,228,214) Blue (bright)
	switch (type)
	{
	case 1: glColor3f(0.0 / 255, 61.0 / 255, 153.0 / 255);
		break;
	case 2: glColor3f(28.0 / 255, 38.0 / 255, 82.0 / 255);
		break;
	case 3: glColor3f(30.0 / 255, 44.0 / 255, 128.0 / 255);
		break;
	case 4: glColor3f(249.0 / 255, 104.0 / 255, 70.0 / 255);
		break;
	case 5: glColor3f(252.0 / 255, 193.0 / 255, 88.0 / 255);
		break;
	case 6: glColor3f(42.0 / 255, 12.0 / 255, 88.0 / 255);
		break;
	case 7: glColor3f(179.0 / 255, 0.0 / 255, 124.0 / 255);
		break;
	case 8: glColor3f(234.0 / 255, 139.0 / 255, 89.0 / 255);
		break;
	case 9: glColor3f(255.0 / 255, 243.0 / 255, 127.0 / 255);
		break;
	case 10: glColor3f(0.0 / 255, 94.0 / 255, 255.0 / 255);
		break;
	case 11: glColor3f(44.0 / 255, 228.0 / 255, 214.0 / 255);
		break;
	default:
		break;
	}
}
	
void when_in_mainloop()
{ // idle callback function
	if (scale == 0)
		scale = 1;
	glViewport(stepx, stepy, w / scale, h / scale);
	glutPostRedisplay(); // force OpenGL to redraw the current window
}
// Noted in main();
void CoverTimer(int value)
{	
	pCoverUp.y += coverStep;
	pCoverDown.y -= coverStep;
	if (pCoverUp.y == h || pCoverDown.y == 0 || pCoverDown.y == -600) coverStep = 0;
	glutTimerFunc(time_interval, CoverTimer, 1);
} 

void FlagTimer(int value)
{
	flagStep++;
	glutTimerFunc(time_interval, FlagTimer, 2);
}

void RotateTimer(int value)
{
	rotation += 20; // for the star
	if (pr.x >= w) { // for the planet
		pr.x = 0;
		pr.y = 290;
		downFlag = 0;
	}
	if (pr.y >= 350) downFlag = 1;
	if(downFlag) pr.y -= (rotateStep / 5);
	else pr.y += (rotateStep / 5);
	pr.x += rotateStep;
	glutTimerFunc(time_interval, RotateTimer, 3);
}

void ScaleTimer(int value)
{	
	if (starFlag) 
	{ // When a star is drawn
		Rs -= 2;
		if (rs > 0) rs -= 1;
		else rs = 0;
		if (Rs<=0) 
		{ 
			Rs = 0; 
			starFlag = 0; 
		}
	}
	glutTimerFunc(time_interval, ScaleTimer, 4);
}

void DownTimer(int value)
{
	downStep += 2;
	glutTimerFunc(time_interval, DownTimer, 5);
}

void LogoTimer(int value)
{
	SolarRotate += 2;
	VenusRotate += 0.9;
	MercuryRotate += 0.7;
	EarthRotate += 0.5;
	glutTimerFunc(time_interval, LogoTimer, 6);
}

void keyboard_input(unsigned char key, int x, int y) // keyboard interactions
{
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 's' || key == 'S') // stop movement
		coverStep = 0;
	else if (key == 'f' || key == 'F') // remove the cover
		coverStep = 3;
	else if (key == 'b' || key == 'B') // move back the cover
		coverStep = -3;
	else if (key == 'w' || key == 'W') // shrink the viewport
		scale++;
	else if (key == 'e' || key == 'E') // enlarge the viewport
		scale--;
}

void SpecialKey(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_UP) stepy++;  // move the viewport up
	if (key == GLUT_KEY_LEFT) stepx--; // move the viewport to the left
	if (key == GLUT_KEY_DOWN) stepy--; // move the viewport down
	if (key == GLUT_KEY_RIGHT) stepx++; // move the viewport to the right
}

void setpoint(GLint x0, GLint y0, GLint x, GLint y, int type)// draw 8 points symmetricly
{
	switch (type)
	{
	case 1: selectColor(4);
		break;
	case 2: selectColor(6);
		break;
	case 3: selectColor(9);
		break;
	case 4: selectColor(10);
		break;
	default: 
		break;
	}
	glVertex2f((x0 + x), (y0 + y));
	glVertex2f((x0 + y), (y0 + x));
	glVertex2f((x0 + y), (y0 - x));
	glVertex2f((x0 + x), (y0 - y));
	switch (type)
	{
	case 1: selectColor(5);
		break;
	case 2: selectColor(7);
		break;
	case 3: selectColor(8);
		break;
	case 4: selectColor(11);
		break;
	default: 
		break;
	}
	glVertex2f((x0 - x), (y0 - y));
	glVertex2f((x0 - y), (y0 - x));
	glVertex2f((x0 - y), (y0 + x));
	glVertex2f((x0 - x), (y0 + y));
}
// 4 sets of colors (dark color first, then light color). The first set [Halo]: (249104,70) (252193,88) The second set [Magenta]: (42,12,88) (179,0124) The third set [Yellow]: (234139,89) (255243127) The fourth set [Blue] (0,94255) (44228214)
void drawPlanet(GLint x0, GLint y0, GLint r, int type) 
{	// Draw the planet(and make it self-rotate)
	glPushMatrix(); // make it rotate around
	glTranslatef(x0, y0, 0);
	glRotatef(MercuryRotate, 0, 0, 1);
	glTranslatef(-x0, -y0, 0);
	GLint x = 0; //initial x coordinate.
	GLint y = r; //initial y coordinate.
	GLint d = 1 - r;      // to simplify the algorithm, change float to int and set 1.25 to 1 to avoid float operation. (Should be 1.25-r)
	glBegin(GL_POLYGON);
	setpoint(x0, y0, x, y, type);
	while (x < y)
	{
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		setpoint(x0, y0, x, y,type);
		glShadeModel(GL_SMOOTH);
	}
	glEnd();
	glPopMatrix();
}

void drawPlanetLines(GLint x0, GLint y0, GLint r, GLint l) 
{	//draw the lines behind the planet
	point top = { x0, y0 + r };
	point right = { x0 + r, y0 };
	point mid = { (x0 + x0 + r) / 2,(y0 + y0 + r) / 2 };
	glLineWidth(3.3);
	selectColor(5);
	glBegin(GL_LINES);
	glVertex2f(top.x, top.y); // start location
	glVertex2f(top.x + l, top.y + l); // end location
	glVertex2f(right.x, right.y);
	glVertex2f(right.x + l, right.y + l);
	glVertex2f(mid.x, mid.y);
	glVertex2f(mid.x + l*1.3, mid.y + l*1.3);
	glEnd();
}

void drawLogo() 
{	// A long series of gl function to draw the logo on the cover
	glPushMatrix();
	glTranslatef(0, -40, 0);
	glPolygonMode(GL_FRONT, GL_FILL);
	// part 1
	glBegin(GL_POLYGON);
	selectColor(2);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y-30);
	glVertex2f(pCoverUp.x + w / 2 - 100, pCoverUp.y - (30 + 70));
	glVertex2f(pCoverUp.x + w / 2 - 100, pCoverUp.y - (30 + 70 + 30));
	selectColor(3);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 100, pCoverUp.y - (30 + 70 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 100, pCoverUp.y - (30 + 70));
	glShadeModel(GL_SMOOTH);
	glEnd();

	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP); 
	glColor3f(1, 1, 1);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - 30);
	glVertex2f(pCoverUp.x + w / 2 + 100, pCoverUp.y - (30 + 70));
	glVertex2f(pCoverUp.x + w / 2 + 100, pCoverUp.y - (30 + 70 + 30));
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 - 100, pCoverUp.y - (30 + 70 + 30));
	glVertex2f(pCoverUp.x + w / 2 - 100, pCoverUp.y - (30 + 70));
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - 30);
	glEnd();
	// part 2
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	selectColor(2);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 140 - 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15)+ 20);
	selectColor(3);
	glVertex2f(pCoverUp.x + w / 2 + 140 - 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30)+ 20);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45+15)+ 25);
	selectColor(2);
	glVertex2f(pCoverUp.x + w / 2 - 140+20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30)+ 20);
	glVertex2f(pCoverUp.x + w / 2 - 140+20, pCoverUp.y - (30 + 70 + 30 + 15 + 15)+ 20);
	glShadeModel(GL_SMOOTH);
	glEnd();

	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 140 - 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15) + 20);
	glVertex2f(pCoverUp.x + w / 2 + 140 - 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30) + 20);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 25);
	glVertex2f(pCoverUp.x + w / 2 - 140 + 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30) + 20);
	glVertex2f(pCoverUp.x + w / 2 - 140 + 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15) + 20);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glEnd();
	// part 3 
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 110, pCoverUp.y - (30 + 70 + 30 + 15) + 10);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30) + 10);
	glVertex2f(pCoverUp.x + w / 2 - 110, pCoverUp.y - (30 + 70 + 30 + 15) + 10);
	glShadeModel(GL_SMOOTH);
	glEnd();

	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 110, pCoverUp.y - (30 + 70 + 30 + 15) + 10);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30) + 10);
	glVertex2f(pCoverUp.x + w / 2 - 110, pCoverUp.y - (30 + 70 + 30 + 15) + 10);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glEnd();
	// part 4 planet
	glPushMatrix(); // make it rotate around
	glTranslatef((pCoverUp.x + w / 2), (pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	glRotatef(SolarRotate, 0, 0, 1);
	glTranslatef(-(pCoverUp.x + w / 2), -(pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	drawPlanet(pCoverUp.x + w / 2, pCoverUp.y - (30 + 70 + 30 + 17), 20 ,1);   // Solar
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); 
	drawPlanet(pCoverUp.x + w / 2, pCoverUp.y - (30 + 70 + 30 + 17), 30 , 4); // circle 1

	glPushMatrix(); // make it rotate around
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef((pCoverUp.x + w / 2), (pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	glRotatef(MercuryRotate, 0, 0, 1);
	glTranslatef(-(pCoverUp.x + w / 2), -(pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	drawPlanet(pCoverUp.x + w / 2 + 27, pCoverUp.y - (30 + 70 + 30 + 20) + 16, 5, 2); // Mercury
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	drawPlanet(pCoverUp.x + w / 2, pCoverUp.y - (30 + 70 + 30 + 17), 40 + 10, 4); // circle 2
	
	glPushMatrix(); // make it rotate around
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef((pCoverUp.x + w / 2), (pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	glRotatef(VenusRotate, 0, 0, 1);
	glTranslatef(-(pCoverUp.x + w / 2), -(pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	drawPlanet(pCoverUp.x + w / 2 + 35, pCoverUp.y - (30 + 70 + 30 + 20 + 30), 9, 4); // Venus
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	drawPlanet(pCoverUp.x + w / 2, pCoverUp.y - (30 + 70 + 30 + 17), 60 + 10, 4); // circle 3

	glPushMatrix(); // make it rotate around
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef((pCoverUp.x + w / 2), (pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	glRotatef(EarthRotate, 0, 0, 1);
	glTranslatef(-(pCoverUp.x + w / 2), -(pCoverUp.y - (30 + 70 + 30 + 17)), 0);
	drawPlanet(pCoverUp.x + w / 2 + 45, pCoverUp.y - (30 + 70 + 30 ) + 36, 13, 4); // Earth
	
	glPushMatrix(); // make it rotate around
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef((pCoverUp.x + w / 2 + 45), (pCoverUp.y - (30 + 70 + 30) + 36), 0);
	glRotatef(MercuryRotate*3, 0, 0, 1);
	glTranslatef(-(pCoverUp.x + w / 2 + 45), -(pCoverUp.y - (30 + 70 + 30) + 36), 0);
	drawPlanet(pCoverUp.x + w / 2 + 47, pCoverUp.y - (30 + 70 + 30 + 24) + 47, 5, 3); // Noon
	glPopMatrix();


	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glColor3f(1, 1, 1);
	glPointSize(3);
	drawPlanet(pCoverUp.x + w / 2, pCoverUp.y - (30 + 70 + 30 + 17), 75 + 10, 0); // circle 4
	glPointSize(2);
	// part5 - arrow
	GLfloat points0[3][3] = 
	{ // Curve --- Bezier Curve
		{pCoverUp.x + w / 2 - 40, pCoverUp.y - (170 + 30 + 30 + 30) + 10 + 25, 0.0},
		{300, pCoverUp.y - 180, 0.0},
		{pCoverUp.x + w / 2 - 10, pCoverUp.y - (30 + 30) - 5, 0.0}
	};
	GLfloat points1[3][3] = 
	{ // set control points
		{pCoverUp.x + w / 2 + 40, pCoverUp.y - (170 + 30 + 30 + 30) + 10 + 25, 0.0},
		{300, pCoverUp.y - 180, 0.0},
		{pCoverUp.x + w / 2 + 10, pCoverUp.y - (30 + 30) - 5, 0.0}
	};
	glEnable(GL_MAP1_VERTEX_3);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &points0[0][0]);	
	selectColor(3);
	for (int m = 0; m < 10; m++) 
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i <= 200; i++)
			glEvalCoord1f((GLfloat)i / 200.0);
		glEnd();
		glTranslatef(1, -1, 0);
	}

	glTranslatef(-10, 10, 0); // Reset the matrix
	glColor3f(1, 1, 1);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);	// white boundary
	for (int i = 0; i <= 200; i++) glEvalCoord1f((GLfloat)i / 200.0);
	glEnd();
	// Other side
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &points1[0][0]);
	selectColor(3);
	for (int m = 0; m < 10; m++) 
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i <= 200; i++)
			glEvalCoord1f((GLfloat)i / 200.0);
		glEnd();
		glTranslatef(-1, -1, 0);
	}

	glTranslatef(10, 10, 0);
	glColor3f(1, 1, 1);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);	// white boundary
	for (int i = 0; i <= 200; i++)
		glEvalCoord1f((GLfloat)i / 200.0);
	glEnd();
	// Lines below
	glLineWidth(3.0);
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP); 
	glVertex2f(pCoverUp.x + w / 2 + 140 - 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30) + 30);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 35);
	glVertex2f(pCoverUp.x + w / 2 - 140 + 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30) + 30);
	glEnd();
	// Lines below 2
	glBegin(GL_LINE_STRIP); 
	glVertex2f(pCoverUp.x + w / 2 + 140 - 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30) + 20);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 25);
	glVertex2f(pCoverUp.x + w / 2 - 140 + 20, pCoverUp.y - (30 + 70 + 30 + 15 + 15 + 30) + 20);
	glEnd();
	selectColor(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Fill land
	glBegin(GL_POLYGON); 
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 70 + 30 + 17));
	glVertex2f(pCoverUp.x + w / 2 + 25, pCoverUp.y - (170 + 30 + 30 + 30) + 10 + 20);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 40);
	glVertex2f(pCoverUp.x + w / 2 - 25, pCoverUp.y - (170 + 30 + 30 + 30) + 10 + 20);
	glEnd();
	// Arrow head
	glBegin(GL_POLYGON); 
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30));
	glVertex2f(pCoverUp.x + w / 2 - 25, pCoverUp.y - (30 + 30 + 20));
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 25, pCoverUp.y - (30 + 30 + 20));
	glEnd();
	glLineWidth(3.0);
	glColor3f(1, 1, 1);
	// Arrow head boundary
	glBegin(GL_LINE_STRIP); 
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30));
	glVertex2f(pCoverUp.x + w / 2 - 25, pCoverUp.y - (30 + 30 + 20));
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30 + 30));
	glVertex2f(pCoverUp.x + w / 2 + 25, pCoverUp.y - (30 + 30 + 20));
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (30));
	glEnd();
	// part 6 
	glTranslatef((pCoverUp.x + w / 2)*0.3, (pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70)*0.3, 0);// move back
	glScalef(0.7,0.7,0); // scale down the coordinate
	glColor3f(1, 1, 1);// central: pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70
	glBegin(GL_POLYGON); // quadrilateral up
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 + 3);
	glVertex2f(pCoverUp.x + w / 2 + 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 + 10);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 105 + 3);
	glVertex2f(pCoverUp.x + w / 2 - 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 + 10);
	glEnd();

	glBegin(GL_POLYGON); // quadrilateral down
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 47);
	glVertex2f(pCoverUp.x + w / 2 + 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 60);
	glVertex2f(pCoverUp.x + w / 2, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 67);
	glVertex2f(pCoverUp.x + w / 2 - 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 60);
	glEnd();

	glBegin(GL_POLYGON); // quadrilateral left
	glVertex2f(pCoverUp.x + w / 2 - 3, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70);
	glVertex2f(pCoverUp.x + w / 2 - 3 - 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 + 7);
	glVertex2f(pCoverUp.x + w / 2 - 3 - 20, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 );
	glVertex2f(pCoverUp.x + w / 2 - 3 - 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 - 7 );
	glEnd();

	glBegin(GL_POLYGON); // quadrilateral right
	glVertex2f(pCoverUp.x + w / 2 + 3, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70);
	glVertex2f(pCoverUp.x + w / 2 + 3 + 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 + 7);
	glVertex2f(pCoverUp.x + w / 2 + 3 + 20, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70);
	glVertex2f(pCoverUp.x + w / 2 + 3 + 7, pCoverUp.y - (170 + 30 + 30 + 45 + 15) + 70 - 7);
	glEnd();

	glPopMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h); // rebuild the coordinate
	glPointSize(2);
 }

void plotText(GLfloat x0, GLfloat y0, const char* str) 
{
 int length = strlen(str); // Plot the text in *str
 for (int m = 0; m <= 4; m++) 
 {
	 switch (m)
	 {
	 case 0:
		 glColor3f(0, 0, 0);
		 glRasterPos2i(x0, y0 - 2);
		 for (int i = 0; i < length; i++)
			 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(str + i));
	 case 1:
		 glColor3f(0, 0, 0);
		 glRasterPos2i(x0 - 2, y0);
		 for (int i = 0; i < length; i++)
			 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(str + i));
	 case 2:
		 glColor3f(0, 0, 0);
		 glRasterPos2i(x0 + 2, y0);
		 for (int i = 0; i < length; i++)
			 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(str + i));
	 case 3:
		 glColor3f(0, 0, 0);
		 glRasterPos2i(x0, y0 + 2);
		 for (int i = 0; i < length; i++)
			 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(str + i));
	 case 4:
		 glColor3f(1, 1, 1);
		 glRasterPos2i(x0, y0);
		 for (int i = 0; i < length; i++)
			 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(str + i));
	 default:
		 break;
		}
	}
 }

void drawFlag(GLfloat x0, GLfloat y0, GLfloat length, int type) 
{ // Draw a Flag using math function
	GLfloat x1, y1;
	glBegin(GL_QUAD_STRIP);
	for (GLfloat i = x0; i <= x0 + length; i = i + 1)
	{
		x1 = i;
		y1 = 10.0 * sin((i + flagStep) / (10.0)) + y0;
		if(type==0) selectColor(7);
		else selectColor(11);
		glVertex2f(x1, y1 - 20);
		if (type == 0) selectColor(6);
		else selectColor(10);
		glVertex2f(x1, y1 + 10);
	}
	glEnd();
}

void drawStar(float cx, float cy, float R, float r, float o)
{//Central coordinates of pentagon x, y, big circle radius R, small circle radius r, initial angle o.
	float x0, y0, x1, y1;
	float o0 = o;
	float o1 = o + 0.2 * 3.14;
	
	for (int i = 0; i < 10; i++)
	{	
		x0 = cx + R * cos(o0);
		y0 = cy + R * sin(o0);
		x1 = cx + r * cos(o1);
		y1 = cy + r * sin(o1);
		if (i % 2 == 0) selectColor(rdm);
		else
		{
			if (rdm % 2 == 0) selectColor(rdm + 1);
			else selectColor(rdm - 1);
		}
		glBegin(GL_POLYGON);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glVertex2f(cx, cy);
		glEnd();
		if (i % 2 == 0) o0 = o0 + 0.4 * 3.14;
		else o1 = o1 + 0.4 * 3.14;
	}
}

void drawStarBack(float cx, float cy, float R, float r, float o)
{//Central coordinates of pentagon x, y, big circle radius R, small circle radius r, initial angle o.
	float x0, y0, x1, y1;
	float o0 = o;
	float o1 = o + 0.2 * 3.14;

	for (int i = 0; i < 10; i++)
	{
		x0 = cx + R * cos(o0);
		y0 = cy + R * sin(o0);
		x1 = cx + r * cos(o1);
		y1 = cy + r * sin(o1);
		if (i % 2 == 0) glColor3f(1, 1, 1);
		else
		{
			glColor3f(248.0/255, 250.0/255, 237.0/255);
		}
		glBegin(GL_POLYGON);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glVertex2f(cx, cy);
		glEnd();
		if (i % 2 == 0) o0 = o0 + 0.4 * 3.14;
		else o1 = o1 + 0.4 * 3.14;
	}
}

void drawRandomStar() {
	GLfloat starXB = 0, starYB = 0, starRB = 0, starrB = 0; //parameters for stars in back ground

	/* Generate random number of stars */
	if (starNum < 50) {
		/* This will store 100 stars' location to a data array. */
		for (starNum = 0; starNum < 50; starNum++) {

			starXB = rand() % 550 + 20;
			starYB = rand() % 750 + 20;
			starRB = rand() % 5 + 10;
			starrB = starRB / 3;

			randomX[starNum] = { starXB };
			randomY[starNum] = { starYB };
			randomR[starNum] = { starRB };
			randomr[starNum] = { starrB };
		}
	}
	else {
		/* This will draw 100 stars on the screen */
		for (int i = 0; i < starNum; i++) {
			glPushMatrix();
			drawStarBack(randomX[i], randomY[i] - downStep, randomR[i], randomr[i], rotation);
			if (randomY[i] - downStep <= 0) randomY[i] = 800 + downStep;
				
			glPopMatrix();
		}
	}


	
}

void mouse_input(int button, int state, int x, int y) 
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) // click down to draw a star
	{
		rdm = rand() % 10 + 2;
		starFlag = 1;
		starX = x;
		starY = h - y;
		Rs = 30;
		rs = 10;
		glutSwapBuffers();
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) // click down to draw a bigger star
	{	
		rdm = rand() % 10 + 2; //random from 3 to 11
		starFlag = 1;
		starX = x;
		starY = h - y;
		Rs = 50;
		rs = 20;
		glutSwapBuffers();
	}
}
////////////////////////////////
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffer mode
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("New Year's Greeting Card from USSG");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h); // rebuild the coordinate
	
	glutDisplayFunc(define_to_OpenGL);
	glutTimerFunc(time_interval, CoverTimer, 1); // Timer of Cover
	glutTimerFunc(time_interval, FlagTimer, 2); // Timer of Flags
	glutTimerFunc(time_interval, RotateTimer, 3); // Timer of Rotation
	glutTimerFunc(time_interval, ScaleTimer, 4);// Timer of Scale of the stars
	glutTimerFunc(time_interval, DownTimer, 5); // Timer of the dropping down of the stars
	glutTimerFunc(time_interval, LogoTimer, 6); // Timer of the plant of logo
	
	glutSpecialFunc(SpecialKey); // special keyboard callback function
	glutKeyboardFunc(keyboard_input); // keyboard callback function
	glutMouseFunc(mouse_input); // mouse act callback function
	glEnable(GL_MULTISAMPLE); // MSAA
	glutIdleFunc(when_in_mainloop);
	glutMainLoop();
	return 0;
}

void define_to_OpenGL()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	/*Inneer section*/
	glBegin(GL_POLYGON); // background
	selectColor(1);
	glVertex2f(0, 0);
	selectColor(2);
	glVertex2f(0, h);
	selectColor(3);
	glVertex2f(w, h);
	selectColor(3);
	glVertex2f(w, 0);
	glShadeModel(GL_SMOOTH);
	glEnd();

	drawPlanet(w / 2, - (h / 2), 250 + (h / 2), 1); //surface
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(3.0);
	drawPlanet(w / 2, -(h / 2), 350 + (h / 2), 3); //circle
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawPlanet(pr.x, pr.y, 30, 4); //planet
	// lines 1
	GLfloat strip = 40;	GLfloat len = 40;
	selectColor(11);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(p0.x + strip, p0.y + strip + len);
	glVertex2f(p0.x + strip + len, p0.y + strip);
	glVertex2f(p0.x + strip, h - (p0.y + strip + len));
	glVertex2f(p0.x + strip + len, h - (p0.y + strip));
	glVertex2f(p0.x + strip, h - (p0.y + strip + len + strip));
	glVertex2f(p0.x + strip, p0.y + strip + len + strip);
	glVertex2f(p0.x + strip + len + strip, h - (p0.y + strip));
	glVertex2f(w - (p0.x + strip + len + strip), h - (p0.y + strip));
	glVertex2f(p0.x + strip + len + strip, p0.y + strip);
	glVertex2f(w - (p0.x + strip + len + strip), p0.y + strip);
	glEnd();
	// Filp
	glPushMatrix();
	glTranslatef(w, 0 ,0);
	glScalef(-1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(p0.x + strip, p0.y + strip + len);
	glVertex2f(p0.x + strip + len, p0.y + strip);
	glVertex2f(p0.x + strip, h - (p0.y + strip + len));
	glVertex2f(p0.x + strip + len, h - (p0.y + strip));
	glVertex2f(p0.x + strip, h - (p0.y + strip + len + strip));
	glVertex2f(p0.x + strip, p0.y + strip + len + strip);
	glEnd();
	glPopMatrix();
	// lines 2
	GLfloat strip2 = 40; GLfloat len2 = 60;
	selectColor(11);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(p0.x + strip2, p0.y + strip2 + len2);
	glVertex2f(p0.x + strip2 + len2, p0.y + strip2);
	glVertex2f(p0.x + strip2, h - (p0.y + strip2 + len2));
	glVertex2f(p0.x + strip2 + len2, h - (p0.y + strip2));
	glEnd();
	// Flip
	glPushMatrix();
	glTranslatef(w, 0, 0);
	glScalef(-1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(p0.x + strip2, p0.y + strip2 + len2);
	glVertex2f(p0.x + strip2 + len2, p0.y + strip2);
	glVertex2f(p0.x + strip2, h - (p0.y + strip2 + len2));
	glVertex2f(p0.x + strip2 + len2, h - (p0.y + strip2));
	glEnd();
	glPopMatrix();
	// Stairs
	selectColor(11);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(w / 2 - 60 - 8, 340); //Stairs left
	glVertex2f(p0.x + strip + len + strip + 10 , (p0.y + strip) + 30); // Bottom left
	glVertex2f(w / 2 + 60 + 8, 340); //Stairs right
	glVertex2f(w - (p0.x + strip + len + strip + 10), (p0.y + strip) + 30); // Bottom right
	glEnd(); 

	GLfloat dx = 0.1; GLfloat dy = 0.25; // decrease stripe of each stair's h and w.
	GLfloat sx = 12; GLfloat sy = 30; // initial step of h and w of each stair
	GLfloat ybegin = (p0.y + strip) + 30 + 3; // initial y location
	for (int  x = p0.x + 12 + strip + len + strip; x <= w / 2 - 60; x += sx) 
	{// loop for Stairs
		glColor3f(248.0 / 255, 246.0 / 255, 231.0 / 255);
		glBegin(GL_POLYGON);
		glVertex2f(x, ybegin);
		glVertex2f(w - x, ybegin);
		glVertex2f(w - x, ybegin - sy);
		glVertex2f(x, ybegin - sy);
		
		glEnd();
		glColor3f(0, 0, 0);
		glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(x, ybegin);
		glVertex2f(x, ybegin - sy);
		glVertex2f(w - x, ybegin - sy);
		glVertex2f(w - x, ybegin);
		glVertex2f(x, ybegin);
		glEnd();
		ybegin += sy;
		sx -= dx;
		sy -= dy;
	} 
	// Flags
	glLineWidth(9.0); 
	glColor3f(248.0 / 255, 246.0 / 255, 231.0 / 255);
	glBegin(GL_LINES);
	glVertex2f(w / 2 - 60 + 5, 340 - 5); 
	glVertex2f(w / 2 - 60 + 5, 400); 
	glVertex2f(w / 2 + 60 - 5, 340 - 5); 
	glVertex2f(w / 2 + 60 - 5, 400); 
	glVertex2f(w / 2, 340 - 5); 
	glVertex2f(w / 2, 430); 
	glEnd();
	drawFlag(w / 2 - 60 + 5, 400 - 5 - 12, 35, 0);
	drawFlag(w / 2 + 60 - 5 , 400 - 5 - 12, 35, 0);
	drawFlag(w / 2, 430 - 5 - 12, 45, 1); 
	// Plot Text
	plotText((p0.x + strip + len + 12), h - (p0.y + strip + 50), " From the cradle of early civilization to the");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 80), "vastness of the stars, mankind has experienced much. ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 110), "Since the beginning of the space age, we have");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 140), "explored, exploited, and planted our flag on new planets. ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 170), "Now, with the arrival of the New Year on USSG's ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 200), "home planet, Earth, our civilization's Venus colony ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 230), "is officially complete. With pride, joy and our blessings, ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 260), "this greeting card is broadcast to the entire solar system, ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 290), "allowing the stars to witness the glory of humanity ");
	plotText((p0.x + strip + len + 8), h - (p0.y + strip + 320), "and shine on the future.");
	plotText((p0.x + strip + len + 12), h - (p0.y + strip + 350), "	May the happiness and glory be with you!");
	plotText(w / 2 - 10, h - (p0.y + strip + 400), " -- USSG Publicity Department");
	plotText(w / 2 + 40, h - (p0.y + strip + 430), " 2123 - 1 - 1 (Earth BC)");
	// Cover - head
	glPolygonMode(GL_FRONT, GL_FILL); // Set the front side(counterclockwise) as the FILL drawing mode
	glBegin(GL_POLYGON);
	selectColor(1);
	glVertex2f(pCoverUp.x, pCoverUp.y-h/3 + 70 - 70 + 10);
	selectColor(2);
	glVertex2f(pCoverUp.x + (w/2), pCoverUp.y-h*2/3+50 + 70 - 70 + 10);
	selectColor(3);
	glVertex2f(pCoverUp.x + w, pCoverUp.y-h/3 + 70 - 70 + 10);
	selectColor(3);
	glVertex2f(pCoverUp.x + w, pCoverUp.y);
	selectColor(1);
	glVertex2f(pCoverUp.x, pCoverUp.y);
	glShadeModel(GL_SMOOTH); 
	glEnd();

	glLineWidth(4.0);
	glPolygonMode(GL_BACK, GL_LINE); // Set the reverse side (clockwise) as the LINE drawing mode
	glColor3f(0, 0, 0); 
	glBegin(GL_POLYGON);
	glVertex2f(pCoverUp.x, pCoverUp.y);
	glVertex2f(pCoverUp.x + w, pCoverUp.y);
	glVertex2f(pCoverUp.x + w, pCoverUp.y - h / 3 + 70-70+ 10);
	glVertex2f(pCoverUp.x + (w / 2), pCoverUp.y - h * 2 / 3 + 50 + 70 - 70 + 10);
	glVertex2f(pCoverUp.x, pCoverUp.y - h / 3 + 70 - 70 + 10);
	glEnd();

	// Cover - bottom
	glPolygonMode(GL_FRONT, GL_FILL); // Set the front side(counterclockwise) as the FILL drawing mode
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	selectColor(1);
	glVertex2f(pCoverDown.x + w / 2, pCoverDown.y + h / 3 + 70);
	selectColor(1);
	glVertex2f(pCoverDown.x, pCoverDown.y + h * 2 / 3 - 50 + 70);
	selectColor(2);
	glVertex2f(pCoverDown.x, pCoverDown.y);
	selectColor(3);
	glVertex2f(pCoverDown.x + w, pCoverDown.y);
	selectColor(3);
	glVertex2f(pCoverDown.x + w, pCoverDown.y + h * 2 / 3 - 50 + 70);
	glShadeModel(GL_SMOOTH);
	glEnd();

	glLineWidth(4.0);
	glPolygonMode(GL_BACK, GL_LINE); // Set the reverse side (clockwise) as the LINE drawing mode
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(pCoverDown.x, pCoverDown.y);
	glVertex2f(pCoverDown.x, pCoverDown.y + h*2/3-50 + 70);
	glVertex2f(pCoverDown.x + w/2, pCoverDown.y + h/3 + 70);
	glVertex2f(pCoverDown.x + w, pCoverDown.y + h * 2 / 3 - 50 + 70);
	glVertex2f(pCoverDown.x + w, pCoverDown.y);
	glEnd();
	// Draw plantes on the cover
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawPlanet(pCoverUp.x + 100, pCoverUp.y - 100, 35, 2); // 1
	drawPlanet(pCoverUp.x + 50, pCoverUp.y - 150, 20, 4); // 2
	drawPlanet(pCoverUp.x + 590, pCoverUp.y - 100, 23, 4); // 3
	drawPlanetLines(pCoverUp.x + 470, pCoverUp.y - 180, 12, 35); // 4
	drawPlanet(pCoverUp.x + 470, pCoverUp.y - 180, 12,4);
	drawPlanetLines(pCoverUp.x + 510, pCoverUp.y - 80, 8, 23); // 5
	drawPlanet(pCoverUp.x + 510, pCoverUp.y - 80, 8,3);
	drawPlanet(pCoverDown.x + 10, pCoverDown.y + 250, 40,2); // 6
	drawPlanet(pCoverDown.x + 130, pCoverDown.y, 25,4); // 7
	drawPlanet(pCoverDown.x + 30, pCoverDown.y + 90, 15,1); // 8
	drawPlanet(pCoverDown.x + 60, pCoverDown.y + 150, 9,4); // 9
	drawPlanet(pCoverDown.x + 550, pCoverDown.y + 40, 110, 1); // 10
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	selectColor(5);
	glPointSize(15);
	drawPlanet(pCoverDown.x + 550, pCoverDown.y + 40, 135, 0); // 10(*) 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawPlanet(pCoverDown.x + 540, pCoverDown.y + 240, 50, 4); // 11
	drawPlanet(pCoverDown.x + 585, pCoverDown.y + 220, 37, 2); // 12
	drawPlanetLines(pCoverDown.x + 390, pCoverDown.y + 140, 9, 20); // 13
	drawPlanet(pCoverDown.x + 390, pCoverDown.y + 140, 9, 1); // 14

	glPointSize(2); // reset the options
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1, 1, 1);
	drawLogo(); // Draw the logo
	// Text
	plotText(165, pCoverUp.y - (350), "Unified Solar System Government");
	plotText(220, pCoverUp.y - (380), "Publicity Department");
	plotText(90, pCoverDown.y + (280), "Press [F] to recive your New Earth Year's greeting card,");
	plotText(230, pCoverDown.y + (230), "From the galaxy.");

	drawStar(starX, starY, Rs, rs, rotation); // initiate star
	drawRandomStar();
	glutSwapBuffers();
}