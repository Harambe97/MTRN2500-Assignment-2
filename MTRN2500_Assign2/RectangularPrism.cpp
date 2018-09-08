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

//Code written by: Mei Yan Tang (z5129009)

//uses variables outlined from the specifications of shape found in Moodle.
RectangularPrism::RectangularPrism(double x_, double y_, double z_, double rotation_, double Lx, double Ly, double Lz):Shape(x_, y_, z_, rotation_) {
	red = 1.0;
	blue = 0.0;
	green = 0.0;
	
	x_length = Lx;
	y_length = Ly;
	z_length = Lz;

}


void RectangularPrism::draw() {
	glPushMatrix(); //pushes the current matrix stack down by one, duplicating the current matrix
	positionInGL(); //sets the position
	setColorInGL(); //sets the colour

		//front face
		glPushMatrix(); 
			glBegin(GL_QUADS); //defines an enclosed shape with 4 vertices
				glVertex3f(x_length / 2, 0, -z_length / 2);
				glVertex3f(x_length / 2, y_length, -z_length / 2);
				glVertex3f(-x_length / 2, y_length, -z_length / 2);
				glVertex3f(-x_length / 2, 0, -z_length / 2);
			glEnd();
		glPopMatrix(); //pops the current matrix stack, replacing the current matrix with the one below it on the stack.

		//right face
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3f(x_length / 2, 0, -z_length / 2);
				glVertex3f(x_length / 2, y_length, -z_length / 2);
				glVertex3f(x_length / 2, y_length, z_length / 2);
				glVertex3f(x_length / 2, 0, z_length / 2);
			glEnd();
		glPopMatrix();

		//back face
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3f(x_length / 2, 0, z_length / 2);
				glVertex3f(x_length / 2, y_length, z_length / 2);
				glVertex3f(-x_length / 2, y_length, z_length / 2);
				glVertex3f(-x_length / 2, 0, z_length / 2);
			glEnd();
		glPopMatrix();

		//left face
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3f(-x_length / 2, y_length, z_length / 2);
				glVertex3f(-x_length / 2, 0, z_length / 2);
				glVertex3f(-x_length / 2, 0, -z_length / 2);
				glVertex3f(-x_length / 2, y_length, -z_length / 2);
			glEnd();
		glPopMatrix();

		//Top face
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3f(-x_length / 2, y_length, -z_length / 2);
				glVertex3f(x_length / 2, y_length, -z_length / 2);
				glVertex3f(x_length / 2, y_length, z_length / 2);
				glVertex3f(-x_length / 2, y_length, z_length / 2);
			glEnd();
		glPopMatrix();

		//bottom face
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3f(-x_length / 2, 0, -z_length / 2);
				glVertex3f(x_length / 2, 0, -z_length / 2);
				glVertex3f(x_length / 2, 0, z_length / 2);
				glVertex3f(-x_length / 2, 0, z_length / 2);
			glEnd();
		glPopMatrix();
	glPopMatrix();
}

// Functions below written by: Haydn St. James (z5118383)

// Functions below are used to set new dimensions for a rectangular prism if required (for example, when drawing other 
// vehicles from the server).
void RectangularPrism::setX_length(double Lx) {
	x_length = Lx;
}

void RectangularPrism::setY_length(double Ly) {
	y_length = Ly;
}

void RectangularPrism::setZ_length(double Lz) {
	z_length = Lz;
}