#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include "vector"
#define PI 3.14159265358979323846
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace std;
GLint imagewidth0, imagewidth1, imagewidth2, imagewidth3;
GLint imageheight0, imageheight1, imageheight2, imageheight3;
GLint pixellength0, pixellength1, pixellength2, pixellength3;
vector<GLubyte*>p; // Similar to GLubyte* for program 3 but for 2 images (so a vector)
GLuint textures[13];
GLfloat angle = 0;

float carSpeed = 5.0f;  // 米每秒
float distanceTraveled = 0.0;
float carX = 6.0f;  // 汽车的 x 位置
float curRotate = 0.0f;
bool turnLeft = FALSE;
bool turnRight = FALSE;
bool lightFlag = FALSE;
bool fogFlag = FALSE;
bool endFlag = FALSE;
bool winFlag = FALSE;
long timeStamp = 0;
int fogStep = 0;
float fuelRemain = 100.0f;
float fogDense = 0.0f;
int remainingTime = 80; // 倒计时初始值（秒）

struct autoFlag{
    bool value = false;
    std::chrono::time_point<std::chrono::steady_clock> setTime;
};

autoFlag turnLeftFlag;
autoFlag turnRightFlag;
autoFlag helpFlag;
autoFlag viewFlag;
float viewStatus = 0.0;

// 改变flag状态
void setFlag(autoFlag &flag) {
    flag.value = true;
    flag.setTime = std::chrono::steady_clock::now(); // 记录当前时间
}
void cancelFlag(autoFlag &flag) {
    flag.value = false;
}

void checkFlag(autoFlag &flag, long long time) {
    if (flag.value) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - flag.setTime).count() >= time) {
            flag.value = false; // 0.5秒后设置为false
//            std::cout << "Flag reset to false." << std::endl; // 调试输出
        }
    }
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

// 加载贴图
void myinit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    glEnable(GL_TEXTURE_2D);
    ReadImage("Road_01_DIFF_512.bmp", imagewidth0, imageheight0, pixellength0);
    ReadImage("SkyDome_2x1k.bmp", imagewidth1, imageheight1, pixellength1);
    ReadImage("Desert_DIFF_512.bmp", imagewidth2, imageheight2, pixellength2);
    ReadImage("Glass_DIFF_Gamma_128.bmp", imagewidth3, imageheight3, pixellength3);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
    glGenTextures(3, &textures[0]); // number of textures names to be generated and an array of textures names

    glBindTexture(GL_TEXTURE_2D, textures[0]); // target to which textures is bound and name of a textures
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

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  // 光照模式
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void setupFog(){
    // 使用雾气
    GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, fogDense); // GL_EXP/GL_EXP2 时有意义, GL_LINEAR时无意义
    glHint(GL_FOG_HINT, GL_FASTEST); // 设置系统如何计算雾气
}

// 光照设置
void setupLighting() {
    glEnable(GL_LIGHTING);   // 启用光照
    glEnable(GL_LIGHT0);     // 启用光源 0
    float angleSun = distanceTraveled *(360.0/1000.0) +45;
    float angleSunRad = angleSun *PI /180.0;
    float dirX = -cos(angleSunRad);
    float dirY = sin(angleSunRad);
    float lightScale = (dirY+1.0)/2.0;


    // 定向光源的方向和颜色
//    GLfloat lightDirection[] = { -0.5f, 0.5f, -0.2f, 0.0f }; // 最后一个值为 0 表示定向光
    GLfloat lightDirection[] = { dirX, dirY, -0.2f, 0.0f }; // 最后一个值为 0 表示定向光

    GLfloat lightDiffuse[] = { (float)(0.9f*lightScale+0.05*(1-lightScale)),
                               (float)(1.0f*lightScale),
                               (float)(1.0f*lightScale+0.1*(1-lightScale)), 1.0f };       // 漫反射光
    GLfloat lightAmbient[] = { (float)(0.9f*lightScale+0.05*(1-lightScale)),
                               (float)(1.0f*lightScale),
                               (float)(1.0f*lightScale+0.1*(1-lightScale)), 1.0f };       // 漫反射光


    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
}

void setupPointLight(float lightX, bool lightFlag) {
    glEnable(GL_LIGHTING);   // 启用光照
    if (lightFlag) glEnable(GL_LIGHT1);     // 启用光源0
    else glDisable(GL_LIGHT1);

    // 定义点光源的位置
    GLfloat lightPos[] = { lightX, 4.0f, -16.0f, 1.0f }; // (x, y, z, 1.0) 表示点光源
    // 定义光源属性
    GLfloat lightAmbient[] = { 5.2f, 5.2f, 5.2f, 1.0f };  // 环境光成分
    GLfloat lightDiffuse[] = { 5.8f, 5.8f, 5.8f, 1.0f };  // 漫反射成分
//    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 镜面反射成分
    // 设置光源的属性
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    // 可选：调整光源衰减参数
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2f); // 二次衰减


    glEnable(GL_LIGHTING);   // 启用光照
    if (lightFlag) glEnable(GL_LIGHT2);     // 启用光源0
    else glDisable(GL_LIGHT2);

    // 定义点光源的位置
    GLfloat lightPos2[] = { 2.4, 5.0f, 13.0f, 1.0f }; // (x, y, z, 1.0) 表示点光源
    // 定义光源属性
    float mod2 = 4.0;
    GLfloat lightAmbient2[] = { 2.2f*mod2, .8f*mod2, 0.2f*mod2, 1.0f };  // 环境光成分
    GLfloat lightDiffuse2[] = { 2.8f*mod2, 1.0f*mod2, 0.5f*mod2, 1.0f };  // 漫反射成分
//    GLfloat lightSpecular2[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 镜面反射成分
    // 设置光源的属性
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
    // 可选：调整光源衰减参数
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 3.6f); // 二次衰减
}


// 设置材质
void setMaterialRoad() {
    GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 环境光
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  // 漫反射
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 100.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialPole() {
    GLfloat matAmbient[] = { 0.4f, 0.2f, 0.1f, 1.0f };  // 环境光成分
    GLfloat matDiffuse[] = { 0.7f, 0.3f, 0.0f, 1.0f };  // 漫反射成分
    GLfloat matSpecular[] = { 0.3f, 0.2f, 0.1f, 1.0f }; // 镜面反射成分
    GLfloat matShininess[] = { 1.0f };                // 高光强度

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialSky() {
    GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 环境光
    GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 漫反射
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 50.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialRuber() {
    GLfloat matAmbient[] = { 0.01f, 0.01f, 0.01f, 1.0f };  // 环境光
    GLfloat matDiffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // 漫反射
    GLfloat matSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 10.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialDarkStone() {
    GLfloat matAmbient[] = { 0.75f, 0.65f, 0.5f, 1.0f };  // 环境光
    GLfloat matDiffuse[] = { .5f, .5f, .5f, 1.0f };  // 漫反射
    GLfloat matSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 10.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialCarPaint(){
    float mod = 0.7;
    GLfloat matAmbient[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };  // 环境光
    GLfloat matDiffuse[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };  // 漫反射
    GLfloat matSpecular[] = { .00f, .00f, .00f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 100.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialCarPaint2(){
    float mod = 0.5;
    GLfloat matAmbient[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };  // 环境光
    GLfloat matDiffuse[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };  // 漫反射
    GLfloat matSpecular[] = { .00f, .00f, .00f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 100.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialGlass(){
    GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, .4f };  // 环境光
    GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, .4f };  // 漫反射
    GLfloat matSpecular[] = { 1.5f, 1.5f, 1.5f, 1.0f }; // 镜面反射
    GLfloat matShininess[] = { 1.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // 启用混合以支持透明度
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 设置混合模式
}

GLfloat matEmissionZero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
void setMaterialEmission() {
    GLfloat matEmission[] = { 0.8f, 0.2f, 0.2f, 1.0f }; // 自发光成分（红色光）
    GLfloat matAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };   // 环境光成分
    GLfloat matDiffuse[] = { 0.5f, 0.2f, 0.2f, 1.0f };   // 漫反射成分
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };  // 镜面反射成分
    GLfloat matShininess[] = { 50.0f };                  // 高光强度

    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);    // 设置自发光
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);      // 设置环境光
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);      // 设置漫反射
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);    // 设置镜面反射
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);  // 设置高光
}

void setMaterialGasTank() {
    float mod = 0.8;
    GLfloat matAmbient[] = { 0.9f*mod, 0.1f*mod, 0.02f*mod, 1.0f };  // 环境光成分
    GLfloat matDiffuse[] = { 0.9f*mod, 0.1f*mod, 0.02f*mod, 1.0f };  // 漫反射成分
    GLfloat matSpecular[] = { 0.9f*mod, 0.1f*mod, 0.02f*mod, 1.0f }; // 镜面反射成分
    GLfloat matShininess[] = { 1.0f };                // 高光强度

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}


// 绘制抛物线
void drawParabola(float transZ) {
    setMaterialRuber();
    glLineWidth(1.6f);
    glPushMatrix();
    glTranslatef(0,4.8,transZ);
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 16.0f; t += 0.1f) {
        float x = 8.35f;                   // 固定 x 值
        float y = 0.02f * t * t - 0.32f * t; // 根据 t 计算 y
        float z = t;                      // z 等于 t
        glVertex3f(x, y, z);              // 将点加入抛物线
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 16.0f; t += 0.1f) {
        float x = 8.05f;                   // 固定 x 值
        float y = 0.02f * t * t - 0.32f * t; // 根据 t 计算 y
        float z = t;                      // z 等于 t
        glVertex3f(x, y, z);              // 将点加入抛物线
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 16.0f; t += 0.1f) {
        float x = 8.65f;                   // 固定 x 值
        float y = 0.02f * t * t - 0.32f * t; // 根据 t 计算 y
        float z = t;                      // z 等于 t
        glVertex3f(x, y, z);              // 将点加入抛物线
    }
    glEnd();
    glPopMatrix();
    glLineWidth(1.0f);
}

// 渲染
void renderGroundItems() {
    // 渲染平面
    glEnable(GL_TEXTURE_2D);        // 启用纹理
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    setMaterialRoad();   // 设置road材质
    for (int i = -16; i < 4; ++i) {
        float roadOffset = i * 8.0 + fmod(distanceTraveled, 8.0);
        glBegin(GL_QUADS);              // 绘制一个四边形
        // 顶点和纹理坐标
        glNormal3f(0.0f, 1.0f, 0.0f); // 法向量（用于光照计算）向上
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -8.0f + roadOffset);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f + roadOffset);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f, 0.0f, 0.0f + roadOffset);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f, 0.0f, -8.0f + roadOffset);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //电线杆
    setMaterialPole();
    for (int fltPoleNumber = -8; fltPoleNumber < 4; fltPoleNumber += 1)
    {
        float fltPoleOffset = fltPoleNumber * 16.0 + fmod(distanceTraveled, 16.0);
        glPushMatrix();
        glTranslatef(8.5, 2.5, fltPoleOffset);
        glPushMatrix();
        glTranslatef(-0.2, 2.3, 0.0);  //位移
        glScalef(12.0, 1.0, 1.0); //长宽高
        glColor3f(1.0, 0.0, 0.0);
        glutSolidCube(.1);
        glColor3f(0.0, 1.0, 0.0);
        glutWireCube(.1);
        glPopMatrix();// 上半部分方块

        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(.7, 50.0, .7);  // 上下2.5m
        glColor3f(0.0, 0.0, 1.0);
        glutSolidCube(.1);
        glColor3f(0.0, 1.0, 1.0);
        glutWireCube(.1);
        glPopMatrix();
        glPopMatrix();
    }

//    //Re: test cube
//    glPushMatrix();
//    setMaterialPole();
//    glTranslatef(4,0.5,0);
////    glRotatef(30,1,0,0);
//    glScalef(1.0, 1.0, 1.0);
//    glutSolidCube(1);
//    glPopMatrix();

    // 渲染电线
    for (int wireNumber = -8; wireNumber < 4; wireNumber += 1){
        float wireOffset = wireNumber * 16.0 + fmod(distanceTraveled, 16.0);
        drawParabola(wireOffset);
    }

    // 渲染护栏
    for (int BarNumber = -24; BarNumber < 8; BarNumber += 1)
    {
        float barOffset = BarNumber * 4.0 + fmod(distanceTraveled, 4.0);
        glPushMatrix();
        glTranslatef(0, 0, barOffset);

        glPushMatrix();
        setMaterialDarkStone();
        glTranslatef(-0.14, 0.14, 0.0);  //位移
        glScalef(1.0, 1.4, 1.0); //长宽 高0.28
        glutSolidCube(.2);
        glPopMatrix();// 上半部分方块

        glPushMatrix();
        setMaterialRoad();
        glTranslatef(-0.14, 0.14*3, 0.0);
        glScalef(1.0, 1.4, 1.0);  //
        glutSolidCube(.2);
        glPopMatrix();

        glPushMatrix();
        setMaterialDarkStone();
        glTranslatef(-0.14, 0.14*5, 0.0);
        glScalef(1.0, 1.4, 1.0);  //
        glutSolidCube(.2);
        glPopMatrix();

        glPushMatrix();
        glLineWidth(1.5f);
        setMaterialPole();
        glTranslatef(-0.14, 0.14*3, 0.0);
        glScalef(1.0+0.1, 1.4*3+0.1, 1.0+0.1);  //
        glutWireCube(.2);
        glPopMatrix();
        glLineWidth(1.0f);

        // 右侧
        glPushMatrix();
        setMaterialDarkStone();
        glTranslatef(8.14, 0.14, 0.0);  //位移
        glScalef(1.0, 1.4, 1.0); //长宽 高0.28
        glutSolidCube(.2);
        glPopMatrix();// 上半部分方块

        glPushMatrix();
        setMaterialRoad();
        glTranslatef(8.14, 0.14*3, 0.0);
        glScalef(1.0, 1.4, 1.0);  //
        glutSolidCube(.2);
        glPopMatrix();

        glPushMatrix();
        setMaterialDarkStone();
        glTranslatef(8.14, 0.14*5, 0.0);
        glScalef(1.0, 1.4, 1.0);  //
        glutSolidCube(.2);
        glPopMatrix();

        glPushMatrix();
        glLineWidth(1.5f);
        setMaterialPole();
        glTranslatef(8.14, 0.14*3, 0.0);
        glScalef(1.0+0.1, 1.4*3+0.1, 1.0+0.1);  //
        glutWireCube(.2);
        glPopMatrix();
        glLineWidth(1.0f);
        glPopMatrix();

        glPopMatrix();
    }

}

void drawGasTank(float x, float z){
    float rotateAngle = fmod(timeStamp, 360);
    float y = (sin(timeStamp*PI/50.0) + 2)/2.0;
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(rotateAngle,0,1,0);

    glPushMatrix();
    setMaterialGasTank();
    glScalef(.5, .6, .2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    setMaterialGasTank();
    glTranslatef(-0.1,0.3,0);
    glScalef(.3, .3, .16);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    setMaterialRuber();
    glTranslatef(0.25,0.2,0);
    glRotatef(-45,0,0,1);
    glScalef(.06, .4, .06);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void drawRock(float x, float z){
    glPushMatrix();
    glTranslatef(x,.05,z);
    glRotatef(90,1,0.1,.1);

    glPushMatrix();
    setMaterialDarkStone();
    glScalef(.5, .6, .2);
    glutSolidIcosahedron();
    setMaterialRuber();
    glutWireIcosahedron();
    glPopMatrix();

    glPopMatrix();
}

void renderSand(){
    glDisable(GL_LIGHT1);
    // 渲染沙漠
    glEnable(GL_TEXTURE_2D);        // 启用纹理
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    setMaterialRoad();   // 设置road材质
    for (int i = -4; i < 2; ++i) {
        float sandLength = 32.0;
        float sandOffset = i * sandLength + fmod(distanceTraveled, sandLength);
        glBegin(GL_QUADS);  // 绘制一个四边形
        // 顶点和纹理坐标 右边
        glNormal3f(0.0f, 1.0f, 0.0f); // 法向量（用于光照计算）向上
        glTexCoord2f(0.0f, 1.0f); glVertex3f(8.0f, 0.0f, -sandLength + sandOffset);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(8.0f, 0.0f, 0.0f + sandOffset);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f + sandLength, 0.0f, 0.0f + sandOffset);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f + sandLength, 0.0f, -sandLength + sandOffset);
        glEnd();
        glBegin(GL_QUADS);  // 绘制一个四边形
        // 顶点和纹理坐标 左边
        glNormal3f(0.0f, 1.0f, 0.0f); // 法向量（用于光照计算）向上
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-sandLength, 0.0f, -sandLength + sandOffset);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-sandLength, 0.0f, 0.0f + sandOffset);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f + sandOffset);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -sandLength + sandOffset);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT1);
}


//Re: Car
void drawWheel(float x, float y, float z, float rof) {
    glPushMatrix();
        setMaterialRuber();
        glTranslatef(x, y, z);
        glRotatef(0, 1, 0, 0);  // roll
        glRotatef(90 + rof, 0, 1, 0);  //turn
        glColor3f(0.3, 0.8, 0.6);
        glutSolidCylinder(30, 10, 40, 1);
        glColor3f(0, 0, 0);
        glutWireCylinder(30, 10, 40, 1);
    glPopMatrix();
}

void drawViewMirror(float x) {
    glPushMatrix();
    setMaterialRuber();
        glTranslatef(x, 90.0, 0.0);
        glScalef(25.0, 8, 10.0);
        glColor3f(0, 0, 0);
        glutWireCube(1);
        glColor3f(1, 1, 1);
        glutSolidCube(1);
    glPopMatrix();
}

void drawCarGlass(float y, float rof) {
    glEnable(GL_TEXTURE_2D);        // 启用纹理
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    setMaterialGlass();

    glPushMatrix();
        glTranslatef(0, 100, y-185);
        glRotatef(-rof, 1, 0, 0);
        glScalef(1.38, 0.7, 1);
        glTranslatef(-150, -150, 0);
        glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, 1.0f); //norm
        glTexCoord2f(0.0f, 1.0f); glVertex3f(95, 80, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(205, 80, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(205, 200, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(95, 200, 0);
        glEnd();

    setMaterialRuber();
    glBegin(GL_LINE_STRIP);
        glVertex3f(205, 192, 0);
        glVertex3f(205, 88, 0);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3f(95, 88, 0);
        glVertex3f(95, 192, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// Using Hierarchical Modelling to design a car
void renderCar(float carX) {
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(carX, -0.02, 0.0);

    if (!turnLeftFlag.value){
        turnLeft = FALSE;
        if (curRotate>0.01) curRotate -=0.1;
        if (curRotate<0.01) curRotate +=0.1;
    }
    if (!turnRightFlag.value){
        turnRight = FALSE;
        if (curRotate>0.01) curRotate -=0.1;
        if (curRotate<0.01) curRotate +=0.1;
    }

    if (turnLeft){
        if (curRotate <5)curRotate +=0.5;
    }
    if (turnRight){
        if (curRotate >-5)curRotate -=0.5;
    }

//    printf("curRotate:%f\n", curRotate);

    glRotatef(curRotate,0,1,0);
    glScalef(0.01, 0.01, 0.01);
    glRotatef(180,0,1,0);

    glPushMatrix();
    setMaterialCarPaint();
        glTranslatef(0, 30.0, -60.0);
        glScalef(150.0+1.0, 10.0, 420.0);
        glColor3f(0.6, 0.6, 0.6);
        glutSolidCube(1);
    setMaterialRuber();
    glColor3f(0, 0, 0);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    setMaterialCarPaint2();
        glTranslatef(0, 60.0, -60.0);
        glScalef(150.0, 50, 400.0);
        glColor3f(1, 1, 0.6);
        glutSolidCube(1);
    setMaterialRuber();
        glColor3f(0, 0, 0);
        glutWireCube(1);
    glPopMatrix();

    // Middle body of the car
    glPushMatrix();
    setMaterialCarPaint();
        glTranslatef(0, 100.0, -70.0);
        glScalef(150-1.0, 50, 130.0);
        glColor3f(1, 1, 0.6);
        glutSolidCube(1);
    setMaterialRuber();
        glColor3f(0, 0, 0);
        glutWireCube(1);
    glPopMatrix();

    // Glass
    drawCarGlass(10, 120);
    // Rear view mirror
    drawViewMirror(80);
    drawViewMirror(-80);

    // Taillight
    glPushMatrix();
    setMaterialEmission();
        glTranslatef(50, 60.0, -259.0);
        glScalef(20, 8, 4);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-50, 60.0, -259.0);
        glScalef(20, 8, 4);
        glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmissionZero);
    // 4 wheels
    drawWheel(80, 30, 50, 0);
    drawWheel(80, 30, -150, 0);
    drawWheel(-90, 30, 50, 0);
    drawWheel(-90, 30, -150, 0);

    glPopMatrix();
}

void renderSkyDome() {
    setMaterialSky();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[1]); // 使用天空贴图

    // 反转法线以便将纹理贴在内表面
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // 禁用背面剔除（因为法线反转了）
    glDisable(GL_CULL_FACE);

    glTranslatef(4.0, 0.0, 0.0); // 适配平面的中心点
    glRotatef(-90, 1.0, 0.0, 0.0); // 调整天空球方向
    glRotatef(180, 0.0, 0.0, 1.0); // 调整天空球方向
    gluSphere(quadric, 200.0, 64, 64); // 绘制一个半径为 200 的球体

    // 恢复剔除设置
    glEnable(GL_CULL_FACE);
    gluDeleteQuadric(quadric);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void timerFunc(int value) {
    glutPostRedisplay(); // 标记窗口需要重新绘制
    glutTimerFunc(1000 / 60, timerFunc, 0); // 设置下次定时器回调，1/60 秒（约 16 毫秒）
}

void updateFuel(){
    //0.001 100-6
    float mod = 0.0019;
    if (!(endFlag||winFlag)){
        if (carSpeed > 10){
            fuelRemain -= carSpeed*mod*2-0.015;
        } else fuelRemain -= carSpeed*mod;
//        printf("%f\n",fuelRemain);
    }
}

// 倒计时更新函数
void updateCountdown(int value) {
    if (remainingTime > 0 && !winFlag && !endFlag) {
        remainingTime--; // 每秒减少1秒
        glutTimerFunc(1000, updateCountdown, 0); // 设置下一次定时器
    }
}




/*
 * 环境光变化；汽车吃油，油桶出现消失逻辑，路牌milestone；游戏胜利失败逻辑（限时）
 * 油桶：100，300，500，700
 * 总路程：1000m 视野-20 100
 * */
int gasTankExist[5] = {1,1,1,1,1};
int rockExist[4] = {1,1,1,1};
void gameLogic(){
    // 油桶出现消失
    if (gasTankExist[0]){
        drawGasTank(2,distanceTraveled-100);
    }
    if (gasTankExist[1]){
        drawGasTank(6,distanceTraveled-100);
    }
    if (gasTankExist[2]){
        drawGasTank(6,distanceTraveled-300);
    }
    if (gasTankExist[3]){
        drawGasTank(2,distanceTraveled-500);
    }
    if (gasTankExist[4]){
        drawGasTank(6,distanceTraveled-700);
    }
    // 汽车触发
    float curFuelRemain = fuelRemain;
    if (distanceTraveled>100 && distanceTraveled<104 && carX>1 && carX<3){
        if (gasTankExist[0]) fuelRemain = std::min(100.0f, (curFuelRemain+10));
        gasTankExist[0] = 0;
    }
    if (distanceTraveled>100 && distanceTraveled<104 && carX>5 && carX<8){
        if (gasTankExist[1]) fuelRemain = std::min(100.0f, (curFuelRemain+15));
        gasTankExist[1] = 0;
    }
    if (distanceTraveled>300 && distanceTraveled<304 && carX>5 && carX<8){
        if (gasTankExist[2]) fuelRemain = std::min(100.0f, (curFuelRemain+15));
        gasTankExist[2] = 0;
    }
    if (distanceTraveled>500 && distanceTraveled<504 && carX>1 && carX<3){
        if (gasTankExist[3]) fuelRemain = std::min(100.0f, (curFuelRemain+15));
        gasTankExist[3] = 0;
    }
    if (distanceTraveled>700 && distanceTraveled<704 && carX>5 && carX<8){
        if (gasTankExist[4]) fuelRemain = std::min(100.0f, (curFuelRemain+25));
        gasTankExist[4] = 0;
    }

    // 石头
    if (rockExist[0]){
        drawRock(2,distanceTraveled-120);
    }
    if (rockExist[1]){
        drawRock(6,distanceTraveled-200);
    }
    if (rockExist[2]){
        drawRock(2,distanceTraveled-400);
    }
    if (rockExist[3]){
        drawRock(2,distanceTraveled-700);
    }

    // 汽车触发
    if (distanceTraveled>120 && distanceTraveled<124 && carX>1 && carX<3){
        if (rockExist[0]) fuelRemain = 0;
        rockExist[0] = 0;
    }
    if (distanceTraveled>200 && distanceTraveled<204 && carX>5 && carX<8){
        if (rockExist[1]) fuelRemain = 0;
        rockExist[1] = 0;
    }
    if (distanceTraveled>400 && distanceTraveled<404 && carX>1 && carX<3){
        if (rockExist[2]) fuelRemain = 0;
        rockExist[2] = 0;
    }
    if (distanceTraveled>700 && distanceTraveled<704 && carX>1 && carX<3){
        if (rockExist[3]) fuelRemain = 0;
        rockExist[3] = 0;
    }

    // 胜利与死亡
    if (distanceTraveled>=1000){
        winFlag = TRUE;
        distanceTraveled = 1000;
        carSpeed = 0;
    }else if (fuelRemain <= 0 || remainingTime<=0){
        endFlag = TRUE;
        fuelRemain = 0;
        carSpeed = 0;
    }
}

//* 表盘
const int MAX_SPEED = 100; // 最大速度
// 绘制圆
void drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; ++i) {
        float angle = i * PI / 180.0f;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

// 使用矢量字体绘制文字
void drawLargeText(const std::string& text, float x, float y, float z, float scale) {
    glPushMatrix();
    setMaterialEmission();
    // 移动到指定位置-8.0f
    glTranslatef(x, y, z);
    // 调整字体大小
    glScalef(scale*0.6, scale, scale);
    // 绘制文字
    for (const char& c : text) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c);
    }
    glPopMatrix();
}

void drawPlainText(string string1, float x, float y){
    glPushMatrix();
    std::ostringstream stream;
    stream << string1;
    std::string text = stream.str();
    // 设置光标位置
    glRasterPos2f(x,y);
    // 绘制文字
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();
}

// 绘制刻度
void drawTicks(float radius) {
    if (lightFlag) setMaterialEmission();
    else setMaterialPole();
    for (int i = 0; i <= MAX_SPEED; i += 20) {
        float angle = (240.0f - (i * 240.0f / MAX_SPEED)) * PI / 180.0f; // 转换速度为角度
        float x1 = radius * cos(angle);
        float y1 = radius * sin(angle);
        float x2 = (radius - 0.1f) * cos(angle);
        float y2 = (radius - 0.1f) * sin(angle);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        // 绘制速度数字
        char speedLabel[4];
        sprintf(speedLabel, "%d", i);
        float textX = (radius) * cos(angle)*0.72f-0.08f;
        float textY = (radius) * sin(angle)*0.72f;
        glRasterPos2f(textX, textY);
        for (char* c = speedLabel; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
        std::ostringstream streamSpeed;
        streamSpeed <<"Speed                              Press [H] for HELP";
        std::string streamSpeedText = streamSpeed.str();
        glRasterPos2f(-0.0, -0.5);
        for (const char& c : streamSpeedText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    // 绘制文字
    // 计算燃料信息
    float fuelLiters = fuelRemain / 2.0f; // 假设需要将燃料量除以 2 转换为升
    // 格式化字符串，保留两位小数
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    stream <<"FUEL: "<< fuelLiters << "/50L <" << fuelRemain << "%>";
    std::string fuelText = stream.str();
    // 设置光标位置
    glRasterPos2f(0.6f+(carX-4)*0.6, 2);
    // 绘制文字
    setMaterialEmission();
    for (const char& c : fuelText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // 计算路程信息
    float traveledMiles = distanceTraveled/2.0f;
    float traveledProportion = distanceTraveled/10.0f;
    // 格式化字符串，保留两位小数
    std::ostringstream stream2;
    stream2 << std::fixed << std::setprecision(1);
    stream2 << "Travel:" << traveledMiles << "/500 Miles <" << traveledProportion << "%>";
    std::string fuelText2 = stream2.str();
    setMaterialRoad();
    drawLargeText(fuelText2, -3.3f, 10.3f, -8.0f, 0.005f);

    // 倒计时信息
    std::ostringstream stream3;
    stream3 << "Countdown:<" << remainingTime << "sec>";
    std::string fuelText3 = stream3.str();
    if (remainingTime<20){
        setMaterialGasTank();
    } else setMaterialEmission();
    drawLargeText(fuelText3, 1.6f, 0.0f,0.0f, 0.003f);

    // Help信息
    if (helpFlag.value){
        setMaterialEmission();
        float mod = 0.0;
        drawPlainText("HELP:",-1.3,6+mod);
        drawPlainText("Press [A][D] to Change Lanes",-1.3,5.8+mod);
        drawPlainText("Press [W][S] to Control Throttle",-1.3,5.6+mod);
        drawPlainText("Press [Space] to Turn ON Light",-1.3,5.4+mod);
        drawPlainText("Press [Q] to Quit",-1.3,5.2+mod);
        drawPlainText("Press [F] to Change VIEW",-1.3,5.0+mod);
        drawPlainText("Tips: The Faster, the MORE Fuel Consumes",-1.3,4.7+mod);
    }

    // 游戏信息
    if (fogStep>100&&fogStep<450){
        setMaterialEmission();
        drawPlainText("Caution! Heavy Fog!",0.6f+(carX-4)*0.6,4);
    }

    if (distanceTraveled>400&&distanceTraveled<600){
        setMaterialEmission();
        drawPlainText("Press [Space] to Light UP!",0.6f+(carX-4)*0.6,4);
    }

    if (winFlag){
        setMaterialRoad();
        drawLargeText("YOU DID IT!", -.1f, 5.5f, -8.0f, 0.005f);
        drawLargeText("Welcome back HOME!", -1.1f, 4.6f, -8.0f, 0.005f);
    }

    if (endFlag){
        setMaterialEmission();
        drawLargeText("Do NOT GIVE UP", -.7f, 5.5f, -8.0f, 0.005f);
        drawLargeText("YOU can DO it!", -.7f, 4.6f, -8.0f, 0.005f);
    }

    if (distanceTraveled>0&&distanceTraveled<50){
        setMaterialEmission();
        drawLargeText("Dash on Route 66", -2.4f, 7.5f, -8.0f, 0.008f);
        drawLargeText("-Go HOME on Time", -.8f, 6.4f, -8.0f, 0.004f);
        drawLargeText("-Caution ROCKs!", -.8f, 5.5f, -8.0f, 0.004f);
        drawLargeText("-Don't forget Fuel!", -.8f, 4.6f, -8.0f, 0.004f);
    }

    glMaterialfv(GL_FRONT, GL_EMISSION, matEmissionZero);
    setMaterialRuber();
}

// 绘制指针
void drawNeedle(float speed, float radius) {
    float angle = (240.0f - (speed * 240.0f / MAX_SPEED)) * PI / 180.0f;
    float x = (radius - 0.2f) * cos(angle);
    float y = (radius - 0.2f) * sin(angle);

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glEnd();
}

// 绘制速度表盘
void drawSpeedometer(float x, float y, float z, float scale, float speed) {
    glPushMatrix();
    glLineWidth(4.0f);
    // 移动和缩放
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);
    glRotatef(-30,1,0,0);

    // 绘制表盘
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(1.0f); // 使用单位圆
    // 绘制刻度
    drawTicks(1.0f);
    // 绘制指针
    glColor3f(1.0f, 0.0f, 0.0f);
    drawNeedle(speed, 1.0f);
    glLineWidth(1.0f);
    glPopMatrix();
}

// 键盘按下事件处理函数
void keyPress(unsigned char key, int x, int y) {
    if (key == 'a'|| key == 'A') {
        if (!(endFlag||winFlag)){  // make sure car won't move after end or win
            if (carX > 1.0){
                turnRight = FALSE;
                turnLeft = TRUE;
                setFlag(turnLeftFlag);
                carX -= 0.1;
            } else{
                turnRight = FALSE;
                turnLeft = FALSE;
            }
        }
    }
    else if (key == 'd'|| key == 'D') {
        if (!(endFlag||winFlag)){
            if (carX < 7.0){
                turnLeft = FALSE;
                turnRight = TRUE;
                setFlag(turnRightFlag);
                carX += 0.1;
            } else{
                turnLeft = FALSE;
                turnRight = FALSE;
            }
        }
    }
    else if ((key == 'w'|| key == 'W') && carSpeed < 25) { // 加速
        carSpeed += 1;
    }
    else if ((key == 's'|| key == 'S') && carSpeed > 5) { // 减速
        carSpeed -= 1;
    }
    else if (key == ' ') {
        lightFlag= !lightFlag;
    }
    else if (key == 'h'|| key == 'H') {
        setFlag(helpFlag);
    }
    else if (key == 'f'|| key == 'F') {
        if (!viewFlag.value){
            setFlag(viewFlag);
        }else cancelFlag(viewFlag);

    }
    else if (key == 'q'|| key == 'Q') {
        exit(0);
    }
}


// 渲染回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色和深度缓冲区
    glLoadIdentity();
    checkFlag(turnLeftFlag, 450);
    checkFlag(turnRightFlag, 450);
    checkFlag(helpFlag,3000);
    checkFlag(viewFlag,5000);
    if (fogFlag){
        glEnable(GL_FOG);
        setupFog();
    } else glDisable(GL_FOG);
    if (distanceTraveled>80 && distanceTraveled<350){
        fogFlag = TRUE;
        if (++fogStep<400){
            fogDense += 0.0001;
        }else fogDense -= 0.00015;
    }else fogFlag = FALSE;

    if (viewFlag.value){
        if (viewStatus < 1.0) viewStatus+= 0.01;
    }else if (viewStatus > 0.0) viewStatus -= 0.01;

    timeStamp += 1;
    updateFuel();
//    gluLookAt(4.0, 12.0, 20.0,  // 摄像机位置
//              4.0, 0.0, 0.0,  // 观察目标
//              0.0, 1.0, 0.0); // 上方向
    gluLookAt((4+0.2*(carX-4))*viewStatus+4.0*(1-viewStatus), 2.0*viewStatus+12.0*(1-viewStatus), 8.0*viewStatus+20.0*(1-viewStatus),  // 摄像机位置
              carX*viewStatus+4.0*(1-viewStatus), 0.0, 0.0,  // 观察目标
              (0.0+0.05*(carX-4))*viewStatus, 1.0, 0.0); // 上方向

    setupLighting();         // 设置环境光照
    renderSand();
    renderSkyDome(); // 渲染天空球

    setupPointLight(carX, lightFlag);  // 车灯
    renderGroundItems(); // 渲染平面

    renderCar(carX);  // 渲染汽车

    gameLogic();
    drawSpeedometer(2.5f, 4.0f, 12.0f, 0.9f, carSpeed*4);   // 中间标准表盘
    float speedPerFrame = carSpeed / 60.0;  // 汽车移动速度
    if (!(endFlag||winFlag)) distanceTraveled += speedPerFrame;
//    printf("float: %f %f\n", speedPerFrame, distanceTraveled);
    glutSwapBuffers();
}

// 窗口大小调整回调函数
void reshape(int width, int height) {
//    glViewport(0, 0, width, height);
    glutReshapeWindow(600, 960);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.01, 500.0); // 45
    glMatrixMode(GL_MODELVIEW);
}

// 主程序入口
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // 多重采样
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(600, 960);
    glutCreateWindow("Five Hundred Miles ~ Way Back Home 66 | Presented by Ruiyang.wu 2257475");

    glEnable(GL_DEPTH_TEST); // 启用深度测试

    myinit(); // 读取贴图

    glutKeyboardFunc(keyPress); // 设置键盘按下事件
    glutDisplayFunc(display);
    glutTimerFunc(0, timerFunc, 0); // 设置首次定时器
    glutReshapeFunc(reshape);
    glutTimerFunc(0, updateCountdown, 0); // 开始倒计时
    glutMainLoop();
    return 0;
}
