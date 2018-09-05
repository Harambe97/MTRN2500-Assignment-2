#include "RectangularPrism.h"

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

// Code written by: Mei Yan Tang (z5129009)

RectangularPrism::RectangularPrism(double x_, double y_, double z_, double rotation_, double Lx, double Ly, double Lz):Shape(x_, y_, z_, rotation_) {
	red = 1.0;
	blue = 0.0;
	green = 0.0;

	x_length = Lx;
	y_length = Ly;
	z_length = Lz;
}

void RectangularPrism::draw() {

	// Front face
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

	// Right face
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

	// Back face
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

	// Left face
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

	// Top face
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

	// Bottom face
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