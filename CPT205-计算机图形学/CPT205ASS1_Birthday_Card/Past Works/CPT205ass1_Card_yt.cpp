#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <math.h>
#include <vector>


GLfloat s = 0;
GLfloat t = 0;
GLfloat flowerRotate = 10;
GLfloat flowerstep = 0;
GLfloat capRotate = 0;
GLfloat capTranslateX = -200;
GLfloat capTranslateY = -90;
GLfloat capstep = 0;
GLfloat starstep = 0;
GLfloat envelopeTranslate = 0;
GLfloat cblampx = 160, cblampy = 161, cblampz = 132, cblampu = 80;
int scene = 0;
bool outer = true;
bool emitstar = false;
GLfloat fireworkScale = 1;
GLfloat heartScale = 1;
bool isletter = false;
int time_interval = 60;
std::vector<std::pair<float, float>> heartVertices;
std::vector<std::pair<float, float>> XJTLUVertices;
std::vector<std::pair<float, float>> XJTLUVertices2;
int currentVertex = 0;
int currentVertex2 = 0;
int currentVertex3 = 0;

void when_in_mainloop()
{
    glutPostRedisplay();
}

void OnTimer(int value)
{
    if (isletter) {
        heartScale += 0.1;
        fireworkScale += 0.1;
    }
    if (emitstar == true) {
        if (starstep < 100) {
            starstep += 5;
        }
        else {
            emitstar = false;
            starstep = 0;
        }

    }
    flowerRotate += flowerstep;
    if (flowerRotate >= 360) {
        flowerRotate = 0;
    }
    if (capstep == 0) {
        capstep = 1;
        capRotate = 0;
        capTranslateX = -200;
        capTranslateY = -90;

    }
    else if (capstep == 1)
    {
        capstep = 2;
        capRotate = 5;
        capTranslateX = -195;
        capTranslateY = -92;
    }
    else if (capstep == 2)
    {
        capstep = 3;
        capRotate = 0;
        capTranslateX = -200;
        capTranslateY = -90;
    }
    else if (capstep == 3)
    {
        capstep = 4;
        capRotate = -5;
        capTranslateX = -205;
        capTranslateY = -88;
    }
    else if (capstep == 4)
    {
        capstep = 0;
        capRotate = 0;
        capTranslateX = -200;
        capTranslateY = -90;
    }

    if (fireworkScale >= 2) {
        fireworkScale = 0;
    }
    if (heartScale >= 1.5) {
        heartScale = 0;
    }

    if (outer == false && envelopeTranslate >= -300)
    {
        envelopeTranslate = envelopeTranslate - 10;
    }
    if (envelopeTranslate <= -300)
    {
        isletter = true;
        if (scene == 0) {
            scene = 1;
        }
    }
    if (isletter == true) {
        if (currentVertex < heartVertices.size() - 6) {
            currentVertex++;
            currentVertex++;
            currentVertex++;
            currentVertex++;
            currentVertex++;
            currentVertex++;
        }
        else {
            currentVertex = 0;
        }

        if (scene == 3)
        {
            if (currentVertex2 < XJTLUVertices.size() - 24) {
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
                currentVertex2++;
            }
            else {
                scene = 4;
            }
        }

        if (scene == 4)
        {
            if (currentVertex3 < XJTLUVertices2.size() - 20) {
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
                currentVertex3++;
            }
            else {
                scene = 5;
            }
        }
    }
    glutTimerFunc(time_interval, OnTimer, 1);


}


void plane()
{
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 203);
    glVertex2f(0, 100);
    glVertex2f(25, 0);
    glVertex2f(50, 25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(224, 224, 179);
    glVertex2f(0, 100);
    glVertex2f(50, 25);
    glVertex2f(65, 0);
    glVertex2f(80, 30);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 203);
    glVertex2f(0, 100);
    glVertex2f(80, 30);
    glVertex2f(110, 40);
    glEnd();
}

void cane()
{
    int i;
    float x, y;
    glColor3ub(3, 140, 15);
    glPointSize(10);
    glBegin(GL_POINTS);
    for (i = 0; i < 360; i = i + 5)
    {
        x = (float)i;
        y = 10.0 * sin(i * (6.284 / 135.0));
        glVertex2f(x, y);
    }
    glEnd();
    glColor3ub(5, 224, 25);
    glBegin(GL_POINTS);
    for (i = 0; i < 360; i = i + 5)
    {
        x = (float)i;
        y = 10.0 * cos(i * (6.284 / 135.0));
        glVertex2f(x, y);
    }
    glEnd();
}

void bear()
{
    //face
    glColor3f(0.8, 0.6, 0.4);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        double angle = 2.0 * 3.14159265 * i / 100;
        double x = 50 * cos(angle);
        double y = 45 * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();

    //ear
    glColor3f(0.8, 0.6, 0.4);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 15 * cos(angle) - 35;
        float y = 15 * sin(angle) + 30;
        glVertex2f(x, y);
    }
    glEnd();
    glColor3f(0.8, 0.6, 0.4);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 15 * cos(angle) + 35;
        float y = 15 * sin(angle) + 30;
        glVertex2f(x, y);
    }
    glEnd();

    //eye
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 5 * cos(angle) + 20;
        float y = 5 * sin(angle) + 7;
        glVertex2f(x, y);
    }
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 5 * cos(angle) - 20;
        float y = 5 * sin(angle) + 7;
        glVertex2f(x, y);
    }
    glEnd();

    //nose
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        double angle = 2.0 * 3.14159265 * i / 100;
        double x = 6 * cos(angle);
        double y = 5 * sin(angle) - 10;
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0, -10);
    glVertex2f(0, -25);
    glEnd();

    glPointSize(3);
    glBegin(GL_LINE_STRIP);
    for (int i = 200; i < 340; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 11 * cos(angle);
        float y = 11 * sin(angle) - 16;
        glVertex2f(x, y);
    }
    glEnd();

    //glass
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 11 * cos(angle) - 20;
        float y = 11 * sin(angle) + 7;
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        float x = 11 * cos(angle) + 20;
        float y = 11 * sin(angle) + 7;
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(13, 7);
    glVertex2f(5, 3);
    glVertex2f(5, 3);
    glVertex2f(-5, 3);
    glVertex2f(-5, 3);
    glVertex2f(-13, 7);
    glEnd();

    //cap
    glColor3ub(38, 26, 51);
    glBegin(GL_POLYGON);
    glVertex2f(-15, 40);
    glVertex2f(-15, 55);
    glVertex2f(15, 55);
    glVertex2f(15, 40);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 50);
    glVertex2f(-30, 60);
    glVertex2f(0, 70);
    glVertex2f(30, 60);
    glEnd();
}
void cap()
{
    glColor3ub(4, 29, 133);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(28, 60);
    glVertex2f(28, 30);
    glVertex2f(28, 45);
    glVertex2f(26, 30);
    glVertex2f(28, 45);
    glVertex2f(30, 30);
    glEnd();
}
void smallflower()
{
    glBegin(GL_LINES);
    glShadeModel(GL_FLAT);
    for (float i = 0; i <= 360; i += 0.1)
    {
        float x = 10 * (2 + sin(6 * (float)i)) * cos(i);
        float y = 10 * (2 + sin(6 * (float)i)) * sin(i);
        glColor3ub(255, 108, 179);
        glVertex2f(x, y);
        glColor3ub(255, 48, 129);
        glVertex2f(0, 0);
    }

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        glColor3ub(255, 251, 12);
        float x = 2 * cos(angle);
        float y = 2 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}
void heart()
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 1) {
        glColor3ub(255, 21, 168);
        float x = 16 * sin(i) * sin(i) * sin(i);
        float y = 13 * cos(i) - 5 * cos(2 * i) - 2 * cos(3 * i) - cos(4 * i);
        glVertex2f(x, y);
    }
    glEnd();
}

void dynamicHeart()
{
    glColor4ub(195, 16, 95, 220);
    glLineWidth(2.5);

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= currentVertex; i++) {
        const auto& vertex = heartVertices[i];
        glVertex2f(vertex.first, vertex.second);
    }

    glEnd();
}

void dynamicXJTLU()
{
    glColor4ub(112, 146, 190, 100);
    glPointSize(3);

    glBegin(GL_POINTS);

    for (int i = 0; i <= currentVertex2; i++) {
        const auto& vertex = XJTLUVertices[i];
        glVertex2f(vertex.first, vertex.second);
    }

    glEnd();
}

void dynamicXIPU()
{
    glColor4ub(255, 41, 85, 200);
    glPointSize(3);

    glBegin(GL_POINTS);

    for (int i = 0; i <= currentVertex3; i++) {
        const auto& vertex = XJTLUVertices2[i];
        glVertex2f(vertex.first, vertex.second);
    }

    glEnd();
}

void firework()
{
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i = i + 10) {
        double angle = 2.0 * 3.14159265 * i / 100;
        double x = 50 * cos(angle);
        double y = 50 * sin(angle);
        glVertex2f(x, y);
        angle = 2.0 * 3.14159265 * i / 100;
        x = 15 * cos(angle);
        y = 15 * sin(angle);
        glVertex2f(x, y);
    }
    for (int i = -5; i < 360; i = i + 5) {
        double angle = 2.0 * 3.14159265 * i / 100;
        double x = 30 * cos(angle);
        double y = 30 * sin(angle);
        glVertex2f(x, y);
        angle = 2.0 * 3.14159265 * i / 100;
        x = 15 * cos(angle);
        y = 15 * sin(angle);
        glVertex2f(x, y);
    }

    for (int i = -5; i < 360; i = i + 10) {
        double angle = 2.0 * 3.14159265 * i / 100;
        double x = 70 * cos(angle);
        double y = 70 * sin(angle);
        glVertex2f(x, y);
        angle = 2.0 * 3.14159265 * i / 100;
        x = 40 * cos(angle);
        y = 40 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}
void emblem() {

    if (scene == 5) {
        glBegin(GL_POLYGON);
        glShadeModel(GL_FLAT);
        glColor4ub(44, 0, 130, 200);
        for (int i = 60; i < 360 + 60; i += 10) {
            float angle = i * 3.14159265 / 180.0;
            float x = 50 * cos(angle);
            float y = 50 * sin(angle);
            if (i == 300) {
                glColor4ub(65, 2, 130, 150);
            }
            if (i == 90) {
                glColor4ub(21, 1, 130, 150);
            }
            if (i == 240) {
                glColor4ub(21, 1, 130, 150);
            }
            if (i == 120) {
                glColor4ub(0, 17, 130, 150);
            }
            if (i == 270) {
                glColor4ub(44, 0, 130, 150);
            }

            glVertex2f(x, y);
        }
        glEnd();
        glColor3f(1, 1, 1);

        glRasterPos2f(-27, -6);
        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"XJTLU");
    }
}

void lightAndWings()
{
    if (scene == 5) {
        glColor3ub(255, 178, 14);
        glRasterPos2f(-80, 20);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Light");
        glRasterPos2f(-20, 20);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"and");
        glRasterPos2f(30, 20);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Wings");
    }
}

void diploma()
{
    //glPushMatrix();
    //glScalef(0.5, 0.5, 0);
    //glRotatef(90, 0, 0, 1);
    glBegin(GL_POLYGON);
    glColor3ub(240, 215, 237);
    for (int i = 45; i < 135; i += 1) {
        float angle = i * 3.14159265 / 180.0;
        float x = 250 * cos(angle);
        float y = 50 * sin(angle);
        glVertex2f(x, y);
    }
    for (int i = 0; i < 180; i += 1) {
        float angle = i * 3.14159265 / 180.0;
        float x = 150 * cos(angle);
        float y = 50 * sin(angle);
        glVertex2f(x, y);
    }
    float angle = 135 * 3.14159265 / 180.0;
    float x = 250 * cos(angle);
    float y = 50 * sin(angle);
    glVertex2f(x, y);
    glEnd();

    glPushMatrix();
    glTranslatef(160, 17, 0);
    glRotatef(-45, 0, 0, 1);
    glBegin(GL_POLYGON);
    glColor3ub(222, 199, 220);
    for (int i = 20; i < 380; i += 1) {
        float angle = i * 3.14159265 / 180.0;
        float x = 13 * cos(angle);
        float y = 23 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-160, 17, 0);
    glRotatef(45, 0, 0, 1);
    glBegin(GL_POLYGON);
    for (int i = 20; i < 380; i += 1) {
        float angle = i * 3.14159265 / 180.0;
        float x = 13 * cos(angle);
        float y = 23 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void bowTie()
{
    glBegin(GL_POLYGON);
    glColor3ub(222, 21, 62);
    glVertex2f(0, 0);
    glVertex2f(15, 7);
    glVertex2f(25, 0);
    glVertex2f(15, -7);
    glVertex2f(0, 0);
    glVertex2f(15, -25);
    glVertex2f(5, -20);
    glVertex2f(2, -27);
    glVertex2f(0, 0);
    glVertex2f(-15, 7);
    glVertex2f(-25, 0);
    glVertex2f(-15, -7);
    glVertex2f(0, 0);
    glVertex2f(-15, -25);
    glVertex2f(-5, -20);
    glVertex2f(-2, -27);
    glEnd();

    glPointSize(7);
    glBegin(GL_POINTS);
    glColor3ub(184, 17, 51);
    glVertex2f(0, -2);
    glEnd();
}

void word()
{
    glColor3f(0, 0, 0);

    glRasterPos2f(-30, -130);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"2024");
    glRasterPos2f(-40, -150);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"XJTLU");
    glRasterPos2f(-100, -170);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Graduation Ceremony");
}

void cb()
{
    glBegin(GL_POLYGON);
    glColor4ub(255, 215, 147, 100);
    glVertex2f(5, 0);
    glVertex2f(50, 0);
    glVertex2f(50, 30);
    glVertex2f(5, 25);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(35, 45);
    glVertex2f(40, 35);
    glVertex2f(50, 35);
    glVertex2f(50, 70);
    glVertex2f(25, 70);
    glVertex2f(22, 60);
    glVertex2f(30, 45);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(17, 60);
    glVertex2f(12, 70);
    glVertex2f(5, 70);
    glVertex2f(5, 35);
    glVertex2f(25, 35);
    glVertex2f(30, 45);
    glVertex2f(22, 60);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 70);
    glVertex2f(0, 35);
    glVertex2f(-15, 28);
    glVertex2f(-17, 65);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-21, 66);
    glVertex2f(-20, 41);
    glVertex2f(-32, 36);
    glVertex2f(-33, 61);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, 22);
    glVertex2f(-23, 28);
    glVertex2f(-33, 25);
    glVertex2f(-33, 5);
    glEnd();
}
void cblamp() {
    glBegin(GL_POLYGON);
    glVertex2f(5, 26);
    glVertex2f(5, 34);
    glVertex2f(50, 34);
    glVertex2f(50, 31);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(26, 34);
    glVertex2f(31, 44);
    glVertex2f(34, 44);
    glVertex2f(39, 34);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(13, 70);
    glVertex2f(17, 61);
    glVertex2f(21, 61);
    glVertex2f(24, 70);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-33, 26);
    glVertex2f(-33, 35);
    glVertex2f(-18, 40);
    glVertex2f(-18, 31);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-15, 27);
    glVertex2f(0, 34);
    glVertex2f(0, 24);
    glEnd();
}
void building()
{
    glColor3ub(255, 205, 4);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-50, 0);
    glVertex2f(0, 0);
    for (int i = 300; i < 330; i++) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle);
        double y = 10 * sin(angle) + 10;
        glVertex2f(x, y);
    }
    glVertex2f(8.5, 20);

    for (int i = 150; i > 100; i--) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 20;
        double y = 10 * sin(angle) + 20;
        glVertex2f(x, y);
    }

    glVertex2f(35, 30);
    glVertex2f(35, 5);

    for (int i = 210; i < 240; i++) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 44;
        double y = 10 * sin(angle) + 10;
        glVertex2f(x, y);
    }

    glVertex2f(55, 0);
    glVertex2f(57, 70);
    glVertex2f(62, 60);
    glVertex2f(64, 78);
    glVertex2f(67, 60);
    glVertex2f(70, 70);
    glVertex2f(73, 20);
    glVertex2f(100, 20);
    for (int i = 300; i < 380; i++) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 110;
        double y = 10 * sin(angle) + 30;
        glVertex2f(x, y);
    }
    for (int i = 90; i > 0; i--) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 120;
        double y = 10 * sin(angle) + 25;
        glVertex2f(x, y);
    }
    glVertex2f(135, 0);
    glVertex2f(170, 0);
    glVertex2f(165, 20);
    glVertex2f(175, 18);
    glVertex2f(185, 19);
    glVertex2f(193, 17);
    glVertex2f(205, 15);
    glVertex2f(204, 0);
    glVertex2f(235, 0);
    glVertex2f(237, 68);
    glVertex2f(245, 0);
    glVertex2f(246, 1);
    glVertex2f(247, 1);
    glVertex2f(248, 2);
    glVertex2f(249, 3);
    glVertex2f(250, 3);
    glVertex2f(251, 20);
    glVertex2f(261, 19);
    glVertex2f(264, 0);
    glVertex2f(290, 0);
    glVertex2f(291, 10);
    glVertex2f(301, 11);
    glVertex2f(303, 70);
    glVertex2f(340, 68);
    glVertex2f(342, 4);
    for (int i = 210; i < 270; i++) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 350;
        double y = 10 * sin(angle) + 10;
        glVertex2f(x, y);
    }
    glVertex2f(400, 0);
    glEnd();
}
void invitation()
{
    /*glBegin(GL_POLYGON);
    glVertex2f(-50, -100);
    glVertex2f(-50, 100);
    glVertex2f(200, 100);
    glVertex2f(200, -100);
    glEnd();*/
    if (scene == 2) {
        glColor3f(0, 0, 0);
        glRasterPos2f(-30, 50);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Sincerely invite you ");
        glRasterPos2f(-30, 25);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"attend the graduation");
        glRasterPos2f(-30, 0);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"ceremony!");
    }
    if (scene == 1) {
        glColor3f(0, 0, 0);
        glRasterPos2f(-10, 50);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Congratulation ");
        glRasterPos2f(-30, 25);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"for your graduation!");
    }

}

void fourstar() {
    glBegin(GL_TRIANGLES);
    glVertex2f(-20.0f, 0.0f);
    glVertex2f(20.0f, 0.0f);
    glVertex2f(0.0f, 40.0f);

    glVertex2f(-20.0f, 0.0f);
    glVertex2f(-60.0f, -20.0f);
    glVertex2f(-20.0f, -40.0f);

    glVertex2f(-20.0f, -40.0f);
    glVertex2f(0.0f, -80.0f);
    glVertex2f(20.0f, -40.0f);

    glVertex2f(20.0f, -40.0f);
    glVertex2f(60.0f, -20.0f);
    glVertex2f(20.0f, 0.0f);;

    glVertex2f(-20.0f, 0.0f);
    glVertex2f(-20.0f, -40.0f);
    glVertex2f(20.0f, 0.0f);

    glVertex2f(-20.0f, -40.0f);
    glVertex2f(20.0f, -40.0f);
    glVertex2f(20.0f, 0.0f);
    glEnd();
}
void star() {
    if (scene == 1 || scene == 2)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 0.0);

        for (int i = 0; i < 5; i++) {
            float angle = i * 2.0 * 3.1415925 / 5 - 3.1415926 / 10;
            float x = 25 * cos(angle);
            float y = 25 * sin(angle);
            glVertex2f(x, y);

            angle = i * 2.0 * 3.1415925 / 5 + 3.1415926 / 5 - 3.1415926 / 10;
            x = 50 * cos(angle);
            y = 50 * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }

    if (scene == 1) {
        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 10) {
            float angle = i * 3.14159265 / 180.0;
            float x = 2 * cos(angle) - 10;
            float y = 3.2 * sin(angle) + 10;
            glVertex2f(x, y);
        }
        glEnd();

        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 10) {
            float angle = i * 3.14159265 / 180.0;
            float x = 2 * cos(angle) + 10;
            float y = 3.2 * sin(angle) + 10;
            glVertex2f(x, y);
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (int i = 182; i < 360; i += 10) {
            float angle = i * 3.14159265 / 180.0;
            float x = 10 * cos(angle);
            float y = 15 * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }

    if (scene == 2) {
        glColor3ub(0, 0, 0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(-13, 14);
        glVertex2f(-6, 10);
        glVertex2f(-13, 6);
        glEnd();
        glColor3ub(0, 0, 0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(13, 14);
        glVertex2f(6, 10);
        glVertex2f(13, 6);
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (int i = 190; i < 360; i += 10) {
            float angle = i * 3.14159265 / 180.0;
            float x = 10 * cos(angle);
            float y = 15 * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        for (int i = 190; i < 360; i += 10) {
            float angle = i * 3.14159265 / 180.0;
            float x = 9 * cos(angle);
            float y = 13 * sin(angle) - 1;
            glVertex2f(x, y);
        }
        glEnd();
    }
}
void remind()
{
    glColor3ub(255, 0, 0);
    glRasterPos2f(-280, -170);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"press 'o' to open the envelope");
}

void remind5()
{
    glColor3ub(255, 0, 0);
    glRasterPos2f(-100, 0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"press 'a' and 'd' to interact with flower");
    glRasterPos2f(-80, -20);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"press 'z' to emit star");
}

void remind2()
{
    glColor3ub(0, 0, 0);
    glRasterPos2f(-280, 20);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"press 'w','s','a','d' ");
    glRasterPos2f(-280, 0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"to move the letter");
}

void remind3()
{
    glColor3ub(0, 0, 0);
    glRasterPos2f(-265, -150);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"press 'e' to turn on/off the light ");
}

void remind4()
{
    if (scene == 1) {
        glColor3ub(255, 0, 0);
        glRasterPos2f(-35, -29);
        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"click mouse left to read next page ");
    }

    else if (scene == 2) {
        glColor3ub(255, 0, 0);
        glRasterPos2f(-35, -29);
        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"continue click left to read next page ");
    }
}
void envelop()
{
    glBegin(GL_POLYGON);
    glShadeModel(GL_FLAT);
    glColor3ub(252, 251, 141);
    glVertex2f(0, -100);
    glColor3ub(224, 255, 201);
    glVertex2f(-300, 100);
    glColor3ub(252, 251, 141);
    glVertex2f(-300, -200);
    glColor3ub(252, 251, 141);
    glVertex2f(300, -200);
    glColor3ub(224, 255, 201);
    glVertex2f(300, 100);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(252, 251, 141);
    glVertex2f(0, -100);
    glColor3ub(224, 255, 201);
    glVertex2f(-300, 100);
    glColor3ub(224, 255, 201);
    glVertex2f(0, -100);
    glColor3ub(252, 251, 141);
    glVertex2f(300, 100);
    glEnd();

    glPushMatrix();
    glTranslatef(-300, 100, 0);
    glRotatef(-33, 0, 0, 1);
    cane();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -100, 0);
    glRotatef(34, 0, 0, 1);
    cane();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -100, 0);
    glScalef(0.5, 0.5, 0);
    glRotatef(75, 0, 0, 1);
    diploma();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(200, -90, 0);
    glScalef(0.48, 0.48, 0);
    glRotatef(90, 0, 0, 1);
    diploma();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(185, -90, 0);
    glScalef(1.2, 1.2, 0);
    glRotatef(-10, 0, 0, 1);
    bowTie();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, -100, 0);
    glScalef(1.2, 1.2, 0);
    bear();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(capTranslateX, capTranslateY, 0);
    glRotatef(capRotate, 0, 0, 1);
    cap();
    glPopMatrix();

    word();

    glPushMatrix();
    glColor4ub(255, 174, 201, 200);
    glTranslatef(0 + starstep, (-100 + starstep) * 0.8 - 20, 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();
    glColor3ub(255, 201, 14);
    glPushMatrix();
    glTranslatef(0, -100 + starstep, 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();
    glColor3ub(112, 146, 190);
    glPushMatrix();
    glTranslatef(0 - starstep, (starstep - 100) * 0.8 - 20, 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();
    glColor3ub(163, 73, 164);
    glPushMatrix();
    glTranslatef(0 + 0.5 * starstep, -100 + starstep, 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();
    glColor3ub(255, 127, 39);
    glPushMatrix();
    glTranslatef(0 + starstep, -50 + 0.5 * (-100 + starstep), 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();
    glColor3ub(181, 230, 29);
    glPushMatrix();
    glTranslatef(0 - 0.5 * starstep, -100 + starstep, 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();
    glColor3ub(185, 122, 87);
    glPushMatrix();
    glTranslatef(0 - starstep, -50 + 0.5 * (-100 + starstep), 0);
    glScalef(0.1, 0.1, 0);
    fourstar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-220, 60, 0);
    glRotatef(-flowerRotate - 30, 0, 0, 1);
    smallflower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-130, -25, 0);
    glRotatef(flowerRotate, 0, 0, 1);
    smallflower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(130, -25, 0);
    glRotatef(-flowerRotate, 0, 0, 1);
    smallflower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(220, 60, 0);
    glRotatef(flowerRotate + 30, 0, 0, 1);
    smallflower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -100, 0);
    glRotatef(flowerRotate, 0, 0, 1);
    smallflower();
    glPopMatrix();


    remind();
    remind5();

}

void letter()
{
    glLineWidth(1.0);
    glBegin(GL_POLYGON);
    glShadeModel(GL_FLAT);
    glColor3ub(255, 176, 141);
    glVertex2f(300, 200);
    glColor3ub(255, 208, 188);
    glVertex2f(0, 200);
    glColor3ub(255, 255, 213);
    glVertex2f(-300, 200);
    glColor3ub(255, 255, 255);
    glVertex2f(-300, -200);
    glColor3ub(255, 255, 213);
    glVertex2f(0, -200);
    glColor3ub(255, 208, 188);
    glVertex2f(300, -200);
    glEnd();

    invitation();

    glPushMatrix();
    glTranslatef(-50, 120, 0);
    glScalef(2, 2, 0);
    //glRotatef(180, 0, 0, 1);
    dynamicHeart();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -20, 0);
    glRotatef(0, 0, 0, 1);
    star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(140, 70, 0);
    glScalef(1, 1, 0);
    glRotatef(0, 0, 0, 1);
    plane();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, 80, 0);
    glScalef(0.5, 0.5, 0);
    glRotatef(-40, 0, 0, 1);
    plane();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(210, 150, 0);
    glScalef(0.3, 0.3, 0);
    glRotatef(45, 0, 0, 1);
    plane();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-140, 70, 0);
    glScalef(heartScale, heartScale, 0);
    glRotatef(0, 0, 0, 1);
    heart();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(270, 20, 0);
    glScalef(heartScale, heartScale, 0);
    glRotatef(0, 0, 0, 1);
    heart();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -150, 0);
    glScalef(heartScale, heartScale, 0);
    glRotatef(0, 0, 0, 1);
    heart();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, -130, 0);
    glScalef(2, 2, 0);
    cb();
    glColor4ub(cblampx, cblampy, cblampz, cblampu);
    cblamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-205, 170, 0);
    glColor3ub(65, 10, 255);
    glScalef(1 * fireworkScale, 1 * fireworkScale, 0);
    firework();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-260, 110, 0);
    glScalef(0.8 * fireworkScale, 0.8 * fireworkScale, 0);
    glColor3ub(255, 116, 14);
    firework();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-180, 80, 0);
    glColor3ub(255, 71, 229);
    glScalef(0.5 * fireworkScale, 0.5 * fireworkScale, 0);
    firework();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130, 30, 0);
    glScalef(0.7, 0.7, 0);
    emblem();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100, -135, 0);
    building();
    glPopMatrix();

    lightAndWings();

    remind2();
    remind3();
    remind4();

    dynamicXJTLU();
    dynamicXIPU();
}
void init()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -200, 200);//2d viewing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(s, t, 0);
    letter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, envelopeTranslate, 0);
    envelop();
    glPopMatrix();
    glFlush();
}

void keyboard_input(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
    else if (key == 'o' || key == 'O')
        outer = false;
    else if (key == 'w' || key == 'W') {
        if (isletter == true) {
            t += 5;
        }
    }
    else if (key == 'S' || key == 's') {
        if (isletter == true) {
            t -= 5;
        }
    }
    else if (key == 'Z' || key == 'z') {
        emitstar = true;
    }
    else if (key == 'a' || key == 'A') {
        if (isletter == true) {
            s -= 5;
        }
        else  if (flowerstep <= 10 && isletter == false) {
            flowerstep += 2;
        }
    }
    else if (key == 'D' || key == 'd') {
        if (isletter == true) {
            s += 5;
        }
        else  if (flowerstep >= -10 && isletter == false) {
            flowerstep -= 2;
        }
    }
    else if (key == 'e' || key == 'E') {
        if (isletter == true) {
            if (cblampx == 160) {
                cblampx = 255;
                cblampy = 253;
                cblampz = 128;
                cblampu = 255;
            }
            else {
                cblampx = 160;
                cblampy = 161;
                cblampz = 132;
                cblampu = 80;
            }
        }
    }
}

void mouse_input(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && scene > 0 && scene < 3 && isletter == true)
        scene += 1;

}

void constructHeart()
{
    for (float i = -50; i < -1; i += 0.5) {
        float y = -15;
        heartVertices.push_back(std::make_pair(i, y));
    }
    for (float t = 3.14159265 + 0.5; t <= 3 * 3.14159265 - 0.5; t += 0.05) {
        float x = 16.0 * sin(t) * sin(t) * sin(t);
        float y = 13.0 * cos(t) - 5.0 * cos(2 * t) - 2.0 * cos(3 * t) - cos(4 * t);
        heartVertices.push_back(std::make_pair(x, y));
    }
    for (float i = 1; i < 120; i += 0.5) {
        float y = -15;
        heartVertices.push_back(std::make_pair(i, y));
    }
    for (float t = 3.14159265 + 0.5; t <= 3 * 3.14159265 - 0.5; t += 0.05) {
        float x = 16.0 * sin(t) * sin(t) * sin(t) + 120;
        float y = 13.0 * cos(t) - 5.0 * cos(2 * t) - 2.0 * cos(3 * t) - cos(4 * t) + 30;
        heartVertices.push_back(std::make_pair(x, -y));
    }
    for (float i = 122; i < 180; i += 0.5) {
        float y = -15;
        heartVertices.push_back(std::make_pair(i, y));
    }
}

void constructXJTLU()
{
    for (float i = -10; i < 0; i += 0.1) {
        float y = 0;
        XJTLUVertices.push_back(std::make_pair(i, y));
    }

    for (float i = 0; i > -20; i -= 0.1) {
        float x = -5;
        XJTLUVertices.push_back(std::make_pair(x, i));
    }

    for (float i = -12; i < 4; i += 0.1) {
        float y = -20;
        XJTLUVertices.push_back(std::make_pair(i, y));
    }

    for (float i = 0; i > -20; i -= 0.1) {
        float x = 20;
        XJTLUVertices.push_back(std::make_pair(x, i));
    }
    for (float i = 20; i < 30; i += 0.1) {
        float y = -20;
        XJTLUVertices.push_back(std::make_pair(i, y));

    }

    for (float t = 3.14159265; t <= 3 * 3.14159265; t += 0.02) {
        float x = 10.0 * sin(t) * sin(t) * sin(t) + 40;
        float y = 7.0 * cos(t) - 5.0 * cos(2 * t) - 2.0 * cos(3 * t) - cos(4 * t) - 7;
        XJTLUVertices.push_back(std::make_pair(x, y));
    }

    for (float i = 55; i < 60; i += 0.1) {
        float y = -4 * (i - 55);
        XJTLUVertices.push_back(std::make_pair(i, y));

    }

    for (float i = 60; i < 65.1; i += 0.1) {
        float y = 4 * (i - 65);
        XJTLUVertices.push_back(std::make_pair(i, y));

    }

    for (float i = 72; i < 82; i += 0.1) {
        float y = 0;
        XJTLUVertices.push_back(std::make_pair(i, y));

    }

    for (float i = 0; i > -20; i -= 0.1) {
        float x = 72;
        XJTLUVertices.push_back(std::make_pair(x, i));

    }

    for (float i = 72; i < 82; i += 0.1) {
        float y = -10;
        XJTLUVertices.push_back(std::make_pair(i, y));
    }

    for (float i = 72; i < 82; i += 0.1) {
        float y = -20;
        XJTLUVertices.push_back(std::make_pair(i, y));
    }

    for (float i = 72; i < 82; i += 0.1) {
        float y = -20;
        XJTLUVertices.push_back(std::make_pair(i, y));
    }
}

void constructXIPU() {
    for (float i = -12; i < 2; i += 0.1) {
        float y = -1.42857 * i - 47;
        XJTLUVertices2.push_back(std::make_pair(i, y));
    }

    for (float i = -12; i < 2; i += 0.1) {
        float y = 1.42857 * i - 33;
        XJTLUVertices2.push_back(std::make_pair(i, y));
    }

    for (float i = 20; i < 30; i += 0.1) {
        float y = -30;
        XJTLUVertices2.push_back(std::make_pair(i, y));
    }

    for (float i = -30; i > -50; i -= 0.1) {
        float x = 25;
        XJTLUVertices2.push_back(std::make_pair(x, i));
    }

    for (float i = 18; i < 32; i += 0.1) {
        float y = -50;
        XJTLUVertices2.push_back(std::make_pair(i, y));
    }

    for (float i = -30; i > -50; i -= 0.1) {
        float x = 48;
        XJTLUVertices2.push_back(std::make_pair(x, i));
    }

    for (int i = -90; i < 91; i += 1) {
        float angle = i * 3.14159265 / 180.0;
        float x = 10 * cos(angle) + 48;
        float y = 8 * sin(angle) - 35;
        XJTLUVertices2.push_back(std::make_pair(x, y));
    }

    for (int i = -180; i < 10; i += 1) {
        float angle = i * 3.14159265 / 180.0;
        float x = 6 * cos(angle) + 78;
        float y = 20 * sin(angle) - 30;
        XJTLUVertices2.push_back(std::make_pair(x, y));
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);//window size: 600*400
    glutInitWindowPosition(50, 50);//position on the screen
    glutCreateWindow("invitation to the 2024 XJTLU Graduation Ceremony");
    constructHeart();
    constructXJTLU();
    constructXIPU();
    glutDisplayFunc(init);
    glutIdleFunc(when_in_mainloop);
    glutTimerFunc(time_interval, OnTimer, 1);
    glutKeyboardFunc(keyboard_input);
    glutMouseFunc(mouse_input);
    glutMainLoop();
}