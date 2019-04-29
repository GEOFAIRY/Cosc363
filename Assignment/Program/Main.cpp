#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "floor.h"
#include "loadTGA.h"
#include "fortress.h"
#include "cannon.h"
#include "robot1.h"
#include "robot2.h"
#include "spaceship.h"
using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
GLUquadric* q; //Required for creating cylindrical objects
float angle = 0, look_x, look_z = -1., eye_x, eye_y, eye_z; //Camera parameters
GLuint texId[8];
bool robotDirection = false;
float robotZ = -20;
bool robot2Direction = false;
float robot2Z = -10;
float spaceshipY = -10;

void loadGLTextures()				// Load bitmaps And Convert To Textures
{
	glGenTextures(8, texId); 		// Create texture ids
	// *** left ***
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	loadTGA("left.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** front ***
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	loadTGA("front.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** right ***
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	loadTGA("right.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** back***
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	loadTGA("back.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** top ***
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	loadTGA("top.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** down ***
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	loadTGA("down.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glBindTexture(GL_TEXTURE_2D, texId[6]); //Use this texture
	loadTGA("stone_ground.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texId[7]); //Use this texture
	loadTGA("robot1.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

//========================================================================================

void skybox() {
	glEnable(GL_TEXTURE_2D);

	////////////////////// LEFT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(-1000, 0, 1000);
	glTexCoord2f(1, 0); glVertex3f(-1000, 0., -1000);
	glTexCoord2f(1, 1); glVertex3f(-1000, 1000., -1000);
	glTexCoord2f(0, 1); glVertex3f(-1000, 1000, 1000);
	glEnd();

	////////////////////// FRONT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(-1000, 0, -1000);
	glTexCoord2f(1, 0);  glVertex3f(1000, 0., -1000);
	glTexCoord2f(1, 1);  glVertex3f(1000, 1000, -1000);
	glTexCoord2f(0, 1);  glVertex3f(-1000, 1000, -1000);
	glEnd();

	////////////////////// RIGHT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(1000, 0, -1000);
	glTexCoord2f(1, 0);  glVertex3f(1000, 0, 1000);
	glTexCoord2f(1, 1);  glVertex3f(1000, 1000, 1000);
	glTexCoord2f(0, 1);  glVertex3f(1000, 1000, -1000);
	glEnd();


	////////////////////// REAR WALL ////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(1000, 0, 1000);
	glTexCoord2f(1, 0);  glVertex3f(-1000, 0, 1000);
	glTexCoord2f(1, 1);  glVertex3f(-1000, 1000, 1000);
	glTexCoord2f(0, 1);  glVertex3f(1000, 1000, 1000);
	glEnd();

	/////////////////////// TOP //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1, 0);  glVertex3f(1000, 1000, -1000);
	glTexCoord2f(1, 1);  glVertex3f(1000, 1000, 1000);
	glTexCoord2f(0, 1);  glVertex3f(-1000, 1000, 1000);
	glEnd();

	/////////////////////// FLOOR //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(-1000, 0., 1000);
	glTexCoord2f(1, 0);  glVertex3f(1000, 0., 1000);
	glTexCoord2f(1, 1);  glVertex3f(1000, 0., -1000);
	glTexCoord2f(0, 1);  glVertex3f(-1000, 0., -1000);
	glEnd();

}

//---------------------------------------------------------------------
void initialise(void)
{
	float grey[4] = { 0.2, 0.2, 0.2, 1.0 };
	float white[4] = { 1.0, 1.0, 1.0, 1.0 };
	q = gluNewQuadric();

	loadGLTextures();
	loadMeshFile("Cannon.off");

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//	Define light's ambient, diffuse, specular properties
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	gluQuadricDrawStyle(q, GLU_FILL);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, 1.0, 1.0, 3000.0);   //Perspective projection
}

//---------------------------------------------------------------------
void display(void)
{
	float lgt_pos[] = { 10.0f, 50.0f, 10.0f, 1.0f }; //light0 position (directly above the origin)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye_x, 0, eye_z, look_x, 0, look_z, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos); //light position

	//draw fort
	glPushMatrix();
	glScalef(1.5, 2, 1.5);
	glTranslatef(15, -5, -20);
	glRotatef(180, 0, 1, 0);
	walls();
	glPopMatrix();

	//draw cannon
	glPushMatrix();
	glTranslatef(5, -10, -20);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.1,0.1,0.1);
	cannon();
	glPopMatrix();

	//draw spaceship
	glPushMatrix();
	glTranslatef(-5, spaceshipY, -45);
	glScalef(2, 2, 2);
	spaceship();
	glPopMatrix();

	//draw cannon
	glPushMatrix();
	glTranslatef(-15, -10, -20);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	cannon();
	glPopMatrix();

	//draw robot1
	glPushMatrix();
	glTranslatef(30, -10, robotZ);
	if (robotDirection) glRotatef(180, 0, 1, 0);
	robot1(texId);
	glPopMatrix();

	//draw robot1
	glPushMatrix();
	glTranslatef(-30, -10, robot2Z);
	if (robot2Direction) glRotatef(180, 0, 1, 0);
	robot2();
	glPopMatrix();

	//draw floor
	glPushMatrix();
	glTranslatef(0, -10, 0);
	floor(texId);
	glPopMatrix();

	//draw skybox
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0, -500, 0);
	skybox();
	glPopMatrix();
	glEnable(GL_LIGHTING);

	glutSwapBuffers(); //Useful for animation
}

//--------------------------------------------------------------
void special(int key, int x, int y) //movement
{
	if (key == GLUT_KEY_LEFT) angle -= 0.1; //Change direction
	else if (key == GLUT_KEY_RIGHT) angle += 0.1;
	else if (key == GLUT_KEY_DOWN)
	{
		//Move backward
		if (eye_x > -100 && eye_x < 100 && eye_z > -100 && eye_z < 100) {
			eye_x -= 1 * sin(angle);
			eye_z += 1 * cos(angle);
		} 
		else
		{
			eye_x = 0 * sin(angle);
			eye_z = 0 * cos(angle);
		}
	}
	else if (key == GLUT_KEY_UP)
	{
		//Move forward
		if (eye_x > -100 && eye_x < 100 && eye_z > -100 && eye_z < 100) {
			eye_x += 1 * sin(angle);
			eye_z -= 1 * cos(angle);
		}
		else
		{
			eye_x = 0 * sin(angle);
			eye_z = 0 * cos(angle);
		}
	}

	look_x = eye_x + 100 * sin(angle);
	look_z = eye_z - 100 * cos(angle);
	glutPostRedisplay();
}
//-------------------------------------------------------------------

void robotAnimation(int value)
{
	if (robotDirection)
	{
		robotZ-=0.3;
		if (robotZ < -20) robotDirection = false;
	}
	else
	{
		robotZ+=0.3;
		if (robotZ > 20) robotDirection = true;
	}
	if (robot2Direction)
	{
		robot2Z -= 0.05;
		if (robot2Z < -10) robot2Direction = false;
	}
	else
	{
		robot2Z += 0.05;
		if (robot2Z > 10) robot2Direction = true;
	}
	glutPostRedisplay();
	glutTimerFunc(1, robotAnimation, 0);
}

void liftOffAnimation(int value)
{
	spaceshipY += 5;
	glutPostRedisplay();
	if (spaceshipY < 1000) glutTimerFunc(10, liftOffAnimation, 0);
}


void keyboardShip(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		glutTimerFunc(10, liftOffAnimation, 0);
		break;
	case 'c':
		if (cannon_done) {
			cannon_x = 0;
			cannon_y = 0;
			glutTimerFunc(1, cannonShotTimer, 0);
		}
		break;
	default:
		glutPostRedisplay();
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment");
	initialise();
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboardShip);
	glutTimerFunc(1, walkTimer, 0);
	glutTimerFunc(1, walkTimer2, 0);
	glutTimerFunc(1, robotAnimation, 0);
	glutTimerFunc(10, spinTimer, 0);

	glutMainLoop();
	return 0;
}
