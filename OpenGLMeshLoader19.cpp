#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <iostream>

int WIDTH = 1280;
int HEIGHT = 720;
double x = 0;
double z = 0;
double angle = 0;
bool whistel = true;
int score = 0;
bool wingame = false;
bool losegame = false;
int t = 5;

char* lives[20];


GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};
Vector motion = Vector(0, 0, 0);
Vector motionball = Vector(0, 0, 0);


Vector Eye(50, 15, 0);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;

// Textures
GLTexture tex_ground;
GLTexture tex_ball;
GLTexture france;
GLTexture england;
GLTexture america;
GLTexture cr7;
GLTexture track;


GLTexture adidas;
GLTexture tiktok;
GLTexture qatar;
GLTexture pepsi;
GLTexture score2;


//=======================================================================
// Lighting Configuration Function
//=======================================================================

void crowd(int) {
	sndPlaySound(TEXT("sounds/crowd.wav"), SND_ASYNC | SND_LOOP | SND_FILENAME);

}
void centerball(int) {
	motionball.x = 0;
	motionball.z = 0;

}

void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}
void time(int val) {
	t += 2;
	glutTimerFunc(200, time, 0);
}

//=======================================================================
// Render Ground Function
//=======================================================================

void drawbenches() {
	/// left benches
	glPushMatrix();
	glTranslatef(6, 1.5, 15.5);
	glScalef(4, 3, 0.2);
	glColor3f(1, 0.45, 0.61);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 1.5, 15.5);
	glScalef(.1, 3, 1);
	glColor3f(0.1, 0.45, 0.61);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 1.5, 15.5);
	glScalef(.1, 3, 1);
	glColor3f(0.1, 0.45, 0.61);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 3, 15.5);
	glScalef(4, .1, 1.1);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.7, 0, 15.5);
	glScalef(1, 1, 0.8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.9, 0, 15.5);
	glScalef(1, 1, 0.8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.1, 0, 15.5);
	glScalef(1, 1, 0.8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	//write benches



	glPushMatrix();
	glTranslatef(-6, 1.5, 16);
	glScalef(4, 3, 0.2);
	glColor3f(1, 0.45, 0.61);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, 1.5, 15.5);
	glScalef(.1, 3, 1);
	glColor3f(0.1, 0.45, 0.61);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 1.5, 15.5);
	glScalef(.1, 3, 1);
	glColor3f(0.1, 0.45, 0.61);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, 3, 15.5);
	glScalef(4, .1, 1.1);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.7, 0, 15.5);
	glScalef(1, 1, 0.8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.9, 0, 15.5);
	glScalef(1, 1, 0.8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.1, 0, 15.5);
	glScalef(1, 1, 0.8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

}

void drawplayer() {

	glPushMatrix();
	glTranslatef(motion.x + 3, 0.5, motion.z);
	glRotatef(angle, 0, 1, 0);
	glTranslatef(-3, 0, 0);


	glPushMatrix(); //legs left
	glColor3f(1, 1, 1);
	glTranslated(3, 0.5, 0.3);
	glScalef(0.2, 0.5, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //legs right
	glColor3f(1, 1, 1);
	glTranslated(3, 0.5, -0.3);
	glScalef(0.2, 0.5, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //upperlegs left
	glColor3f(0, 0, 0);
	glTranslated(3, 0.875, 0.3);
	glScalef(0.2, 0.25, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //upperlegs right
	glColor3f(0, 0, 0);
	glTranslated(3, 0.875, -0.3);
	glScalef(0.2, 0.25, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //chest
	glColor3f(1, 0, 0);
	glTranslated(3, 1.5, 0);
	glScalef(0.2, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // head
	glColor3f(1, 1, 1);
	glTranslated(3, 2.3, 0);
	glScalef(0.7, 0.7, 0.7);
	glutSolidSphere(.4, 15, 15);
	glPopMatrix();

	glPushMatrix(); //shoulders left
	glColor3f(1, 0, 0);
	glTranslated(3, 1.9, 0.7);
	glScalef(0.2, 0.2, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //shoulders right
	glColor3f(1, 0, 0);
	glTranslated(3, 1.9, -0.7);
	glScalef(0.2, 0.2, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //hand left
	glColor3f(1, 1, 1);
	glTranslated(3, 1.4, 0.75);
	glScalef(0.2, 0.8, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //hand right
	glColor3f(1, 1, 1);
	glTranslated(3, 1.4, -0.75);
	glScalef(0.2, 0.8, 0.3);
	glutSolidCube(1);
	glPopMatrix();


	glPopMatrix();


}
void drawbanners() {
	/// //// adidas /////
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, adidas.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-30, 3, 20);
	glTexCoord2f(5, 0);
	glVertex3f(-30, 3, -20);
	glTexCoord2f(5, 1);
	glVertex3f(-30, 0, -20);
	glTexCoord2f(0, 1);
	glVertex3f(-30, 0, 20);
	glEnd();
	glPopMatrix();
	////////////////////////////////////////
	/// //// qatar /////
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, qatar.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(30, 3, 20);
	glTexCoord2f(5, 0);
	glVertex3f(30, 3, -20);
	glTexCoord2f(5, 1);
	glVertex3f(30, 0, -20);
	glTexCoord2f(0, 1);
	glVertex3f(30, 0, 20);
	glEnd();
	glPopMatrix();
	////////////////////////////////////////
	/////pepsi/////////////////////////
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pepsi.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-30, 3, -20);
	glTexCoord2f(5, 0);
	glVertex3f(30, 3, -20);
	glTexCoord2f(5, 1);
	glVertex3f(30, 0, -20);
	glTexCoord2f(0, 1);
	glVertex3f(-30, 0, -20);
	glEnd();
	glPopMatrix();
	//////////////////////
	/////tiktok/////////////////////////
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tiktok.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-30, 3, 20);
	glTexCoord2f(5, 0);
	glVertex3f(30, 3, 20);
	glTexCoord2f(5, 1);
	glVertex3f(30, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(-30, 0, 20);
	glEnd();
	glPopMatrix();
	//////////////////////



}
void RenderGround()
{

	glDisable(GL_LIGHTING);	// Disable lighting 
	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, track.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);
	glColor3f(0.5, 0.4, 0.8);
	glVertex3f(30, -0.01, 20);
	glColor3f(0.5, 0.4, 0.8);
	glTexCoord2f(5, 0);
	glVertex3f(-30, -0.01, 20);
	glColor3f(0.5, 0.4, 0.8);
	glTexCoord2f(5, 5);
	glVertex3f(-30, -0.01, -20);
	glColor3f(0.5, 0.4, 0.8);
	glTexCoord2f(0, 5);
	glVertex3f(30, -0.01, -20);
	glEnd();
	glPopMatrix();


	glDisable(GL_LIGHTING);	// Disable lighting 
	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(25, 0, 15);
	glTexCoord2f(1, 0);
	glVertex3f(-25, 0, 15);
	glTexCoord2f(1, 1);
	glVertex3f(-25, 0, -15);
	glTexCoord2f(0, 1);
	glVertex3f(25, 0, -15);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void arda() {
	// 3arda
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-21, 1.5, 3);
	glScalef(0.2, 3, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(-21, 1.5, -3);
	glScalef(0.2, 3, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(-21, 3.1, 0);
	glScalef(0.2, 0.2, 6.2);
	glutSolidCube(1);
	glPopMatrix();


	// 3arda
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 1.5, 3);
	glScalef(0.2, 3, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 1.5, -3);
	glScalef(0.2, 3, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 3.1, 0);
	glScalef(0.2, 0.2, 6.2);
	glutSolidCube(1);
	glPopMatrix();
}
void scoreboard() {

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-27.5, 1.5, 2);
	glScalef(0.2, 5, 0.2);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-27.5, 1.5, -2);
	glScalef(0.2, 5, 0.2);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_LIGHTING);	// Disable lighting 
	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, score2.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-27.5, 8, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-27.5, 4, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-27.5, 4, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-27.5, 8, 3);
	glEnd();
	glPopMatrix();


}
void ads() {
	// ads
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 3.1, 0);
	glScalef(0.2, 0.2, 6.2);
	glutSolidCube(1);
	glPopMatrix();



	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 3.1, 0);
	glScalef(0.2, 0.2, 6.2);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 3.1, 0);
	glScalef(0.2, 0.2, 6.2);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21, 3.1, 0);
	glScalef(0.2, 0.2, 6.2);
	glutSolidCube(1);
	glPopMatrix();
}
void flags() {
	///flags

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-21.3, 0, -13);
	glScalef(0.2, 4, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, france.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-21.2, 1, -12.88);
	glTexCoord2f(1, 0);
	glVertex3f(-21.2, 2.1, -12.88);
	glTexCoord2f(1, 1);
	glVertex3f(-21.2, 2.1, -11);
	glTexCoord2f(0, 1);
	glVertex3f(-21.2, 1, -11);
	glEnd();
	glPopMatrix();

	/////

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-21.3, 0, 13);
	glScalef(0.2, 4, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, america.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-21.2, 1, 12.88);
	glTexCoord2f(1, 0);
	glVertex3f(-21.2, 2.1, 12.88);
	glTexCoord2f(1, 1);
	glVertex3f(-21.2, 2.1, 11);
	glTexCoord2f(0, 1);
	glVertex3f(-21.2, 1, 11);
	glEnd();
	glPopMatrix();

	/////

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21.3, 0, -13);
	glScalef(0.2, 4, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, cr7.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(21.2, 1, 12.88);
	glTexCoord2f(1, 0);
	glVertex3f(21.2, 2.1, 12.88);
	glTexCoord2f(1, 1);
	glVertex3f(21.2, 2.1, 11);
	glTexCoord2f(0, 1);
	glVertex3f(21.2, 1, 11);
	glEnd();
	glPopMatrix();

	/////

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(21.3, 0, 13);
	glScalef(0.2, 4, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, england.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(21.2, 1, -12.88);
	glTexCoord2f(1, 0);
	glVertex3f(21.2, 2.1, -12.88);
	glTexCoord2f(1, 1);
	glVertex3f(21.2, 2.1, -11);
	glTexCoord2f(0, 1);
	glVertex3f(21.2, 1, -11);
	glEnd();
	glPopMatrix();

	//////
}
void ball() {
	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	glTranslated(0 + motionball.x, 0.4, motionball.z + 0);
	glBindTexture(GL_TEXTURE_2D, tex_ball.texture[0]);
	gluQuadricTexture(qobj1, true);
	gluQuadricNormals(qobj1, GL_SMOOTH);
	gluSphere(qobj1, 0.4, 15, 15);
	gluDeleteQuadric(qobj1);
}

void worldcup() {
	glPushMatrix();
	glColor3f(0.9f, 0.4f, 0.1f);
	glTranslatef(0, 1.8, 15.5);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(0.5, 2, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0, 0.25, 15.5);
	glScalef(0.6, 0.5, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9f, 0.6f, 0.1f);
	glTranslatef(0, 2.0, 15.5);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.9f, 0.4f, 0.1f);
	glTranslatef(10, 1.8, 15.5);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(0.5, 2, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(10, 0.25, 15.5);
	glScalef(0.6, 0.5, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9f, 0.6f, 0.1f);
	glTranslatef(10, 2.0, 15.5);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.9f, 0.4f, 0.1f);
	glTranslatef(-10, 1.8, 15.5);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(0.5, 2, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-10, 0.25, 15.5);
	glScalef(0.6, 0.5, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9f, 0.6f, 0.1f);
	glTranslatef(-10, 2.0, 15.5);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();
}
void print(int x, int y, int z,char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y,z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	if (t > 600 && score==0) {
		glColor3f(1.0f, 0.0f, 0.0f);
		sprintf((char*)lives, "Game Over");
		print(3, 10,6, (char*)lives);
	}
	if (score > 1) {
		glColor3f(1.0f, 0.0f, 0.0f);
		sprintf((char*)lives, "Congratulation you win");
		print(3, 10,6, (char*)lives);
	}
	
	// Draw Tree Model
	glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	//model_tree.Draw();
	glPopMatrix();

	// Draw house Model
	glPushMatrix();
	glRotatef(90.f, 1, 0, 0);
	//model_house.Draw();
	glPopMatrix();

	arda();
	scoreboard();

	flags();

	ads();
	worldcup();







	// ball


	//ads
	drawbenches();
	drawbanners();
	drawplayer();


	//sky box

	glPushMatrix();
	RenderGround();
	glPopMatrix();
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	glPushMatrix();

	ball();


	glPopMatrix();
	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

Vector3f eye = Vector3f(Eye.x, Eye.y, Eye.z);

Vector3f center = Vector3f(At.x, At.y, At.z);
Vector3f up = Vector3f(Up.x, Up.y, Up.z);

double deg2rad(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}
//=======================================================================
// Keyboard Function
//=======================================================================

void Special(int key, int x, int y) {
	float a = .5;
	float b = 0.5;

	/*std::cout << motion.x - 3 << std::endl;
	std::cout << motionball.x << std::endl;
	std::cout << motion.z -.3<< std::endl;
	std::cout << motionball.z << std::endl;
	*/

	switch (key) {
	case GLUT_KEY_UP: {
		if (motion.x > -23.5) {
			motion.x -= a;
		}

		angle = 0;
		if (abs(motion.x + 3 - motionball.x) < b && abs(motionball.z - motion.z + 0.3) < b) {
			motionball.x -= 3.7;
			sndPlaySound(TEXT("sounds/kick.wav"), SND_ASYNC | SND_FILENAME);
			glutTimerFunc(1000, crowd, 0);

		}
		break;
	}
	case GLUT_KEY_DOWN: {
		if (motion.x < 18) {
			motion.x += a;
		}
		angle = 180;
		if (abs(motionball.x - motion.x - 3) < b && abs(motionball.z - motion.z - 0.3) < b) {
			motionball.x += 3.7;
			sndPlaySound(TEXT("sounds/kick.wav"), SND_ASYNC | SND_FILENAME);
			glutTimerFunc(1000, crowd, 0);
		}
		break; }
	case GLUT_KEY_LEFT: {

		if (motion.z < 12) {
			motion.z += a;
		}

		angle = 90;
		if (abs(motion.x + 3 - motionball.x) < b && abs(motionball.z - motion.z + 0.3) < b) {
			motionball.z += 3.5;
			sndPlaySound(TEXT("sounds/kick.wav"), SND_ASYNC | SND_FILENAME);
			glutTimerFunc(1000, crowd, 0);
		}
		break; }
	case GLUT_KEY_RIGHT: {
		if (motion.z > -12) {
			motion.z -= a;
		}
		angle = -90;
		if (abs(motion.x + 3 - motionball.x) < b && abs(motionball.z - motion.z + 0.3) < b) {
			motionball.z -= 3.5;
			sndPlaySound(TEXT("sounds/kick.wav"), SND_ASYNC | SND_FILENAME);
			glutTimerFunc(1000, crowd, 0);
		}
		break; }
	}
	if (motionball.x < -20 && motionball.z > -2.5 && motionball.z < 2.5) {
		sndPlaySound(TEXT("sounds/whistel.wav"), SND_ASYNC | SND_FILENAME);
		glutTimerFunc(1000, crowd, 0);
		//glutTimerFunc(500, centerball, 0);
		score++;
		std::cout << score << std::endl;

	}
	else if (motionball.x > 19 || motionball.x < -19 || motionball.z > 12 || motionball.z < -12) {

		sndPlaySound(TEXT("sounds/whistel.wav"), SND_ASYNC | SND_FILENAME);
		glutTimerFunc(1000, crowd, 0);
		glutTimerFunc(500, centerball, 0);
		//motionball.x = 0;
		//motionball.z = 0;
		score--;
		std::cout << score << std::endl;

	}

	glutPostRedisplay();
}






void myKeyboard(unsigned char button, int x, int y)

{

	float d = 1;
	switch (button)
	{
	case 'm': {
		motionball.x = 0;
		motionball.z = 0;
	}
	case 'a': {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
		break; }
	case 'w':
	{eye = eye + up.unit() * d;
	center = center + up.unit() * d;
	break; }
	case 'd':
	{
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * (-d);
		center = center + right * (-d);
		break;
	}
	case 's':
	{eye = eye + up.unit() * (-d);
	center = center + up.unit() * (-d);
	break; }
	case 'x':
	{Vector3f view = (center - eye).unit();
	eye = eye + view * d;
	center = center + view * d;
	break; }
	case 'z':
	{Vector3f view = (center - eye).unit();
	eye = eye + view * (-d);
	center = center + view * (-d);
	break; }
	case'q': {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(deg2rad(1)) + up * sin(deg2rad(1));
		up = view.cross(right);
		center = eye + view;
		break;
	}
	case'e': {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(deg2rad(-1)) + up * sin(deg2rad(-1));
		up = view.cross(right);
		center = eye + view;
		break;
	}
	case't': {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(deg2rad(1)) + right * sin(deg2rad(1));
		right = view.cross(up);
		center = eye + view;
		break;
	}
	case'y': {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(deg2rad(-1)) + right * sin(deg2rad(-1));
		right = view.cross(up);
		center = eye + view;
		break;
	}
	case '7':
		//topView
		eye = Vector3f(0, 40, 0);
		center = Vector3f(0, 0, 0);
		up = Vector3f(0, 0, 1);
		break;
	case '8':
		//frontView
		eye = Vector3f(30, 20, 0);
		center = Vector3f(0, 0, 0);
		up = Vector3f(0, 1, 0);
		break;
	case '9':
		//sideView
		eye = Vector3f(0, 15, -20);
		center = Vector3f(0, 0, 0);
		up = Vector3f(0, 1, 0);
		break;



	default:
		break;
	}


	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");

	// Loading texture files
	england.Load("Textures/england.bmp");
	france.Load("Textures/france.bmp");
	cr7.Load("Textures/cr7.bmp");
	america.Load("Textures/america.bmp");

	pepsi.Load("Textures/pepsi.bmp");
	tiktok.Load("Textures/tiktok.bmp");
	adidas.Load("Textures/adidas.bmp");
	qatar.Load("Textures/qatar.bmp");
	score2.Load("Textures/score2.bmp");
	track.Load("Textures/track2.bmp");



	tex_ground.Load("Textures/ground.bmp");
	tex_ball.Load("Textures/ball.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);

}


//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);
	glutSpecialFunc(Special);

	glutReshapeFunc(myReshape);
	if (whistel) {
		sndPlaySound(TEXT("sounds/whistel.wav"), SND_ASYNC | SND_FILENAME);
		whistel = false;
		glutTimerFunc(1000, crowd, 0);

	}

	glutTimerFunc(200, time, 0);


	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}