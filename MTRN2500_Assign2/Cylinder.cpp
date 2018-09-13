#include "Cylinder.h"

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

// Utilises the constructor in the 'Shape' class to determine if the cylinder is to be translated or rotated.
// Works similarly to the 'Obstacle' class.
// Uses the variables outlined in the server specifications for shapes, which can be found on the Moodle page of MTRN2500.
Cylinder::Cylinder(double x_, double y_, double z_, double rotation_, double Radius, double Depth):Shape(x_, y_, z_, rotation_) {
	radius = Radius;
	depth = Depth;
	isRolling = false;
	isSteering = false;
}

// Take note that the coordinate axes and rotations follow a left - handed convention.
void Cylinder::draw() {
	static GLUquadric * CylinderQuadric = gluNewQuadric();
	
	glPushMatrix(); // Places the shape to be defined on top of the stack.
	positionInGL(); // When called, changes the position of the coordinate axes to the values that have been set.
	setColorInGL(); // When called, changes the colour of the cylinder to the values that have been set.

		// Draw the curved surface.
		glPushMatrix(); // Places the surface to be defined on top of the stack.
			glTranslated(0, radius, -depth / 2); // Set the cylinder to rest with its circumference on the 'floor' of the
												 // digital world, halfway along its depth at the origin of the coordinate axes.
			gluCylinder(CylinderQuadric, radius, radius, depth, 6, 1); // Draw using the in - built OpenGL cylinder function.
		glPopMatrix(); // Pops the defined surface off the stack, will reset origin.

		// Draw the front face.
		glPushMatrix(); 
			glTranslated(0, radius, -depth / 2); // Set the front face to rest with its circumference on the 'floor' of the 
												 // digital world. Similarly done for the back face of the cylinder.
			gluDisk(CylinderQuadric, 0, radius, 6, 1); // Draw using the in - built OpenGL disk function.
		glPopMatrix();

		// Draw the back face.
		glPushMatrix();
			glTranslated(0, radius, depth / 2);
			gluDisk(CylinderQuadric, 0, radius, 6, 1);
		glPopMatrix();
	glPopMatrix(); // Pops the defined shape off the stack, will reset origin.
}

// Functions below are used to set new dimensions for a cylinder if required (for example, when drawing other 
// vehicles from the server).
void Cylinder::setRadius(double Radius) {
	radius = Radius;
}

void Cylinder::setDepth(double Depth) {
	depth = Depth;
}

// Functions below are used to set the rolling and steering of cylinders used to define the wheels of a vehicle if required
// (for example, when drawing other vehicles from the server).
void Cylinder::setIfRolling(bool Rolling) {
	isRolling = Rolling;
}

void Cylinder::setIfSteering(bool Steering) {
	isSteering = Steering;
}

// Functions below are used to obtain the dimensions of a locally instantiated cylinder to be sent to the server. 
double Cylinder::getRadius() {
	return radius;
}

double Cylinder::getDepth() {
	return depth;
}

// Functions below are used to obtain the steering and rolling of cylinders used to define the wheels of a vehicle to be
// sent to the server.
bool Cylinder::getIfRolling() {
	return isRolling;
}

bool Cylinder::getIfSteering() {
	return isSteering;
}