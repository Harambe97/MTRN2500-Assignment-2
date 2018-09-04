#include "RectangularPrism.h"
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//Code written by: Mei Yan Tang (z5129009)

RectangularPrism::RectangularPrism(double x_, double y_, double z_, double rotation_, double Lx, double Ly, double Lz):Shape(x_, y_, z_, rotation_) {
	x_length = Lx;
	y_length = Ly;
	z_length = Lz;

}

void RectangularPrism::draw() {

	//front face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(x_length / 2, 0, -z_length / 2);
		glVertex3f(x_length / 2, y_length, -z_length / 2);
		glVertex3f(-x_length / 2, y_length, -z_length / 2);
		glVertex3f(-x_length / 2, 0, -z_length / 2);
	glEnd();
	glPopMatrix();

	//right face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(x_length / 2, 0, -z_length / 2);
		glVertex3f(x_length / 2, y_length, -z_length / 2);
		glVertex3f(x_length / 2, y_length, z_length / 2);
		glVertex3f(x_length / 2, 0, z_length / 2);
	glEnd();
	glPopMatrix();

	//back face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(x_length / 2, 0, z_length / 2);
		glVertex3f(x_length / 2, y_length, z_length / 2);
		glVertex3f(-x_length / 2, y_length, z_length / 2);
		glVertex3f(-x_length / 2, 0, z_length / 2);
	glEnd();
	glPopMatrix();

	//left face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(-x_length / 2, y_length, z_length / 2);
		glVertex3f(-x_length / 2, 0, z_length / 2);
		glVertex3f(-x_length / 2, 0, -z_length / 2);
		glVertex3f(-x_length / 2, y_length, -z_length / 2);
	glEnd();
	glPopMatrix();

	//Top face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(-x_length / 2, y_length, -z_length / 2);
		glVertex3f(x_length / 2, y_length, -z_length / 2);
		glVertex3f(x_length / 2, y_length, z_length / 2);
		glVertex3f(-x_length / 2, y_length, z_length / 2);
	glEnd();
	glPopMatrix();

	//bottom face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(-x_length / 2, 0, -z_length / 2);
		glVertex3f(x_length / 2, 0, -z_length / 2);
		glVertex3f(x_length / 2, 0, z_length / 2);
		glVertex3f(-x_length / 2, 0, z_length / 2);
	glEnd();
	glPopMatrix();

}


