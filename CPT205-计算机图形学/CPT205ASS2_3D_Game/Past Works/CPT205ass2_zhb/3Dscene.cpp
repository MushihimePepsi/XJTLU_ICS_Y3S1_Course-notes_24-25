// Stellarium Project
// Author: Hongbin Zhang
#define FREEGLUT_STATIC
#include "GL/freeglut.h" // OpenGL library
// C/C++ Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
// Hide the terminal windows
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace std;
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#define root_2 1.414
#define root_3 1.732
#define PI 3.14
#define SunEarthAngle 90 - 66.34
const int GL_MULTISAMPLE = 0x809D; // MSAA

// Parameters for view
GLint winWidth = 700, winHeight = 700; // Initial display window size
GLfloat fltFOV = 90.0; // Field of view
GLfloat aspect = winWidth / winHeight; 
GLfloat znear = 0.0;
GLfloat zfar = 10000;

GLfloat world_radius = 300; // Radius of sphere
GLfloat view_radius = world_radius / cos(fltFOV / 2); // Radius of longger line of FOV
GLfloat length = sqrt(pow(view_radius, 2) - pow(world_radius, 2)); // Length between vertex and look at point
GLfloat camera_x = 0, camera_y = 0, camera_z = 0; // Viewing co-ordinate origin // Point to -z direction!!!
GLfloat lookat_x = world_radius, lookat_y = 0, lookat_z = 0; // Look-at point
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector

// Initial states for all objects
GLfloat eye_rotation = 0; // Rotate value of FOV
GLfloat eye_updown = 0; // Rotate value of FOV (Up and Down)
GLfloat eye_rotate_speed = 5; 
GLfloat move_speed = 1; // Move speed
GLfloat wall_height = world_radius * root_2 / 3; // The height of 8 walls

GLint CultureState = 0; // 0 --> Western culture, 1 --> Chinese culture
GLint SkyState = 0; // 0 --> With atmosphere, 1 --> No atmosphere, 2 --> With constellation, 3--> With onstellation patterns
GLint TimeState = 0; // 0 --> day, 1--> night (Make wall_height = -wall_height)
GLint Rotatestep = 0; // Rotation step when time change or receive rotate order
GLfloat planet_rotation = 0.0; // If night --> fast turn to 180, if rotate --> slow increase
GLfloat leg_arm_rotation = 0; // Rotate the arms and legs while moving
GLfloat leg_arm_rotation_speed = 5; // Rotation speed of the arms and legs while moving

GLboolean rotateFlag = FALSE; // Rise when receive rotate order
GLboolean fogFlag = FALSE; // Rise when active fog effect
GLboolean finderFlag = TRUE; // Rise when active star finder
GLboolean infoFlag = TRUE; // Rise when showing infomation
GLboolean suninfoFlag = FALSE; // Rise when look at sun
GLboolean mooninfoFlag = FALSE; // Rise when look at moon
GLboolean landFlag = TRUE; // Rise when showing the land/human/lamps/roads
GLboolean restrFlag = TRUE; // Rise when active move restriction
GLboolean humanFlag = TRUE; // Rise when show human

GLboolean LLGFlag = FALSE; // Rise when latitude and longitude grid is drawn
GLboolean EQGFlag = FALSE; // Rise when equatorial grid is drawn
GLboolean ECGFlag = FALSE; // Rise when ecliptic grid is drawn

// Textures
GLuint textures[114]; // Array to save all the textures
GLubyte* earth_data;
GLubyte* grass_data;
GLubyte* sun_data;
GLubyte* moon_data;
GLubyte* BG_data[8];
GLubyte* sky_balls_data[10];
GLubyte* road_data;

struct point 
{
	GLfloat x, y, z;
};
//point shaft = { sin(SunEarthAngle), cos(SunEarthAngle), 0}; // Autorotation shaft
point shaft = { 1, 0, 0}; // Autorotation shaft
point solar = { -27.4, 550.6 ,-367.4 }; // Solar's coordinates
point moon = {230.0, 500.0 ,-200.0 }; // Moon's coordinates


// Reshape the viewport
void myReshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}


// Animation
void myIdleFunc(void)
{
	planet_rotation += Rotatestep;
	if (planet_rotation >= 180 && rotateFlag == FALSE)
		
	{
		Rotatestep = 0; // If turn to night, just rotate 180 degree
		planet_rotation = 180;
	}
	if (planet_rotation < 0 && rotateFlag == FALSE)
	{
		Rotatestep = 0; // If turn to night, just rotate 180 degree
		planet_rotation = 0;
	}
	glutPostRedisplay();	// Redisplay
}


// Restrict areas that can be moved to
bool move_restriction(GLfloat pos_x, GLfloat pos_z)
{
	// To build an air wall
	if (pos_z > world_radius / 2 || pos_z < - world_radius / 2)
		return false;
	if (pos_x > world_radius / 2 || pos_x < - world_radius / 2)
		return false;
	return true;
}


// Keyboard input
void myKeyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') exit(0); // Quit

	// Move
	if (key == 'w' || key == 'W')	 // Look up and look down
		eye_updown += eye_rotate_speed;
	if (key == 's' || key == 'S')
		eye_updown -= eye_rotate_speed;
	if (key == 'a' || key == 'A')	// Rotate the eye direction
		eye_rotation -= eye_rotate_speed; // Turn left --> z- x+     OpenGL follows the RIGHT HAND coordinate.
	if (key == 'd' || key == 'D')
		eye_rotation += eye_rotate_speed; // Turn right --> z+ x-
	if (eye_updown >= 90) eye_updown = 90;
	if (eye_updown <= -90) eye_updown = -90;
	lookat_x = world_radius * cos(eye_rotation / 180 * PI) * cos(eye_updown / 180 * PI) + camera_x; // To make the view stay in a ball
	lookat_z = world_radius * sin((eye_rotation) / 180 * PI) * cos(eye_updown / 180 * PI) + camera_z; // To make the view stay in a ball
	lookat_y = world_radius * sin(eye_updown / 180 * PI) + camera_y; // To make the view stay in a ball

	// Back to initial location
	if (key == 'b' || key == 'B')
	{
		camera_x = 0, camera_y = 0, camera_z = 0;
		lookat_x = world_radius, lookat_y = 0, lookat_z = 0;
		eye_rotation = 0, fltFOV = 90.0; eye_updown = 0;
		leg_arm_rotation = 0;
	}

	// Change states
	if (key == '-' || key == '_') // Slow down rotation or time flow reverse
	{
		rotateFlag = TRUE;
		Rotatestep -= 1;
	}
	if (key == '=' || key == '+') // Begin rotation (begin time flow)
	{
		rotateFlag = TRUE;
		Rotatestep += 1;
	}

	if (key == 'z' || key == 'Z') // Show/hide longitude and lagitude gird
	{
		if (!LLGFlag) LLGFlag = TRUE;
		else LLGFlag = FALSE;
	}
	if (key == 'x' || key == 'X') // Show/hide equatorial gird
	{
		if (!EQGFlag) EQGFlag = TRUE;
		else EQGFlag = FALSE;
	}
	if (key == 'c' || key == 'C') // Show/hide ecliptic grid
	{
		if (!ECGFlag) ECGFlag = TRUE;
		else ECGFlag = FALSE;
	}
	if (key == 'f' || key == 'F') // Show/hide fog
	{
		if (!fogFlag) fogFlag = TRUE;
		else fogFlag = FALSE;
	}
	if (key == 'r' || key == 'R') // Show/hide star finder
	{
		if (!finderFlag) finderFlag = TRUE;
		else finderFlag = FALSE;
	}
	if (key == 'h' || key == 'H') // Show/hide human
	{
		if (!humanFlag) humanFlag = TRUE;
		else humanFlag = FALSE;
	}
	if (key == 'i' || key == 'I') // Show/hide information
	{
		if (!infoFlag) infoFlag = TRUE;
		else
		{
			infoFlag = FALSE; 
			mooninfoFlag = FALSE; 
			suninfoFlag = FALSE;
		}
	}
	if (key == 'l' || key == 'L') // Show/hide land elements
	{
		if (!landFlag) landFlag = TRUE;
		else landFlag = FALSE;
	}
	if (key == 'o' || key == 'O') // See sun
	{
		lookat_x = solar.x; lookat_y = solar.y; lookat_z = solar.z;
		infoFlag = TRUE;
		suninfoFlag = TRUE;
		mooninfoFlag = FALSE;
	}
	if (key == 'p' || key == 'P') // See moon
	{
		lookat_x = moon.x; lookat_y = moon.y; lookat_z = moon.z;
		infoFlag = TRUE;
		suninfoFlag = FALSE;
		mooninfoFlag = TRUE;
	}
	if (key == 'g' || key == 'G') // Active/disable move restriction
	{
		if (!restrFlag) restrFlag = TRUE;
		else restrFlag = FALSE;
	}
}


// Keyboard interaction (special keys)
void specialKeyboardKeys(int key, int xx, int yy) 
{
	// Move the position of camera and lookat point, to simulate walking
	GLfloat ori_Lookat_x = lookat_x, ori_Lookat_z = lookat_z;	// Record the original position before moving
	GLfloat ori_Cam_x = camera_x, ori_Cam_z = camera_z;

	switch (key) 
	{
		case GLUT_KEY_LEFT:	// Move left //z- x+
			camera_x += move_speed * sin(eye_rotation / 180 * PI);
			camera_z -= move_speed * cos(eye_rotation / 180 * PI);
			lookat_x += move_speed * sin(eye_rotation / 180 * PI);
			lookat_z -= move_speed * cos(eye_rotation / 180 * PI);
			leg_arm_rotation += leg_arm_rotation_speed;
			if (leg_arm_rotation >= 90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			if (leg_arm_rotation <= -90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			break;
		case GLUT_KEY_RIGHT: // Move right
			camera_x -= move_speed * sin(eye_rotation / 180 * PI);
			camera_z += move_speed * cos(eye_rotation / 180 * PI);
			lookat_x -= move_speed * sin(eye_rotation / 180 * PI);
			lookat_z += move_speed * cos(eye_rotation / 180 * PI);
			leg_arm_rotation += leg_arm_rotation_speed;
			if (leg_arm_rotation >= 90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			if (leg_arm_rotation <= -90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			break;
		case GLUT_KEY_DOWN:	// Move back
			camera_x -= move_speed * cos(eye_rotation / 180 * PI);
			camera_z -= move_speed * sin(eye_rotation / 180 * PI);
			lookat_x -= move_speed * cos(eye_rotation / 180 * PI);
			lookat_z -= move_speed * sin(eye_rotation / 180 * PI);
			leg_arm_rotation += leg_arm_rotation_speed;
			if (leg_arm_rotation >= 90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			if (leg_arm_rotation <= -90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			break;
		case GLUT_KEY_UP: // Move forward
			camera_x += move_speed * cos(eye_rotation / 180 * PI);
			camera_z += move_speed * sin(eye_rotation / 180 * PI);
			lookat_x += move_speed * cos(eye_rotation / 180 * PI);
			lookat_z += move_speed * sin(eye_rotation / 180 * PI);
			leg_arm_rotation += leg_arm_rotation_speed;
			if (leg_arm_rotation >= 90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			if (leg_arm_rotation <= -90) leg_arm_rotation_speed = -leg_arm_rotation_speed;
			break;

		// Change states
		case GLUT_KEY_F1: // F1 C = 0, S = 0 --> Inital state
		{
			CultureState = 0;
			SkyState = 0;
			planet_rotation = 0; // Reset the rotation
			Rotatestep = 0;
			TimeState = 0;
			break;
		}
		case GLUT_KEY_F2: // F2 C = 1 --> Chinese culture
		{
			CultureState = 1; 
			planet_rotation = 0; // Reset the rotation
			Rotatestep = 0;
			TimeState = 0;
			break;
		}
		case GLUT_KEY_F3: // F3 Close the light --> night
		{
			if (TimeState == 1) 
			{
				TimeState = 0;
				rotateFlag = FALSE;
				planet_rotation = 180;
				Rotatestep = -5 ; // A larger value
				break;
			}
			else
			{
				TimeState = 1;
				rotateFlag = FALSE;
				planet_rotation = 0;
				Rotatestep = 5;// A larger value
				break;
			}
		}
		case GLUT_KEY_F4: // F4 C = 0, S = 1 --> No atmosphere
		{
			CultureState = 0;
			SkyState = 1;
			planet_rotation = 0; // Reset the rotation
			Rotatestep = 0;
			TimeState = 0;
			break;
		}
		case GLUT_KEY_F5: // F5 C = 0, S = 2 --> With constellation
		{
			CultureState = 0;
			SkyState = 2;
			planet_rotation = 0; // Reset the rotation
			Rotatestep = 0;
			TimeState = 0;
			break;
		}
		case GLUT_KEY_F6: // F6 C = 0, S = 3 --> With pattern
		{
			CultureState = 0;
			SkyState = 3;
			planet_rotation = 0; // Reset the rotation
			Rotatestep = 0;
			TimeState = 0;
			break;
		}
	}

	if (restrFlag)
	{
		// Add move restriction
		if (!move_restriction(camera_x, camera_z))
		{	// If can not, step back to the position before move
			lookat_x = ori_Lookat_x, lookat_z = ori_Lookat_z;
			camera_x = ori_Cam_x, camera_z = ori_Cam_z;
		}
	}
}


// Mouse interaction
void mouseInput(int button, int state, int x, int y) 
{	
	GLfloat delta = fltFOV * 0.15;
	if (state == GLUT_UP && button == GLUT_WHEEL_UP) 
	{	// Zoom in by glut wheel up
		fltFOV -= delta;
		if (fltFOV <= 0.002) fltFOV = 0.002;
	}
	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN) 
	{	// Zoom out by glut wheel down
		fltFOV += delta;
		if (fltFOV >= 170) fltFOV = 170;
	}
}


// Load a image as a texture (BGR)
GLubyte* loadImg(string filename) 
{
	GLint image_width;
	GLint image_height;
	GLint pixel_len;
	GLubyte* data;
	// Read in and open an image file
	FILE* pfile = NULL;
	fopen_s(&pfile, filename.c_str(), "rb"); // Read the image in binary mode
	if (pfile == 0) exit(0);	// Fail to read
	fseek(pfile, 0x0012, SEEK_SET); // Move pointer to 0x0012 (bmp.width)
	fread(&image_width, sizeof(image_width), 1, pfile);  // Read 4 byte(GLint)(read 1 element) Now point to bmp.height
	fread(&image_height, sizeof(image_height), 1, pfile); 
	pixel_len = image_width * 3;
	while (pixel_len % 4 != 0)
		pixel_len++;
	pixel_len *= image_height;		// Total size to save the image
	data = (GLubyte*)malloc(pixel_len);	// Memory allocation
	if (data == 0)
		exit(0);	// Fail to read
	fseek(pfile, 54, SEEK_SET);
	fread(data, pixel_len, 1, pfile);
	fclose(pfile);
	for (int i = 0; i < pixel_len / 3; i++) 
	{	// The original order of color information from the file is BGR, change the order to RGB
			GLubyte x = data[i * 3];
			GLubyte z = data[i * 3 + 2];
			data[i * 3 + 2] = x;
			data[i * 3] = z;
	}
	return data;	// Save the texture information in data and return
}


// Load a image as a texture(BGRA)
GLubyte* loadImgA(string filename)
{
	GLint image_width;
	GLint image_height;
	GLint pixel_len;
	GLubyte* data;
	// Read in and open an image file
	FILE* pfile = NULL;
	fopen_s(&pfile, filename.c_str(), "rb"); // Read the image in binary mode
	if (pfile == 0) exit(0);	// Fail to read
	fseek(pfile, 0x0012, SEEK_SET); // Move pointer to 0x0012 (bmp.width)
	fread(&image_width, sizeof(image_width), 1, pfile);  // Read 4 byte(GLint)(read 1 element) Now point to bmp.height
	fread(&image_height, sizeof(image_height), 1, pfile);
	fseek(pfile, 0x0022, SEEK_SET); // Move pointer to 0x0022 (bmp.biSizeImage)
	fread(&pixel_len, sizeof(pixel_len), 1, pfile);	// Total size to save the image
	data = (GLubyte*)malloc(pixel_len);	// Memory allocation
	if (data == 0)
		exit(0);	// Fail to read
	fseek(pfile, 0x0036, SEEK_SET);
	fread(data, pixel_len, 1, pfile);
	fclose(pfile);
	 // File has 32 bits with BGRA , convert to RGBA
	for (int i = 0; i < pixel_len / 4; i++)
	{	
		GLubyte x = data[i * 4];
		GLubyte z = data[i * 4 + 2];
		data[i * 4 + 2] = x;
		data[i * 4] = z;
	}
	return data;	// Save the texture information in data and return
}


// ParaleelLight --> Simulate sun light, adjust overall brightness
void parallelLight() 
{
	// Define propertities of the light
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat lightDirection[] = { 1.0, 1.0, 1.0, 0.0 };
	// Set propertities
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);	
}


// Spot lights --> Simulate the sun light and moon light, flash light
void spotLight() 
{
	GLfloat sun_light_position[] = { solar.x, solar.y, solar.z, 1.0 }, sun_light_direction[] = { -solar.x, -solar.y, -solar.z };
	GLfloat moon_light_position[] = { moon.x, moon.y, moon.z, 1.0 }, moon_light_direction[] = { -moon.x, -moon.y, -moon.z };
	GLfloat light_ambient[] = { 1.0, 1.0, 0.1, 1.0 }, light_diffuse[] = { 1.0, 1.0, 0.4, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glPushMatrix();
	if (TimeState == 0) // Day time
	{
		glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		// Set propertities
		glLightfv(GL_LIGHT1, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
		// Special propertities of spot light
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, sun_light_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.7);	// More intense spotlight
	}
	else
	{
		glRotatef(planet_rotation + 180, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glEnable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
		// Set propertities
		glLightfv(GL_LIGHT2, GL_POSITION, moon_light_position);
		glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
		// Special propertities of spot light
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, moon_light_direction);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.005);	// More soft spotlight
	}
	glPopMatrix();
}


void setLight(void)  
{
	// Global ambient light
	GLfloat Light_day[] = { 0.7 , 0.7 , 0.6 , 0.5 };
	GLfloat Light_night[] = { 0.3 , 0.3, 0.4 , 0.5 };
	if (TimeState == 0) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_day);
	else glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_night);
	spotLight();
	parallelLight();
}


void myInit(void)
{	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, aspect, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, lookat_x, lookat_y, lookat_z, Vx, Vy, Vz);

	glEnable(GL_DEPTH_TEST); // Enable depth
	glDepthFunc(GL_LEQUAL); // If depth less or equal to the reference value, then pass
	glEnable(GL_LIGHTING);	// Enable lighting
	glDepthRange(znear,zfar);

	glEnable(GL_TEXTURE_2D); // Enable texture
	glEnable(GL_COLOR_MATERIAL); // Enable material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	
	// Load textures
	string path = "textures/";
	earth_data = loadImg(path + "earth.bmp"); // .bmp is BGR not BGRA
	grass_data = loadImg(path + "grass1.bmp");
	sun_data = loadImg(path + "sun.bmp");
	moon_data = loadImg(path + "moon.bmp");
	string BG = "textures/guereins";
	for (int i = 0; i < 8; i++)
		BG_data[i] = loadImgA(BG + to_string(i + 1) + ".bmp"); // .bmp is BGRA
	string SkyBall = "textures/SkyBall";
	for (int i = 0; i < 10; i++)
		sky_balls_data[i] = loadImg(SkyBall + to_string(i + 1) + ".bmp"); // .bmp is BGRA
	road_data = loadImg(path + "rock.bmp");

	// Bind and save textures
	glShadeModel(GL_SMOOTH); // Select flat or smooth shading
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Specify a two-dimensional texture image
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Set texture environment parameters
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Defining perspective correction hint. Choose the most correct or highest quality option
	glGenTextures(114, textures); // Generate textures' index and fill them into an array

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 4096, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, earth_data); // Target, level, components(3 for RGB), w, h, border, format, type, texels
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	// Both s and t direction apply 'GL_CLAMP'
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Magnification and Minification use Nearest Interpolation
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_data); // Target, level, components(3 for RGB), w, h, border, format, type, texels
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// Both s and t direction apply 'GL_REPEAT'
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	for (int i = 0; i < 8; i++) 
	{
		glBindTexture(GL_TEXTURE_2D, textures[2 + i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, BG_data[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture parameters
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	// Both s and t direction apply 'GL_CLAMP'
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	for (int i = 0; i < 10; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[10 + i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, sky_balls_data[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture parameters
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	// Both s and t direction apply 'GL_CLAMP'
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Magnification and Minification use Nearest Interpolation
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, textures[20]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, sun_data); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[21]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 4096, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, moon_data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textures[22]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 474, 355, 0, GL_RGB, GL_UNSIGNED_BYTE, road_data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


void drawSky(void)
{
	GLUquadric* quadricObj = gluNewQuadric(); // Create a quadric surface object
	gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTranslatef(0, 0, 0);
	gluSphere(quadricObj, world_radius * 1.5, 180, 360);
	glPopMatrix();
	gluDeleteQuadric(quadricObj); // Object must be deleted or it will be created every call of the function and memory taken!!!
}


void drawGround(void) 
{
	GLfloat x_init = -(world_radius / 2) * root_2, x_len = world_radius * root_2;	// Set the size of ground
	GLfloat z_init = -(world_radius / 2) * root_2, z_len = world_radius * root_2;
	GLfloat tex_len = 80;	// Length of each texture

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPushMatrix();
	glTranslatef(0, -10, 0);
	for (int i = 0; i < x_len / tex_len; i++) // Divide into many parts, each one use one texture(avoid repeat)
	{   
		for (int j = 0; j < z_len / tex_len; j++) 
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0), glVertex3f(x_init + tex_len * i, 0, z_init + tex_len * (j + 1));
			glTexCoord2f(0.0, 1.0), glVertex3f(x_init + tex_len * i, 0, z_init + tex_len * j);
			glTexCoord2f(1.0, 1.0), glVertex3f(x_init + tex_len * (i + 1), 0, z_init + tex_len * j);
			glTexCoord2f(1.0, 0.0), glVertex3f(x_init + tex_len * (i + 1), 0, z_init + tex_len * (j + 1));
			glEnd();
		}
	}
	glPopMatrix();
}


void drawGoundBG(void)
{ // TO DO: RGBAͼ��λ���� --> ͨ����������ָ��������
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(root_2 * world_radius / 6, wall_height / 2, root_2 * world_radius / 2);
	glTexCoord2f(0.0, 0.0), glVertex3f(root_2 * world_radius / 6, -wall_height / 2, root_2 * world_radius / 2);
	glTexCoord2f(1.0, 0.0), glVertex3f(-root_2 * world_radius / 6, -wall_height / 2, root_2 * world_radius / 2);
	glTexCoord2f(1.0, 1.0), glVertex3f(-root_2 * world_radius / 6, wall_height / 2, root_2 * world_radius / 2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(-root_2 * world_radius / 6, wall_height / 2, root_2 * world_radius / 2);
	glTexCoord2f(0.0, 0.0), glVertex3f(-root_2 * world_radius / 6, -wall_height / 2, root_2 * world_radius / 2);
	glTexCoord2f(1.0, 0.0), glVertex3f(-root_2 * world_radius / 2, -wall_height / 2, root_2 * world_radius / 6);
	glTexCoord2f(1.0, 1.0), glVertex3f(-root_2 * world_radius / 2, wall_height / 2, root_2 * world_radius / 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(-root_2 * world_radius / 2, wall_height / 2, root_2 * world_radius / 6);
	glTexCoord2f(0.0, 0.0), glVertex3f(-root_2 * world_radius / 2, -wall_height / 2, root_2 * world_radius / 6);
	glTexCoord2f(1.0, 0.0), glVertex3f(-root_2 * world_radius / 2, -wall_height / 2, -root_2 * world_radius / 6);
	glTexCoord2f(1.0, 1.0), glVertex3f(-root_2 * world_radius / 2, wall_height / 2, -root_2 * world_radius / 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(-root_2 * world_radius / 2, wall_height / 2, -root_2 * world_radius / 6);
	glTexCoord2f(0.0, 0.0), glVertex3f(-root_2 * world_radius / 2, -wall_height / 2, -root_2 * world_radius / 6);
	glTexCoord2f(1.0, 0.0), glVertex3f(-root_2 * world_radius / 6, -wall_height / 2, -root_2 * world_radius / 2);
	glTexCoord2f(1.0, 1.0), glVertex3f(-root_2 * world_radius / 6, wall_height / 2, -root_2 * world_radius / 2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(-root_2 * world_radius / 6, wall_height / 2, -root_2 * world_radius / 2);
	glTexCoord2f(0.0, 0.0), glVertex3f(-root_2 * world_radius / 6, -wall_height / 2, -root_2 * world_radius / 2);
	glTexCoord2f(1.0, 0.0), glVertex3f(root_2 * world_radius / 6, -wall_height / 2, -root_2 * world_radius / 2);
	glTexCoord2f(1.0, 1.0), glVertex3f(root_2 * world_radius / 6, wall_height / 2, -root_2 * world_radius / 2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(root_2 * world_radius / 6, wall_height / 2, -root_2 * world_radius / 2);
	glTexCoord2f(0.0, 0.0), glVertex3f(root_2 * world_radius / 6, -wall_height / 2, -root_2 * world_radius / 2);
	glTexCoord2f(1.0, 0.0), glVertex3f(root_2 * world_radius / 2, -wall_height / 2, -root_2 * world_radius / 6);
	glTexCoord2f(1.0, 1.0), glVertex3f(root_2 * world_radius / 2, wall_height / 2, -root_2 * world_radius / 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(root_2 * world_radius / 2, wall_height / 2, -root_2 * world_radius / 6);
	glTexCoord2f(0.0, 0.0), glVertex3f(root_2 * world_radius / 2, -wall_height / 2, -root_2 * world_radius / 6);
	glTexCoord2f(1.0, 0.0), glVertex3f(root_2 * world_radius / 2, -wall_height / 2, root_2 * world_radius / 6);
	glTexCoord2f(1.0, 1.0), glVertex3f(root_2 * world_radius / 2, wall_height / 2, root_2 * world_radius / 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0), glVertex3f(root_2 * world_radius / 2, wall_height / 2, root_2 * world_radius / 6);
	glTexCoord2f(0.0, 0.0), glVertex3f(root_2 * world_radius / 2, -wall_height / 2, root_2 * world_radius / 6);
	glTexCoord2f(1.0, 0.0), glVertex3f(root_2 * world_radius / 6, -wall_height / 2, root_2 * world_radius / 2);
	glTexCoord2f(1.0, 1.0), glVertex3f(root_2 * world_radius / 6, wall_height / 2, root_2 * world_radius / 2);
	glEnd();
}


void drawStarSky(GLint Cstate, GLint Sstate) 
{
	GLdouble eqn1[4] = { 0.0,1.0,0.0,0.0 };
	GLdouble eqn2[4] = { 0.0,-1.0,0.0,0.0 };
	GLfloat Night_emmission[] = { 0.3, 0.3, 0.3 };
	GLfloat Day_emmission[] = { 0.1, 0.1, 0.1 };
	GLfloat No_emmission[] = { 0.0, 0.0, 0.0 };
	if (Cstate == 0 && Sstate == 0)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, Day_emmission);
		// C=0, S=0 Sky daylight
		glPushMatrix();
		// If Tstate = 1 then rotate
		glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[10]); // Up
		GLUquadric* quadricObj = gluNewQuadric(); // Create a quadric surface object
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[15]); // Down
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(-90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		gluDeleteQuadric(quadricObj); // Object must be deleted or it will be created every call of the function and memory taken!!!
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();
		glPopMatrix();
	}
	
	else if (Cstate == 1) 
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, Night_emmission);
		// C = 1, Chinese Culture
		glPushMatrix();
		// If Tstate = 1 then rotate
		glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[13]); // Up
		GLUquadric* quadricObj = gluNewQuadric(); // Create a quadric surface object
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[18]); // Down
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(-90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		gluDeleteQuadric(quadricObj); // Object must be deleted or it will be created every call of the function and memory taken!!!
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();
		glPopMatrix();
	}

	else if (Cstate == 0 && Sstate == 1)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, Night_emmission);
		// C=0,S=1 No air
		glPushMatrix();
		// If Tstate = 1 then rotate
		glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[11]); // Up
		GLUquadric* quadricObj = gluNewQuadric(); // Create a quadric surface object
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[16]); // Down
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(-90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		gluDeleteQuadric(quadricObj); // Object must be deleted or it will be created every call of the function and memory taken!!!
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();
		glPopMatrix();
	}

	else if (Cstate == 0 && Sstate == 2)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, Night_emmission);
		//  C=0,S=1 Normal Star Sky
		glPushMatrix();
		// if Tstate = 1 then rotate
		glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[12]); // Up
		GLUquadric* quadricObj = gluNewQuadric(); // Create a quadric surface object
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[17]); // Down
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(-90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		gluDeleteQuadric(quadricObj); // Object must be deleted or it will be created every call of the function and memory taken!!!
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();
		glPopMatrix();
	}

	else if (Cstate == 0 && Sstate == 3)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, Night_emmission);
		//  C=0,S=1 Normal Star Sky
		glPushMatrix();
		// if Tstate = 1 then rotate
		glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[14]); // Up
		GLUquadric* quadricObj = gluNewQuadric(); // Create a quadric surface object
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[19]); // Down
		gluQuadricTexture(quadricObj, GL_TRUE); // Set texture mode to true
		glTranslatef(0, 0, 0);
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
		glRotatef(-90, 0, 0, 1);
		gluSphere(quadricObj, world_radius, 3600, 3600);
		gluDeleteQuadric(quadricObj); // Object must be deleted or it will be created every call of the function and memory taken!!!
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();
		glPopMatrix();
	}

	glMaterialfv(GL_FRONT, GL_EMISSION, No_emmission);
}


void drawSunandMoon(void)
{	
	//Draw solar
	glPushMatrix(); 
	glRotatef(planet_rotation, shaft.x, shaft.y, shaft.z); // Autorotation shaft
	glTranslatef(solar.x, solar.y, solar.z);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[20]);
	glutSolidSphere(10, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//Draw moon
	glPushMatrix();
	glRotatef(planet_rotation + 180, shaft.x, shaft.y, shaft.z); // Autorotation shaft
	glTranslatef(moon.x, moon.y, moon.z);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[21]);
	glutSolidSphere(20, 100, 100); // Moon is larger (for human)
	glPopMatrix();
	glPopMatrix();
}


void drawGrids(void)
{
  
	if (LLGFlag)
	{
		glLineWidth(4.0);
		glDisable(GL_TEXTURE_2D); // Disable texture
		glPushMatrix();
		glColor3f(0, 1, 0); // Define color of frame
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutWireSphere(world_radius*1.5, 12, 12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D); // Re - enable texture
	}
	if (EQGFlag)
	{	
		glLineWidth(4.0);
		glDisable(GL_TEXTURE_2D); // Disable texture
		glPushMatrix();
		glRotatef(SunEarthAngle, 0, 0, 1); // SunEarthAngle degree to LL grid
		glColor3f(0, 0, 1); // Define color of frame
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutWireSphere(world_radius * 1.5, 12, 12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D); // Re - enable texture
	}
	if (ECGFlag)
	{
		glLineWidth(4.0);
		glDisable(GL_TEXTURE_2D); // Disable texture
		glPushMatrix();
		glRotatef(23.2621, 2.53, 0, 1.14); // 23.2621 degree to EQ grid
		glRotatef(SunEarthAngle, 0, 0, 1); // SunEarthAngle degree to LL grid
		glColor3f(1, 1, 0); // Define color of frame
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutWireSphere(world_radius * 1.5, 12, 12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D); // Re - enable texture
	}
}


void plotText(GLfloat x0, GLfloat y0, GLfloat z0, string string)
{
	const char* str = data(string);
	int length = strlen(str); // Plot the text in *st
	glColor3f(1, 0, 0);
	glRasterPos3f(x0, y0, z0);
	for (int i = 0; i < length; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(str + i));
 }


void plotSmallText(GLfloat x0, GLfloat y0, GLfloat z0, string string)
{
	const char* str = data(string);
	int length = strlen(str); // Plot the text in *st
	glColor3f(1, 0, 0);
	glRasterPos3f(x0, y0, z0);
	for (int i = 0; i < length; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
}


void drawBody(void)
{
	glPushMatrix(); // Body
	{
		glTranslatef(0, 5, 0);
		glScalef(10, 20, 20);
		glColor3f(221.0 / 255, 154.0 / 255, 127.0 / 255);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
	}
	glPopMatrix();
}


void drawLeg(bool flip)
{
	glPushMatrix(); // Leg
	{	
		if (flip) glRotatef(-leg_arm_rotation, 0, 0, 1);
		else glRotatef(leg_arm_rotation, 0, 0, 1);
		glTranslatef(0, -8, 0);
		glScalef(5.0, 20.0, 5.0);
		glColor3f(221.0 / 255, 154.0 / 255, 127.0 / 255);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
	}
	glPopMatrix();
}


void drawArm(bool flip)
{
	glPushMatrix(); // Left arm
	{
		if (flip) glRotatef(-leg_arm_rotation, 0, 0, 1);
		else glRotatef(leg_arm_rotation, 0, 0, 1);
		glTranslatef(0, -8, 0);
		glScalef(6, 20, 6);
		glColor3f(221.0 / 255, 154.0 / 255, 127.0 / 255);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
	}
	glPopMatrix();
}


void drawHead(void)
{
	glPushMatrix(); // Head
	{
		glTranslatef(0, 0, 0);
		glRotatef(eye_updown, 0, 0, 1); // Head up and down
		glScalef(10, 10, 10);
		glColor3f(221.0 / 255, 154.0 / 255, 127.0 / 255);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
	}
	glPopMatrix();
}


// Build a humanoid model with <Hierarchical Modelling>
void drawMan()
{
	if (humanFlag)
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		{
			glTranslatef(20 + camera_x, -5 + camera_y, 5 + camera_z);
			glRotatef(-eye_rotation, 0, 1, 0); // Overall T R S matrix (Body) ---> include head, arms and legs
			glScalef(0.7, 0.7, 0.7);
			drawBody();

			glPushMatrix(); // Left leg
			{
				glTranslatef(0, -10, -6); // Left leg T R S matrix
				drawLeg(TRUE); // Make it flip so that wave opposite from right leg
			}
			glPopMatrix();
			glPushMatrix(); // Right leg
			{
				glTranslatef(0, -10, 6); // Right leg T R S matrix
				drawLeg(FALSE);
			}
			glPopMatrix();
			glPushMatrix(); // Left arm
			{
				glTranslatef(0, 12, -13); // Left arm T R S matrix
				drawArm(FALSE);
			}
			glPopMatrix();
			glPushMatrix(); // Right arm
			{
				glTranslatef(0, 12, 13); // Left arm T R S matrix
				drawArm(TRUE); // Make it flip so that wave opposite from left arm
			}
			glPopMatrix();
			glPushMatrix(); // Head
			{
				glTranslatef(0, 20, 0); // Head T R S matrix
				drawHead();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
}


void drawCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat h, GLfloat direction, bool ball)
{
	GLUquadricObj* objCylinder = gluNewQuadric();
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glRotatef(direction, 1, 0, 0);
	gluCylinder(objCylinder, r, r, h, 32, 5);
	if (ball)
	{	// Draw spheres at top and bottom to make it beautiful
		glutSolidSphere(r, 20, 20);
		glPushMatrix();
		glTranslatef(0, 0, h);
		glutSolidSphere(r, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
	gluDeleteQuadric(objCylinder);
}


void drawLamp(GLfloat x_loc, GLfloat y_loc, GLfloat z_loc) 
{
	glDisable(GL_TEXTURE_2D);
	GLfloat emmission[] = { 0.4, 0.3, 0.1 };
	GLfloat no_emmission[] = { 0.0, 0.0, 0.0 };
	if (TimeState == 1) glMaterialfv(GL_FRONT, GL_EMISSION, emmission); // Only emmission at night
	else glMaterialfv(GL_FRONT, GL_EMISSION, no_emmission);
	glPushMatrix();
	glTranslatef(x_loc, y_loc, z_loc);
	glScalef(0.2, 0.2, 0.2);
	glColor4f(199 / 255.0, 146 / 248.0, 100 / 255.0 , 1);
	drawCylinder(0, 0, 0, 15, 40, 90, true);	// Shine part of lamp
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emmission);
	// Top and bottom frames
	glColor3f(0, 0, 0);
	drawCylinder(0, 14, 0, 10, 4, 90, false);
	drawCylinder(0, -50, 0, 10, 6, 90, false);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}


// Draw a cuboid with TEXTURE
void drawCuboid(GLfloat cen_x, GLfloat cen_y, GLfloat cen_z, GLfloat len_x, GLfloat len_y, GLfloat len_z) {
	GLfloat x_start = cen_x - len_x, x_end = cen_x + len_x;
	GLfloat y_start = cen_y - len_y, y_end = cen_y + len_y;
	GLfloat z_start = cen_z - len_z, z_end = cen_z + len_z;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0), glVertex3f(x_start, y_start, z_end);
	glTexCoord2f(0.0, 1.0), glVertex3f(x_start, y_start, z_start);
	glTexCoord2f(1.0, 1.0), glVertex3f(x_end, y_start, z_start);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_end, y_start, z_end);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0), glVertex3f(x_start, y_end, z_end);
	glTexCoord2f(0.0, 1.0), glVertex3f(x_start, y_end, z_start);
	glTexCoord2f(1.0, 1.0), glVertex3f(x_end, y_end, z_start);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_end, y_end, z_end);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0), glVertex3f(x_start, y_start, z_end);
	glTexCoord2f(0.0, 1.0), glVertex3f(x_start, y_start, z_start);
	glTexCoord2f(1.0, 1.0), glVertex3f(x_start, y_end, z_start);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_start, y_end, z_end);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0), glVertex3f(x_end, y_start, z_end);
	glTexCoord2f(0.0, 1.0), glVertex3f(x_end, y_start, z_start);
	glTexCoord2f(1.0, 1.0), glVertex3f(x_end, y_end, z_start);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_end, y_end, z_end);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0), glVertex3f(x_start, y_start, z_end);
	glTexCoord2f(0.0, 1.0), glVertex3f(x_start, y_end, z_end);
	glTexCoord2f(1.0, 1.0), glVertex3f(x_end, y_end, z_end);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_end, y_start, z_end);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_end, y_start, z_end);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0), glVertex3f(x_start, y_start, z_start);
	glTexCoord2f(0.0, 1.0), glVertex3f(x_start, y_end, z_start);
	glTexCoord2f(1.0, 1.0), glVertex3f(x_end, y_end, z_start);
	glTexCoord2f(1.0, 0.0), glVertex3f(x_end, y_start, z_start);
	glEnd();
}


void drawRoad(GLfloat x, GLfloat y, GLfloat degree) 
{
	glBindTexture(GL_TEXTURE_2D, textures[22]);
	glPushMatrix();
	
	glRotated(degree, 0, 1, 0); // Change road direction
	// First part
	drawCuboid(x - 20, y, -20, 9, 1, 8); 
	drawCuboid(x - 20, y, -5.5, 9, 1, 4.5);
	drawCuboid(x - 20, y, 14.5, 9, 1, 13.5);
	// Second part
	drawCuboid(x, y, -8, 9, 1, 20);
	drawCuboid(x, y, 21, 9, 1, 7);
	// Third part
	drawCuboid(x + 20, y, -23, 9, 1, 5);
	drawCuboid(x + 20, y, -1, 9, 1, 15);
	drawCuboid(x + 20, y, 22, 9, 1, 6);
	glPopMatrix();
}


void myDisplay(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, aspect, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	gluLookAt(camera_x, camera_y, camera_z, lookat_x, lookat_y, lookat_z, Vx, Vy, Vz);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// Set fog
	if (fogFlag)
	{
		if (TimeState == 0) // dayFog
		{
			glEnable(GL_FOG); // Enable fog --> The brightness of an object is varied as a function of its distance to the viewing position
			{
				glFogi(GL_FOG_MODE, GL_LINEAR);
				glFogf(GL_FOG_COLOR, (0.5, 0.5, 0.5, 1.0));
				glFogf(GL_FOG_DENSITY, 0.1);
				glHint(GL_FOG_HINT, GL_DONT_CARE);
				glFogf(GL_FOG_START, root_2 * world_radius / 3 - 50);  // Day - fog further
				glFogf(GL_FOG_END, world_radius + 50);
			}
		}

		if (TimeState == 1) // dayFog
		{
			glEnable(GL_FOG); // Enable fog --> The brightness of an object is varied as a function of its distance to the viewing position
			{
				glFogi(GL_FOG_MODE, GL_LINEAR); 
				glFogf(GL_FOG_COLOR, (0.5, 0.5, 0.5, 1.0));
				glFogf(GL_FOG_DENSITY, 0.3);
				glHint(GL_FOG_HINT, GL_DONT_CARE);
				glFogf(GL_FOG_START, root_2 * world_radius / 6 - 50); // Night - fog closer
				glFogf(GL_FOG_END, world_radius + 50);
			}
		}
	}
	else
	{
		glDisable(GL_FOG);
	}
	// Set lights
	setLight();
	// Define material parameters
	GLfloat ambient[4] = { 1.0, 1.0, 1.0, 1.0 }, diffuse[4] = { 1.0, 1.0, 1.0, 1.0 }, specular[] = { 1, 1, 1, 1.0 };
	GLfloat shininess = 10.0, emission[] = { 0.0, 0.0, 0.0, 1.0 };
	// Set material parameters
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glEnable(GL_TEXTURE_2D);
	// Draw backgrounds 
	drawSky();
	drawSunandMoon();
	drawStarSky(CultureState, SkyState);
	glEnable(GL_BLEND); // Mixture texture
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Mixture texture function
	drawGrids();
	if(landFlag)
	{
		glPushMatrix();
		glTranslatef(0, -10, 0);
		drawGoundBG();
		glPopMatrix();
		
		glDisable(GL_BLEND);
		glDepthMask(GL_FALSE);
	
		glPushMatrix();
		glTranslatef(0, -10, 0);
		drawGround();
		for (int i = 20; i <= world_radius; i += 60)
		{
			drawRoad(i, -10, 0);
			drawRoad(-i, -10, 0); // North to South
		}
		for (int i = 20; i <= world_radius; i += 60)
		{
			drawRoad(i, -10, 90);
			drawRoad(-i, -10, 90);// West to East
		}
		glEnable(GL_CULL_FACE); // Enable face-culling
		glCullFace(GL_BACK); // Remove back face
		drawLamp(-20, 0, -20);
		drawLamp(20, 0, -20);
		drawLamp(20, 0, 20);
		drawLamp(-20, 0, 20);
		drawMan();
		glDisable(GL_CULL_FACE);
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	// Draw 2D objects
	if(TRUE)
	{	
		glMatrixMode(GL_PROJECTION); // Ortho view for 2D image
		glLoadIdentity();
		glRotatef(90, 0, 1, 0);
		glOrtho(-300, 300, -300, 300, -300, 300);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1, 1, 1);
		// Active star finder
		if (finderFlag)
		{
			glLineWidth(3.0);
			glColor3f(1, 0, 0);
			glPushMatrix();
			glBegin(GL_LINE_LOOP);
			glVertex3f(0, -50, -150);
			glVertex3f(0, -50, 150);
			glVertex3f(0, 50, 150);
			glVertex3f(0, 50, -150);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(0, 0, -10);
			glVertex3f(0, 0, 10);
			glVertex3f(0, 10, 0);
			glVertex3f(0, -10, 0);
			glEnd();

			plotText(0, -45, 145, "Current FOV: " + to_string(fltFOV));
			glColor3f(1, 1, 1);
			glPopMatrix();
		}
		// Show info
		if (infoFlag)
		{	
			glColor3f(1, 1, 1);
			if (CultureState == 0) plotText(0, -295, 295, "Current Culture: Western (Modern)");
			else plotText(0, -295, 295, "Current Culture: China (Ancient)");
			if (TimeState == 0) plotText(0, -275, 295, "Current Location: Northern Hemisphere");
			else plotText(0, -275, 295, "Current Location: Southern Hemisphere");

			glPushMatrix();
			glTranslatef(0, 200, -200);
			glScalef(1, 3, 3);
			glRotatef(eye_rotation, 1, 0, 0);
			plotText(0, 17, 5, "North");
			plotText(0, -19, 5, "South");
			plotText(0, 0, -17, "East");
			plotText(0, 0, 28, "West");
			glBegin(GL_POLYGON); // Up
			glVertex3f(0, 0, 0);
			glVertex3f(0, 6, -3);
			glVertex3f(0, 16, 0);
			glVertex3f(0, 6, 3);
			glEnd();
			glBegin(GL_POLYGON); // Down
			glVertex3f(0, 0, 0);
			glVertex3f(0, -6, -3);
			glVertex3f(0, -16, 0);
			glVertex3f(0, -6, 3);
			glEnd();
			glPushMatrix(); // Left and right
			glRotatef(90, 1, 0, 0); // Just rotate 90 degree
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 6, -3);
			glVertex3f(0, 16, 0);
			glVertex3f(0, 6, 3);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0);
			glVertex3f(0, -6, -3);
			glVertex3f(0, -16, 0);
			glVertex3f(0, -6, 3);
			glEnd();
			glPopMatrix();
			glPopMatrix();

			if (suninfoFlag)
			{
				plotSmallText(0, 290, 295, "Type: Star");
				plotSmallText(0, 275, 295, "Magnitude: - 27.78 (optical quality reduced to - 27.78 through 3.41 atmosphere)");
				plotSmallText(0, 260, 295, "Absolute magnitude: 4.83");
				plotSmallText(0, 245, 295, "Right ascension/declination: 256.06570`/-22.8216`");
				plotSmallText(0, 230, 295, "Yellow declination angle: 23.4380`");
				plotSmallText(0, 215, 295, "Liter: 6h45m (Dawn: 6h18m)");
				plotSmallText(0, 200, 295, "Midday: 11h50m");
				plotSmallText(0, 185, 295, "Falling: 16h55m (Twilight: 17h22m)");
				plotSmallText(0, 170, 295, "Hourly motion: 0.0419` direction 94.9`");
				plotSmallText(0, 155, 295, "Distance: 0.985 AU");
				plotSmallText(0, 140, 295, "Apparent diameter: 0.54104`");
				plotSmallText(0, 125, 295, "Diameter: 1391400.0 km");
			}
			if (mooninfoFlag)
			{
				plotSmallText(0, 290, 295, "Type: Satellite");
				plotSmallText(0, 275, 295, "Magnitude: 0.21");
				plotSmallText(0, 260, 295, "Absolute magnitude: 4.83");
				plotSmallText(0, 245, 295, "Right ascension/declination: 89.96575`/26.5257`");
				plotSmallText(0, 230, 295, "Azimuth/horizon: 37.3782 `/-21.0821`");
				plotSmallText(0, 215, 295, "Liter: 17h37m (Dawn: 6h18m)");
				plotSmallText(0, 200, 295, "Midday: 1h05m");
				plotSmallText(0, 185, 295, "Falling: 7h40m (Twilight: 17h22m)");
				plotSmallText(0, 170, 295, "Hourly motion: 0.6620` direction 83.3`");
				plotSmallText(0, 155, 295, "Distance: 0.002708 AU");
				plotSmallText(0, 140, 295, "Apparent diameter: 0.49144`");
				plotSmallText(0, 125, 295, "Diameter: 3474.8 km");
				plotSmallText(0, 110, 295, "Star position angle: -35.4315`");
				plotSmallText(0, 95, 295, "Star cycle: 27.32 days");
				plotSmallText(0, 80, 295, "Track speed: 0.981km/s");
				plotSmallText(0, 65, 295, "Heliocentric speed: 31.196km/s");
				plotSmallText(0, 50, 295, "Phase angle: 13.4147`");
			}
			glColor3f(1, 1, 1);
		}
	}
	glutSwapBuffers();
}


void menu(int item) // Mouse and keyboard can control the display altogether
{
	myKeyboardFunc((unsigned char)item, 0, 0);
	mouseInput((unsigned char)item, GLUT_UP, 0, 0);
	specialKeyboardKeys((unsigned char)item, 0, 0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	int s_width = glutGet(GLUT_SCREEN_WIDTH);
	int s_height = glutGet(GLUT_SCREEN_HEIGHT);
	// Create the window
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition((s_width - winWidth) / 2, (s_height - winHeight) / 2); // Center the window
	glutCreateWindow("Stellarium");

	myInit();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshapeFunc);
	glEnable(GL_MULTISAMPLE); // MSAA
	glutIdleFunc(myIdleFunc);	// Animation
	glutKeyboardFunc(myKeyboardFunc);	// Keyboard callback function
	glutSpecialFunc(specialKeyboardKeys);
	glutMouseFunc(mouseInput);	// Mouse callback function

	int showMenu, viewMenu, skyMenu; // Define the menu
	showMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Item Showing Menu", '\0');
	glutAddMenuEntry("----------------------------------", '\0');
	glutAddMenuEntry("Show/Hide Longitude and Lagitude Grid [Z]", 'z');
	glutAddMenuEntry("Show/Hide Equatorial Grid [X]", 'x');
	glutAddMenuEntry("Show/Hide Ecliptic Grid [C]", 'c');
	glutAddMenuEntry("Show/Hide Fog Effect [F]", 'f');
	glutAddMenuEntry("Show/Hide Star Finder [R]", 'r');
	glutAddMenuEntry("Show/Hide ALL Information [I]", 'i');
	glutAddMenuEntry("Show/Hide Human [H]", 'h');
	glutAddMenuEntry("Show/Hide Land Elements(Including human) [L]", 'l');
	glutAddMenuEntry("Catch the Sun [O]", 'o');
	glutAddMenuEntry("Catch the Moon [P]", 'p');
	glutAddMenuEntry("----------------------------------", '\0');

	viewMenu = glutCreateMenu(menu);
	glutAddMenuEntry("View and Moving Menu", '\0');
	glutAddMenuEntry("----------------------------------", '\0');
	glutAddMenuEntry("Turn Left [A]", 'a');
	glutAddMenuEntry("Turn Right [R]", 'r');
	glutAddMenuEntry("Look Up [W]", 'w');
	glutAddMenuEntry("Look Down [S]", 's');
	glutAddMenuEntry("Move Forward [UP]", GLUT_KEY_UP);
	glutAddMenuEntry("Move Back [DOWN]", GLUT_KEY_DOWN);
	glutAddMenuEntry("Move Left [LEFT]", GLUT_KEY_LEFT);
	glutAddMenuEntry("Move Right [RIGHT]", GLUT_KEY_RIGHT);
	glutAddMenuEntry("Zoom in(Decrease FOV) [WHEEL UP]", GLUT_WHEEL_UP);
	glutAddMenuEntry("Zoom out(Increase FOV) [WHEEL DOWN]", GLUT_WHEEL_DOWN);
	glutAddMenuEntry("Active/Disable Move Restriction [G]", 'g');
	glutAddMenuEntry("Back to the Initial State [B]", 'b');
	glutAddMenuEntry("----------------------------------", '\0');

	skyMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Sky Changing Menu", '\0');
	glutAddMenuEntry("----------------------------------", '\0');
	glutAddMenuEntry("Inial Sky (Day/Western Culture) [F1]", GLUT_KEY_F1);
	glutAddMenuEntry("Chinese Culture [F2]", GLUT_KEY_F2);
	glutAddMenuEntry("Rotate to Southern Hemisphere (Night) [F3]", GLUT_KEY_F3);
	glutAddMenuEntry("Disable Atmosphere [F4]", GLUT_KEY_F4);
	glutAddMenuEntry("Active Constelations [F5]", GLUT_KEY_F5);
	glutAddMenuEntry("Active Patterns [F6]", GLUT_KEY_F6);
	glutAddMenuEntry("----------------------------------", '\0');

	glutCreateMenu(menu);
	glutAddMenuEntry("Control Menu", '\0');
	glutAddMenuEntry("----------------------------------", '\0');
	glutAddSubMenu("Item Showing Menu ", showMenu);
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry(" ", '\0');
	glutAddSubMenu("View and Moving Menu ", viewMenu);
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry(" ", '\0');
	glutAddSubMenu("Sky Changing Menu ", skyMenu);
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry("----------------------------------", '\0');
	glutAddMenuEntry("Thank you for testing my program.", '\0');
	glutAddMenuEntry("----------------------------------", '\0');
	glutAddMenuEntry("Quit [Q]", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON); // Open the menu

	
	glutMainLoop();
}