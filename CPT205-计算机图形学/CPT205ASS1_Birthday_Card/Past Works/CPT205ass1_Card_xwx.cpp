#define FREEGLUT_STATIC // Define a static library for calling functions
#include <GL/freeglut.h> // Include the header file 
#include <math.h>
#include <iostream>
#include <random>
#define MAX_CHAR 128
using namespace std;


typedef struct point { float x, y; };

//put some constants here
float t1 = 0.0; //the speed of layer 1
float rs = 5;// the rotate speed
float scalesize = 0.8;
int time_interval = 20; // declare refresh interval in ms
//translation: move, zoom, rotation,
float x_move = 0.0;
float y_move = 0.0;
float z_rotation = 0.0;
float zoom = 1.0f;
bool mouseLeftDown;
bool mouseRightDown;
float mouse_X, mouse_Y;
float viewAngleX;
float viewAngleY;
const float Pi = 3.1415926536f;
bool is_instru = false;

void drawSolidShape(int edgeNumber, int a, int b);
void drawhalfSolidShape(int edgeNumber, int a, int b);
void drawBaizerCurve(GLfloat* ctrlpoints, GLfloat LineWidth);
void restTranslation();



void drawrecursivetree(int n)
{
    if (n > 0)
    {

        glPushMatrix();

        glTranslatef(-0.5, 1.0, 0);
        glRotatef(45, 0.0, 0.0, 1.0);

        // 1/sqrt(2)=0.707
        glScalef(0.707, 0.707, 0.707);

        //recursion
        drawrecursivetree(n - 1);

        glPopMatrix();
        ////////////////////////////

        glPushMatrix();
        glTranslatef(0.5, 1.0, 0);
        glRotatef(-45, 0.0, 0.0, 1.0);
        glScalef(0.707, 0.707, 0.707);
        drawrecursivetree(n - 1);
        glPopMatrix();
        //draw a cube
        glutSolidCube(1);
    }
}

void treeInit(int n)
{
    // assign the colour of the tree
    glColor3f(1.0, 0.0, 0.0);
    drawrecursivetree(n);
}

void drawlantern() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 67.0f);
    glVertex2f(0.0f, 87.0f);
    glVertex2f(0.0f, -60.0f);
    glVertex2f(0.0f, -65.0f);
    glEnd();



    glPolygonMode(GL_FRONT, GL_LINE);
    glPushMatrix();
    glTranslatef(0, -70, 0);
    glColor3ub(0, 0, 0);
    drawSolidShape(1000, 5, 5);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub(227, 207, 87);
    drawSolidShape(1000, 5, 5);
    glPopMatrix();

    glPolygonMode(GL_FRONT, GL_LINE);
    glPushMatrix();
    glTranslatef(0, -93, 0);
    glColor3ub(0, 0, 0);
    drawhalfSolidShape(1000, 10, 18);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub(227, 207, 87);
    drawhalfSolidShape(1000, 10, 18);
    glPopMatrix();


    //draw the solid part
    glLineWidth(5.0f);
    glBegin(GL_QUADS);
    glColor3ub(227, 23, 13);
    glVertex2f(-20, 47);
    glVertex2f(20, 47);
    glVertex2f(20, 57);
    glVertex2f(-20, 57);
    glBegin(GL_QUADS);
    glVertex2f(27, -50);
    glVertex2f(-27, -50);
    glVertex2f(-27, -59);
    glVertex2f(27, -59);
    glEnd();
    glColor3ub(255, 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-20, 57);
    glVertex2f(20, 57);
    glVertex2f(20, 67);
    glVertex2f(-20, 67);
    glEnd();



    //draw the edge part
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(-20, 47);
    glVertex2f(20, 47);
    glVertex2f(20, 57);
    glVertex2f(-20, 57);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-20, 57);
    glVertex2f(20, 57);
    glVertex2f(20, 67);
    glVertex2f(-20, 67);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(27, -50);
    glVertex2f(-27, -50);
    glVertex2f(-27, -59);
    glVertex2f(27, -59);
    glEnd();
    drawSolidShape(1000, 70, 50);

    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1, 0, 0);
    drawSolidShape(1000, 70, 50);

    glColor3f(0, 0, 0);
    GLfloat ctrlPts[3][3] = { {-15.0,50.0,0.0},{-80.0,0.0,0.0},{-15.0,-50.0,0.0} };
    drawBaizerCurve(&ctrlPts[0][0], 2.0f);
    GLfloat ctrlPts1[3][3] = { {15.0,50.0,0.0},{80.0,0.0,0.0},{15.0,-50.0,0.0} };
    drawBaizerCurve(&ctrlPts1[0][0], 2.0f);
    GLfloat ctrlPts2[3][3] = { {0.0,50.0,0.0},{-45.0,0.0,0.0},{0.0,-50.0,0.0} };
    drawBaizerCurve(&ctrlPts2[0][0], 2.0f);
    GLfloat ctrlPts3[3][3] = { {0.0,50.0,0.0},{45.0,0.0,0.0},{0.0,-50.0,0.0} };
    drawBaizerCurve(&ctrlPts3[0][0], 2.0f);

    glBegin(GL_LINES);
    glVertex2f(0, -50);
    glVertex2f(0, 50);
    glVertex2f(3, -93);
    glVertex2f(3, -75);
    glVertex2f(-3, -93);
    glVertex2f(-3, -75);
    glEnd();



}

void drawFireCracker() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub(255, 215, 0);
    drawSolidShape(1000, 30, 10);


    glColor3ub(255, 235, 205);
    for (GLfloat incre = 0; incre < 30; incre += 0.2) {
        GLfloat ctrlPts0[3][3] = { {-30.0,-32.0 + incre,0.0},{0.0,-50.0 + incre,0.0},{30.0,-32.0 + incre,0.0} };
        drawBaizerCurve(&ctrlPts0[0][0], 2.0f);
    }

    glColor3ub(255, 69, 0);
    for (GLfloat incre = 0; incre < 68; incre += 0.2) {
        GLfloat ctrlPts00[3][3] = { {-30.0,-32.0 - incre,0.0},{0.0,-50.0 - incre,0.0},{30.0,-32.0 - incre,0.0} };
        drawBaizerCurve(&ctrlPts00[0][0], 2.0f);
    }
    glLineWidth(1.5f);
    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0, 0, 0);
    drawSolidShape(1000, 30, 10);
    glBegin(GL_LINES);
    glVertex2f(-30, 0);
    glVertex2f(-30, -100);
    glVertex2f(30, 0);
    glVertex2f(30, -100);
    glEnd();


    GLfloat ctrlPts[3][3] = { {-30.0,-32.0,0.0},{0.0,-50.0,0.0},{30.0,-32.0,0.0} };
    drawBaizerCurve(&ctrlPts[0][0], 1.5f);
    GLfloat ctrlPts1[3][3] = { {-30.0,-100.0,0.0},{0.0,-120.0,0.0},{30.0,-100.0,0.0} };
    drawBaizerCurve(&ctrlPts1[0][0], 1.5f);
    GLfloat ctrlPts2[3][3] = { {-5.0,0.0,0.0},{-5.0,30.0,0.0},{10.0,50.0,0.0} };
    drawBaizerCurve(&ctrlPts2[0][0], 1.5f);





}

void drawDialogBox() {

    const GLfloat Pi = 3.1415926536f;
    int edgeNumber = 100;
    int i;
    glBegin(GL_LINE_LOOP);
    glVertex2f(-10, -10);
    glVertex2f(10, 10);
    for (i = 50; i > 25; --i)
        glVertex2f(30 + 20 * cos(2 * Pi / edgeNumber * i), 20 + 20 * sin(2 * Pi / edgeNumber * i));
    glVertex2f(150, 40);
    for (i = 25; i > 0; --i)
        glVertex2f(150 + 20 * cos(2 * Pi / edgeNumber * i), 20 + 20 * sin(2 * Pi / edgeNumber * i));
    glVertex2f(170, 20);
    glVertex2f(170, -20);
    for (i = 0; i > -25; --i)
        glVertex2f(150 + 20 * cos(2 * Pi / edgeNumber * i), -40 + 20 * sin(2 * Pi / edgeNumber * i));
    glVertex2f(30, -60);
    for (i = -25; i > -50; i--)
        glVertex2f(30 + 20 * cos(2 * Pi / edgeNumber * i), -40 + 20 * sin(2 * Pi / edgeNumber * i));
    glVertex2f(10, -30);
    glEnd();




}

void drawBaizerCurve(GLfloat* ctrlpoints, GLfloat LineWidth) {
    glLineWidth(LineWidth);
    //using three control points to draw two-dimensional Baizer Curve
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, ctrlpoints);
    glEnable(GL_MAP1_VERTEX_3);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 50; i++)
    {
        glEvalCoord1f((GLfloat)i / 50.0);
    }
    glEnd();


}
void drawSolidShape(int edgeNumber, int a, int b)
{
    const GLfloat Pi = 3.1415926536f;
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < edgeNumber; ++i)
        glVertex2f(a * cos(2 * Pi / edgeNumber * i), b * sin(2 * Pi / edgeNumber * i));
    glEnd();
}

void drawhalfSolidShape(int edgeNumber, int a, int b)
{
    const GLfloat Pi = 3.1415926536f / 2;
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < edgeNumber; ++i)
        glVertex2f(a * cos(2 * Pi / edgeNumber * i), b * sin(2 * Pi / edgeNumber * i));
    glEnd();
}



void drawSimelingFace() {
    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0, 0, 0);
    drawSolidShape(100, 50, 50);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1, 1, 0);
    drawSolidShape(100, 50, 50);

    glLineWidth(5.0f);

    glPushMatrix();
    glTranslatef(0, -10, 0);
    glRotatef(180, 0, 0, 1);
    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0, 0, 0);
    drawhalfSolidShape(100, 20, 10);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1, 1, 1);
    drawhalfSolidShape(100, 20, 10);
    glPopMatrix();

    glLineWidth(2.0f);
    glPushMatrix();
    glTranslatef(-15, 20, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(0, 0, 0);
    drawSolidShape(100, 3, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, 20, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(0, 0, 0);
    drawSolidShape(100, 3, 7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-30, 0, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1, 0, 0);
    drawSolidShape(100, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 0, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1, 0, 0);
    drawSolidShape(100, 15, 5);
    glPopMatrix();


}


void selectFont(int size, int width, int charset, const char* face)
{
    /*
        size : 字体大小
        charset ：  字符集
        face ： 字体名称
    */
    HFONT hFont = CreateFontA(size, width, 0, 0, FW_MEDIUM, 0, 0, 0,
                              charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}


void drawString(const char* str)
{
    int isFirstCall = 1;
    GLuint lists;

    if (isFirstCall)
    {
        // 如果是第一次调用，执行初始化
        // 为每一个ASCII 字符产生一个显示列表
        isFirstCall = 0;
        // 申请 MAX_CHAR 个连续的显示列表编号
        lists = glGenLists(MAX_CHAR);

        // 把每个字符的绘制命令都装到对应的显示列表中
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // 调用每个字符对应的显示列表，绘制每个字符
    for (; *str != '\0'; ++str)
    {
        glCallList(lists + *str);
    }
}



void drawCNString(const char* str)
{
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    len = 0;
    for (i = 0; str[i] != '\0'; ++i)
    {
        if (IsDBCSLeadByte(str[i]))
        {
            ++i;
        }
        ++len;
    }

    wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    for (i = 0; i < len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }


    free(wstring);
    glDeleteLists(list, 1);
}





void layer1() {
    //the upper polygen
    int p1[] = { 0,400 };
    int p2[] = { 0,266 };
    int p3[] = { 77,133 };
    int p4[] = { 423,266 };
    int p5[] = { 500,133 };
    int p6[] = { 500,400 };
    glBegin(GL_POLYGON);
    glColor3ub(255, 69, 0);
    glVertex2iv(p1);
    glColor3ub(255, 99, 0);
    glVertex2iv(p2);
    glColor3ub(255, 128, 114);
    glVertex2iv(p3);
    glColor3ub(176, 23, 31);
    glVertex2iv(p4);
    glColor3ub(178, 34, 34);
    glVertex2iv(p5);
    glColor3ub(255, 127, 80);
    glVertex2iv(p6);
    glEnd();
    glPushMatrix();
    glTranslatef(400, 280, 0);
    glScalef(30, 30, 0);
    treeInit(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(110, 165, 0);
    glScalef(20, 20, 0);
    treeInit(10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(180, 340, 0);
    drawFireCracker();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(120, 340, 0);
    drawFireCracker();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(300, 250, 0);
    glScalef(1.1, 0.8, 0.0);
    glRotatef(270, 0, 0, 1);
    drawFireCracker();
    glPopMatrix();






}

void DrawStar(float cx, float cy, float R, float r, float o)
{
    float x0, y0, x1, y1;
    float o0 = o; //大圆对应角度
    float o1 = o + 0.2 * 3.14; //小圆对应角度
    for (int i = 0; i < 10; i++)
    {
        x0 = cx + R * cos(o0);//大圆对应的x坐标
        y0 = cy + R * sin(o0);//大圆对应y坐标
        x1 = cx + r * cos(o1);//小圆对应x坐标
        y1 = cy + r * sin(o1);//小圆对应y坐标
        if (i % 2 == 0)
        {
            glColor3f(1, 1, 0);
        }
        else
        {
            glColor3f(0.92, 0.89, 0.41);
        }
        glBegin(GL_POLYGON);//绘制
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glVertex2f(cx, cy);
        glEnd();
        if (i % 2 == 0)
        {
            o0 = o0 + 0.4 * 3.14;//大圆对应角度变换
        }
        else
        {
            o1 = o1 + 0.4 * 3.14;//小圆对应角度变换
        }
    }
}

void drawflower() {
    double x, y;
    double t;
    double r = 100;
    glBegin(GL_LINE_STRIP);
    for (t = 0; t <= 360; t += 0.1)
    {
        x = 5 * (2 + sin(6 * t)) * cos(t);
        y = 5 * (2 + sin(6 * t)) * sin(t);
        glVertex3f(x, y, 0);
    }
    glEnd();
}
void restTranslation() {
    x_move = 0.0;
    y_move = 0.0;
    z_rotation = 0.0;
    zoom = 1.0;
    viewAngleX = 0.0;
    viewAngleY = 0.0;
}

void layer2() {
    //the lower polygen
    int p1[] = { 0,0 };
    int p2[] = { 0,266 };
    int p3[] = { 77,133 };
    int p4[] = { 423,266 };
    int p5[] = { 500,133 };
    int p6[] = { 500,0 };
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2iv(p1);
    glColor3ub(227, 207, 87);
    glVertex2iv(p2);
    glColor3ub(255, 153, 18);
    glVertex2iv(p3);
    glColor3ub(255, 227, 132);
    glVertex2iv(p4);
    glColor3ub(255, 215, 0);
    glVertex2iv(p5);
    glColor3ub(255, 128, 0);
    glVertex2iv(p6);
    glEnd();
    glPushMatrix();
    glTranslatef(420, 150, 0);


    glScalef(0.9, 0.9, 0);
    drawlantern();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130, 90, 0);
    glScalef(1.4, 1.2, 0);
    drawDialogBox();
    glPopMatrix();


    selectFont(48, 0, ANSI_CHARSET, "Comic Sans MS");
    glColor3ub(0, 0, 0);
    glRasterPos2f(149, 100);
    drawString("I wish you success,");
    glRasterPos2f(149, 100);
    drawString("I wish you success,happy");
    glRasterPos2f(190, 120);
    drawString("Happy new year");
    glRasterPos2f(148, 80);
    drawString("smile always accompany you!");
    glRasterPos2f(148, 60);
    drawString("May you march forward.");


    glColor3ub(255, 0, 0);
    glRasterPos2f(148, 40);
    drawString("Press 'o' to open the card");


    glPushMatrix();
    glTranslatef(60, 70, 0);
    glScalef(1.2, 1.1, 0);
    drawSimelingFace();
    glPopMatrix();







}

void rabbit() {

    glColor3ub(255, 227, 132);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.9, 0.15);
    glVertex2f(1.9, 0);
    glVertex2f(1.87, -0.61);
    glVertex2f(2.1, -1.01);
    glVertex2f(2.04, -1.33);
    glVertex2f(1.95, -1.4);
    glVertex2f(2.17, -1.42);
    glVertex2f(2.53, -0.87);
    glVertex2f(2.57, -0.52);
    glVertex2f(2.33, 0.158);
    glVertex2f(2.25, 0.135);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.33, 0.158);
    glVertex2f(2.57, -0.52);
    glVertex2f(2.53, -0.87);
    glVertex2f(2.17, -1.42);
    glVertex2f(2.33, -1.3);
    glVertex2f(2.6655, -1.33);
    glVertex2f(2.55, -1.13);
    glVertex2f(2.72, -0.7);
    glVertex2f(2.88, -0.58);
    glVertex2f(3.06, -0.61);
    glVertex2f(3.16, -1);
    glVertex2f(3.21, -0.79);
    glVertex2f(3.04, -0.24);
    glVertex2f(2.72, -0.1);
    glVertex2f(2.49, 0.21);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.6655, -1.33);
    glVertex2f(2.55, -1.13);
    glVertex2f(2.72, -0.7);
    glVertex2f(2.59, -1.11);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.2, -1.38);
    glVertex2f(2.33, -1.3);
    glVertex2f(2.6655, -1.33);
    glVertex2f(2.59, -1.11);
    glVertex2f(2.72, -0.7);
    glVertex2f(2.88, -0.58);
    glVertex2f(3.04, -0.68);
    glVertex2f(3.16, -1);
    glVertex2f(3.13, -1.2);
    glVertex2f(3, -1.4);
    glVertex2f(2.44, -1.47);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.2, -1.38);
    glVertex2f(2.44, -1.47);
    glVertex2f(2.18, -1.48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(3, -1.4);
    glVertex2f(3.08, -1.24);
    glVertex2f(3.18, -1.28);
    glVertex2f(3.28, -1.33);
    glVertex2f(3.25, -1.45);
    glVertex2f(3.1, -1.485);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.878, -1.482);
    glVertex2f(2.16, -1.48);
    glVertex2f(2.17, -1.42);
    glVertex2f(1.95, -1.42);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.955, -0.75);
    glVertex2f(2.04, -1.11);
    glVertex2f(1.98, -1.32);
    glVertex2f(1.92, -1.34);
    glVertex2f(1.872, -1.38);
    glVertex2f(1.95, -1.4);
    glVertex2f(2.04, -1.33);
    glVertex2f(2.1, -1.01);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.872, -1.38);
    glVertex2f(1.83, -1.452);
    glVertex2f(1.92, -1.453);
    glVertex2f(1.95, -1.4);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.9, 0.15);
    glVertex2f(1.755, 0.22);
    glVertex2f(1.755, 0.35);
    glVertex2f(1.854, 0.42);
    glVertex2f(1.98, 0.58);
    glVertex2f(2.17, 0.655);
    glVertex2f(2.3, 0.65);
    glVertex2f(2.32, 0.52);
    glVertex2f(2.477, 0.46);
    glVertex2f(2.49, 0.21);
    glVertex2f(2.33, 0.158);
    glVertex2f(2.25, 0.135);
    glVertex2f(2.49, 0.21);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.17, 0.655);
    glVertex2f(2.22, 0.755);
    glVertex2f(2.06, 1.2);
    glVertex2f(2.21, 1.06);
    glVertex2f(2.34, 0.83);
    glVertex2f(2.29, 0.73);
    glVertex2f(2.3, 0.65);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.477, 0.46);
    glVertex2f(2.32, 0.52);
    glVertex2f(2.3, 0.65);
    glVertex2f(2.29, 0.73);
    glVertex2f(2.34, 0.83);
    glVertex2f(2.43, 0.98);
    glVertex2f(2.43, 0.61);
    glVertex2f(2.55, 0.625);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.43, 0.98);
    glVertex2f(2.43, 0.61);
    glVertex2f(2.55, 0.625);
    glVertex2f(2.675, 0.75);
    glVertex2f(2.76, 1);
    glVertex2f(2.74, 1.3);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.76, 0.295);
    glVertex2f(1.755, 0.35);
    glVertex2f(1.854, 0.42);
    glVertex2f(1.865, 0.32);
    glVertex2f(1.81, 0.27);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(2.08, 0.415);
    glVertex2f(2.1, 0.49);
    glVertex2f(2.17, 0.52);
    glVertex2f(2.23, 0.49);
    glVertex2f(2.23, 0.42);
    glVertex2f(2.19, 0.39);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.88, 0.22);
    glVertex2f(1.91, 0.24);
    glVertex2f(2.08, 0.045);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.92, 0.265);
    glVertex2f(1.93, 0.31);
    glVertex2f(2.16, 0.26);
    glEnd();
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(1.79, 0.36);
    glVertex2f(1.735, 0.56);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(1.854, 0.42);
    glVertex2f(1.86, 0.64);
    glEnd();




}





void frame()
{
    glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth(10.0f);
    glBegin(GL_POLYGON);
    glColor3f(1, 0.498, 0.32);
    glVertex2f(1, 0);
    glVertex2f(499, 0);
    glVertex2f(499, 399);
    glVertex2f(0, 399);
    // 绘制四边形结束
    glEnd();
    glPolygonMode(GL_FRONT, GL_FILL);



}

void maincontent() {

    glBegin(GL_QUADS);
    glColor3f(0.89, 0.09, 0.05);
    glVertex2f(0, 0);
    glColor3f(1, 0, 0);
    glVertex2f(500, 0);
    glColor3f(0.1, 0.1, 0.1);
    glVertex2f(500, 500);
    glColor3f(0, 0, 0);
    glVertex2f(0, 500);
    glShadeModel(GL_SMOOTH);
    glEnd();

    //Background end



    glColor3ub(235, 142, 85);
    selectFont(68, 48, GB2312_CHARSET, "楷体_GB2312");
    glRasterPos2f(177, 360);
    drawCNString("z新年好");

    selectFont(36, 24, ANSI_CHARSET, "Comic Sans MS");
    glColor3ub(235, 142, 85);
    glRasterPos2f(185, 340);
    drawString("Xinnian hao");

    glColor3ub(235, 142, 85);
    selectFont(36, 24, GB2312_CHARSET, "楷体_GB2312");
    glRasterPos2f(217, 40);
    drawCNString("兔年");

    selectFont(48, 36, ANSI_CHARSET, "Comic Sans MS");
    glColor3ub(235, 142, 85);
    glRasterPos2f(98, 20);
    drawString("Year of the Rabbit");

    glPushMatrix();
    glTranslatef(-15, 205, 0);
    glScalef(110, 100, 0);
    rabbit();
    glPopMatrix();
    frame();

    glBegin(GL_QUADS);
    glColor3ub(227, 23, 13);
    glVertex2f(45, 320);
    glVertex2f(85, 320);
    glVertex2f(85, 88);
    glVertex2f(45, 88);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(227, 23, 13);
    glVertex2f(455, 320);
    glVertex2f(415, 320);
    glVertex2f(415, 88);
    glVertex2f(455, 88);
    glEnd();

    selectFont(48, 36, GB2312_CHARSET, "华文仿宋");
    glColor3ub(0, 0, 0);
    glRasterPos2f(42, 301);
    drawCNString("神");
    glRasterPos2f(42, 271);
    drawCNString("舟");
    glRasterPos2f(42, 241);
    drawCNString("喜");
    glRasterPos2f(42, 211);
    drawCNString("慶");
    glRasterPos2f(42, 181);
    drawCNString("萬");
    glRasterPos2f(42, 151);
    drawCNString("象");
    glRasterPos2f(42, 121);
    drawCNString("一");
    glRasterPos2f(42, 91);
    drawCNString("新");

    selectFont(48, 36, GB2312_CHARSET, "华文仿宋");
    glColor3ub(0, 0, 0);
    glRasterPos2f(412, 301);
    drawCNString("瑞");
    glRasterPos2f(412, 271);
    drawCNString("兔");
    glRasterPos2f(412, 241);
    drawCNString("祥");
    glRasterPos2f(412, 211);
    drawCNString("臨");
    glRasterPos2f(412, 181);
    drawCNString("春");
    glRasterPos2f(412, 151);
    drawCNString("暉");
    glRasterPos2f(412, 121);
    drawCNString("大");
    glRasterPos2f(412, 91);
    drawCNString("地");

    selectFont(20, 10, ANSI_CHARSET, "Comic Sans MS");
    glColor3f(1, 1, 1);
    if (is_instru) {
        glRasterPos2f(90, 100);
        drawString("Try to press 'w''a''s''d''z'''x' to change the card position");
        glRasterPos2f(90, 90);
        drawString("Hold left or right mouse and move to rotate the card");
        glRasterPos2f(90, 80);
        drawString("press r to reset the card");
    }
    else
    {
        glRasterPos2f(290, 300);
        drawString("press 'i' to see or hide");
        glRasterPos2f(290, 290);
        drawString("the instructions");

    }



    default_random_engine e(time(0));
    uniform_real_distribution<double> u1(0, 500);
    uniform_real_distribution<double> u2(0, 400);
    int Number = 15;
    for (int i = 0; i < Number; i++) {
        float star_x = u1(e);
        float star_y = u2(e);
        glPushMatrix();
        glTranslatef(star_x, star_y, 0);
        glScalef(scalesize, scalesize, 0);
        glRotatef(rs, 0, 0, 1);
        DrawStar(0, 0, 12, 5, 0.5 * 3.14);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(40, 360, 0);
    glScalef(2, 2, 0);
    drawflower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(40, 40, 0);
    glScalef(2, 2, 0);
    drawflower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(460, 360, 0);
    glScalef(2, 2, 0);
    glRotatef(-30, 0, 0, 1);
    drawflower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(460, 40, 0);
    glScalef(2, 2, 0);
    glRotatef(-30, 0, 0, 1);
    drawflower();
    glPopMatrix();


}
void OnTimer1(int value)
{
    if (t1 < 400) {
        t1 += 10;
    }
    glutTimerFunc(time_interval, OnTimer1, 1);
}
//curve up and down

void OnTimer2(int value)
{
    rs += 5;
    if (rs >= 360)
        rs = 0;
    else if (rs <= 0)
        rs = 359;

    scalesize -= 0.1;
    if (scalesize <= -0.8)
        scalesize = 0.8;
    glutTimerFunc(time_interval, OnTimer2, 2);
}


void keyboard_input(unsigned char key, int x, int y)
{
    if (key == 'o' || key == 'O')
    {
        glutTimerFunc(time_interval, OnTimer1, 1);
    }

    if (key == 'q' || key == 'Q') { exit(0); }	//quit
    else if (key == 'd' || key == 'D')       x_move += 5.0;	//Move in the positive direction of X axis
    else if (key == 'a' || key == 'A')       x_move -= 5.0f;	//Move in the negative direction of X axis
    else if (key == 'w' || key == 'W')       y_move += 5.0f;	//Move in the positive direction of Y axis
    else if (key == 's' || key == 'S')       y_move -= 5.0f;	//Move in the negative direction of Y axis
    else if (key == 'z' || key == 'Z')       zoom += 0.05f;		//enlarge
    else if (key == 'x' || key == 'X')       zoom -= 0.05f;
    else if (key == 'r' || key == 'R')       restTranslation();
    else if (key == 'i' || key == 'I')       					//siwitch between coverTime page and content page
        if (is_instru) {
            is_instru = false;
        }
        else {
            is_instru = true;

        }	//shrink
    //when press "w" key layer 1 goes up, layer two goes down
}
void myMouse(int button, int state, int x, int y)
{
    mouse_X = x;
    mouse_Y = y;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if (state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if (state == GLUT_UP)
            mouseRightDown = false;
    }
}

//Monitor mouse movement
void myMouseMotion(int x, int y)
{
    if (mouseLeftDown)
    {
        viewAngleY += (x - mouse_X);
        viewAngleX += (y - mouse_Y);
        mouse_X = x;
        mouse_Y = y;
    }
    if (mouseRightDown)
    {
        z_rotation += (y - mouse_Y) * 0.3f;
        mouse_Y = y;
    }
}



void when_in_mainloop()
{ // idle callback function
    glutPostRedisplay(); // force OpenGL to redraw the current window
}




///////////////////////////////////
void define_to_OpenGL()
{
    glClearColor(0.254, 0.411, 0.88, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 400);



    glPushMatrix();
    glTranslatef(x_move, y_move, 0);
    glScalef(zoom, zoom, 0);
    glRotatef(z_rotation, 0, 0, 1);
    glRotatef(viewAngleX, 1, 0, 0);
    glRotatef(viewAngleY, 0, 1, 0);
    maincontent();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, t1, 0);
    layer1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -t1, 0);
    layer2();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Graphics Primitives");
    glutDisplayFunc(define_to_OpenGL);
    glutIdleFunc(when_in_mainloop);
    glutTimerFunc(time_interval, OnTimer2, 2);
    glutKeyboardFunc(keyboard_input);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMouseMotion);
    glutMainLoop();
}