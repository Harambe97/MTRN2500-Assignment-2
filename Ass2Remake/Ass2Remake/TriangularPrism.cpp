#include "TriangularPrism.h"
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

//uses variables outlined from the specifications of shape found in Moodle.
//length_d represents the depth of the triangular prism.
TriangularPrism::TriangularPrism(double x_, double y_, double z_, double rotation_, double length_a, double length_b, double length_d, double angle):Shape(x_,y_,z_, rotation_) {
	
	a_length = length_a;
	b_length = length_b;
	depth = length_d;
	theta = angle;
}

//Note that the coordinate axes follow a left - handed convention.
void TriangularPrism::draw() {

	//to convert degrees to radians
	double degree = theta * (3.14159265358979323846264338327950/180); 
	//to calculate the height of the triangle
	double height = b_length*sin(degree);
	//to calculate the x coordinate for the third point.
	double front = (a_length / 2) - height * cos(degree);

	//front face
	glPushMatrix(); //pushes the current matrix stack down by one, duplicating the current matrix
	positionInGL(); //sets the position
	setColorInGL(); //sets the colour
	glBegin(GL_TRIANGLES); //defines an enclosed shape with 3 vertices
		glVertex3f(a_length/2, 0, -depth/2);
		glVertex3f(-a_length/2, 0, -depth/2);
		glVertex3f(front, height, -depth/2);
	glEnd();
	glPopMatrix(); //pops the current matrix stack, replacing the current matrix with the one below it on the stack.

	//back face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_TRIANGLES);
		glVertex3f(a_length / 2, 0, depth / 2);
		glVertex3f(-a_length / 2, 0, depth / 2);
		glVertex3f(front, height, depth / 2);
	glEnd();
	glPopMatrix();

	//right face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(a_length / 2, 0, -depth / 2);
		glVertex3f(front, height, -depth / 2);
		glVertex3f(front, height, depth / 2);
		glVertex3f(a_length / 2, 0, depth / 2);
	glEnd();
	glPopMatrix();


	//left face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(-a_length / 2, 0, -depth / 2);
		glVertex3f(front, height, -depth / 2);
		glVertex3f(front, height, depth / 2);
		glVertex3f(-a_length / 2, 0, depth / 2);
	glEnd();
	glPopMatrix();

	//bottom face
	glPushMatrix();
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);
		glVertex3f(a_length / 2, 0, -depth / 2);
		glVertex3f(-a_length / 2, 0, -depth / 2);
		glVertex3f(-a_length / 2, 0, depth / 2);
		glVertex3f(a_length / 2, 0, depth / 2);
	glEnd();
	glPopMatrix();



}
