#include "TrapezoidPrism.h"

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

// Code written by: Haydn St. James (z5118383)

// Utilises the constructor in the 'Shape' class to determine if the prism is to be translated or rotated.
// Works similarly to the 'Obstacle' class.
// Uses the variables outlined in the server specifications for shapes, which can be found on the Moodle page of MTRN2500.
TrapezoidPrism::TrapezoidPrism(double x_, double y_, double z_, double rotation_, double Bottom_length, double Top_length, double Height, double Depth, double Offset):Shape(x_, y_, z_, rotation_) {
	red = 0.0;
	green = 0.0;
	blue = 1.0;

	a_length = Bottom_length;
	b_length = Top_length;
	height = Height;
	depth = Depth;
	a_offset = Offset;
}

// Define the front, back, top, bottom and corners of the trapezoid using geometry and draw the trapezoid face - by - face.
// Take note that the coordinate axes and rotations follow a left - handed convention.
void TrapezoidPrism::draw() { 
	double front = -depth / 2;
	double back = depth / 2;
	double top = height;
	double top_left = (a_length / 2) - (a_length - a_offset - b_length);
	double top_right = -((a_length / 2) - a_offset);
	double bottom = 0;
	double bottom_left = a_length / 2;
	double bottom_right = -a_length / 2;
	
	glPushMatrix(); // Places the shape to be defined on top of the stack.
	positionInGL(); // When called, changes the position of the coordinate axes to the values that have been set.
	setColorInGL(); // When called, changes the colour of the prism to the values that have been set.

		// Draw the front face.
		glPushMatrix(); // Places the surface to be defined on top of the stack.
			glBegin(GL_QUADS);
				// Defines vertices to enclose a shape, order of defining vertices matters.
				// The OpenGL functions 'trace' the outline of the surface using the defined vertices.
				glVertex3d(top_left, top, front);
				glVertex3d(bottom_left, bottom, front);
				glVertex3d(bottom_right, bottom, front);
				glVertex3d(top_right, top, front);
			glEnd();
		glPopMatrix(); // Pops the defined surface off the stack, will reset origin.	
	
		// Draw the back face.
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3d(top_left, top, back);
				glVertex3d(bottom_left, bottom, back);
				glVertex3d(bottom_right, bottom, back);
				glVertex3d(top_right, top, back);
			glEnd();
		glPopMatrix(); 

		// Draw the top face.
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3d(top_left, top, front);
				glVertex3d(top_left, top, back);
				glVertex3d(top_right, top, back);
				glVertex3d(top_right, top, front);
			glEnd();
		glPopMatrix();

		// Draw the bottom face.
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3d(bottom_left, bottom, front);
				glVertex3d(bottom_left, bottom, back);
				glVertex3d(bottom_right, bottom, back);
				glVertex3d(bottom_right, bottom, front);
			glEnd();
		glPopMatrix();

		// Draw the left face.
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3d(top_left, top, front);
				glVertex3d(top_left, top, back);
				glVertex3d(bottom_left, bottom, back);
				glVertex3d(bottom_left, bottom, front);
			glEnd();
		glPopMatrix();

		// Draw the right face.
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3d(top_right, top, front);
				glVertex3d(top_right, top, back);
				glVertex3d(bottom_right, bottom, back);
				glVertex3d(bottom_right, bottom, front);
			glEnd();
		glPopMatrix();
	glPopMatrix(); // Pops the defined shape off the stack, will reset origin.
}

// Functions below are used to set new dimensions for a trapezoidal prism if required (for example, when drawing other 
// vehicles from the server).
void TrapezoidPrism::setA_length(double Bottom_length) {
	a_length = Bottom_length;
}

void TrapezoidPrism::setB_length(double Top_length) {
	b_length = Top_length;
}

void TrapezoidPrism::setHeight(double Height) {
	height = Height;
}

void TrapezoidPrism::setDepth(double Depth) {
	depth = Depth;
}

void TrapezoidPrism::setA_offset(double Offset) {
	a_offset = Offset;
}

// Functions below are used to obtain the dimensions of a locally instantiated trapezoidal prism to be sent to the server. 
double TrapezoidPrism::getA_length() {
	return a_length;
}

double TrapezoidPrism::getB_length() {
	return b_length;
}

double TrapezoidPrism::getHeight() {
	return height;
}

double TrapezoidPrism::getDepth() {
	return depth;
}

double TrapezoidPrism::getA_offset() {
	return a_offset;
}