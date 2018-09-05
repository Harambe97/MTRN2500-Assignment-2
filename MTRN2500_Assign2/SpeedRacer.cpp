#include "SpeedRacer.h"
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidPrism.h"
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

// Code written by: Haydn St. James (z5118383) & Mei Yan Tang (z5129009)

// The constructor for 'SpeedRacer' uses the variables in the 'Shape' class to determine the position and orientation of 
// an instantiated 'SpeedRacer' object.
SpeedRacer::SpeedRacer(double x_, double y_, double z_, double rotation_) {
	x = x_;
	y = y_;
	z = z_;
	rotation = rotation_;
}

void SpeedRacer::draw() {
	/*// move to the vehicle’s local frame of reference
	glPushMatrix();
	positionInGL();
		glTranslated(-30, 0, 0);
		TrapezoidPrism Prism1(0, 0, 0, 0, 4, 2, 2, 2, 1);
		Cylinder C1(0, 0, 0, 0, 1, 3);
		addShape(&Prism1);
		addShape(&C1);
		for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
			(*it)->draw();
		}
	// move back to global frame of reference
	glPopMatrix();*/

	// Move to the vehicle’s local frame of reference.
	glPushMatrix();
		positionInGL();
			// Instantiate the shapes that were derived from the shape class and draw the shapes relative to the vehicle's
			// local frame of reference.
			RectangularPrism R1(0, 0, 0, 90, 2, 2, 4);
			R1.draw();
			TriangularPrism T1(3, 0, 0, 180, 2, 2, 2, 90);
			T1.draw();
			TrapezoidPrism Trap1(-2, 2, 0, 0, 2, 2, 1, 2, 1);
			Trap1.draw();
			Cylinder C1(1, 0, 0, 0, 1, 3);
			C1.draw();
			Cylinder C2(-2, 0, 0, 0, 1, 3);
			C2.draw();
	// Move back to global frame of reference.
	glPopMatrix();
}