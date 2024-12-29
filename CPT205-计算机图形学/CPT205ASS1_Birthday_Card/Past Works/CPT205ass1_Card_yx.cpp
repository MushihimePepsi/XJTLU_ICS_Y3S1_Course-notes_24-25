#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <math.h>

const float PI = 3.14159265358979323846;
float circleX = 250; // 圆的初始位置
float circleY = 100;
float translationSpeed = 2; // 平移速度
bool flag = true;
int x, y = 0;
float starX;
float starY;
float starSize;
float starX1;
float starY1;
float starSize1;
float starX2;
float starY2;
float starSize2;
float starX3;
float starY3;
float starSize3;
float starX4;
float starY4;
float starSize4;
float starX5;
float starY5;
float starSize5;
float starX6;
float starY6;
float starSize6;
float starX7;
float starY7;
float starSize7;
float starX8;
float starY8;
float starSize8;
float starX9;
float starY9;
float starSize9;
float starX10;
float starY10;
float starSize10;
float starX11;
float starY11;
float starSize11;
int characterX = 0; // 鼠标点击点的X坐标
float angle = 0.0f; // 矩形的旋转角度

float randomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
}

void drawback()  //绘制背景色
{
    glBegin(GL_QUADS);
    glColor3f(200.0 / 255.0, 219.0 / 255.0, 228.0 / 255.0);
    glVertex2f(0, 0);  // 左下角顶点
    glVertex2f(0, 500);   // 左上角顶点
    glColor3f(120.0 / 255.0, 147.0 / 255.0, 168.0 / 255.0);
    glVertex2f(180, 500);    // 右上角顶点
    glVertex2f(180, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(120.0 / 255.0, 147.0 / 255.0, 168.0 / 255.0);
    glVertex2f(180, 0);  // 左下角顶点
    glVertex2f(180, 500);   // 左上角顶点
    glVertex2f(200, 500);    // 右上角顶点
    glVertex2f(200, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(120.0 / 255.0, 147.0 / 255.0, 168.0 / 255.0);
    glVertex2f(200, 0);  // 左下角顶点
    glVertex2f(200, 500);   // 左上角顶点
    glColor3f(157.0 / 255.0, 184.0 / 255.0, 205.0 / 255.0);
    glVertex2f(280, 500);    // 右上角顶点
    glVertex2f(280, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(157.0 / 255.0, 184.0 / 255.0, 205.0 / 255.0);
    glVertex2f(280, 0);  // 左下角顶点
    glVertex2f(280, 500);   // 左上角顶点
    glVertex2f(300, 500);    // 右上角顶点
    glVertex2f(300, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(157.0 / 255.0, 184.0 / 255.0, 205.0 / 255.0);
    glVertex2f(300, 0);  // 左下角顶点
    glVertex2f(300, 500);   // 左上角顶点
    glColor3f(120.0 / 255.0, 147.0 / 255.0, 168.0 / 255.0);
    glVertex2f(380, 500);    // 右上角顶点
    glVertex2f(380, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(120.0 / 255.0, 147.0 / 255.0, 168.0 / 255.0);
    glVertex2f(380, 0);  // 左下角顶点
    glVertex2f(380, 500);   // 左上角顶点
    glVertex2f(400, 500);    // 右上角顶点
    glVertex2f(400, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(173.0 / 255.0, 167.0 / 255.0, 177.0 / 255.0);
    glVertex2f(400, 0);  // 左下角顶点
    glVertex2f(400, 500);   // 左上角顶点
    glColor3f(217.0 / 255.0, 188.0 / 255.0, 175.0 / 255.0);
    glVertex2f(500, 500);    // 右上角顶点
    glVertex2f(500, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(217.0 / 255.0, 188.0 / 255.0, 175.0 / 255.0);
    glVertex2f(500, 0);  // 左下角顶点
    glVertex2f(500, 500);   // 左上角顶点
    glColor3f(244.0 / 255.0, 221.0 / 255.0, 206.0 / 255.0);
    glVertex2f(600, 500);    // 右上角顶点
    glVertex2f(600, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(244.0 / 255.0, 221.0 / 255.0, 206.0 / 255.0);
    glVertex2f(600, 0);  // 左下角顶点
    glVertex2f(600, 500);   // 左上角顶点
    glVertex2f(620, 500);    // 右上角顶点
    glVertex2f(620, 0);   // 右下角顶点
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(244.0 / 255.0, 221.0 / 255.0, 206.0 / 255.0);
    glVertex2f(620, 0);  // 左下角顶点
    glVertex2f(620, 500);   // 左上角顶点
    glColor3f(215.0 / 255.0, 219.0 / 255.0, 221.0 / 255.0);
    glVertex2f(800, 500);    // 右上角顶点
    glVertex2f(800, 0);   // 右下角顶点
    glEnd();
}

void drawcb(float w)    //绘制cb
{
    if (flag) {
        glColor3f(1.0, 1.0, 1.0);
        glLineWidth(w); // 设置边框线宽为2.0
        glBegin(GL_LINE_LOOP);
        glVertex2f(300, 350);
        glVertex2f(330, 350);
        glVertex2f(340, 330);
        glVertex2f(360, 330);
        glVertex2f(360, 350);
        glVertex2f(500, 350);
        glVertex2f(500, 240);
        glVertex2f(460, 240);
        glVertex2f(460, 300);
        glVertex2f(420, 300);
        glVertex2f(380, 240);
        glVertex2f(300, 240);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(324, 350);
        glVertex2f(336, 325);
        glVertex2f(365, 325);
        glVertex2f(365, 350);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(300, 240);
        glVertex2f(300, 235);
        glVertex2f(383, 235);
        glVertex2f(423, 295);
        glVertex2f(455, 295);
        glVertex2f(455, 235);
        glVertex2f(500, 235);
        glVertex2f(500, 240);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(310, 235);
        glVertex2f(310, 190);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(490, 235);
        glVertex2f(490, 215);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(300, 188);
        glVertex2f(300, 165);
        glVertex2f(500, 165);
        glVertex2f(500, 215);
        glVertex2f(435, 215);;
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(500, 210);
        glVertex2f(438, 210);
        glVertex2f(300, 183);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(300, 170);
        glVertex2f(500, 170);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(310, 165);
        glVertex2f(310, 145);
        glVertex2f(490, 145);
        glVertex2f(490, 165);
        glEnd();
    }
}

void drawtext(const char* text) {
    // 绘制文本
    if (flag) {
        while (*text)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
            ++text;
        }
    }
}
void drawtext1(const char* text) {
    // 绘制文本
    if (!flag) {
        while (*text)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
            ++text;
        }
    }
}

void drawtext2(const char* text) {
    // 绘制文本
    if (!flag) {
        while (*text)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            ++text;
        }
    }
}

void drawtext3(const char* text) {
    // 绘制文本
    if (circleX == 550 && flag) {
        while (*text)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text);
            ++text;
        }
    }
}

void drawString(const char* str)
{
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    len = 0;
    for (i = 0; str[i] != '\0'; ++i)
    {
        if (IsDBCSLeadByte(str[i]))
            ++i;
        ++len;
    }

    wstring = (wchar_t*)malloc((static_cast<unsigned long long>(len) + 1) * sizeof(wchar_t));
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

void selectFont(int size, int charset, const char* face)
{
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
                              charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void drawtext4() {
    if (flag) {
        glColor3f(1.0, 1.0, 1.0);
        selectFont(35, ANSI_CHARSET, "Lucida Handwriting");
        glRasterPos2f(160, 400);
        drawString("2024 XJTLU Graduation Ceremony");
    }
}

void drawzfj()    //纸飞机
{
    if (flag) {
        glColor3f(1.0, 1.0, 1.0);
    }
    else {
        glColor3f(143.0 / 255.0, 103.0 / 255.0, 59.0 / 255.0);
    }
    glLineWidth(2); // 设置边框线宽为2.0
    glBegin(GL_LINE_LOOP);
    glVertex2f(220, 145);
    glVertex2f(100, 130);
    glVertex2f(120, 105);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(120, 105);
    glVertex2f(120, 85);
    glVertex2f(220, 145);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(220, 145);
    glVertex2f(155, 62);
    glVertex2f(130, 91);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(120, 85);
    glVertex2f(134, 86.36);
    glEnd();

}

void drawbsm()     //博士帽
{
    if (flag) {

        glColor3f(1.0, 1.0, 1.0);
        glLineWidth(2); // 设置边框线宽为2.0
        glBegin(GL_LINE_LOOP);
        glVertex2f(640, 150);
        glVertex2f(580, 120);
        glVertex2f(640, 90);
        glVertex2f(700, 120);
        glEnd();
        glBegin(GL_LINE_STRIP);
        float radius = 120;
        for (int i = 250; i <= 290; ++i)
        {
            float angle = i * PI / 180.0f;
            float x = 640 + radius * cos(angle);
            float y = 185 + radius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
        float a = 640 + radius * cos(250 * PI / 180.0f);
        float b = 185 + radius * sin(250 * PI / 180.0f);
        float c = 640 + radius * cos(290 * PI / 180.0f);
        float d = 185 + radius * sin(290 * PI / 180.0f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(a, b);
        glVertex2f(a, -0.5 * a + 410);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(c, d);
        glVertex2f(c, 0.5 * c - 230);
        glEnd();
        glLineWidth(1);
        glBegin(GL_LINE_STRIP);
        glVertex2f(640, 120);
        glVertex2f(695, 113);
        glVertex2f(695, 75);
        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(694, 75);
        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(640, 119);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(695, 75);
        glVertex2f(695, 60);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(693, 75);
        glVertex2f(693, 60);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(697, 75);
        glVertex2f(697, 60);
        glEnd();
    }
}

void drawline() {
    if (flag) {

        glColor3f(1.0, 1.0, 1.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2, 0x00FF); // 设置虚线模式

        glLineWidth(4);
        glBegin(GL_LINES);

        glVertex2f(250, 86.5);
        glVertex2f(550, 86.5);
        glEnd();

        glDisable(GL_LINE_STIPPLE);

    }
}


void drawCircle(float radius)
{
    if (flag) {
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; ++i)
        {
            float angle = i * PI / 180.0f;
            float x = circleX + radius * cos(angle);
            float y = circleY + radius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        characterX = x; // 记录鼠标点击点的X坐标
    }
}

void motion(int x, int y)
{
    int dx = x - characterX; // 计算鼠标拖动的距离

    angle += dx * 0.2f; // 根据距离来确定旋转角度

    characterX = x; // 更新鼠标点击点的X坐标

    glutPostRedisplay();
}

void drawinvitation() {
    if (!flag) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, 0.5);
        glBegin(GL_POLYGON);
        glVertex2f(70 + ::x, 70 + ::y);
        glVertex2f(70 + ::x, 430 + ::y);
        glVertex2f(730 + ::x, 430 + ::y);
        glVertex2f(730 + ::x, 70 + ::y);
        glEnd();
        glDisable(GL_BLEND);

        glColor3f(143.0 / 255.0, 103.0 / 255.0, 59.0 / 255.0);// 设置文本绘制颜色
        glRasterPos2f(305 + ::x, 380 + ::y);// 设置文本位置
        drawtext1("I N V I T A T I O N");
        glColor3f(143.0 / 255.0, 103.0 / 255.0, 59.0 / 255.0);// 设置文本绘制颜色
        glRasterPos2f(130 + ::x, 310 + ::y);// 设置文本位置
        drawtext2("Dear students,");
        glColor3f(143.0 / 255.0, 103.0 / 255.0, 59.0 / 255.0);// 设置文本绘制颜色
        glRasterPos2f(130 + ::x, 280 + ::y);// 设置文本位置
        drawtext2("We sincerely invite you to participant in 2024 XJTLU Graduation ");
        glRasterPos2f(130 + ::x, 250 + ::y);// 设置文本位置
        drawtext2("Ceremony and look forward to seeing you again and celebrating");
        glRasterPos2f(130 + ::x, 220 + ::y);// 设置文本位置
        drawtext2("your graduation together.");
        glRasterPos2f(550 + ::x, 180 + ::y);// 设置文本位置
        drawtext2("Best wishes!");
        glRasterPos2f(570 + ::x, 150 + ::y);// 设置文本位置
        drawtext2("XJTLU");
    }
    glutPostRedisplay();
}

void drawStar(float x, float y, float size)
{
    if (!flag) {
        glColor3f(253.0 / 255.0, 204.0 / 255.0, 10.0 / 255.0);
        glBegin(GL_POLYGON);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + 4.5 * size);
        glVertex2f(x - size, y + size);
        glVertex2f(x - size * 4.5, y);
        glVertex2f(x - size, y - size);
        glVertex2f(x, y - size * 4.5);
        glVertex2f(x + size, y - size);
        glVertex2f(x + size * 4.5, y);
        glEnd();
    }

}

void timer(int value)
{
    // 边界检查，如果圆超出屏幕范围，反向平移
    if (circleX < 550)
    {
        circleX += translationSpeed;
    }
    glutPostRedisplay();
    glutTimerFunc(32, timer, 0); // 设置定时器回调函数
}

void timer1(int value)
{
    starX = randomFloat(0, 90);
    starY = randomFloat(0, 500);
    starSize = randomFloat(3, 5);
    starX1 = randomFloat(0, 800);
    starY1 = randomFloat(410, 500);
    starSize1 = randomFloat(3, 5);
    starX2 = randomFloat(0, 800);
    starY2 = randomFloat(0, 90);
    starSize2 = randomFloat(3, 5);
    starX3 = randomFloat(710, 800);
    starY3 = randomFloat(0, 500);
    starSize3 = randomFloat(3, 5);
    starX4 = randomFloat(0, 90);
    starY4 = randomFloat(0, 500);
    starSize4 = randomFloat(3, 5);
    starX5 = randomFloat(0, 800);
    starY5 = randomFloat(410, 500);
    starSize5 = randomFloat(3, 5);
    starX6 = randomFloat(0, 800);
    starY6 = randomFloat(0, 90);
    starSize6 = randomFloat(3, 5);
    starX7 = randomFloat(710, 800);
    starY7 = randomFloat(0, 500);
    starSize7 = randomFloat(3, 5);
    starX8 = randomFloat(0, 90);
    starY8 = randomFloat(0, 500);
    starSize8 = randomFloat(3, 5);
    starX9 = randomFloat(0, 800);
    starY9 = randomFloat(410, 500);
    starSize9 = randomFloat(3, 5);
    starX10 = randomFloat(0, 800);
    starY10 = randomFloat(0, 90);
    starSize10 = randomFloat(3, 5);
    starX11 = randomFloat(710, 800);
    starY11 = randomFloat(0, 500);
    starSize11 = randomFloat(3, 5);

    glutTimerFunc(500, timer1, 0);
    glutPostRedisplay();  // 触发重绘

}

void keyboard_input(unsigned char key, int x, int y) // keyboard interactions
{
    if (key == 'q' || key == 'Q')
        exit(0);
    else if (key == 'o' || key == 'O') // 打开邀请函
        flag = !flag;
    else if (key == 'w' || key == 'W')
        ::y++;
    else if (key == 's' || key == 'S')
        ::y--;
    else if ((key == 'a' || key == 'A') && ::x > -70)
        ::x--;
    else if (key == 'd' || key == 'D')
        ::x++;
    else if (key == 'r' || key == 'R') {
        ::x = 0;
        ::y = 0;
        circleX = 250;
    }
}

void myDisplay(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  //清除颜色缓冲区，即设置背景颜色。
    drawback();  // 绘制邀请函背景
    drawcb(2);  //绘制cb
    drawtext4();
    glColor3f(217.0 / 255.0, 188.0 / 255.0, 175.0 / 255.0);// 设置文本绘制颜色
    glRasterPos2f(120, 250);// 设置文本位置
    drawtext("X J T L U");
    glColor3f(157.0 / 255.0, 184.0 / 255.0, 205.0 / 255.0);// 设置文本绘制颜色
    glRasterPos2f(590, 250);// 设置文本位置
    drawtext("F U T U R E");
    glColor3f(1.0, 1.0, 1.0);// 设置文本绘制颜色
    glRasterPos2f(320, 60);// 设置文本位置
    drawtext("L O A D I N G . . .");
    glColor3f(0, 0, 0);// 设置文本绘制颜色
    glRasterPos2f(570, 30);// 设置文本位置
    drawtext3("Click 'o' or 'O' to open the invitation");
    drawbsm();
    drawline();



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angle, 0, 0, 1.0f);
    drawinvitation();
    drawStar(starX, starY, starSize);
    drawStar(starX1, starY1, starSize1);
    drawStar(starX2, starY2, starSize2);
    drawStar(starX3, starY3, starSize3);
    drawStar(starX4, starY4, starSize4);
    drawStar(starX5, starY5, starSize5);
    drawStar(starX6, starY6, starSize6);
    drawStar(starX7, starY7, starSize7);

    drawzfj();
    glColor3f(1.0f, 1.0f, 1.0f); // 设置颜色为白色
    drawCircle(10); // 绘制半径为 0.1 的圆
    glutSwapBuffers();



    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 500);
    glutCreateWindow("2024 XJTLU Graduation Ceremony Invitation");
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard_input);
    reshape(800, 500);
    glutReshapeFunc(reshape);
    glutTimerFunc(500, timer1, 0);
    glutTimerFunc(0, timer, 0); // 设置初始定时器回调函数
    glutMouseFunc(mouse);
    glutMotionFunc(motion);


    glutMainLoop();

    return 0;
}