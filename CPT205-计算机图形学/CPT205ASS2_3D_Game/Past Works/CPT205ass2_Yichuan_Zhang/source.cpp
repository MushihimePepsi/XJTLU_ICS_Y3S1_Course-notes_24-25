#define FREEGLUT_STATIC
#define GLUT_DISABLE_ATEXIT_HACK
#define PI 3.14159265
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

// Control points for the Bezier surfaces
GLfloat ctrlPoints[4][4][3] = {
    // v=0
    {
        {-15.0f, -3.2f, 1.0f},
        {0.0f, -3.2f, 1.0f},
        {4.0f, -3.2f, 1.0f},
        {9.0f, 0.72f, -2.0f}
    },
    // v=1
    {
        {-15.0f, -2.0f, 1.0f},
        {0.0f, -2.0f, 1.0f},
        {4.0f, -2.0f, 1.0f},
        {9.0f, 0.9f, -1.8f}
    },
    // v=2
    {
        {-15.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {4.0f, 0.0f, 1.0f},
        {9.0f, 1.2f, -1.8f}
    },
    // v=3
    {
        {-15.0f, 1.5f, 1.0f},
        {0.0f, 1.5f, 1.0f},
        {4.0f, 1.5f, 1.0f},
        {9.0f, 1.5f, -2.15f}
    }
};

GLfloat ctrlPoints2[4][4][3] = {
    // v=0
    {
        {-15.0f, -4.0f, 0.0f},
        {0.0f, -4.0f, 0.0f},
        {4.0f, -4.0f, 0.0f},
        {9.0f, 0.5f, -2.2f}
    },
    // v=1
    {
        {-15.0f, -4.0f, 0.5f},
        {0.0f, -4.0f, 0.5f},
        {4.0f, -4.0f, 0.5f},
        {9.0f, 1.0f, -1.9f}
    },
    // v=2
    {
        {-15.0f, -3.6f, 0.85f},
        {0.0f, -3.6f, 0.85f},
        {4.0f, -3.6f, 0.85f},
        {9.0f, 1.0f, -1.85f}
    },
    // v=3
    {
        {-15.0f, -3.2f, 1.0f},
        {0.0f, -3.2f, 1.0f},
        {4.0f, -3.2f, 1.0f},
        {9.0f, 0.92f, -2.0f}
    }
};

GLfloat ctrlPointsMiddle[4][4][3] = {
    // v=0
    {
        {-15.0f, -4.0f, 0.0f},
        {0.0f, -4.0f, 0.0f},
        {4.0f, -4.0f, 0.0f},
        {9.0f, 0.55f, -2.5f}
    },
    // v=1
    {
        {-15.0f, -4.0f, -1.5f},
        {0.0f, -4.0f, -1.5f},
        {4.0f, -4.0f, -1.5f},
        {9.0f, 0.48f, -2.3f}
    },
    // v=2
    {
        {-15.0f, -4.0f, -3.3f},
        {0.0f, -4.0f, -3.3f},
        {4.0f, -4.0f, -3.3f},
        {9.0f, 0.48f, -2.7f}
    },
    // v=3
    {
        {-15.0f, -4.0f, 0.0f},
        {0.0f, -4.0f, 0.0f},
        {4.0f, -4.0f, 0.0f},
        {9.0f, 0.5f, -2.2f}
    }
};

GLfloat plainMiddle[4][4][3] = {
    // v=0
    {
        {-15.0f, -4.0f, 0.0f},
        {0.0f, -4.0f, 0.0f},
        {4.0f, -4.0f, 0.0f},
        {9.0f, -4.0f, -2.5f}
    },
    // v=1
    {
        {-15.0f, -4.0f, -1.5f},
        {0.0f, -4.0f, -1.5f},
        {4.0f, -4.0f, -1.5f},
        {9.0f, -4.0f, -1.5f}
    },
    // v=2
    {
        {-15.0f, -4.0f, -2.7f},
        {0.0f, -4.0f, -2.7f},
        {4.0f, -4.0f, -2.7f},
        {9.0f, -4.0f, -2.7f}
    },
    // v=3
    {
        {-15.0f, -4.0f, 0.0f},
        {0.0f, -4.0f, 0.0f},
        {4.0f, -4.0f, 0.0f},
        {9.0f, -4.0f, 0.0f}
    }
};

GLfloat plain[4][4][3] = {
    // v=0
    {
        {-15.0f, -3.2f, 1.0f},
        {0.0f, -3.2f, 1.0f},
        {4.0f, -3.2f, 1.0f},
        {9.0f, -3.2f, 1.0f}
    },
    // v=1
    {
        {-15.0f, -2.0f, 1.0f},
        {0.0f, -2.0f, 1.0f},
        {4.0f, -2.0f, 1.0f},
        {9.0f, -2.0f, 1.0f}
    },
    // v=2
    {
        {-15.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {4.0f, 0.0f, 1.0f},
        {9.0f, 0.0f, 1.0f}
    },
    // v=3
    {
        {-15.0f, 1.5f, 1.0f},
        {0.0f, 1.5f, 1.0f},
        {4.0f, 1.5f, 1.0f},
        {9.0f, 1.5f, 1.0f}
    }
};

GLfloat plain2[4][4][3]{
    // v=0
    {
        {-15.0f, -4.0f, 0.0f},
        {0.0f, -4.0f, 0.0f},
        {4.0f, -4.0f, 0.0f},
        {9.0f, -4.0f, 0.0f}
    },
    // v=1
    {
        {-15.0f, -4.0f, 0.5f},
        {0.0f, -4.0f, 0.5f},
        {4.0f, -4.0f, 0.5f},
        {9.0f, -4.0f, 0.5f}
    },
    // v=2
    {
        {-15.0f, -3.6f, 0.85f},
        {0.0f, -3.6f, 0.85f},
        {4.0f, -3.6f, 0.85f},
        {9.0f, -3.6f, 0.85f}
    },
    // v=3
    {
        {-15.0f, -3.2f, 1.0f},
        {0.0f, -3.2f, 1.0f},
        {4.0f, -3.2f, 1.0f},
        {9.0f, -3.2f, 1.0f}
    }
};

GLfloat plainMirror[4][4][3];
GLfloat plainMirror2[4][4][3];
GLfloat Rotate = 0;
GLfloat RotateSpeed = 20;

GLfloat mat_diffuse[] = { 0.0f, 0.5f, 0.8f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess[] = { 128.0f };

// Mirrored control points (4x4) for the right side (mirrored Bezier surface)
GLfloat ctrlPointsMirrored[4][4][3];
GLfloat ctrlPointsMirrored2[4][4][3];

GLint imagewidth0, imageheight0, pixellength0;
GLint imagewidth1, imageheight1, pixellength1;
GLint imagewidth2, imageheight2, pixellength2;
GLint imagewidth3, imageheight3, pixellength3;
GLint imagewidth4, imageheight4, pixellength4;
GLint imagewidth5, imageheight5, pixellength5;
GLint imagewidth6, imageheight6, pixellength6;
GLint imagewidth7, imageheight7, pixellength7;
vector<GLubyte*> p;
GLuint texture[8];
GLfloat angle = 0.0f;

// Train positions and speed
GLfloat train1Pos = -120;
GLfloat train2Pos = 0;
GLfloat trainSpeed = 2;

// Camera parameters
GLfloat eyeX = 120;
GLfloat eyeY = 5;
GLfloat eyeZ = 10;

GLfloat centerX = 0.0f;
GLfloat centerY = 0.0f;
GLfloat centerZ = 0.0f;

GLfloat upX = 0.0f;
GLfloat upY = 1.0f;
GLfloat upZ = 0.0f;

GLfloat tra_ambient[] = { 0.05, 0.05, 0.05, 1.00 };
GLfloat tra_diffuse[] = { 0.45, 0.45, 0.52, 1.00 };
GLfloat tra_specular[] = { 0.774597, 0.774597, 0.774597, 1.000000 };
GLfloat tra_shininess[] = { 76.800003 };

GLboolean isOn = false;
GLboolean train1 = true;
GLboolean train2 = false;

enum CameraState { IDLE, MOVING_TO_START, MOVING_TO_BACK };
CameraState cameraState = IDLE;
bool isMovingForward = true; // direction flag
const float initialEyeY = 5.0f; // initial Y pos of camera

// Global variables for camera rotation and position
float angleX = 0.0f, angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isDragging = false;
bool isStart = false;
bool isBack = false;

// Camera position
float camX = 100, camY = 2.0f, camZ = -2.5f;

// Camera move step
const float moveStep = 1;

// Ellipsoid position and scaling
float ellipsoidPosX = 9.0f;
float ellipsoidPosY = 1.0f;
float ellipsoidPosZ = -2.5f;
float ellipsoidScaleX = 0.55f;
float ellipsoidScaleY = 0.55f;
float ellipsoidScaleZ = 0.65f;

void drawCuboid(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat height, GLfloat depth);
void drawEllipsoid(float rx, float ry, float rz, int slices, int stacks);
void drawControlPoints(GLfloat ctrlPts[4][4][3], GLfloat color[3]);
void drawTriprim(GLfloat length, GLfloat depth, GLfloat angle);
void drwSlop(GLfloat length, GLfloat depth, GLfloat angle);
void ReadImage(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength);
void loadTexture(void);
void drawSolidCylinder(float radius, float height, int slices);
void drawDiskWithThickness(GLfloat radius, GLfloat thickness, GLint slices);
void drawWheel1();
void GL_WHEEL2();
void drawCuboid(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat height, GLfloat depth);
void drawBezierSurface(GLfloat ctrlPts[4][4][3]);
void drawParameterLines();
void drawFilledEllipse(float a, float b, int segments);
void drawRectangle(float width, float height);
void drawRectangleAtPosition(float x, float y, float z, float width, float height);
void Antenna(float baseX, float baseY, float baseZ);
void drawWood(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat height, GLfloat depth);
void drawRAIl(GLfloat track_x);
void Railroad(void);
void train();
void drawPole();
void drawWall();
void drawGroundWithTexture(GLfloat width, GLfloat depth, GLfloat x, GLfloat y, GLfloat z);
void drawTrain();
void drawRailroad();

// Draw ellipsoid
void drawEllipsoid(float rx, float ry, float rz, int slices, int stacks) {
    glPushMatrix();
    glScalef(rx, ry, rz);
    glutSolidSphere(1.0f, slices, stacks);
    glPopMatrix();
}

// Draw control points for debugging
void drawControlPoints(GLfloat ctrlPts[4][4][3], GLfloat color[3]) {
    glDisable(GL_LIGHTING);
    glColor3fv(color);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (int v = 0; v < 4; v++) {
        for (int u = 0; u < 4; u++) {
            glVertex3fv(ctrlPts[v][u]);
        }
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

// Draw a triangular prism with a specific angle
void drawTriprim(GLfloat length, GLfloat depth, GLfloat angle) {
    GLfloat height = length * tan(angle);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, 0.5 * depth);

    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, -0.5 * depth);

    glNormal3f(sin(angle), cos(angle), 0);
    glVertex3f(-0.5 * length, 0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, 0.5 * depth);
    glVertex3f(0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(0.5 * length, -0.5 * height, -0.5 * depth);
    glEnd();

    // Top and bottom are triangles
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1);
    glVertex3f(0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, -0.5 * depth);

    glNormal3f(0, 0, 1);
    glVertex3f(0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, 0.5 * depth);
    glEnd();
}

// Draw slope object with texture and specific material
void drwSlop(GLfloat length, GLfloat depth, GLfloat angle) {
    // Material properties for the side
    GLfloat mat_ambient_side[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse_side[] = { 0.8f, 0.0f, 0.0f, 1.0f };
    GLfloat mat_specular_side[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess_side[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_side);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_side);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_side);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_side);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    GLfloat height = length * tan(angle);

    // Draw side quad
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, 0.5 * depth);

    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, -0.5 * depth);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);

    glNormal3f(sin(angle), cos(angle), 0);
    glTexCoord2f(1, 0); glVertex3f(-0.5 * length, 0.5 * height, -0.5 * depth);
    glTexCoord2f(1, 1); glVertex3f(-0.5 * length, 0.5 * height, 0.5 * depth);
    glTexCoord2f(0, 1); glVertex3f(0.5 * length, -0.5 * height, 0.5 * depth);
    glTexCoord2f(0, 0); glVertex3f(0.5 * length, -0.5 * height, -0.5 * depth);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Material for top and bottom
    GLfloat mat_ambient_top_bottom[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse_top_bottom[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat mat_specular_top_bottom[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess_top_bottom[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_top_bottom);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_top_bottom);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_top_bottom);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_top_bottom);

    // Draw top and bottom triangles
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1);
    glVertex3f(0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, -0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, -0.5 * depth);

    glNormal3f(0, 0, 1);
    glVertex3f(0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, -0.5 * height, 0.5 * depth);
    glVertex3f(-0.5 * length, 0.5 * height, 0.5 * depth);
    glEnd();
}

// Read .bmp image
void ReadImage(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
    GLubyte* pixeldata;
    FILE* pfile;
    fopen_s(&pfile, path, "rb");
    if (pfile == 0) {
        printf("Cannot open file: %s\n", path);
        exit(1);
    }
    fseek(pfile, 0x0012, SEEK_SET);
    fread(&imagewidth, sizeof(imagewidth), 1, pfile);
    fread(&imageheight, sizeof(imageheight), 1, pfile);
    pixellength = imagewidth * 3;
    while (pixellength % 4 != 0) pixellength++;
    pixellength *= imageheight;
    pixeldata = (GLubyte*)malloc(pixellength);
    if (pixeldata == 0) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    fseek(pfile, 54, SEEK_SET);
    fread(pixeldata, pixellength, 1, pfile);
    p.push_back(pixeldata);
    fclose(pfile);
}

// Load textures
void loadTexture(void) {
    glEnable(GL_TEXTURE_2D);

    // Load image data
    ReadImage("WD.bmp", imagewidth0, imageheight0, pixellength0);
    ReadImage("BG.bmp", imagewidth1, imageheight1, pixellength1);
    ReadImage("rock.bmp", imagewidth2, imageheight2, pixellength2);
    ReadImage("grass.bmp", imagewidth3, imageheight3, pixellength3);
    ReadImage("wall1.bmp", imagewidth4, imageheight4, pixellength4);
    ReadImage("sky1.bmp", imagewidth5, imageheight5, pixellength5);
    ReadImage("window.bmp", imagewidth6, imageheight6, pixellength6);
    ReadImage("logo.bmp", imagewidth7, imageheight7, pixellength7);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(8, texture);

    // Texture 0 (WD.bmp)
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Texture 1 (BG.bmp)
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Texture 2 (rock.bmp)
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth2, imageheight2, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[2]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Texture 3 (grass.bmp)
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth3, imageheight3, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[3]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth4, imageheight4, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[4]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth5, imageheight5, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[5]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth6, imageheight6, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[6]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth7, imageheight7, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[7]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glDisable(GL_TEXTURE_2D);
}

// Draw a solid cylinder
void drawSolidCylinder(float radius, float height, int slices) {
    float angleStep = 2.0f * PI / slices;

    // Side
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glNormal3f(x / radius, y / radius, 0.0f);
        glVertex3f(x, y, 0.0f);
        glVertex3f(x, y, height);
    }
    glEnd();

    // Bottom disk
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    // Top disk
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, height);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, height);
    }
    glEnd();
}

// Draw a disk with thickness
void drawDiskWithThickness(GLfloat radius, GLfloat thickness, GLint slices) {
    GLUquadric* quad = gluNewQuadric();

    // Top disk
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, thickness / 2.0f);
    gluDisk(quad, 0.0f, radius, slices, 1);
    glPopMatrix();

    // Bottom disk
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -thickness / 2.0f);
    glRotatef(180, 1, 0, 0);
    gluDisk(quad, 0.0f, radius, slices, 1);
    glPopMatrix();

    // Side cylinder
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -thickness / 2.0f);
    gluCylinder(quad, radius, radius, thickness, slices, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

// Generate wheel (type 1)
void drawWheel1() {
    glRotatef(Rotate, 0, 0, 1);
    glColor3f(0.15, 0.15, 0.15);
    drawDiskWithThickness(1.0f, 0.1f, 30);

    glTranslatef(0.0f, 0.0f, -0.1f);
    drawDiskWithThickness(0.5f, 0.35f, 30);

    glTranslatef(0.0f, 0.0f, -0.25f);
    drawDiskWithThickness(1.0f, 0.1f, 30);

    GLint numNuts = 10;
    GLfloat smallDiskThickness = 0.02f;
    GLint slices = 10;
    GLfloat wheelRadius = 0.3f;
    GLfloat smallDiskRadius = wheelRadius * 0.05f;
    for (int j = 0; j < numNuts; j++) {
        GLfloat angle = 2.0f * PI * j / numNuts;
        GLfloat xOffset = (wheelRadius - smallDiskRadius) * cos(angle);
        GLfloat yOffset = (wheelRadius - smallDiskRadius) * sin(angle);

        glColor3f(0.7f, 0.7f, 0.7f);
        glPushMatrix();
        glTranslatef(xOffset, yOffset, -0.081f);
        glRotatef(angle * 180.0f / PI, 0, 0, 1);
        drawDiskWithThickness(smallDiskRadius, smallDiskThickness, slices);
        glPopMatrix();
    }
}

// Generate wheel (type 2)
void GL_WHEEL2() {
    glRotatef(Rotate, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, -0.1f);
    glColor3f(0.15, 0.15, 0.15);

    drawDiskWithThickness(1.0f, 0.1f, 30);
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawDiskWithThickness(0.5f, 0.35f, 30);
    glTranslatef(0.0f, 0.0f, 0.25f);
    drawDiskWithThickness(1.0f, 0.1f, 30);
    glTranslatef(0.0f, 0.0f, -0.25f);

    GLint numNuts = 10;
    GLfloat smallDiskThickness = 0.02f;
    GLint slices = 10;
    GLfloat wheelRadius = 0.3f;
    GLfloat smallDiskRadius = wheelRadius * 0.05f;
    for (int j = 0; j < numNuts; j++) {
        GLfloat angle = 2.0f * PI * j / numNuts;
        GLfloat xOffset = (wheelRadius - smallDiskRadius) * cos(angle);
        GLfloat yOffset = (wheelRadius - smallDiskRadius) * sin(angle);

        glColor3f(0.7f, 0.7f, 0.7f);
        glPushMatrix();
        glTranslatef(xOffset, yOffset, 0.34);
        glRotatef(angle * 180.0f / PI, 0, 0, 1);
        drawDiskWithThickness(smallDiskRadius, smallDiskThickness, slices);
        glPopMatrix();
    }
}

// Draw a cuboid by using triangular prisms
void drawCuboid(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat height, GLfloat depth) {
    glPushMatrix();
    glTranslatef(x, y, z);
    drawTriprim(length, depth, atan(height / length));
    glRotatef(180, 0, 0, 1);
    drawTriprim(length, depth, atan(height / length));
    glPopMatrix();
}

// Initialization
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Light properties
    GLfloat lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 0.9f, 0.9f, 0.9f, 1.0f };

    // Using w=1.0 for positional light here
    GLfloat lightPosition[] = { 1.0f, 100.0f, 100.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Material properties
    GLfloat matAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat matDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_MAP2_VERTEX_3);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    loadTexture();
    glMapGrid2f(30, 0.0, 1.0, 30, 0.0, 1.0);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // Initialize mirrored control points for right side
    for (int v = 0; v < 4; v++) {
        for (int u = 0; u < 4; u++) {
            ctrlPointsMirrored[v][u][0] = ctrlPoints[v][u][0];
            ctrlPointsMirrored[v][u][1] = ctrlPoints[v][u][1];
            ctrlPointsMirrored[v][u][2] = -ctrlPoints[v][u][2];
        }
    }

    for (int v = 0; v < 4; v++) {
        for (int u = 0; u < 4; u++) {
            ctrlPointsMirrored2[v][u][0] = ctrlPoints2[v][u][0];
            ctrlPointsMirrored2[v][u][1] = ctrlPoints2[v][u][1];
            ctrlPointsMirrored2[v][u][2] = -ctrlPoints2[v][u][2];
        }
    }

    for (int u = 0; u < 4; u++) {
        ctrlPointsMiddle[0][u][0] = ctrlPointsMirrored2[0][u][0];
        ctrlPointsMiddle[0][u][1] = ctrlPointsMirrored2[0][u][1];
        ctrlPointsMiddle[0][u][2] = ctrlPointsMirrored2[0][u][2] - 5.0f;
    }

    for (int v = 0; v < 4; v++) {
        for (int u = 0; u < 4; u++) {
            plainMirror[v][u][0] = plain[v][u][0];
            plainMirror[v][u][1] = plain[v][u][1];
            plainMirror[v][u][2] = -plain[v][u][2] - 5.0f;
        }
    }

    for (int v = 0; v < 4; v++) {
        for (int u = 0; u < 4; u++) {
            plainMirror2[v][u][0] = plain2[v][u][0];
            plainMirror2[v][u][1] = plain2[v][u][1];
            plainMirror2[v][u][2] = -plain2[v][u][2] - 5.0f;
        }
    }

    for (int u = 0; u < 4; u++) {
        plainMiddle[0][u][0] = plainMirror2[0][u][0];
        plainMiddle[0][u][1] = plainMirror2[0][u][1];
        plainMiddle[0][u][2] = plainMirror2[0][u][2];
    }
}

// Draw Bezier surface
void drawBezierSurface(GLfloat ctrlPts[4][4][3]) {
    glMap2f(GL_MAP2_VERTEX_3,
        0.0, 1.0, 3, 4,
        0.0, 1.0, 12, 4,
        &ctrlPts[0][0][0]);

    glEnable(GL_MAP2_VERTEX_3);
    glEvalMesh2(GL_FILL, 0, 30, 0, 30);
}

// Draw parameter lines (optional)
void drawParameterLines() {
    glDisable(GL_LIGHTING);

    // u-direction lines (constant v)
    glColor3f(0.5f, 0.0f, 0.5f);
    glLineWidth(2.0f);
    for (int v = 0; v < 4; v++) {
        glBegin(GL_LINE_STRIP);
        for (int u = 0; u < 4; u++) {
            glVertex3fv(ctrlPointsMiddle[v][u]);
        }
        glEnd();
    }

    // v-direction lines (constant u)
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    for (int u = 0; u < 4; u++) {
        glBegin(GL_LINE_STRIP);
        for (int v = 0; v < 4; v++) {
            glVertex3fv(ctrlPointsMiddle[v][u]);
        }
        glEnd();
    }

    glEnable(GL_LIGHTING);
}

// Draw filled ellipse
void drawFilledEllipse(float a, float b, int segments) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float t = 2 * PI * i / segments;
        float x = a * cos(t);
        float z = b * sin(t);
        float u = (cos(t) + 1.0f) / 2.0f;
        float v = (sin(t) + 1.0f) / 2.0f;
        glTexCoord2f(u, v);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Draw rectangle with given width and height
void drawRectangle(float width, float height) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2.0f, 0.0f, -height / 2.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2.0f, 0.0f, -height / 2.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2.0f, 0.0f, height / 2.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2.0f, 0.0f, height / 2.0f);
    glEnd();
}

// Draw rectangle at a specific position
void drawRectangleAtPosition(float x, float y, float z, float width, float height) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 1, 0, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    drawRectangle(width, height);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

// Draw Antenna-like object
void Antenna(float baseX, float baseY, float baseZ) {
    drawCuboid(baseX, baseY, baseZ, 1, 0.1, 2);

    glPushMatrix();
    glTranslatef(baseX + 1.3f, baseY - 1.38f, baseZ);
    glRotatef(-55, 0, 0, 1);
    drawCuboid(0, 0, 0, 3.0, 0.15, 0.15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(baseX + 2.19f, baseY - 2.70f, baseZ);
    glRotatef(-90, 0, 1, 0);
    drawCuboid(0, 0, 0, 3.0, 0.15, 0.15);
    glPopMatrix();
}

// Draw wood sleepers
void drawWood(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat height, GLfloat depth) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
    // Front
    glNormal3f(0, 0, -1);
    glTexCoord2f(0.0, 0.0); glVertex3f(x - 0.5f * length, y - 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.0, 0.5); glVertex3f(x + 0.5f * length, y - 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.1, 0.5); glVertex3f(x + 0.5f * length, y + 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.1, 0.0); glVertex3f(x - 0.5f * length, y + 0.5f * height, z - 0.5f * depth);

    // Top
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(x - 0.5f * length, y + 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.0, 0.5); glVertex3f(x + 0.5f * length, y + 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.1, 0.5); glVertex3f(x + 0.5f * length, y + 0.5f * height, z + 0.5f * depth);
    glTexCoord2f(0.1, 0.0); glVertex3f(x - 0.5f * length, y + 0.5f * height, z + 0.5f * depth);

    // Back
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 0.0); glVertex3f(x - 0.5f * length, y + 0.5f * height, z + 0.5f * depth);
    glTexCoord2f(0.0, 0.5); glVertex3f(x + 0.5f * length, y + 0.5f * height, z + 0.5f * depth);
    glTexCoord2f(0.1, 0.5); glVertex3f(x + 0.5f * length, y - 0.5f * height, z + 0.5f * depth);
    glTexCoord2f(0.1, 0.0); glVertex3f(x - 0.5f * length, y - 0.5f * height, z + 0.5f * depth);

    // Left
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(x - 0.5f * length, y - 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.0, 0.1); glVertex3f(x - 0.5f * length, y + 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.5, 0.1); glVertex3f(x - 0.5f * length, y + 0.5f * height, z + 0.5f * depth);
    glTexCoord2f(0.5, 0.0); glVertex3f(x - 0.5f * length, y - 0.5f * height, z + 0.5f * depth);

    // Right
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(x + 0.5f * length, y - 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.0, 0.1); glVertex3f(x + 0.5f * length, y + 0.5f * height, z - 0.5f * depth);
    glTexCoord2f(0.5, 0.1); glVertex3f(x + 0.5f * length, y + 0.5f * height, z + 0.5f * depth);
    glTexCoord2f(0.5, 0.0); glVertex3f(x + 0.5f * length, y - 0.5f * height, z + 0.5f * depth);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draw rails
void drawRAIl(GLfloat track_x) {
    GLfloat baseY = -4.0f;
    GLfloat railCenterZ = 200.0f;
    GLfloat railDepth = 2000.0f;

    drawCuboid(track_x, baseY + 0.85f, railCenterZ, 1.4f, 0.6f, railDepth);
    drawCuboid(track_x, baseY + 1.75f, railCenterZ, 0.53f, 1.2f, railDepth);
    drawCuboid(track_x, baseY + 2.7f, railCenterZ, 0.98f, 0.7f, railDepth);

    for (int i = -800; i <= 1200; i += 2) {
        glPushMatrix();
        glTranslatef(track_x, baseY + 3.05f, i);
        glScalef(1, 0.5, 1);
        glutSolidCylinder(0.49f, 2.0f, 20, 1);
        glPopMatrix();
    }
}

// Draw entire railroad (rails and sleepers)
void Railroad(void) {
    glDisable(GL_COLOR_MATERIAL);

    // Rail material
    GLfloat met_ambient[] = { 0.25, 0.25, 0.25, 1.00 };
    GLfloat met_diffuse[] = { 0.40, 0.40, 0.40, 1.00 };
    GLfloat met_specular[] = { 0.774597, 0.774597, 0.774597, 1.000000 };
    GLfloat met_shininess[] = { 76.800003 };

    // Wood sleeper material
    GLfloat wood_ambient_and_diffuse[] = { 0.610, 0.606, 0.610, 1.000 };
    GLfloat wood_specular[] = { 0.610, 0.606, 0.610, 1.000 };
    GLfloat wood_shininess[] = { 10 };

    // Screw material
    GLfloat screw_ambient[] = { 0.252, 0.239, 0.227, 1.000 };
    GLfloat screw_diffuse[] = { 0.327, 0.314, 0.301, 1.000 };
    GLfloat screw_specular[] = { 0.407, 0.494, 0.481, 1.000 };
    GLfloat screw_shininess[] = { 43.400003 };

    // Rails
    glMaterialfv(GL_FRONT, GL_AMBIENT, met_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, met_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, met_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, met_shininess);
    drawRAIl(12.5f);
    drawRAIl(-12.5f);
    drawRAIl(84.5f);
    drawRAIl(59.5f);

    // Wood sleepers
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wood_ambient_and_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wood_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, wood_shininess);
    GLfloat baseY = -4.0f;

    for (int i = -50; i <= 75; i++) drawWood(0, baseY, i * 16.0f, 40.0f, 1.0f, 4.0f);
    for (int i = -50; i <= 75; i++) drawWood(72.0f, baseY, i * 16.0f, 40.0f, 1.0f, 4.0f);

    // Screw material
    glMaterialfv(GL_FRONT, GL_AMBIENT, screw_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, screw_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, screw_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, screw_shininess);
    glEnable(GL_COLOR_MATERIAL);
}

// Draw the train composed of multiple Bezier surfaces
void train() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, tra_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tra_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tra_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tra_shininess);

    // Left side Bezier surfaces
    glPushMatrix();
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(ctrlPoints);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(ctrlPoints2);
    glColor3f(0, 0, 0);
    drawBezierSurface(ctrlPointsMiddle);

    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(ctrlPointsMirrored);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(ctrlPointsMirrored2);
    glPopMatrix();

    // Texture example
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glPushMatrix();
    glTranslatef(-6, 0.2f, 1);
    glRotatef(180, 0, 0, 1);
    glRotatef(180, 0, 1, 0);
    glScalef(1.4, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-2, -1, -2.5);
    glRotatef(30, 0, 1, 0);
    glColor3f(0.15, 0.15, 0.15);
    drawCuboid(3, 3, 3, 5.0, 1.0, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0, -1, -7.87);
    glRotatef(-30, 0, 1, 0);
    drawCuboid(3, 3, 3, 5.0, 1.0, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.5, -1, -5.6);
    glRotatef(0, 0, 1, 0);
    drawCuboid(3, 3, 3, 15.0, 1.0, 5);
    glPopMatrix();

    // Wheels arrangement
    int numRings = 6;
    GLfloat startX = -0.5;
    GLfloat step = -2.3;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, -5.2f);
        drawWheel1();
        glPopMatrix();
    }

    startX = -0.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2, 0.2);
        GL_WHEEL2();
        glPopMatrix();
    }

    GLfloat gla_ambient_diffuse[] = { 0.705882, 0.715882, 0.705882, 0.500000 };
    GLfloat gla_specular[] = { 0.933333, 0.943333, 0.933333, 0.500000 };
    GLfloat gla_shininess[] = { 59.846150 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gla_ambient_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, gla_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, gla_shininess);

    glPushMatrix();
    glTranslatef(ellipsoidPosX, ellipsoidPosY, ellipsoidPosZ);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawEllipsoid(ellipsoidScaleX, ellipsoidScaleY, ellipsoidScaleZ, 30, 30);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, tra_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tra_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tra_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tra_shininess);

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-15.9, 0, 0);
    glScalef(0.1, 1, 1);
    drawBezierSurface(plain);
    drawBezierSurface(plain2);
    drawBezierSurface(plainMirror);
    drawBezierSurface(plainMirror2);
    drawBezierSurface(plainMiddle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-26.4, 0, 0);
    glScalef(1, 1, 1);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(plain);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(plain2);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(plainMirror);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(plainMirror2);
    glColor3f(0, 0, 0);
    drawBezierSurface(plainMiddle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33.5, -1, -5.6);
    glRotatef(0, 0, 1, 0);
    glScalef(1.4, 1, 1);
    drawCuboid(3, 3, 3, 15.0, 1.0, 5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-68.7, 0, 0);
    glScalef(0.1, 1, 1);
    drawBezierSurface(plain);
    drawBezierSurface(plain2);
    drawBezierSurface(plainMirror);
    drawBezierSurface(plainMirror2);
    drawBezierSurface(plainMiddle);
    glPopMatrix();

    glColor3f(0.0f, 0.5f, 0.8f);

    glPushMatrix();
    glTranslatef(-85.2, 0, -5);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(ctrlPoints);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(ctrlPoints2);
    glColor3f(0, 0, 0);
    drawBezierSurface(ctrlPointsMiddle);

    glPushMatrix();
    glTranslatef(5, -2.25, -2.5);
    glRotatef(90, 0, 1, 0);
    glRotatef(-25.5, 1, 0, 0);
    glScalef(0.8, 1, 1);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawFilledEllipse(2.0f, 1.0f, 50);
    glPopMatrix();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(ctrlPointsMirrored);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(ctrlPointsMirrored2);
    glTranslatef(0.0f, 0.0f, 5.0f);
    glTranslatef(ellipsoidPosX, ellipsoidPosY, ellipsoidPosZ);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawEllipsoid(ellipsoidScaleX, ellipsoidScaleY, ellipsoidScaleZ, 30, 30);
    glPopMatrix();

    glColor3f(0.15, 0.15, 0.15);
    glPushMatrix();
    glTranslatef(-82.5, -1, -5.6);
    glRotatef(0, 0, 1, 0);
    glScalef(1, 1, 1);
    drawCuboid(3, 3, 3, 15.0, 1.0, 5);
    glPopMatrix();

    numRings = 6;
    startX = -73.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, 0.2);
        GL_WHEEL2();
        glPopMatrix();
    }
    startX = -73.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, -5.2f);
        drawWheel1();
        glPopMatrix();
    }

    numRings = 8;
    startX = -20.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, 0.2);
        GL_WHEEL2();
        glPopMatrix();
    }
    startX = -20.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, -5.2f);
        drawWheel1();
        glPopMatrix();
    }

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-42.3, 0, 0);
    glScalef(0.1, 1, 1);
    drawBezierSurface(plain);
    drawBezierSurface(plain2);
    drawBezierSurface(plainMirror);
    drawBezierSurface(plainMirror2);
    drawBezierSurface(plainMiddle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-52.8, 0, 0);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(plain);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(plain2);
    glColor3f(0.501961, 0.501961, 0.501961);
    drawBezierSurface(plainMirror);
    glColor3f(0.545098, 0.0, 0.0);
    drawBezierSurface(plainMirror2);
    glColor3f(0, 0, 0);
    drawBezierSurface(plainMiddle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60.2, -1, -5.6);
    glRotatef(0, 0, 1, 0);
    glScalef(1.4, 1, 1);
    drawCuboid(3, 3, 3, 15.0, 1.0, 5);
    glPopMatrix();

    startX = -47.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, 0.2);
        GL_WHEEL2();
        glPopMatrix();
    }

    startX = -47.5;
    step = -2.5;
    for (int i = 0; i < numRings; i++) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.8f);
        glTranslatef(startX + i * step, 2.0f, -5.2f);
        drawWheel1();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(5, -2.25, -2.5);
    glRotatef(90, 0, 1, 0);
    glRotatef(-25.5, 1, 0, 0);
    glScalef(0.8, 1, 1);
    drawFilledEllipse(2.0f, 1.0f, 50);
    glPopMatrix();

    glColor3f(0, 0, 0);
    drawRectangleAtPosition(-10, -2, 1.05, 8.0f, 2.0f);
    drawRectangleAtPosition(-25, -2, 1.05, 8.0f, 2.0f);
    drawRectangleAtPosition(-34, -2, 1.05, 8.0f, 2.0f);
    drawRectangleAtPosition(-52, -2, 1.05, 8.0f, 2.0f);
    drawRectangleAtPosition(-61, -2, 1.05, 8.0f, 2.0f);
    drawRectangleAtPosition(-75, -2, 1.05, 8.0f, 2.0f);

    drawRectangleAtPosition(-10, -2, -6.02, 8.0f, 2.0f);
    drawRectangleAtPosition(-25, -2, -6.02, 8.0f, 2.0f);
    drawRectangleAtPosition(-34, -2, -6.02, 8.0f, 2.0f);
    drawRectangleAtPosition(-52, -2, -6.02, 8.0f, 2.0f);
    drawRectangleAtPosition(-61, -2, -6.02, 8.0f, 2.0f);
    drawRectangleAtPosition(-75, -2, -6.02, 8.0f, 2.0f);

    Antenna(-12, -4.2f, -2.5f);
    Antenna(-30, -4.2f, -2.5f);
    Antenna(-48, -4.2f, -2.5f);
    Antenna(-60, -4.2f, -2.5f);
    Antenna(-72, -4.2f, -2.5f);
}

// Draw poles
void drawPole() {
    drawCuboid(5, -5, 5, 0.2, 20, 0.2);
    drawCuboid(5, -5, -25, 0.2, 20, 0.2);
    drawCuboid(5, -15, -10, 0.2, 0.2, 30);

    glPushMatrix();
    glRotatef(30, 0, 1, 0);
    glTranslatef(1.8, -7.2, 2);
    drawCuboid(0, 0, 0, 0.2, 0.2, 10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30, 0, 1, 0);
    glTranslatef(6.9, -7.2, -3);
    drawCuboid(0, 0, 0, 0.2, 0.2, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -42);
    glRotatef(180, 0, 1, 0);

    glPushMatrix();
    glTranslatef(0, 0, -22);
    glRotatef(30, 0, 1, 0);
    glTranslatef(1.8, -7.2, 2);
    drawCuboid(0, 0, 0, 0.2, 0.2, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -22);
    glRotatef(-30, 0, 1, 0);
    glTranslatef(6.9, -7.2, -3);
    drawCuboid(0, 0, 0, 0.2, 0.2, 10);
    glPopMatrix();

    glPopMatrix();
    drawCuboid(10, -7.2f, -10, 0.2, 0.2, 13);
    drawCuboid(0, -7.2f, -10, 0.2, 0.2, 13);
}

// Draw arch structure
void drawArch(float width, float height, float archRadius, int segments, float x = 0, float y = 0, float z = 0) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);
    glVertex3f(-width / 2.0f, 0.0f, 0.0f);
    glVertex3f(width / 2.0f, 0.0f, 0.0f);
    glVertex3f(width / 2.0f, height, 0.0f);
    glVertex3f(-width / 2.0f, height, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, height, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = PI * i / segments;
        float dx = archRadius * cos(angle);
        float dy = archRadius * sin(angle) + height;
        glVertex3f(dx, dy, 0.0f);
    }
    glEnd();
    glPopMatrix();
}

// Draw walls and arches
void drawWall() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(10, -2.0f, -100);
    glScalef(60, 20, 10);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glRotatef(180, 1, 0, 0);
    glTranslatef(2.5, -4, 99);
    drawArch(10.0f, 12.0f, 5.0f, 50);
    glTranslatef(16, 0, 0);
    drawArch(10.0f, 12.0f, 5.0f, 50);
    glPopMatrix();

    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(10, -2.0f, 400);
    glScalef(60, 20, 10);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glRotatef(180, 1, 0, 0);
    glTranslatef(2.5, -4, -399);
    drawArch(10.0f, 12.0f, 5.0f, 50);
    glTranslatef(16, 0, 0);
    drawArch(10.0f, 12.0f, 5.0f, 50);
    glPopMatrix();
}

// Draw ground with texture
void drawGroundWithTexture(GLfloat width, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2.0f, 0.0f, -depth / 2.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2.0f, 0.0f, -depth / 2.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2.0f, 0.0f, depth / 2.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2.0f, 0.0f, depth / 2.0f);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void drawTrain() {
    glPushMatrix();
    glTranslatef(train1Pos, 0, 0);
    train();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-103 + train1Pos, 0, 0);
    train();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(-540 + train2Pos, 0, 21.3);
    train();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(-540 + train2Pos + 103, 0, 21.3);
    train();
    glPopMatrix();
}

void drawRailroad() {
    glPushMatrix();
    glScalef(0.3f, -0.3f, 0.225f);
    glRotatef(90, 0, 1, 0);
    glTranslatef(11.3, -7.6, 150);
    Railroad();
    glPopMatrix();
}
// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        eyeX, eyeY, eyeZ,
        centerX, centerY, centerZ,
        upX, upY, upZ
    );

    // Flip vertically (scale Y by -1), just a habbit..
    glScalef(1.0f, -1.0f, 1.0f);

    glEnable(GL_NORMALIZE);

    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, tra_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tra_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tra_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tra_shininess);

	drawTrain();

    drawRailroad();

    drawPole();

    glPushMatrix();
    glTranslatef(200, 0, 0);
    drawPole();
    glPopMatrix();

    drawCuboid(0, -7.2f, -2.5f, 800, 0.06, 0.06);
    drawCuboid(0, -7.2f, -19, 800, 0.06, 0.06);

    glColor3f(1, 1, 1);

    for (int i = -10; i < 30; i++) {
        drawGroundWithTexture(20, 20, i * 20, 3.6f, 0.5f);
    }
    for (int i = -10; i < 30; i++) {
        drawGroundWithTexture(20, 20, i * 20, 3.6f, -19.5f);
    }

    glPushMatrix();
    glTranslatef(0, -9, 30);
    glRotatef(180, 1, 0, 0);
    glRotatef(-90, 0, 1, 0);
    for (int i = -10; i < 15; i++) {
        glPushMatrix();
        glTranslatef(0, 0, -360 + 40.0f * i);
        drwSlop(40, 40, 10);
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(580, -9, -49);
    glRotatef(180, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    for (int i = -10; i < 15; i++) {
        glPushMatrix();
        glTranslatef(0, 0, -360 + 40.0f * i);
        drwSlop(40, 40, 10);
        glPopMatrix();
    }
    glPopMatrix();

    drawWall();

	// Skybox
    glColor3f(1, 1, 1);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glRotatef(-210, 1, 0, 1);
    glRotatef(60, 0, 1, 0);

    GLUquadric* quadricObj = gluNewQuadric();
    gluQuadricTexture(quadricObj, GL_TRUE);
    gluQuadricNormals(quadricObj, GLU_SMOOTH);
    gluSphere(quadricObj, 800, 80, 80);
    gluDeleteQuadric(quadricObj);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glutSwapBuffers();
}

// Window reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Mouse button callback
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (cameraState == IDLE) {
            cameraState = isMovingForward ? MOVING_TO_START : MOVING_TO_BACK;
            isMovingForward = !isMovingForward;
        }
    }
}

// Update animation logic
void updateAnimation() {
    Rotate += RotateSpeed;
    centerX = train1Pos;

    if (Rotate > 360.0f) {
        Rotate -= 360.0f;
    }

    switch (cameraState) {
    case MOVING_TO_START:
        if (eyeY < 10.0f) {
            eyeY += 1.0f;
            if (eyeY > 10.0f) eyeY = 10.0f;
        }
        if (eyeZ > -30.0f) {
            eyeZ -= 1.0f;
            if (eyeZ < -30.0f) eyeZ = -30.0f;
        }
        if (eyeY == 10.0f && eyeZ == -30.0f) {
            cameraState = IDLE;
        }
        break;

    case MOVING_TO_BACK:
        if (eyeY > initialEyeY) {
            eyeY -= 1.0f;
            if (eyeY < initialEyeY) eyeY = initialEyeY;
        }
        if (eyeZ < 10.0f) {
            eyeZ += 1.0f;
            if (eyeZ > 10.0f) eyeZ = 10.0f;
        }
        if (eyeY == initialEyeY && eyeZ == 10.0f) {
            cameraState = IDLE;
        }
        break;

    case IDLE:
    default:
        break;
    }

    // Train movement logic
    if (train1Pos < 640 && train1) {
        train1Pos += trainSpeed;
    }
    else {
        train1Pos = -120;
        train1 = false;
        train2 = true;
        centerX = 540 - train2Pos - 90;
        centerZ = -21.3f;
    }

    if (train2Pos < 790 && train2) {
        train2Pos += trainSpeed;
    }
    else {
        train2Pos = 0;
        train1 = true;
        train2 = false;
    }

    glutPostRedisplay();
}

// Timer callback
void timer(int value) {
    updateAnimation();
    glutTimerFunc(16, timer, 0);
}

// Mouse motion callback
void mouseMotion(int x, int y) {
    if (isDragging) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        angleY += dx * 0.2f;
        angleX += dy * 0.2f;

        if (angleX > 360.0f) angleX -= 360.0f;
        if (angleX < -360.0f) angleX += 360.0f;
        if (angleY > 360.0f) angleY -= 360.0f;
        if (angleY < -360.0f) angleY += 360.0f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        if (eyeY < 10) eyeY += moveStep;
        break;
    case 's':
    case 'S':
        if (eyeY > 5) eyeY -= moveStep;
        break;
    case 'a':
    case 'A':
        if (eyeX > 0) eyeX -= moveStep;
        break;
    case 'd':
    case 'D':
        if (eyeX < 200) eyeX += moveStep;
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("High speed railway between caves");

    init();
    glutTimerFunc(16, timer, 0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
