#define FREEGLUT_STATIC 
#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>

// Enable math constants
#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global variables
bool isRainy = false;

// Number of screen textures
#define NUM_SCREEN_TEXTURES 3
// Screen texture array
GLuint screenTextures[NUM_SCREEN_TEXTURES];

// Current displayed texture index
int currentTextureIndex = 0;

// Global Quadric object
GLUquadric* quad = nullptr;

// Window size
int windowWidth = 800;
int windowHeight = 600;

// Last mouse position
int lastMouseX = 0;
int lastMouseY = 0;

// Mouse control state
bool isLeftButtonPressed = false;

// View and camera
bool firstPerson = false;
float cameraAngleX = 0.0f;
float cameraAngleY = 20.0f;
float cameraDistance = 50.0f;

// Person position and state
float personPosX = 0.0f;
float personPosZ = 0.0f;
float personAngle = 0.0f;

// Person limbs angles
float leftArmAngle = 0.0f;
float rightArmAngle = 0.0f;
float leftLegAngle = 0.0f;
float rightLegAngle = 0.0f;

// Ornament animation parameters
float ornamentTime = 0.0f;
float ornamentFrequency = 0.0001f;

// Animation parameters
float swingAmplitude = 30.0f;
float swingFrequency = 0.05f;
float animationTime = 0.0f;

// Movement state
bool isMoving = false;

// Road parameters
float roadWidth = 60.0f;
float laneWidth = 25.0f;
float dividerWidth = 2.0f;
float roadLength = 200.0f;

// Minimum safe distance for cars
float minSafeDistance = 30.0f;

// Car dimensions
float carWidth = laneWidth * 0.4f;
float carLength = laneWidth * 0.8f;
float carHeight = laneWidth * 0.3f;
float wheelRadius = carHeight * 0.4f;

// Texture array
GLuint textures[114];

// Car structure
struct Car {
    float x;
    float y;
    float z;
    float speed;
    float direction;
    float maxSpeed;
    float wheelRotation;
    float wheelRadius;
};

// Global cars
std::vector<Car> cars;

// Function prototypes
void timer(int value);
void drawOrnaments(float x, float z);
void drawLights(float x, float z);
void drawChristmasTree(float x, float z);
void drawPerson();
void handleKeypress(unsigned char key, int x, int y);
void handleKeyRelease(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void mouseWheel(int wheel, int direction, int x, int y);
void setupLighting();
void reshape(int w, int h);
void renderScene();
void initOpenGL();
void cleanup();
unsigned char* loadBMP(const char* filename, int& width, int& height);
void drawBush(float x, float z);
void updateCars();
void drawRoad();
void drawSky();
void drawBoundary(float x, float y, float z, float width, float height, float depth, float rotation, GLuint textureID);
void drawCastleAtEnd(float roadLengthParam, GLuint textureID);
void drawRock(float x, float z, float size);
void drawStreetLight(float x, float z);
void drawGrass();
void drawCar(const Car& car);
void groupAndSortCars(std::vector<Car>& laneCars, float laneZ, bool forward);
void drawScreen(float x, float z);
void initCars();

// Convert degrees to radians
inline float degToRad(float degrees) {
    return degrees * static_cast<float>(M_PI) / 180.0f;
}

// Calculate direction vectors based on camera angles
void calculateDirectionVectors(float& forwardX, float& forwardZ, float& leftX, float& leftZ) {
    float radX = degToRad(cameraAngleX);

    forwardX = sin(radX);
    forwardZ = cos(radX);

    leftX = sin(radX - M_PI / 2.0f);
    leftZ = cos(radX - M_PI / 2.0f);
}

// Draw ornaments
void drawOrnaments(float x, float z) {
    int numOrnaments = 15;
    float ornamentRadius = 0.7f;
    for (int i = 0; i < numOrnaments; ++i) {
        float angle = (2.0f * static_cast<float>(M_PI) / numOrnaments) * i;
        float radius = 5.0f + static_cast<float>(rand()) / RAND_MAX * 2.0f;
        float height = 20.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f;
        float ox = x + radius * cos(angle);
        float oz = z + radius * sin(angle);
        float oy = height;

        float r = static_cast<float>(rand()) / RAND_MAX;
        float g = static_cast<float>(rand()) / RAND_MAX;
        float b = static_cast<float>(rand()) / RAND_MAX;
        glColor3f(r, g, b);

        glPushMatrix();
        glTranslatef(ox, oy, oz);
        glutSolidSphere(ornamentRadius, 16, 16);
        glPopMatrix();
    }
}

// Draw sky dome
void drawSky() {
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, isRainy ? textures[28] : textures[25]);

    glColor3f(1.0f, 1.0f, 1.0f);

    float radius = 500.0f;
    int slices = 50;
    int stacks = 25;

    for (int i = 0; i < stacks; ++i) {
        float lat0 = M_PI / 2 - (float)i * (M_PI / 2) / stacks;
        float lat1 = M_PI / 2 - (float)(i + 1) * (M_PI / 2) / stacks;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float)j / slices;
            float x = cos(lng);
            float z = sin(lng);

            float y0 = radius * sin(lat0);
            float x0 = radius * cos(lat0) * x;
            float z0 = radius * cos(lat0) * z;
            float u0 = (float)j / slices;
            float v0 = 1.0f - ((lat0 + M_PI / 2) / (M_PI));

            float y1 = radius * sin(lat1);
            float x1 = radius * cos(lat1) * x;
            float z1 = radius * cos(lat1) * z;
            float u1 = (float)j / slices;
            float v1 = 1.0f - ((lat1 + M_PI / 2) / (M_PI));

            glTexCoord2f(u0, v0);
            glVertex3f(x0, y0, z0);

            glTexCoord2f(u1, v1);
            glVertex3f(x1, y1, z1);
        }
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);

    glPopMatrix();
}

// Draw lights
void drawLights(float x, float z) {
    int numLights = 30;
    float lightHeight = 0.3f;
    float lightRadius = 0.15f;
    for (int i = 0; i < numLights; ++i) {
        float angle = (2.0f * static_cast<float>(M_PI) / numLights) * i;
        float radius = 6.0f + static_cast<float>(rand()) / RAND_MAX * 2.0f;
        float height = 18.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f;
        float lx = x + radius * cos(angle);
        float lz = z + radius * sin(angle);
        float ly = height;

        GLfloat lightEmission[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, lightEmission);
        glColor3f(1.0f, 1.0f, 0.0f);

        glPushMatrix();
        glTranslatef(lx, ly, lz);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, lightRadius, lightRadius, lightHeight, 8, 8);
        glPopMatrix();

        GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    }
}

// Draw a Christmas tree
void drawChristmasTree(float x, float z) {
    // Trunk
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 2.0f, 2.0f, 15.0f, 16, 16);
    glPopMatrix();

    // Leaves
    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(x, 15.0f, z);

    int layers = 7;
    float baseRadius = 8.0f;
    float height = 5.0f;
    float overlap = 1.5f;

    for (int i = 0; i < layers; ++i) {
        float radius = baseRadius - i * 1.2f;
        if (radius <= 0.0f) break;

        glPushMatrix();
        glTranslatef(0.0f, i * (height - overlap), 0.0f);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(radius, height, 16, 16);
        glPopMatrix();
    }
    glPopMatrix();

    // Ornaments and lights
    drawOrnaments(x, z);
    drawLights(x, z);
}

// Draw the road
void drawRoad() {
    glBindTexture(GL_TEXTURE_2D, textures[22]);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.01f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    float textureRepeatX = roadLength / 100.0f;
    float textureRepeatZ = roadWidth / 60.0f;

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-roadLength / 2.0f, 0.0f, -roadWidth / 2.0f);
    glTexCoord2f(textureRepeatX, 0.0f); glVertex3f(-roadLength / 2.0f, 0.0f, roadWidth / 2.0f);
    glTexCoord2f(textureRepeatX, textureRepeatZ); glVertex3f(roadLength / 2.0f, 0.0f, roadWidth / 2.0f);
    glTexCoord2f(0.0f, textureRepeatZ); glVertex3f(roadLength / 2.0f, 0.0f, -roadWidth / 2.0f);
    glEnd();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);
    int numDashes = 30;
    float dashLength = roadLength / (2.0f * numDashes);
    float gapLength = dashLength * 1.5f;

    glPushMatrix();
    glTranslatef(0.0f, 0.02f, 0.0f);

    for (int i = 0; i < numDashes; ++i) {
        float xStart = -roadLength / 2.0f + i * (dashLength + gapLength);
        float xEnd = xStart + dashLength;

        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(xStart, 0.0f, -dividerWidth / 2.0f);
        glVertex3f(xStart, 0.0f, dividerWidth / 2.0f);
        glVertex3f(xEnd, 0.0f, dividerWidth / 2.0f);
        glVertex3f(xEnd, 0.0f, -dividerWidth / 2.0f);
        glEnd();
    }

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

// Draw car
void drawCar(const Car& car) {
    glPushMatrix();
    glTranslatef(car.x, car.y + carHeight / 2.0f, car.z);
    float angleDeg = car.direction * 180.0f / static_cast<float>(M_PI);
    glRotatef(angleDeg, 0.0f, 1.0f, 0.0f);

    // Car body
    glColor3f(1.0f, 0.6f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, carHeight * 0.3f, 0.0f);
    glScalef(carLength, carHeight * 0.6f, carWidth);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Car top (hemispheric)
    glColor3f(1.0f, 0.6f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, carHeight * 0.75f, 0.0f);
    glScalef(carLength * 0.9f, carHeight * 0.6f, carWidth * 0.9f);
    glutSolidSphere(0.5f, 30, 30);
    glPopMatrix();

    // Wheels
    glColor3f(0.2f, 0.2f, 0.2f);
    float wheelWidth = carWidth * 0.3f;

    // left front wheel
    glPushMatrix();
    glTranslatef(-carLength * 0.4f, -carHeight * 0.2f, carWidth * 0.4f);
    glutSolidCylinder(wheelRadius, wheelWidth, 30, 30);
    glPopMatrix();

    // right front wheel
    glPushMatrix();
    glTranslatef(-carLength * 0.4f, -carHeight * 0.2f, -carWidth * 0.7f);
    glutSolidCylinder(wheelRadius, wheelWidth, 30, 30);
    glPopMatrix();

    // left rear wheel
    glPushMatrix();
    glTranslatef(carLength * 0.4f, -carHeight * 0.2f, carWidth * 0.4f);
    glutSolidCylinder(wheelRadius, wheelWidth, 30, 30);
    glPopMatrix();

    // right rear wheel
    glPushMatrix();
    glTranslatef(carLength * 0.4f, -carHeight * 0.2f, -carWidth * 0.7f);
    glutSolidCylinder(wheelRadius, wheelWidth, 30, 30);
    glPopMatrix();

    // Windows
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.2f, 0.6f, 0.8f, 0.5f);

    // left window
    glPushMatrix();
    glTranslatef(0.0f, carHeight * 0.75f, carWidth * 0.45f);
    glScalef(carLength * 0.6f, carHeight * 0.4f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // right window
    glPushMatrix();
    glTranslatef(0.0f, carHeight * 0.75f, -carWidth * 0.45f);
    glScalef(carLength * 0.6f, carHeight * 0.4f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glDisable(GL_BLEND);

    // Headlights
    glColor3f(1.0f, 1.0f, 0.0f);
    float lightRadius = 0.2f;

    // left headlight
    glPushMatrix();
    glTranslatef(-carLength * 0.5f + 0.2f, carHeight * 0.4f, carWidth * 0.4f);
    glutSolidSphere(lightRadius, 20, 20);
    glPopMatrix();

    // right headlight
    glPushMatrix();
    glTranslatef(-carLength * 0.5f + 0.2f, carHeight * 0.4f, -carWidth * 0.4f);
    glutSolidSphere(lightRadius, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

// Draw a screen
void drawScreen(float x, float z) {
    float screenWidth = 60.0f;
    float screenHeight = 40.0f;

    glPushMatrix();
    glTranslatef(x, 20.0f, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, screenTextures[currentTextureIndex]);
    glColor3f(1.0f, 1.0f, 1.0f);

    // front
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-screenWidth / 2, -screenHeight / 2, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(screenWidth / 2, -screenHeight / 2, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(screenWidth / 2, screenHeight / 2, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-screenWidth / 2, screenHeight / 2, 1.0f);
    glEnd();

    // back
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-screenWidth / 2, -screenHeight / 2, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(screenWidth / 2, -screenHeight / 2, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(screenWidth / 2, screenHeight / 2, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-screenWidth / 2, screenHeight / 2, -1.0f);
    glEnd();

    // edges
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Draw a bush
void drawBush(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glColor3f(0.0f, 0.5f, 0.0f);
    glScalef(4.0f, 4.0f, 4.0f);
    glutSolidSphere(1.5f, 16, 16);
    glPopMatrix();
}

// Draw person
void drawPerson() {
    glPushMatrix();
    glTranslatef(personPosX, 0.0f, personPosZ);
    glRotatef(personAngle, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glDisable(GL_TEXTURE_2D);

    // Body
    glColor3f(0.8f, 0.5f, 0.2f);
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glScalef(1.0f, 1.5f, 1.0f);
    glutSolidCube(2.0f);
    glPopMatrix();

    // Head
    glColor3f(1.0f, 0.8f, 0.6f);
    glPushMatrix();
    glTranslatef(0.0f, 5.5f, 0.0f);
    glutSolidSphere(1.0f, 16, 16);
    glPopMatrix();

    // Arms
    glColor3f(0.8f, 0.5f, 0.2f);
    glPushMatrix();
    glTranslatef(-1.5f, 4.0f, 0.0f);
    glRotatef(leftArmAngle, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 2.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, 4.0f, 0.0f);
    glRotatef(rightArmAngle, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 2.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Legs
    glColor3f(0.3f, 0.3f, 0.8f);
    glPushMatrix();
    glTranslatef(-0.5f, 1.0f, 0.0f);
    glRotatef(leftLegAngle, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 3.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 1.0f, 0.0f);
    glRotatef(rightLegAngle, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 3.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);

    glPopMatrix();
    glPopMatrix();
}

// Setup lighting
void setupLighting() {
    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPos[] = { 100.0f, 100.0f, 100.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Draw a rock
void drawRock(float x, float z, float size) {
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(x, size / 2.0f, z);
    glutSolidSphere(size, 16, 16);
    glPopMatrix();
}

// Draw streetlight
void drawStreetLight(float x, float z) {
    float poleHeight = 29.625f;
    float lampHeight = poleHeight;

    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.3f, 0.3f, poleHeight, 12, 12);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(x, lampHeight, z);
    glutSolidSphere(1.0f, 12, 12);
    glPopMatrix();
}

// Draw grass
void drawGrass() {
    glColor3f(0.3f, 0.8f, 0.3f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();
}

// Load BMP
unsigned char* loadBMP(const char* filename, int& width, int& height) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0 || !file) {
        printf("Unable to open texture file: %s\n", filename);
        return nullptr;
    }

    unsigned char header[54];
    size_t readBytes = fread(header, sizeof(unsigned char), 54, file);
    if (readBytes != 54) {
        printf("Unable to read BMP header: %s\n", filename);
        fclose(file);
        return nullptr;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a valid BMP file: %s\n", filename);
        fclose(file);
        return nullptr;
    }

    int dataPos = *(int*)&(header[0x0A]);
    int imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    fseek(file, dataPos, SEEK_SET);

    unsigned char* data = new unsigned char[imageSize];
    readBytes = fread(data, sizeof(unsigned char), imageSize, file);
    if (readBytes != imageSize) {
        printf("Failed to read image data: %s\n", filename);
        delete[] data;
        fclose(file);
        return nullptr;
    }
    fclose(file);

    if (imageSize % 3 != 0) {
        printf("Image size is not a multiple of 3: %s\n", filename);
        delete[] data;
        return nullptr;
    }

    // Convert BGR to RGB
    for (int i = 0; i < imageSize; i += 3) {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }

    return data;
}

// Draw boundary (like walls)
void drawBoundary(float x, float y, float z, float width, float height, float depth, float rotation, GLuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    glDisable(GL_CULL_FACE);

    glPushMatrix();
    glTranslatef(x, y + height / 2.0f, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);

    // front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, depth / 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, depth / 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width / 2.0f, height / 2.0f, depth / 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, depth / 2.0f);

    // back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, -depth / 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, -depth / 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width / 2.0f, height / 2.0f, -depth / 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, -depth / 2.0f);

    glEnd();

    glPopMatrix();

    glEnable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawCastleAtEnd(float roadLengthParam, GLuint textureID) {
    float boundaryWidth = roadLengthParam;
    float boundaryHeight = 90.0f;
    float boundaryDepth = 0.5f;
    float rotationAngle = 90.0f;

    float boundaryPosX = roadLengthParam / 2.0f;
    float boundaryPosZ = 0.0f;

    drawBoundary(boundaryPosX, 0.0f, boundaryPosZ, boundaryWidth, boundaryHeight, boundaryDepth, rotationAngle, textureID);
}

void groupAndSortCars(std::vector<Car>& laneCars, float laneZ, bool forward) {
    laneCars.clear();
    for (auto& c : cars) {
        if (std::fabs(c.z - laneZ) < 0.1f) {
            laneCars.push_back(c);
        }
    }

    std::sort(laneCars.begin(), laneCars.end(), [](const Car& a, const Car& b) {
        return a.x < b.x;
        });
}

// Update cars
void updateCars() {
    std::vector<Car*> lanePositive;
    std::vector<Car*> laneNegative;

    for (auto& car : cars) {
        if (std::fabs(car.z - 10.0f) < 0.1f) {
            lanePositive.push_back(&car);
        }
        else if (std::fabs(car.z + 10.0f) < 0.1f) {
            laneNegative.push_back(&car);
        }
    }

    std::sort(lanePositive.begin(), lanePositive.end(), [](Car* a, Car* b) {
        return a->x > b->x;
        });

    std::sort(laneNegative.begin(), laneNegative.end(), [](Car* a, Car* b) {
        return a->x < b->x;
        });

    for (size_t i = 0; i < lanePositive.size(); ++i) {
        Car* current = lanePositive[i];
        if (i == 0) {
            current->speed = std::min(current->speed + 0.01f, current->maxSpeed);
        }
        else {
            Car* front = lanePositive[i - 1];
            float distance = front->x - current->x - carLength;
            if (distance < minSafeDistance) {
                current->speed = std::min(current->speed, front->speed * 0.9f);
                if (current->speed < 0.2f) current->speed = 0.2f;
            }
            else {
                current->speed = std::min(current->speed + 0.01f, current->maxSpeed);
            }
        }
    }

    for (size_t i = 0; i < laneNegative.size(); ++i) {
        Car* current = laneNegative[i];
        if (i == 0) {
            current->speed = std::min(current->speed + 0.01f, current->maxSpeed);
        }
        else {
            Car* front = laneNegative[i - 1];
            float distance = current->x - front->x - carLength;
            if (distance < minSafeDistance) {
                current->speed = std::min(current->speed, front->speed * 0.9f);
                if (current->speed < 0.2f) current->speed = 0.2f;
            }
            else {
                current->speed = std::min(current->speed + 0.01f, current->maxSpeed);
            }
        }
    }

    for (auto& car : cars) {
        car.x += car.speed * cosf(car.direction);
        car.z += car.speed * sinf(car.direction);

        if (car.direction == 0.0f && car.x > roadLength / 2.0f + 50.0f) {
            car.x = -roadLength / 2.0f - 50.0f;
        }
        else if (std::fabs(car.direction - M_PI) < 0.001f && car.x < -roadLength / 2.0f - 50.0f) {
            car.x = roadLength / 2.0f + 50.0f;
        }
    }
}

// Reshape callback
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input
void handleKeypress(unsigned char key, int x, int y) {
    float moveStep = 1.0f;
    float forwardX, forwardZ, leftX, leftZ;
    calculateDirectionVectors(forwardX, forwardZ, leftX, leftZ);

    switch (key) {
    case 'w': case 'W':
        personAngle = atan2(forwardX, forwardZ) * 180.0f / static_cast<float>(M_PI);
        personPosX -= moveStep * forwardX;
        personPosZ -= moveStep * forwardZ;
        isMoving = true;
        break;
    case 's': case 'S':
        personAngle = atan2(-forwardX, -forwardZ) * 180.0f / static_cast<float>(M_PI);
        personPosX += moveStep * forwardX;
        personPosZ += moveStep * forwardZ;
        isMoving = true;
        break;
    case 'a': case 'A':
        personAngle = atan2(leftX, leftZ) * 180.0f / static_cast<float>(M_PI);
        personPosX += moveStep * leftX;
        personPosZ += moveStep * leftZ;
        isMoving = true;
        break;
    case 'd': case 'D':
        personAngle = atan2(-leftX, -leftZ) * 180.0f / static_cast<float>(M_PI);
        personPosX -= moveStep * leftX;
        personPosZ -= moveStep * leftZ;
        isMoving = true;
        break;
    case 'v': case 'V':
        firstPerson = !firstPerson;
        break;
    case 'c': case 'C':
        currentTextureIndex = (currentTextureIndex + 1) % NUM_SCREEN_TEXTURES;
        break;
    case 't': case 'T':
        isRainy = !isRainy;
        break;
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

// Key release
void handleKeyRelease(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W' || key == 's' || key == 'S' ||
        key == 'a' || key == 'A' || key == 'd' || key == 'D') {
        isMoving = false;
    }
    glutPostRedisplay();
}

// Special keys (arrow keys)
void handleSpecialKeypress(int key, int x, int y) {
    float moveStep = 1.0f;
    float forwardX, forwardZ, leftX, leftZ;
    calculateDirectionVectors(forwardX, forwardZ, leftX, leftZ);

    switch (key) {
    case GLUT_KEY_UP:
        personAngle = atan2(forwardX, forwardZ) * 180.0f / static_cast<float>(M_PI);
        personPosX -= moveStep * forwardX;
        personPosZ -= moveStep * forwardZ;
        isMoving = true;
        break;
    case GLUT_KEY_DOWN:
        personAngle = atan2(-forwardX, -forwardZ) * 180.0f / static_cast<float>(M_PI);
        personPosX += moveStep * forwardX;
        personPosZ += moveStep * forwardZ;
        isMoving = true;
        break;
    case GLUT_KEY_LEFT:
        personAngle = atan2(leftX, leftZ) * 180.0f / static_cast<float>(M_PI);
        personPosX += moveStep * leftX;
        personPosZ += moveStep * leftZ;
        isMoving = true;
        break;
    case GLUT_KEY_RIGHT:
        personAngle = atan2(-leftX, -leftZ) * 180.0f / static_cast<float>(M_PI);
        personPosX -= moveStep * leftX;
        personPosZ -= moveStep * leftZ;
        isMoving = true;
        break;
    }

    glutPostRedisplay();
}

// Mouse motion
void mouseMotion(int x, int y) {
    if (isLeftButtonPressed) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        cameraAngleX += deltaX * 0.3f;
        cameraAngleY += deltaY * 0.3f;

        if (cameraAngleY > 89.0f) cameraAngleY = 89.0f;
        if (cameraAngleY < -89.0f) cameraAngleY = -89.0f;

        lastMouseX = x;
        lastMouseY = y;

        if (firstPerson) {
            personAngle = cameraAngleX;
        }

        glutPostRedisplay();
    }
}

// Mouse button
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isLeftButtonPressed = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else {
            isLeftButtonPressed = false;
        }
    }
    else if (button == 3) {
        cameraDistance -= 2.0f;
        if (cameraDistance < 10.0f) cameraDistance = 10.0f;
        glutPostRedisplay();
    }
    else if (button == 4) {
        cameraDistance += 2.0f;
        if (cameraDistance > 200.0f) cameraDistance = 200.0f;
        glutPostRedisplay();
    }
}

// Mouse wheel
void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction > 0) {
        cameraDistance -= 2.0f;
    }
    else {
        cameraDistance += 2.0f;
    }

    if (cameraDistance < 10.0f) cameraDistance = 10.0f;
    if (cameraDistance > 200.0f) cameraDistance = 200.0f;

    glutPostRedisplay();
}

// Render scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera setup
    if (!firstPerson) {
        float radX = degToRad(cameraAngleX);
        float radY = degToRad(cameraAngleY);
        float camX = personPosX + cameraDistance * cos(radY) * sin(radX);
        float camY = 5.0f + cameraDistance * sin(radY);
        float camZ = personPosZ + cameraDistance * cos(radY) * cos(radX);

        gluLookAt(camX, camY, camZ,
            personPosX, 6.0f, personPosZ,
            0.0f, 1.0f, 0.0f);
    }
    else {
        float camX = personPosX;
        float camY = 5.0f;
        float camZ = personPosZ;

        float targetX = camX - cos(degToRad(cameraAngleY)) * sin(degToRad(cameraAngleX));
        float targetY = camY - sin(degToRad(cameraAngleY));
        float targetZ = camZ - cos(degToRad(cameraAngleY)) * cos(degToRad(cameraAngleX));

        gluLookAt(camX, camY, camZ,
            targetX, targetY, targetZ,
            0.0f, 1.0f, 0.0f);
    }

    drawSky();
    setupLighting();
    drawGrass();
    drawRoad();

    drawCastleAtEnd(roadLength, isRainy ? textures[29] : textures[23]);

    float mountainPosX_neg = -roadLength / 2.0f;
    float mountainPosZ_neg1 = 0.0f;
    float boundaryWidth_mountain = roadLength;
    float boundaryHeight_mountain = 90.0f;
    float boundaryDepth_mountain = 0.5f;
    float rotationAngle_mountain = 90.0f;

    drawBoundary(mountainPosX_neg, 0.0f, mountainPosZ_neg1, boundaryWidth_mountain, boundaryHeight_mountain, boundaryDepth_mountain, rotationAngle_mountain, isRainy ? textures[30] : textures[24]);

    float boundaryWidth = 200.0f;
    float boundaryHeight = 90.0f;
    float boundaryDepth = 0.5f;

    drawBoundary(0.0f, 0.0f, 100.0f, boundaryWidth, boundaryHeight, boundaryDepth, 180.0f, isRainy ? textures[31] : textures[26]);
    drawBoundary(0.0f, 0.0f, -100.0f, boundaryWidth, boundaryHeight, boundaryDepth, 0.0f, isRainy ? textures[32] : textures[27]);

    if (!firstPerson) {
        drawPerson();
    }

    updateCars();

    std::vector<std::pair<float, float>> treePositions = {
        {-80.0f, -80.0f}, {-60.0f, -80.0f}, {-40.0f, -80.0f}, {-20.0f, -80.0f},
        {0.0f, -80.0f}, {20.0f, -80.0f}, {40.0f, -80.0f}, {60.0f, -80.0f},
        {80.0f, -80.0f}, {-80.0f, 80.0f}, {-60.0f, 80.0f}, {-40.0f, 80.0f},
        {-20.0f, 80.0f}, {0.0f, 80.0f}, {20.0f, 80.0f}, {40.0f, 80.0f},
        {60.0f, 80.0f}, {80.0f, 80.0f}
    };

    for (auto& pos : treePositions) {
        drawChristmasTree(pos.first, pos.second);
    }

    std::vector<std::pair<float, float>> bushPositions = {
        {-70.0f, -70.0f}, {-50.0f, -70.0f}, {-30.0f, -70.0f},
        {50.0f, 50.0f}, {70.0f, 50.0f}, {90.0f, 50.0f}
    };

    for (auto& pos : bushPositions) {
        drawBush(pos.first, pos.second);
    }

    std::vector<std::pair<float, float>> rocks = {
        {-70.0f, 70.0f}, {-60.0f, 75.0f}, {-50.0f, 65.0f},
        {70.0f, -70.0f}, {60.0f, -75.0f}, {50.0f, -65.0f}
    };

    for (const auto& r : rocks) {
        drawRock(r.first, r.second, 2.0f);
    }

    float streetLightInterval = 20.0f;
    float roadStartX = -roadLength / 2.0f;
    float roadEndX = roadLength / 2.0f;

    for (float x = roadStartX; x <= roadEndX; x += streetLightInterval) {
        drawStreetLight(x, 28.0f);
        drawStreetLight(x, -28.0f);
    }

    float rockX = 90.0f, rockZ = 0.0f;
    float bushX = -90.0f, bushZ = -90.0f;
    float screenX = (rockX + bushX) / 2.0f;
    float screenZ = (rockZ + bushZ) / 2.0f;

    for (const auto& car : cars) {
        drawCar(car);
    }

    drawScreen(screenX, screenZ);
    glutSwapBuffers();
}

// Initialize cars
void initCars() {
    // Forward lane (z=10)
    for (int i = 0; i < 5; ++i) {
        Car c;
        c.x = -roadLength / 2.0f - i * 30.0f;
        c.y = 0.0f;
        c.z = 10.0f;
        c.speed = 0.5f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
        c.direction = 0.0f;
        c.maxSpeed = c.speed;
        c.wheelRotation = 0.0f;
        c.wheelRadius = carHeight * 0.4f;
        cars.push_back(c);
    }

    // Opposite lane (z=-10)
    for (int i = 0; i < 5; ++i) {
        Car c;
        c.x = roadLength / 2.0f + i * 30.0f;
        c.y = 0.0f;
        c.z = -10.0f;
        c.speed = 0.5f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
        c.direction = static_cast<float>(M_PI);
        c.maxSpeed = c.speed;
        c.wheelRotation = 0.0f;
        c.wheelRadius = carHeight * 0.4f;
        cars.push_back(c);
    }
}

// Init OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    setupLighting();

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    int w, h;
    glGenTextures(114, textures);

    // Load road texture
    unsigned char* road_data = loadBMP("texture_image/road.bmp", w, h);
    if (!road_data) { printf("Failed to load road.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[22]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, road_data);
    delete[] road_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // background1.bmp
    unsigned char* background_data = loadBMP("texture_image/background1.bmp", w, h);
    if (!background_data) { printf("Failed to load background1.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[23]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, background_data);
    delete[] background_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // background2.bmp (mountain)
    unsigned char* mountain_data = loadBMP("texture_image/background2.bmp", w, h);
    if (!mountain_data) { printf("Failed to load background2.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[24]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, mountain_data);
    delete[] mountain_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // sky1.bmp
    unsigned char* sky_data = loadBMP("texture_image/sky1.bmp", w, h);
    if (!sky_data) { printf("Failed to load sky1.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[25]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, sky_data);
    delete[] sky_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // Screen textures
    const char* screenFiles[NUM_SCREEN_TEXTURES] = { "texture_image/cb.bmp", "texture_image/nature.bmp", "texture_image/shop.bmp" };
    glGenTextures(NUM_SCREEN_TEXTURES, screenTextures);
    for (int i = 0; i < NUM_SCREEN_TEXTURES; i++) {
        unsigned char* scrData = loadBMP(screenFiles[i], w, h);
        if (!scrData) {
            printf("Failed to load screen texture: %s\n", screenFiles[i]);
            exit(1);
        }

        glBindTexture(GL_TEXTURE_2D, screenTextures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, scrData);
        delete[] scrData;
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // side1.bmp
    unsigned char* boundary3_data = loadBMP("texture_image/side1.bmp", w, h);
    if (!boundary3_data) { printf("Failed to load side1.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[26]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, boundary3_data);
    delete[] boundary3_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // Another side1.bmp
    unsigned char* boundary4_data = loadBMP("texture_image/side1.bmp", w, h);
    if (!boundary4_data) { printf("Failed to load side1.bmp second time\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[27]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, boundary4_data);
    delete[] boundary4_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // sky2.bmp (rainy sky)
    unsigned char* rainy_sky_data = loadBMP("texture_image/sky2.bmp", w, h);
    if (!rainy_sky_data) { printf("Failed to load sky2.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[28]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, rainy_sky_data);
    delete[] rainy_sky_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // rain1.bmp
    unsigned char* rainy_boundary1_data = loadBMP("texture_image/rain1.bmp", w, h);
    if (!rainy_boundary1_data) { printf("Failed to load rain1.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[29]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, rainy_boundary1_data);
    delete[] rainy_boundary1_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // rain2.bmp
    unsigned char* rainy_boundary2_data = loadBMP("texture_image/rain2.bmp", w, h);
    if (!rainy_boundary2_data) { printf("Failed to load rain2.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[30]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, rainy_boundary2_data);
    delete[] rainy_boundary2_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    // side2.bmp
    unsigned char* rainy_boundaryR3_data = loadBMP("texture_image/side2.bmp", w, h);
    if (!rainy_boundaryR3_data) { printf("Failed to load side2.bmp\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[31]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, rainy_boundaryR3_data);
    delete[] rainy_boundaryR3_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    unsigned char* rainy_boundaryR4_data = loadBMP("texture_image/side2.bmp", w, h);
    if (!rainy_boundaryR4_data) { printf("Failed to load side2.bmp second time\n"); exit(1); }
    glBindTexture(GL_TEXTURE_2D, textures[32]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, rainy_boundaryR4_data);
    delete[] rainy_boundaryR4_data;
    glBindTexture(GL_TEXTURE_2D, 0);

    glutTimerFunc(16, timer, 0);
}

void cleanup() {
    if (quad) {
        gluDeleteQuadric(quad);
        quad = nullptr;
    }

    glDeleteTextures(114, textures);
}

void timer(int value) {
    ornamentTime += ornamentFrequency;

    if (isMoving) {
        animationTime += swingFrequency;
        leftArmAngle = -swingAmplitude * sin(animationTime);
        rightArmAngle = swingAmplitude * sin(animationTime);
        leftLegAngle = swingAmplitude * sin(animationTime);
        rightLegAngle = -swingAmplitude * sin(animationTime);
    }
    else {
        leftArmAngle = 0.0f;
        rightArmAngle = 0.0f;
        leftLegAngle = 0.0f;
        rightLegAngle = 0.0f;
    }

    updateCars();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D Modeling");

    lastMouseX = windowWidth / 2;
    lastMouseY = windowHeight / 2;

    initOpenGL();
    initCars();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyRelease);
    glutSpecialFunc(handleSpecialKeypress);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
#ifdef GLUT_MOUSE_WHEEL_SUPPORTED
    glutMouseWheelFunc(mouseWheel);
#endif

    srand(static_cast<unsigned int>(time(NULL)));
    atexit(cleanup);
    glutMainLoop();
    return 0;
}
