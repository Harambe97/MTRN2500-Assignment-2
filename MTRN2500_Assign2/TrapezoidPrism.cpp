#include "TrapezoidPrism.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif

TrapezoidPrism::TrapezoidPrism(double Bottom_length, double Top_length, double Height, double Depth, double offset) {
	a_length = Bottom_length;
	b_length = Top_length;
	height = Height;
	depth = Depth;
	a_offset = offset;
}

// Define the front, back, top, bottom and corners of the trapezoid using geometry and draw the trapezoid.
// Take note that the coordinate axes follow a left - handed convention, not a right - handed convention.
void TrapezoidPrism::draw() { 
	double front = -depth / 2;
	double back = depth / 2;
	double top = height;
	double top_left = (a_length / 2) - a_offset;
	double top_right = -((a_length / 2) - (a_length - a_offset - b_length));
	double bottom = 0;
	double bottom_left = a_length / 2;
	double bottom_right = -a_length / 2;
	
	// Draw the front face.
	glPushMatrix(); // Places the defined shape on top of the stack
		glBegin(GL_QUADS);
			// Defines vertices to enclose a shape, order of defining vertices matters.
			// The OpenGL functions 'trace' the outline of the surface using the defined vertices.
			glVertex3d(top_left, top, front);
			glVertex3d(bottom_left, bottom, front);
			glVertex3d(bottom_right, bottom, front);
			glVertex3d(top_right, top, front);
		glEnd();
	glPopMatrix(); // Pops the defined shape off the stack, will reset origin	
	
	// Draw the back face
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex3d(top_left, top, back);
			glVertex3d(bottom_left, bottom, back);
			glVertex3d(bottom_right, bottom, back);
			glVertex3d(top_right, top, back);
		glEnd();
	glPopMatrix(); 

	// Draw the top face of the trapezoid.
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex3d(top_left, top, front);
			glVertex3d(top_left, top, back);
			glVertex3d(top_right, top, back);
			glVertex3d(top_right, top, front);
		glEnd();
	glPopMatrix();

	// Draw the bottom face
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
}