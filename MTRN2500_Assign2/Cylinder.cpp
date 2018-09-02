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
	red = 1.0;
	blue = 0.5;
	green = 1.0;
	
	radius = Radius;
	depth = Depth;
}

// Take note that the coordinate axes and rotations follow a left - handed convention.
void Cylinder::draw() {
	static GLUquadric * CylinderQuadric = gluNewQuadric();

	// Draw the curved surface.
	glPushMatrix(); // Places the defined shape on top of the stack.
		positionInGL(); // When called, changes the position of the coordinate axes to the values that have been set.
		setColorInGL(); // When called, changes the colour of the cylinder to the values that have been set.
		glTranslated(0, radius, -depth / 2); // Set the cylinder to rest with its circumference on the 'floor' of the
											 // digital world, halfway along its depth.
		gluCylinder(CylinderQuadric, radius, radius, depth, 20, 1); // Draw using the in - built OpenGL cylinder function.
	glPopMatrix(); // Pops the defined shape off the stack, will reset origin.

    // Draw the front face.
	glPushMatrix(); 
		positionInGL(); 
		setColorInGL(); 
		glTranslated(0, radius, -depth / 2); // Set the front face to rest with its circumference on the 'floor' of the 
											 // digital world. Similarly done for the back face of the cylinder.
		gluDisk(CylinderQuadric, 0, radius, 20, 1); // Draw using the in - built OpenGL disk function.
	glPopMatrix();

	// Draw the back face.
	glPushMatrix();
		positionInGL();
		setColorInGL();
		glTranslated(0, radius, depth / 2);
		gluDisk(CylinderQuadric, 0, radius, 20, 1);
	glPopMatrix();
}