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
Cylinder::Cylinder(double x_, double y_, double z_, double rotation_, double Radius, double Depth, double zRotate):Shape(x_, y_, z_, rotation_) {
	radius = Radius;
	depth = Depth;
	z_Rotate = zRotate;
}

// Take note that the coordinate axes and rotations follow a left - handed convention.
void Cylinder::draw() {
	//double newAngle = 0;
	//double i = 0;

	static GLUquadric * CylinderQuadric = gluNewQuadric();
	
	glPushMatrix(); // Places the shape to be defined on top of the stack.
	positionInGL(); // When called, changes the position of the coordinate axes to the values that have been set.
	setColorInGL(); // When called, changes the colour of the cylinder to the values that have been set.
	glRotated(z_Rotate, 0, 0, 1); //makes it rotate in z axis

		// Draw the curved surface.
		glPushMatrix(); // Places the surface to be defined on top of the stack.
			glTranslated(0, radius, -depth / 2); // Set the cylinder to rest with its circumference on the 'floor' of the
												 // digital world, halfway along its depth at the origin of the coordinate axes.
			gluCylinder(CylinderQuadric, radius, radius, depth, 20, 1); // Draw using the in - built OpenGL cylinder function.
		glPopMatrix(); // Pops the defined surface off the stack, will reset origin.

		// Draw the front face.
		glPushMatrix(); 
			glTranslated(0, radius, -depth / 2); // Set the front face to rest with its circumference on the 'floor' of the 
												 // digital world. Similarly done for the back face of the cylinder.
			gluDisk(CylinderQuadric, 0, radius, 20, 1); // Draw using the in - built OpenGL disk function.
		glPopMatrix();

		// Draw the back face.
		glPushMatrix();
			glTranslated(0, radius, depth / 2);
			gluDisk(CylinderQuadric, 0, radius, 20, 1);
		glPopMatrix();
	glPopMatrix(); // Pops the defined shape off the stack, will reset origin.
}

// Sets the Boolean variable that defines the rotation of the cylinder about its z - axis to be true.
bool Cylinder::setIfRotating() {
	return isRotating = true;
}

// Sets the Boolean variable that defines the rotation of the cylinder about its y - axis to be true.
bool Cylinder::setIfSteering() {
	return isSteering = true;
}
