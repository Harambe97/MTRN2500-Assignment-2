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
	// Move to the vehicle’s local frame of reference.
	glPushMatrix();
		positionInGL();
			// Instantiate the shapes that were derived from the shape class and draw the shapes relative to the vehicle's
			// local frame of reference. Each shape was given a name to represent their function/location on the vehicle.
			RectangularPrism Body(0, 0, 0, 90, 2, 2, 4);
			Body.draw();
			TriangularPrism Bumper(3, 0, 0, 180, 2, 2, 2, 90);
			Bumper.draw();
			TrapezoidPrism Spoiler(-2, 2, 0, 0, 2, 2, 1, 2, 1);
			Spoiler.draw();

			// Draw the front wheels of the vehicle.
			Cylinder FrontWheelLeft(1, 0, -1, 0, 0.75, 1);
			FrontWheelLeft.draw();
			Cylinder FrontWheelRight(1, 0, 1, 0, 0.75, 1);
			FrontWheelRight.draw();

			// *** NEED TO IMPLEMENT
			// Check if the vehicle is steering. If yes, rotate the front wheels about their respective y - axes.
			if (steering != 0) {
				FrontWheelLeft.setRotation(steering);
				FrontWheelRight.setRotation(steering);
			}

			// Draw the back wheels of the vehicle.
			Cylinder BackWheelLeft(-1, 0, -1, 0, 0.75, 1);
			BackWheelLeft.draw();
			Cylinder BackWheelRight(-1, 0, 1, 0, 0.75, 1);
			BackWheelRight.draw();

			// *** NEED TO IMPLEMENT 
			// Check if the car is moving. If yes, rotate all the wheels about their respective z - axes.
			if (speed != 0) {
				
			}

	// Move back to global frame of reference.
	glPopMatrix();
}