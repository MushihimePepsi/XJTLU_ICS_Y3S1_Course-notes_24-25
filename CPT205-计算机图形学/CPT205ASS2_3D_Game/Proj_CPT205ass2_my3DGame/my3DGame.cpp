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

float carSpeed = 5.0f;  // m/s
float distanceTraveled = 0.0;
float carX = 6.0f;  // x pos of car
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
int remainingTime = 80; // initial cd

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
    flag.setTime = std::chrono::steady_clock::now(); // record current time
}
void cancelFlag(autoFlag &flag) {
    flag.value = false;
}

void checkFlag(autoFlag &flag, long long time) {
    if (flag.value) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - flag.setTime).count() >= time) {
            flag.value = false; // set false after time
//            std::cout << "Flag reset to false." << std::endl; // test
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

//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  // light mod
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void setupFog(){
    // use fog
    GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, fogDense); // GL_EXP/GL_EXP2 make sense, GL_LINEAR no sense
    glHint(GL_FOG_HINT, GL_FASTEST); // cal fog method
}

// 光照设置
void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float angleSun = distanceTraveled *(360.0/1000.0) +45;
    float angleSunRad = angleSun *PI /180.0;
    float dirX = -cos(angleSunRad);
    float dirY = sin(angleSunRad);
    float lightScale = (dirY+1.0)/2.0;


    // set spotlight
    GLfloat lightDirection[] = { dirX, dirY, -0.2f, 0.0f }; // last val=0 -> dir

    GLfloat lightDiffuse[] = { (float)(0.9f*lightScale+0.05*(1-lightScale)),
                               (float)(1.0f*lightScale),
                               (float)(1.0f*lightScale+0.1*(1-lightScale)), 1.0f };
    GLfloat lightAmbient[] = { (float)(0.9f*lightScale+0.05*(1-lightScale)),
                               (float)(1.0f*lightScale),
                               (float)(1.0f*lightScale+0.1*(1-lightScale)), 1.0f };


    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
}

void setupPointLight(float lightX, bool lightFlag) {
    glEnable(GL_LIGHTING);
    if (lightFlag) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);

    GLfloat lightPos[] = { lightX, 4.0f, -16.0f, 1.0f }; // (x, y, z, 1.0) -> point light

    GLfloat lightAmbient[] = { 5.2f, 5.2f, 5.2f, 1.0f };
    GLfloat lightDiffuse[] = { 5.8f, 5.8f, 5.8f, 1.0f };
//    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);

    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2f); // QUADRATIC_ATTENUATION


    glEnable(GL_LIGHTING);
    if (lightFlag) glEnable(GL_LIGHT2);
    else glDisable(GL_LIGHT2);


    GLfloat lightPos2[] = { 2.4, 5.0f, 13.0f, 1.0f }; // (x, y, z, 1.0) -> point light

    float mod2 = 4.0;
    GLfloat lightAmbient2[] = { 2.2f*mod2, .8f*mod2, 0.2f*mod2, 1.0f };
    GLfloat lightDiffuse2[] = { 2.8f*mod2, 1.0f*mod2, 0.5f*mod2, 1.0f };

    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);

    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 3.6f); // QUADRATIC_ATTENUATION
}


// 设置材质
void setMaterialRoad() {
    GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat matShininess[] = { 100.0f };  // 高光系数

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialPole() {
    GLfloat matAmbient[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    GLfloat matDiffuse[] = { 0.7f, 0.3f, 0.0f, 1.0f };
    GLfloat matSpecular[] = { 0.3f, 0.2f, 0.1f, 1.0f };
    GLfloat matShininess[] = { 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialSky() {
    GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat matShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialRuber() {
    GLfloat matAmbient[] = { 0.01f, 0.01f, 0.01f, 1.0f };
    GLfloat matDiffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat matSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matShininess[] = { 10.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialDarkStone() {
    GLfloat matAmbient[] = { 0.75f, 0.65f, 0.5f, 1.0f };
    GLfloat matDiffuse[] = { .5f, .5f, .5f, 1.0f };
    GLfloat matSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat matShininess[] = { 10.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialCarPaint(){
    float mod = 0.7;
    GLfloat matAmbient[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };
    GLfloat matDiffuse[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };
    GLfloat matSpecular[] = { .00f, .00f, .00f, 1.0f };
    GLfloat matShininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialCarPaint2(){
    float mod = 0.5;
    GLfloat matAmbient[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };
    GLfloat matDiffuse[] = { 0.53f*mod, 0.81f*mod, 0.98f*mod, 1.0f };
    GLfloat matSpecular[] = { .00f, .00f, .00f, 1.0f };
    GLfloat matShininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialGlass(){
    GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, .4f };
    GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, .4f };
    GLfloat matSpecular[] = { 1.5f, 1.5f, 1.5f, 1.0f };
    GLfloat matShininess[] = { 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLfloat matEmissionZero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
void setMaterialEmission() {
    GLfloat matEmission[] = { 0.8f, 0.2f, 0.2f, 1.0f }; // emission red
    GLfloat matAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat matDiffuse[] = { 0.5f, 0.2f, 0.2f, 1.0f };
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat matShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void setMaterialGasTank() {
    float mod = 0.8;
    GLfloat matAmbient[] = { 0.9f*mod, 0.1f*mod, 0.02f*mod, 1.0f };
    GLfloat matDiffuse[] = { 0.9f*mod, 0.1f*mod, 0.02f*mod, 1.0f };
    GLfloat matSpecular[] = { 0.9f*mod, 0.1f*mod, 0.02f*mod, 1.0f };
    GLfloat matShininess[] = { 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}


// draw Parabola
void drawParabola(float transZ) {
    setMaterialRuber();
    glLineWidth(1.6f);
    glPushMatrix();
    glTranslatef(0,4.8,transZ);
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 16.0f; t += 0.1f) {
        float x = 8.35f;
        float y = 0.02f * t * t - 0.32f * t;
        float z = t;
        glVertex3f(x, y, z);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 16.0f; t += 0.1f) {
        float x = 8.05f;
        float y = 0.02f * t * t - 0.32f * t;
        float z = t;
        glVertex3f(x, y, z);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 16.0f; t += 0.1f) {
        float x = 8.65f;
        float y = 0.02f * t * t - 0.32f * t;
        float z = t;
        glVertex3f(x, y, z);
    }
    glEnd();
    glPopMatrix();
    glLineWidth(1.0f);
}

// render
void renderGroundItems() {
    // render road
    glEnable(GL_TEXTURE_2D);        // enable texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    setMaterialRoad();   // set road material
    for (int i = -16; i < 4; ++i) {
        float roadOffset = i * 8.0 + fmod(distanceTraveled, 8.0);
        glBegin(GL_QUADS);              // draw a quad
        // vertex and texture corr
        glNormal3f(0.0f, 1.0f, 0.0f); // normal vector up
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -8.0f + roadOffset);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f + roadOffset);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f, 0.0f, 0.0f + roadOffset);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f, 0.0f, -8.0f + roadOffset);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //telegraph pole
    setMaterialPole();
    for (int fltPoleNumber = -8; fltPoleNumber < 4; fltPoleNumber += 1)
    {
        float fltPoleOffset = fltPoleNumber * 16.0 + fmod(distanceTraveled, 16.0);
        glPushMatrix();
        glTranslatef(8.5, 2.5, fltPoleOffset);
        glPushMatrix();
        glTranslatef(-0.2, 2.3, 0.0);  // delta
        glScalef(12.0, 1.0, 1.0); // l,w,h
        glColor3f(1.0, 0.0, 0.0);
        glutSolidCube(.1);
        glColor3f(0.0, 1.0, 0.0);
        glutWireCube(.1);
        glPopMatrix();// up half

        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(.7, 50.0, .7);  // up down 2.5m
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

    // render wire
    for (int wireNumber = -8; wireNumber < 4; wireNumber += 1){
        float wireOffset = wireNumber * 16.0 + fmod(distanceTraveled, 16.0);
        drawParabola(wireOffset);
    }

    // render road bar
    for (int BarNumber = -24; BarNumber < 8; BarNumber += 1)
    {
        float barOffset = BarNumber * 4.0 + fmod(distanceTraveled, 4.0);
        glPushMatrix();
        glTranslatef(0, 0, barOffset);

        glPushMatrix();
        setMaterialDarkStone();
        glTranslatef(-0.14, 0.14, 0.0);  //delta
        glScalef(1.0, 1.4, 1.0); //lw h=0.28
        glutSolidCube(.2);
        glPopMatrix();// up half

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

        // right side
        glPushMatrix();
        setMaterialDarkStone();
        glTranslatef(8.14, 0.14, 0.0);
        glScalef(1.0, 1.4, 1.0);
        glutSolidCube(.2);
        glPopMatrix();

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

// render sand both side
void renderSand(){
    glDisable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);        // enable tex
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    setMaterialRoad();   // set road mat
    for (int i = -4; i < 2; ++i) {
        float sandLength = 32.0;
        float sandOffset = i * sandLength + fmod(distanceTraveled, sandLength);
        glBegin(GL_QUADS);
        // right
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(8.0f, 0.0f, -sandLength + sandOffset);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(8.0f, 0.0f, 0.0f + sandOffset);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f + sandLength, 0.0f, 0.0f + sandOffset);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f + sandLength, 0.0f, -sandLength + sandOffset);
        glEnd();
        glBegin(GL_QUADS);
        // left
        glNormal3f(0.0f, 1.0f, 0.0f);
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
    glEnable(GL_TEXTURE_2D);
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
    glBindTexture(GL_TEXTURE_2D, textures[1]); // use sky dome texture

    // Reverse normals to apply texture to the inner surface
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // Disable backside removal (because normals have been reversed)
    glDisable(GL_CULL_FACE);

    glTranslatef(4.0, 0.0, 0.0); // ctrl center pos
    glRotatef(-90, 1.0, 0.0, 0.0); // ctrl dir
    glRotatef(180, 0.0, 0.0, 1.0); // ctrl dir
    gluSphere(quadric, 200.0, 64, 64); // sphere r = 200

    // 恢复剔除设置
    glEnable(GL_CULL_FACE);
    gluDeleteQuadric(quadric);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// redisplay 60fps
void timerFunc(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timerFunc, 0);
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
        remainingTime--; // -1s per second
        glutTimerFunc(1000, updateCountdown, 0); // set next timer
    }
}


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

    // win and fail
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
const int MAX_SPEED = 100; // max speed
// 绘制圆
void drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; ++i) {
        float angle = i * PI / 180.0f;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

// Draw text using vector fonts
void drawLargeText(const std::string& text, float x, float y, float z, float scale) {
    glPushMatrix();
    setMaterialEmission();
    // move
    glTranslatef(x, y, z);
    // set size
    glScalef(scale*0.6, scale, scale);
    // draw text
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
    // set pos
    glRasterPos2f(x,y);
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
        float angle = (240.0f - (i * 240.0f / MAX_SPEED)) * PI / 180.0f; // convert speed to angle (rad)
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

    // draw text
    // cal fuel
    float fuelLiters = fuelRemain / 2.0f; // convert to lites
    // format string .2
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    stream <<"FUEL: "<< fuelLiters << "/50L <" << fuelRemain << "%>";
    std::string fuelText = stream.str();

    glRasterPos2f(0.6f+(carX-4)*0.6, 2);
    setMaterialEmission();
    for (const char& c : fuelText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // cal mile
    float traveledMiles = distanceTraveled/2.0f;
    float traveledProportion = distanceTraveled/10.0f;

    std::ostringstream stream2;
    stream2 << std::fixed << std::setprecision(1);
    stream2 << "Travel:" << traveledMiles << "/500 Miles <" << traveledProportion << "%>";
    std::string fuelText2 = stream2.str();
    setMaterialRoad();
    drawLargeText(fuelText2, -3.3f, 10.3f, -8.0f, 0.005f);

    // render cd
    std::ostringstream stream3;
    stream3 << "Countdown:<" << remainingTime << "sec>";
    std::string fuelText3 = stream3.str();
    if (remainingTime<20){
        setMaterialGasTank();
    } else setMaterialEmission();
    drawLargeText(fuelText3, 1.6f, 0.0f,0.0f, 0.003f);

    // render Help
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

    // render game info
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

// draw needle
void drawNeedle(float speed, float radius) {
    float angle = (240.0f - (speed * 240.0f / MAX_SPEED)) * PI / 180.0f;
    float x = (radius - 0.2f) * cos(angle);
    float y = (radius - 0.2f) * sin(angle);

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glEnd();
}

// draw speed meter
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
    else if ((key == 'w'|| key == 'W') && carSpeed < 25) { // speed up
        carSpeed += 1;
    }
    else if ((key == 's'|| key == 'S') && carSpeed > 5) { // speed down
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

void updateView(){

}

// 渲染回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    // 设置观察矩阵
    updateView();
//    gluLookAt(4.0, 12.0, 20.0,  // cam pos
//              4.0, 0.0, 0.0,  // aim pos
//              0.0, 1.0, 0.0); // up vec
    gluLookAt((4+0.2*(carX-4))*viewStatus+4.0*(1-viewStatus), 2.0*viewStatus+12.0*(1-viewStatus), 8.0*viewStatus+20.0*(1-viewStatus),
              carX*viewStatus+4.0*(1-viewStatus), 0.0, 0.0,
              (0.0+0.05*(carX-4))*viewStatus, 1.0, 0.0);

    setupLighting();
    renderSand();
    renderSkyDome();

    setupPointLight(carX, lightFlag);  // car light
    renderGroundItems();

    renderCar(carX);

    gameLogic();
    drawSpeedometer(2.5f, 4.0f, 12.0f, 0.9f, carSpeed*4);
    float speedPerFrame = carSpeed / 60.0;  // 汽车移动速度
    if (!(endFlag||winFlag)) distanceTraveled += speedPerFrame;
//    printf("float: %f %f\n", speedPerFrame, distanceTraveled);
    glutSwapBuffers();
}

// win size
void reshape(int width, int height) {
//    glViewport(0, 0, width, height);
    glutReshapeWindow(600, 960);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.01, 500.0); // 45
    glMatrixMode(GL_MODELVIEW);
}

// entrance
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // MULTISAMPLE
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(600, 960);
    glutCreateWindow("Five Hundred Miles ~ Way Back Home 66 | Presented by Ruiyang.Wu 2257475");

    glEnable(GL_DEPTH_TEST);

    myinit(); // read texture

    glutKeyboardFunc(keyPress); // keyboard event
    glutDisplayFunc(display);
    glutTimerFunc(0, timerFunc, 0); // set timer
    glutReshapeFunc(reshape);
    glutTimerFunc(0, updateCountdown, 0); // start cd
    glutMainLoop();
    return 0;
}
