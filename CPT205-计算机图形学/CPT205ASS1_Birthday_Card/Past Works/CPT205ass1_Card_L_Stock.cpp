// File ID: NewYearCard.cpp
// Title: Happy New Year!
// Author: L_Stock
#define FREEGLUT_STATIC
#define PI 3.14159265
#include <GL/freeglut.h>
#include <iostream>

GLint time_interval = 3;         																       // the time interval
GLfloat viewPortx = 0, viewPorty = 0, viewPWidth = 1280;					                           // the location and size of the viewport
GLfloat viewPxStep = 0, viewPyStep = 0, viewPWStep = 0;												   // steps of the viewport's location and size
GLfloat Color = 0, ColorStep = 0;																	   // the color of the words
GLfloat star = 292, starRotate = 0, starStep = 0, starRotateStep = 0.03;						       // location and step of the stars
GLfloat fwStart = -450, fwStartSize = 3, fwSStep = 0, fwSSStep = 0;								       // starting point, its size and step of the starting flame in a firework
GLfloat flameLength = -50, flameSize = -4, deFlameLength = 0, deFlameSize = 0;					       // length and size of the flame
GLfloat flameLStep = 0, flameSStep = 0, deFlameLStep = 0, deFlameSStep = 0;						       // steps of length and size above

void display(void);
void GL_CIRCLE(float x, float y, float r, int n);													   // draw a circle
void GL_ELLIPSE(float x, float y, float longr, float shortr, int n);								   // draw a ellipse
void GL_STAR(float x, float y, float longr, float degree);											   // draw a star
void GL_LEAVES(float x, float y, float size, float light);										       // draw some leaves with snow
void GL_TREE(float x, float y, float size, float light);										       // draw a tree
void GL_FLAME(float startx, float starty, float endx, float endy, float size);					       // draw a piece of flame
void GL_FIREWORK(float x, float y);																       // draw a firework
void selectFont(int size, int charset, const char* face);										       // select the font
void keyboard_input(unsigned char key, int x, int y);											       // keyboard interaction
void mouse_input(int button, int state, int x, int y);											       // mouse interactions
void when_in_mainloop();																		       // idle callback function
void OnTimer(int value);

int main(int argc, char** argv)
{
    // make sure the window is big enough and set its location in the screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - 640, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 360);
    glutInitWindowSize(1280, 720);

    // create the window
    glutCreateWindow("Happy New Year!");
    glutDisplayFunc(display);
    glutIdleFunc(when_in_mainloop);
    glutTimerFunc(time_interval, OnTimer, 1);
    glutKeyboardFunc(keyboard_input);
    glutMouseFunc(mouse_input);
    glutMainLoop();
}

// to display the figures onto the screen
void display(void)
{
    // initialization
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // to draw a background with color transiting smoothly from dark blue to black
    glBegin(GL_QUADS);
    // one quad
    glColor3f(0, 0, 0.2);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glColor3f(0, 0, 0.06);
    glVertex2f(800, 300);
    glVertex2f(0, 300);
    // the other quad
    glColor3f(0, 0, 0.06);
    glVertex2f(0, 300);
    glVertex2f(800, 300);
    glColor3f(0, 0, 0);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();

    // the moon, it is made up of two circles, between which one is black and the other is white.
    glColor3f(1, 0.985, 0.88);
    GL_CIRCLE(100, 460, 70, 40);
    glColor3f(0, 0, 0.04);
    GL_CIRCLE(80, 480, 75, 40);

    // strings for greeting
    glColor3f(PixelColor, PixelColor, PixelColor + 0.045);
    selectFont(256, ANSI_CHARSET, "Times New Roman");
    glRasterPos2f(207, 310);
    static int isFirstCall = 1;
    static GLuint lists;
    if (isFirstCall) {
        isFirstCall = 0;
        lists = glGenLists(256);
        wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, lists);
    }
    const char* str = "2 0 2 3";
    for (; *str != '\0'; ++str) {
        glCallList(lists + *str);
    }
    glColor3f(PixelColor, PixelColor, PixelColor + 0.08);
    glRasterPos2f(277, 265);
    for (const char* c = "GREETINGS FOR THE NEW YEAR !"; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    // firework
    GL_FIREWORK(400, 400);
    GL_FIREWORK(150, 350);
    GL_FIREWORK(650, 350);

    // seven stars
    GL_STAR(350, 380 + star, 13, -30);
    GL_STAR(430, 455 + star, 13, 80);
    GL_STAR(500, 440 + star, 13, -30);
    GL_STAR(600, 435 + star, 13, 80);
    GL_STAR(640, 330 + star, 13, -30);
    GL_STAR(760, 350 + star, 13, 80);
    GL_STAR(765, 510 + star, 13, -30);

    // green trees on the snow land
    GL_TREE(50, 95, 65, 0.7);
    GL_TREE(110, 70, 55, 0.5);
    GL_TREE(150, 90, 70, 0.85);
    glColor3f(0.91, 0.91, 0.96);
    GL_ELLIPSE(260, -10, 170, 60, 50);
    glColor3f(0.95, 0.95, 1);
    GL_ELLIPSE(0, -20, 260, 110, 60);
    GL_TREE(80, 100, 80, 1);
    GL_TREE(300, 60, 70, 0.9);

    // do you want to build a snowman
    glColor3f(0.93, 0.93, 0.97);
    GL_ELLIPSE(705, 60, 65, 60, 40);
    glColor3f(0.95, 0.95, 1);
    GL_ELLIPSE(709, 160, 44, 40, 40);
    glColor3f(0, 0, 0);
    GL_ELLIPSE(720, 165, 4, 6, 20);
    GL_ELLIPSE(680, 165, 3, 4.5, 20);
    glRasterPos2f(694.5, 143);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'v');
    glColor3f(0, 0.5, 0.8);
    for (float i = -2 * PI / 3; i <= -PI / 3; i += 0.05)
        GL_CIRCLE(709 + 83 * cos(i), 189 + 75 * sin(i), 8, 20);
    glBegin(GL_QUADS);
    glVertex2f(739, 130);
    glVertex2f(749, 130);
    glVertex2f(770, 102);
    glVertex2f(756, 90);
    glEnd();

    glutSwapBuffers();
}

// to draw a circle, the location of the center of which and the radius are required
// it is worth noticing that: when the polygon has enough sides, it is difficult to distinguish it from the circle
// so a positive integer n is given to set the number of sides.
void GL_CIRCLE(float x, float y, float r, int n)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) glVertex2f(x + r * cos(2 * PI / n * i), y + r * 4 / 3 * sin(2 * PI / n * i));
    glEnd();
}

// draw a ellipse, the principle of which is similar to that of drawing a circle
void GL_ELLIPSE(float x, float y, float longr, float shortr, int n)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) glVertex2f(x + longr * cos(2 * PI / n * i), y + shortr * 4 / 3 * sin(2 * PI / n * i));
    glEnd();
}

// to draw a star, broken the star into 10 triangles and draw them one by one.
// Rotation matrixs are utilized to set the deviation angle.
void GL_STAR(float x, float y, float longr, float degree)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1, 1.333, 0);
    glRotatef(degree + starRotate, 0, 0, 1);
    glScalef(1, 0.75, 0);
    glTranslatef(-x, -y, 0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; i++) {
        glColor3f(1, 0.93, 0.6);
        glVertex2f(x, y);
        glColor3f(0.72, 0.6, 0);
        glVertex2f(x + longr / 2 * cos(2 * PI / 5 * (i - 1.0) + PI / 5), y + longr / 2 * 4 / 3 * sin(2 * PI / 5 * (i - 1.0) + PI / 5));
        glColor3f(0.82, 0.7, 0);
        glVertex2f(x + longr * cos(2 * PI / 5 * i), y + longr * 4 / 3 * sin(2 * PI / 5 * i));
    }
    for (int i = 0; i < 5; i++) {
        glColor3f(1, 0.93, 0.6);
        glVertex2f(x, y);
        glColor3f(0.72, 0.6, 0);
        glVertex2f(x + longr / 2 * cos(2 * PI / 5 * i + PI / 5), y + longr / 2 * 4 / 3 * sin(2 * PI / 5 * i + PI / 5));
        glColor3f(0.82, 0.7, 0);
        glVertex2f(x + longr * cos(2 * PI / 5 * i), y + longr * 4 / 3 * sin(2 * PI / 5 * i));
    }
    glEnd();
    glPopMatrix();
}

// to draw some leaves with snow on them
void GL_LEAVES(float x, float y, float size, float light)
{
    // leaves
    glBegin(GL_POLYGON);
    glColor3f(0.35 * light, 0.54 * light, 0.23 * light);
    glVertex2f(x, y + size / 10);
    glColor3f(0.22 * light, 0.34 * light, 0.14 * light);
    glVertex2f(x, y - size);
    glVertex2f(x - size / 9, y - size * 13 / 9);
    glVertex2f(x - size / 5, y - size);
    glVertex2f(x - size * 2 / 3, y - size * 14 / 9);
    glVertex2f(x - size * 5 / 9, y - size);
    glVertex2f(x - size, y - size * 9 / 8);
    glEnd();

    // and snow on them. Snow has two layers, the upper one is white while the lower one is grey.
    float t = 0;
    glColor3f(0.5 * light, 0.5 * light, 0.5 * light);
    for (int i = 0; i < 8; i++) {
        GL_CIRCLE(x - size * 5 / 8 + i * size / 14,							                           // x
                  y - size * 7 / 10 + i * size / 60 - pow(-1, i) * size / 25 + t,                            // y
                  size / 10, 														                           // r
                  (int)(size / 2));												                           // n
        if (i == 4) t = size / 16;
    }
    t = 0;
    glColor3f(0.95 * light, 0.95 * light, light);
    for (int i = 0; i < 8; i++) {
        GL_CIRCLE(x - size * 5 / 8 + i * size / 14,							                           // x
                  y - size * 2 / 3 + i * size / 60 - pow(-1, i) * size / 25 + t,                             // y
                  size / 10, 														                           // r
                  (int)(size / 2));												                           // n
        if (i == 4) t = size / 16;
    }
}

// to draw a tree, a tree is made up of 6 pieces of leaves
void GL_TREE(float x, float y, float size, float light)
{
    // the brown trunk
    glColor3f(0.4 * light, 0.16 * light, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y - size / 25);
    glColor3f(0.5 * light, 0.25 * light, 0);
    glVertex2f(x + size / 12, y);
    glVertex2f(x + size / 20, y + size * 4 / 5);
    glVertex2f(x - size / 20, y + size * 4 / 5);
    glVertex2f(x - size / 12, y);
    glEnd();
    float localsize = size / 9;

    // the white snow and the green leaves
    for (int i = 0; i < 3; i++) {
        GL_LEAVES(x,																	               // x
                  y + size * 5 / 4 + i * size * 2 / 5 - pow(i / 2, 2) * size / 6,                            // y
                  size * 2 / 3 - i * size / 6,												               // size
                  light + light * i / 6);					   									               // light
        glPushMatrix();
        glTranslatef(x, 0, 0);
        glScalef(-1, 1, 0);
        glTranslatef(-x, 0, 0);
        GL_LEAVES(x,																	               // x
                  y + size * 5 / 4 + i * size * 2 / 5 - pow(i / 2, 2) * size / 6,   			               // y
                  size * 2 / 3 - i * size / 6,												               // size
                  light + light * i / 6);					   									               // light
        glPopMatrix();
    }
}

// to draw a flame. It uses a triangle fan to imitate a circular cone.
void GL_FLAME(float startx, float starty, float endx, float endy, float size)
{
    glColor3f(1, 0, 0);
    size += flameSize - deFlameSize;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(startx + deFlameLength, starty);
    glColor3f(1, 0.8, 0);
    for (int i = 0; i <= 20; i++)
        glVertex2f(endx + size * cos(2 * PI / 15 * i) + flameLength, 				               // x
                   endy + size * 4 / 3 * sin(2 * PI / 15 * i));							               // y
    glEnd();
}

// to draw a firework which is made up of 18 flames and 5 stars
void GL_FIREWORK(float x, float y)
{
    // the starting flame is also a triangle fan
    float size = 4;
    glColor3f(0.7, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y - 50 + fwStart);
    glColor3f(0.8, 0.5, 0);
    for (int i = 0; i <= 20; i++)
        glVertex2f(x + fwStartSize * cos(2 * PI / 15 * i),											   // x
                   y + fwStart + fwStartSize * 4 / 3 * sin(2 * PI / 15 * i));								   // y
    glEnd();

    // the location of every flame is different, enabled by a periodic function.
    for (float i = 0; i < 18; i++) {
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(1, 1.333, 0);
        glRotatef(i * 20, 0, 0, 1);
        glScalef(1, 0.75, 0);
        glTranslatef(-x, -y, 0);
        GL_FLAME(x + 3 * size + 2 * size * sin(i * 2),												   // startx
                 y,																						   // starty
                 x + 20 * size + 2 * size * (sin(i * 3) + cos(i * 3)),									   // endx
                 y,																						   // endy
                 size);																					   // size
        glPopMatrix();
    }
    size += flameSize - deFlameSize;

    // five flame stars, showing up along with the firework
    for (float i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(1, 1.333, 0);
        glRotatef(i * 72, 0, 0, 1);
        glScalef(1, 0.75, 0);
        glTranslatef(-x, -y, 0);
        GL_STAR(x + 100 + flameLength,																	// x
                y,																							// y
                2 * size,																					// longr
                i * 20);																					// degree
        glPopMatrix();
        glEnd();
    }
}

// to select a font
void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
                              CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void keyboard_input(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q') exit(0);
    else if (key == ' ' && fwStart == -450) {
        viewPxStep = 4;
        viewPWStep = 8;
    }
}

void mouse_input(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) starStep = 0.8;
}

// force OpenGL to redraw the current window
void when_in_mainloop() {
    glViewport(viewPortx, viewPorty, viewPWidth, viewPWidth * 0.5625);
    glutPostRedisplay();
}

void OnTimer(int value)
{
    viewPortx -= viewPxStep;
    viewPorty -= viewPyStep;
    viewPWidth += viewPWStep;
    star -= starStep;
    starRotate -= starRotateStep;
    fwStart += fwSStep;
    fwStartSize += fwSSStep;
    flameLength += flameLStep;
    flameSize += flameSStep;
    deFlameLength += deFlameLStep;
    deFlameSize += deFlameSStep;
    PixelColor += ColorStep;

    if (viewPortx <= -500) {
        viewPxStep = 0;
        viewPWStep = 0;
        fwSStep = 0.9;
        fwSSStep = -0.006;
        viewPyStep = fwSStep;
    }
    if (starRotate < -360) starRotate += 360;
    if (star <= 0) {
        starStep = 0;
        star = 0;
    }
    if (fwStart >= 0) {
        fwSStep = 0;
        fwSSStep = 0;
        flameLStep = 0.4;
        flameSStep = 0.032;
        viewPyStep = -3.6;
        viewPxStep = -4;
        viewPWStep = -8;
    }
    if (flameLength >= 0) {
        flameLStep = 0;
        flameSStep = 0;
        deFlameLStep = 0.1;
        deFlameSStep = 0.008;
        ColorStep = 0.004;
        viewPyStep = 0;
        viewPxStep = 0;
        viewPWStep = 0;
    }
    if (deFlameLength >= 50) {
        deFlameLStep = 0;
        deFlameSStep = 0;
        ColorStep = 0;
    }

    glutTimerFunc(time_interval, OnTimer, 1);
}