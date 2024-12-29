#define FREEGLUT_STATIC
#include "GL/freeglut.h"
#include <Windows.h>
#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// Overload for vector definition and operations; Union for multiple access
struct Vec2
{
	Vec2()
		: x(0.0f), y(0.0f)
	{};

	Vec2(float inX, float inY)
		: x(inX), y(inY)
	{
	}

	Vec2 operator*(float value)
	{
		return Vec2(x * value, y * value);
	}

	const float& operator[](int index) const
	{
		return value[index];
	}

	float& operator[](int index)
	{
		return value[index];
	}

	union
	{
		struct
		{
			float x;
			float y;
		};

		struct
		{
			float value[2];
		};
	};
};

struct Vec3
{
	Vec3()
		: x(0.0f), y(0.0f), z(0.0f)
	{};

	Vec3(float inX, float inY, float inZ)
		: x(inX), y(inY), z(inZ)
	{
	}

	Vec3 operator*(float value)
	{
		return Vec3(x * value, y * value, z * value);
	}

	Vec3 operator+=(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	const float& operator[](int index) const
	{
		return value[index];
	}

	float& operator[](int index)
	{
		return value[index];
	}

	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float value[3];
		};
	};
};

struct Vec4
{
	Vec4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{};

	Vec4(float inX, float inY, float inZ, float inW)
		: x(inX), y(inY), z(inZ), w(inW)
	{
	}

	Vec4 operator*(float value)
	{
		return Vec4(x * value, y * value, z * value, w * value);
	}

	operator Vec3()
	{
		return { x, y, z };
	}

	Vec4 operator+=(const Vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec4 operator-=(const Vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	const float& operator[](int index) const
	{
		return value[index];
	}

	float& operator[](int index)
	{
		return value[index];
	}

	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float value[4];
		};
	};
};

// Inline expansion for reducing function calling overhead, directly insert the method body
inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vec4 operator+(const Vec4& a, const Vec4& b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z, 1.0f };
}

inline Vec4 operator-(const Vec4& a, const Vec4& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z, 1.0f };
}

inline float dot(const Vec3& a, const Vec3& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline Vec3 cross(const Vec3& a, const Vec3& b)
{
	return { a.y * b.z - a.z * b.y,
		   -(a.x * b.z - a.z * b.x),
			 a.x * b.y - a.y * b.x };
}

// Color definition
namespace Color
{
	static Vec4 RGB2Float(int r, int g, int b)
	{
		return Vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0);
	}

	static Vec4 White = RGB2Float(255, 255, 255);
	static Vec4 Black = RGB2Float(0, 0, 0);
	static Vec4 Red{ 1.0f, 0.0f, 0.0f, 1.0f };
	static Vec4 Green{ 0.0f, 1.0f, 0.0f, 1.0f };
	static Vec4 PeriwinklePurple = RGB2Float(190, 147, 228);
	static Vec4 Pink = RGB2Float(244, 170, 196);
}

inline float length(const Vec3& v)
{
	return std::sqrtf(dot(v, v));
}

struct Plane
{
	void moveUP() { position.y += speed; }
	void moveDown() { position.y -= speed; }
	void moveForward() { position += forward * speed; }
	void moveBack() { position -= forward * speed; }

	Vec4 position{ 0.0f, 10.0f, 1.0f, 1.0f };
	Vec4 forward{ 0.0f, 0.0f, -1.0f, 0.0f };
	Vec4 right{ 1.0f, 0.0f, 0.0f, 0.0f };
	Vec3 rotation{ 0.0f, 0.0f, 0.0f };

	float speed = 0.1f;
};

struct Bullet
{
	void update()
	{
		position += direction * speed;
	}

	Vec3 position;
	Vec3 size{ 1.0f, 1.0f, 1.0f };
	Vec3 direction;

	float radius = 0.05f;
	float speed = 0.5f;
};

struct Enemy
{
	Vec3 position{ 0.0f, 0.0f, 0.0f };
	Vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
	float radius = 1.0f;
	bool dead = false;
};

struct Vertex
{
	float x, y, z;
	float nX, nY, nZ;
};

// Forward Declaration
void key(unsigned char key, int x, int y);
void keyboard(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

void reshape(int width, int height);
void drawAxis();
void drawSkybox();
void drawSea();
void drawLand();
void drawGrid();
void drawBullets();
void drawEnemies();
void drawPlane();
void drawScene();

void printKeyControl();

void shoot();
void generateEnemies();
void processInput();
void updateCamera();
void updatePlane();
void updateBullets();
void updateEnemies();
void update();
void display();

inline float toRadians(float angle)
{
	return static_cast<float>(M_PI / 180.0f * angle);
}

// Enumerable class for camera view transformation
enum class ECameraView
{
	Top,
	Front,
	Side
};

void setCameraView(ECameraView cameraView);

const float axisLineWidth = 5.0f;
const float axisLength = 10.0f;

const int GLUT_KEY_ESCAPE = 27;

bool fullScreen = false;

bool toggleFog = true;
bool toggleLand = true;
bool toggleLandTexture = true;
bool toggleGrid = false;

float cameraSpeed = 0.1f;
float cameraRotation = 100.0f;

Vec3 planeOffset{ -2.0f, 0.0f, 0.0f };

const float SkyboxRadius = 300.0f;

const float PlaneHeight = 10.0f;

int windowWidth = 1920;
int windowHeight = 1080;

Vec4 Forward{ 0.0f, 0.0f, -1.0f, 0.0f };
Vec4 Right{ 1.0f, 0.0f, 0.0f, 0.0f };

Vec4 direction = Forward;

std::vector<Vertex> vertices;

// Terrain
int numX = 0;
int numY = 0;
int onumX = 0;
int onumY = 0;
int stepX = 0;
int stepY = 0;

// Multiple bullets and enemies
std::vector<Bullet> bullets;
std::vector<Enemy> enemies;

Vec3 getColor(int32_t index);

class Camera
{
public:
	Camera();
	Vec4 position;
	Vec4 target;
	~Camera() = default;
};

Camera::Camera() :position{ 0.0f, 10.0f, 20.0f, 1.0f },
target{ 0.0f, 10.0f, 0.0f, 1.0f } {};

// Lighting source definition
class PointLight
{
public:
	Vec4 color;
	Vec4 position;

	PointLight();
	void addLight();
	void draw();
	void disable();
	void enable();
	~PointLight() = default;
};

PointLight::PointLight() : color{ 0.691f, 0.653f, 0.254f , 1.0f },
position{ 4.3f, 3.0f, 0.0f , 1.0f } {}

// Set light position and color
void PointLight::addLight() {
	if (!glIsEnabled(GL_LIGHT0))
		return;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &color[0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &color[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, &position[0]);
	//The initial spot cutoff is 180, resulting in uniform light distribution.
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
}

// Draw light
void PointLight::draw()
{
	if (!glIsEnabled(GL_LIGHT0))
		return;
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4fv(&color[0]);
	glutSolidSphere(0.2, 100, 100);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

// Switch off the light
void PointLight::disable()
{
	glDisable(GL_LIGHT0);
}

// Switch on the light
void PointLight::enable()
{
	glEnable(GL_LIGHT0);
}

class DirectionalLight
{
public:
	Vec4 color;
	Vec4 position;

	DirectionalLight();
	void addLight();
	void draw();
	void disable();
	void enable();
	~DirectionalLight() = default;
};

DirectionalLight::DirectionalLight() : color(Color::PeriwinklePurple),
	// Directional light,  w component should be 0
	position{ 1.0f, 1.0f, 1.0f , 0.0f }
{
}

void DirectionalLight::addLight() {
	if (!glIsEnabled(GL_LIGHT2))
		return;

	glLightfv(GL_LIGHT2, GL_DIFFUSE, &color[0]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, &color[0]);
	glLightfv(GL_LIGHT2, GL_POSITION, &position[0]);
}

void DirectionalLight::draw()
{
	if (!glIsEnabled(GL_LIGHT2))
		return;

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4fv(&color[0]);
	glutSolidSphere(0.2, 100, 100);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void DirectionalLight::disable()
{
	glDisable(GL_LIGHT2);
}

void DirectionalLight::enable()
{
	glEnable(GL_LIGHT2);
}

class SpotLight {
public:
	Vec4 position{ -1.0f, 2.5f, 0.0f , 1.0f };

	Vec4 target{ 0.1f, 0.0f, 0.0f, 1.0f };
	Vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat cutoff = 30.0f;
	GLfloat exponent = 0.0f;

	SpotLight();
	void addlight();
	void draw();
	void disable();
	void enable();
	~SpotLight() = default;

private:
	void normalize(const GLfloat* vec, GLfloat* output);
	void cross(const GLfloat* vec1, const GLfloat* vec2, GLfloat* output);
	void lookAt(GLfloat* eye, GLfloat* center, GLfloat* up);
};

SpotLight::SpotLight() :position{ -1.0f, 2.5f, 0.0f , 1.0f },
target{ 0.1f, 0.0f, 0.0f, 1.0f },
color{ 1.0f, 1.0f, 1.0f, 1.0f },
cutoff(30.0f),
exponent(0.0f) {}

void SpotLight::addlight() {
	if (!glIsEnabled(GL_LIGHT1))
		return;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, &color[0]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, &color[0]);
	glLightfv(GL_LIGHT1, GL_POSITION, &position[0]);
	GLfloat direction[3] = { target[0] - position[0],
							 target[1] - position[1],
							 target[2] - position[2] };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
}

void SpotLight::draw() {
	if (!glIsEnabled(GL_LIGHT1))
		return;

	glPushMatrix();
	GLfloat up[3] = { 0, 1, 0 };
	lookAt(&position[0], &target[0], up);

	GLfloat ambient[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat diffuse[4] = { 0.01f, 0.01f, 0.01f, 1.0f };
	GLfloat specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat shininess = 32.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glutSolidCone(0.3, 0.6, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 0.1f);
	glutSolidCylinder(0.2, 0.39, 10, 10);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glColor3fv(&color[0]);
	glutSolidSphere(0.2, 100, 100);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void SpotLight::disable()
{
	glDisable(GL_LIGHT1);
}

void SpotLight::enable()
{
	glEnable(GL_LIGHT1);
}

// Vector normalization
void SpotLight::normalize(const GLfloat* vec, GLfloat* output)
{
	GLfloat length = sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	output[0] /= length;
	output[1] /= length;
	output[2] /= length;
}

// Cross product
void SpotLight::cross(const GLfloat* vec1, const GLfloat* vec2, GLfloat* output) {
	output[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	output[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	output[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

// Set view matrix to simulate spotlight
void SpotLight::lookAt(GLfloat* eye, GLfloat* center, GLfloat* up)
{
	GLfloat f[3] = { center[0] - eye[0],
		center[1] - eye[1],
		center[2] - eye[2] };

	normalize(f, f);
	GLfloat u[3];
	normalize(up, u);
	GLfloat s[3];
	cross(f, u, s);
	normalize(s, s);
	cross(s, f, u);
	normalize(u, u);

	GLfloat rotationMatrix[16];
	rotationMatrix[0] = s[0];
	rotationMatrix[1] = s[1];
	rotationMatrix[2] = s[2];
	rotationMatrix[3] = 0;

	rotationMatrix[4] = u[0];
	rotationMatrix[5] = u[1];
	rotationMatrix[6] = u[2];
	rotationMatrix[7] = 0;

	rotationMatrix[8] = -f[0];
	rotationMatrix[9] = -f[1];
	rotationMatrix[10] = -f[2];
	rotationMatrix[11] = 0;

	rotationMatrix[12] = 0;
	rotationMatrix[13] = 0;
	rotationMatrix[14] = 0;
	rotationMatrix[15] = 1;

	glMultMatrixf(rotationMatrix);
}

class Context {
public:
	GLfloat globalAmbient = 0.3f;
	int isDogView = 0;
	Camera camera;
	PointLight pointlight;
	SpotLight spotlight;
	DirectionalLight directionalLight;
};

std::vector<Vec3> colorTable
{
	{ 1.0f, 0.0f, 0.0f },		// Red
	{ 0.0f, 0.0f, 0.0f },		// Black
	{ 0.8f, 0.76f, 0.89f },		// Light purple
	{ 0.0f, 0.0f, 1.0f }		// Blue
};

float randomFloat(float low, float high)
{
	return low + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

Vec3 getColor(int32_t index)
{
	if (index == 4 || index == 5)
	{
		return colorTable[1];
	}
	else if (index == 6)
	{
		return colorTable[2];
	}
	else if ((index == 7) || (index >= 14 && index <= 25))
	{
		return colorTable[3];
	}

	return colorTable[0];
}

class Texture
{
public:
	enum class EType
	{
		Texture2D,
	};

	Texture();

	void ReadImage(const char path[256]);

	void use() const;

	int32_t getWidth() const { return width; }
	int32_t getHeight() const { return height; }

private:
	uint32_t id = 0;
	EType type = EType::Texture2D;

	int32_t width = 0;
	int32_t height = 0;

	uint8_t* data = nullptr;
};

Texture::Texture()
{
}

// Load image and bind textures
void Texture::ReadImage(const char path[256]) {
	GLubyte* pixeldata;
	FILE* pfile;
	fopen_s(&pfile, path, "rb");
	if (pfile == 0) exit(0);
	fseek(pfile, 0x0012, SEEK_SET);

	GLint imageWidth;
	GLint imageHeight;
	GLint pixelLength;

	fread(&imageWidth, sizeof(imageWidth), 1, pfile);
	fread(&imageHeight, sizeof(imageHeight), 1, pfile);
	pixelLength = imageWidth * 3;
	while (pixelLength % 4 != 0)pixelLength++;
	pixelLength *= imageHeight;
	pixeldata = (GLubyte*)malloc(pixelLength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixelLength, 1, pfile);
	std::vector<GLubyte*> p;
	p.push_back(pixeldata);
	fclose(pfile);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Create ith textures
	glGenTextures(1, &id);
	// Bind coresponding textures to textures ID
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
	// GL_MODULATE: combine the textures with material color; GL_REPEAT: Repeat wrapping; GL_LINEAR: Linear interpolation
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Texture::use() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

// Single point of access to all rendered objects
Context gContext;

Plane plane;
Texture skyTexture;
Texture seaTexture;

// Keyboard interaction
void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f':
	case 'F':
		glutFullScreenToggle();
		break;
	case '1':
		setCameraView(ECameraView::Top);
		break;
	case '2':
		setCameraView(ECameraView::Front);
		break;
	case '3':
		setCameraView(ECameraView::Side);
		break;
	case ' ':
		shoot();
		break;
	case 'e':
	case 'E':
		glutExit();
		break;
	case GLUT_KEY_ESCAPE:
		glutExit();
		break;
	default:
		break;
	}
}

// Special keys
void keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_PAGE_UP:
		cameraSpeed += 0.05f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		cameraSpeed -= 0.05f;
		if (cameraSpeed < 0.1f)
		{
			cameraSpeed = 0.1f;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
}

// Mouse-based rotation
void mouseMotion(int x, int y)
{
	auto currentMousePosition = Vec2(x, y);

	auto rate = static_cast<float>(currentMousePosition.x) / windowWidth;

	rate = rate * 2.0f - 1.0f;

	plane.rotation.y = -rate * 180.0f - 90.0f;

	plane.rotation.z = -rate * 30.0f;

	cameraRotation = -rate * 180.0f;
}

void reshape(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, windowWidth, windowHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0);

	glutPostRedisplay();
}

// Draw co-ordinate axes
void drawAxis()
{
	glDisable(GL_LIGHTING);

	glLineWidth(axisLineWidth);

	// X-Axis
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(axisLength, 0.0f, 0.0f);
	glEnd();

	// Y-Axis
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, axisLength, 0.0f);
	glEnd();

	// Z-Axis
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, axisLength);
	glEnd();

	glLineWidth(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glutSolidSphere(0.01f, 32, 32);

	glEnable(GL_LIGHTING);
}

// Draw sky
void drawSkybox()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &Color::White[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &Color::White[0]);

	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_FRONT); // See from inside to outside

	skyTexture.use();

	// Create a new quadric object for rendering the skybox
	GLUquadric* quadObject = gluNewQuadric();

	gluQuadricTexture(quadObject, true); // Generate textures co-ordinates

	glPushMatrix();

	const float radius = SkyboxRadius;
	float height = static_cast<float>(2.0f * M_PI * radius) / (static_cast<float>(skyTexture.getWidth()) / skyTexture.getHeight());

	glTranslatef(0.0f, height, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	gluCylinder(quadObject, radius, radius, height, 64, 64);

	glPopMatrix();

	glCullFace(GL_BACK);
	glDisable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &Color::Black[0]);
}

// Draw sea
void drawSea()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &Color::White[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &Color::White[0]);

	// Enable fog effect if the toggleFog flag is true
	if (toggleFog)
	{
		glEnable(GL_FOG);

		float fogDensity = 0.01f;

		glFogi(GL_FOG_MODE, GL_EXP2);

		glFogfv(GL_FOG_COLOR, &Color::Pink[0]);

		glFogf(GL_FOG_DENSITY, fogDensity);

		glHint(GL_FOG_HINT, GL_NICEST);
	}

	glEnable(GL_TEXTURE_2D);

	seaTexture.use();

	GLUquadric* quadObject = gluNewQuadric();

	gluQuadricTexture(quadObject, true);

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	gluDisk(quadObject, 0.0f, SkyboxRadius, 64, 64);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	if (toggleFog)
	{
		glDisable(GL_FOG);
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &Color::Black[0]);
}

// Draw the land base
void drawLand()
{
	// Disables face culling to render both front and back faces
	glDisable(GL_CULL_FACE);

	if (toggleLandTexture)
	{
		glEnable(GL_TEXTURE_2D);
	}

	GLfloat landColor[]{ 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, landColor);

	static float r = 0;
	r += 0.5;
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	// Translates terrain to center it in the rendering window
	glTranslated(-(onumX * stepX) / 2, -(onumY * stepY) / 2, 0);

	float texcoordStepX = 1.0f / numX;
	float texcoordStepY = 1.0f / numY;

	// Draw the terrain using triangles
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < (numY - 2); i++) {
		for (int j = 0; j < (numX - 2); j++) {

			int index = (i * numX + j);
			glTexCoord2f((j)*texcoordStepX, (i + 1) * texcoordStepY);
			glNormal3f(vertices.at(index).nX, vertices.at(index).nY, vertices.at(index).nZ);
			glVertex3f(vertices.at(index).x, vertices.at(index).y, vertices.at(index).z);

			index = ((i + 1) * numX + j);
			glTexCoord2f((j + 1) * texcoordStepX, (i + 1) * texcoordStepY);
			glNormal3f(vertices.at(index).nX, vertices.at(index).nY, vertices.at(index).nZ);
			glVertex3f(vertices.at(index).x, vertices.at(index).y, vertices.at(index).z);

			index = (i * numX + (j + 1));
			glTexCoord2f(j * texcoordStepX, i * texcoordStepY);
			glNormal3f(vertices.at(index).nX, vertices.at(index).nY, vertices.at(index).nZ);
			glVertex3f(vertices.at(index).x, vertices.at(index).y, vertices.at(index).z);

			index = (i * numX + (j + 1));
			glTexCoord2f(j * texcoordStepX, i * texcoordStepY);
			glNormal3f(vertices.at(index).nX, vertices.at(index).nY, vertices.at(index).nZ);
			glVertex3f(vertices.at(index).x, vertices.at(index).y, vertices.at(index).z);

			index = ((i + 1) * numX + (j + 1));
			glTexCoord2f(j * texcoordStepX, (i + 1) * texcoordStepY);
			glNormal3f(vertices.at(index).nX, vertices.at(index).nY, vertices.at(index).nZ);
			glVertex3f(vertices.at(index).x, vertices.at(index).y, vertices.at(index).z);

			index = ((i + 1) * numX + j);
			glTexCoord2f((j + 1) * texcoordStepX, (i + 1) * texcoordStepY);
			glNormal3f(vertices.at(index).nX, vertices.at(index).nY, vertices.at(index).nZ);
			glVertex3f(vertices.at(index).x, vertices.at(index).y, vertices.at(index).z);

		}
	}
	glEnd();
	glPopMatrix();

	if (toggleLandTexture)
	{
		glDisable(GL_TEXTURE_2D);
	}

	glEnable(GL_CULL_FACE);
}

// Draw grids on the ground plane for reference
void drawGrid()
{
	float hight = 0.001f;

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &Color::White[0]);

	glLineWidth(2.0);

	glBegin(GL_LINE_LOOP);

	glVertex3f(-20.0f, 0.0f, -20.0f);
	glVertex3f(20.0f, 0.0f, -20.0f);
	glVertex3f(20.0f, 0.0f, 20.0f);
	glVertex3f(-20.0f, 0.0f, 20.0f);

	glEnd();

	for (int i = 0; i <= 40; )
	{
		glBegin(GL_LINES);

		glVertex3f(-20.0f, 0.0f, -20.0f + i);
		glVertex3f(20.0f, 0.0f, -20.0f + i);

		glVertex3f(-20.0f + i, 0.0f, -20.0f);
		glVertex3f(-20.0f + i, 0.0f, 20.0f);

		glEnd();

		i += 2;
	}
}

// Spherical bullets
void drawBullets()
{
	for (const auto& bullet : bullets)
	{
		glPushMatrix();
		glTranslated(bullet.position.x, bullet.position.y, bullet.position.z);
		glutSolidSphere(bullet.radius, 64, 64);
		glPopMatrix();
	}
}

// Spherical enemies
void drawEnemies()
{
	for (const auto& enemy : enemies)
	{
		glPushMatrix();
		glTranslated(enemy.position.x, enemy.position.y, enemy.position.z);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &enemy.color[0]);
		glutSolidSphere(enemy.radius, 64, 64);
		glPopMatrix();
	}
}

// Lighting effects
void drawLights()
{
	glPushMatrix();
	glTranslatef(gContext.pointlight.position[0], gContext.pointlight.position[1], gContext.pointlight.position[2]);
	gContext.pointlight.addLight();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(gContext.spotlight.position[0], gContext.spotlight.position[1], gContext.spotlight.position[2]);
	gContext.spotlight.addlight();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(gContext.pointlight.position[0], gContext.pointlight.position[1], gContext.pointlight.position[2]);
	gContext.pointlight.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(gContext.spotlight.position[0], gContext.spotlight.position[1], gContext.spotlight.position[2]);
	gContext.spotlight.draw();
	glPopMatrix();

	gContext.directionalLight.addLight();
}

// Draw aircraft
void drawPlane()
{	
	glPushMatrix();
	glTranslatef(plane.position.x, plane.position.y, plane.position.z);

	glRotatef(cameraRotation - 90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(plane.rotation.z, 1.0f, 0.0f, 0.0f);

	glTranslatef(planeOffset.x, planeOffset.y, planeOffset.z);

	// Body
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCylinder(0.05f, 1.0f, 32, 32);
	glPopMatrix();

	// Wings
	glPushMatrix();
	glTranslatef(0.3f, 0.0f, 0.0);
	glScalef(0.25f, 0.025f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Tails
	glPushMatrix();
	glTranslatef(0.85f, 0.0f, 0.0);
	glScalef(0.125f, 0.0125f, 0.25f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.85f, 0.0f, 0.0);
	glutSolidCone(0.085, 0.1, 50, 50);
	glPopMatrix();

	// Head
	glPushMatrix();
	glTranslatef(0.1f, -0.0005f, 0.0);
	glRotatef(90.0f, 90.0f, 90.0f, 90.0f);
	glScalef(0.15f, 0.15f, 0.2f);
	glutSolidCone(0.6, 0.6, 50, 50);
	glPopMatrix();

	// Propellers
	glPushMatrix();
	glTranslatef(0.1f, -0.000000000005f, -0.27);
	glRotatef(90.0f, 90.0f, 90.0f, 0.0f);
	glScalef(0.15f, 0.15f, 0.1f);
	glutSolidCone(0.6, 0.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, -0.000000000005f, 0.27f);
	glRotatef(90.0f, 90.0f, 90.0f, 0.0f);
	glScalef(0.15f, 0.15f, 0.1f);
	glutSolidCone(0.6, 0.6, 50, 50);
	glPopMatrix();

	glPopMatrix();
}

// Model 3D scene
void drawScene() {
	drawLights();
	drawAxis();

	if (toggleGrid)
	{
		glPushMatrix();
		glTranslatef(0.0f, 5.0f, 0.0f);
		drawGrid();
		glPopMatrix();
	}
	else
	{
		drawSkybox();
		drawSea();
	}

	drawPlane();

	drawBullets();

	drawEnemies();

	// Reset the random number generator with a new seed based on the current time
	srand(time(nullptr));

	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	drawLand();
	glPopMatrix();

	srand(time(nullptr));

	glPushMatrix();
	glTranslatef(100.0f, 0.5f, 100.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	drawLand();
	glPopMatrix();

	srand(time(nullptr));

	glPushMatrix();
	glTranslatef(-100.0f, 0.5f, 100.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	drawLand();
	glPopMatrix();
}

// Produce bullets
void shoot()
{
	Bullet bulletLeft;

	auto position = plane.position - plane.right * 0.5f + plane.forward * 3.0f;

	bulletLeft.position = position;
	bulletLeft.position.y -= 0.3f;
	bulletLeft.direction = plane.forward;

	bullets.emplace_back(bulletLeft); // Add bullet to the collection of bullets

	Bullet bulletRight;

	position = plane.position + plane.right * 0.5f + plane.forward * 3.0f;

	bulletRight.position = position;
	bulletRight.position.y -= 0.3f;
	bulletRight.direction = plane.forward;

	bullets.emplace_back(bulletRight);
}

// Produce enemies with random positions, colors and sizes
void generateEnemies()
{
	for (auto i = 0; i < 100; i++)
	{
		Enemy enemy;
		enemy.position = { randomFloat(-100, 100.0f), randomFloat(5.0f, 10.0f), randomFloat(-100.0f, 100.0f) };
		enemy.color = { randomFloat(0.1f, 1.0f), randomFloat(0.2f, 1.0f), randomFloat(0.3f, 1.0f), 1.0f };
		enemy.radius = randomFloat(0.5f, 1.0f);
		enemies.emplace_back(enemy); // Add enemy to the collection of enemies
	}
}

void setCameraView(ECameraView cameraView)
{
	switch (cameraView)
	{
	case ECameraView::Top:
		gContext.camera.position.x = gContext.camera.position.x;
		gContext.camera.position.y = 1.0f;
		gContext.camera.position.z = gContext.camera.position.z;
		break;
	case ECameraView::Front:
		gContext.camera.position.x = 1.0f;
		gContext.camera.position.y = 0.0f;
		gContext.camera.position.z = 0.0f;
		break;
	case ECameraView::Side:
		gContext.camera.position.x = 0.0f;
		gContext.camera.position.y = 0.0f;
		gContext.camera.position.z = 1.0f;
		break;
	default:
		break;
	}
}

// Interaction instructions
void printKeyControl()
{
	printf("f - Toggle full screen.\n");
	printf("page up - Speed up.\n");
	printf("page down - Speed down.\n");
	printf("space bar - Shoot bullet.\n");
	printf("e - Exit program.\n");
}

// Update the view matrix based on the camera and plane's orientation
void updateViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Calculate new forward direction based on camera rotation
	auto rx = std::cosf(toRadians(cameraRotation)) * Forward.x + std::sinf(toRadians(cameraRotation)) * Forward.z;
	auto rz = -std::sinf(toRadians(cameraRotation)) * Forward.x + std::cosf(toRadians(cameraRotation)) * Forward.z;

	plane.forward.x = rx;
	plane.forward.z = rz;

	// Calculate the plane's forward and right vectors
	auto forward = Vec3(plane.forward.x, plane.forward.y, plane.forward.z);
	auto right = cross(forward, Vec3(0.0f, 1.0f, 0.0f));

	plane.right.x = right.x;
	plane.right.y = right.y;
	plane.right.z = right.z;

	// Update target
	gContext.camera.target = gContext.camera.position + plane.forward;

	plane.position = gContext.camera.position;

	plane.position.y -= 0.3f;

	// Set the view
	gluLookAt(gContext.camera.position.x, gContext.camera.position.y, gContext.camera.position.z,
		gContext.camera.target.x, gContext.camera.target.y, gContext.camera.target.z, 0, 1, 0);
}

// Special input processing and adjust camera and plane positions according to UP arrow or DOWN arrow
void processInput()
{
	if (GetAsyncKeyState(VK_UP))
	{
		gContext.camera.position.y += cameraSpeed;
		gContext.camera.target.y += cameraSpeed;

		plane.moveUP();
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		gContext.camera.position.y -= cameraSpeed;
		gContext.camera.target.y -= cameraSpeed;

		plane.moveDown();
	}
}

// Update camera positions
void updateCamera()
{
	gContext.camera.position += plane.forward * cameraSpeed;
}

void updatePlane()
{
	plane.moveForward();
}

// Update bullets states
void updateBullets()
{
	for (auto i = 0; i < bullets.size(); i++)
	{
		bullets[i].update();

		auto planePosition = Vec3(plane.position.x, plane.position.y, plane.position.z);

		// If the bullet is far enough from the plane, remove it from the vector
		auto distance = length(bullets[i].position - planePosition); 

		if (distance > 30.0f)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
	}
}

// Update enemies states
void updateEnemies()
{
	for (auto i = 0; i < enemies.size(); i++)
	{
		// Check each bullet to see if it hits an enemy
		for (auto j = 0; j < bullets.size(); j++)
		{
			auto enemy = enemies[i];
			auto bullet = bullets[j];

			// If a bullet is within the radius of an enemy (indicating a hit), remove both from their vectors
			if (length(enemy.position - bullet.position) < (enemy.radius + bullet.radius))
			{
				enemies.erase(enemies.begin() + i); // Remove enemies
				bullets.erase(bullets.begin() + j); // Remove bullets

				return;
			}
		}
	}
}

void update()
{
	processInput();

	updateCamera();

	updateBullets();

	updateEnemies();

	updatePlane();

	glutPostRedisplay();
}

// Render the project
void display() {
	glClearColor(Color::PeriwinklePurple.x, Color::PeriwinklePurple.y, Color::PeriwinklePurple.z, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat globalAmbientVec[4] = { 0.2f, 0.2f, 0.2f, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientVec);

	updateViewMatrix();
	drawScene();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Flight Simulator");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	glutIdleFunc(update);
	glutPassiveMotionFunc(mouseMotion);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gContext.pointlight.enable();
	gContext.spotlight.enable();
	gContext.directionalLight.enable();

	plane.position = { gContext.camera.position.x, 0.0f, gContext.camera.position.z - 11.0f, 1.0f };

	skyTexture.ReadImage("Textures/sky.bmp");
	seaTexture.ReadImage("Textures/sea.bmp");

	generateEnemies();

	printKeyControl();

	glutMainLoop();

	return 0;
}