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
	// Move to the vehicle�s local frame of reference.
	glPushMatrix();
		positionInGL();

			// Instantiate the shapes that were derived from the shape class and draw the shapes relative to the vehicle's
			// local frame of reference. Each shape was given a name to represent their function/location on the vehicle.
			RectangularPrism Body(0, 0, 0, 90, 2, 2, 4);
			Body.draw();
			TriangularPrism Bumper(3, 0, 0, 0, 2, 2, 2, 90);
			Bumper.draw();
			TrapezoidPrism Spoiler(-2, 2, 0, 0, 2, 2, 1, 2, 1);
			Spoiler.draw();


			// Set the rotation of the front wheels about their respective y - axes to be equal to the steering angle.
			Cylinder FrontWheelLeft(1, 0, -1, getSteering(), 0.75, 1, (x / 0.75)*(180 / 3.14));
			FrontWheelLeft.draw();
			Cylinder FrontWheelRight(1, 0, 1, getSteering(), 0.75, 1,0);
			FrontWheelRight.draw();
			Cylinder BackWheelLeft(-1, 0, -1, 0, 0.75, 1,0);
			BackWheelLeft.draw();
			Cylinder BackWheelRight(-1, 0, 1, 0, 0.75, 1,0);
			BackWheelRight.draw();
			
			// Check if the vehicle is moving forward or backward. If yes, set that the cylinders representing the wheels
			// are rotating using the variable 'isRotating' in 'Cylinder.h'.
			if (getSpeed() != 0) {
				FrontWheelLeft.setIfRotating();
				FrontWheelRight.setIfRotating();
				BackWheelLeft.setIfRotating();
				BackWheelRight.setIfRotating();
			}




			// Check if the vehicle is steering left or right. If yes, set that the cylinders representing the front wheels
			// are steering using the variable 'isSteering' in 'Cylinder.h'.
			if (getSteering() != 0) {
				FrontWheelLeft.setIfSteering();
				FrontWheelRight.setIfSteering();
			}
			// *** NEED TO IMPLEMENT 
			// Check if the vehicle is moving. If yes, rotate all the wheels about their respective z - axes according to 
			// the direction that the vehicle is accelerating in.
			/*isRotating = false;
			double i = 0.0;
			TriangularPrism T2(45, 0, 0, i, 5, 5, 5, 60);
			if (speed != 0) {
				isRotating = true;
			}
			else {
				isRotating = false;
			}
			while (isRotating) {
				if (speed > 0.0) {
					for (i; i < 360.0; i++) {
						if (i >= 360.0) {
							i = 0.0;
						}
					}
				}
				else if (speed < 0.0) {
					if (speed < 0.0) {
						for (i; i > 0.0; i--) {
							if (i <= 0.0) {
								i = 0.0;
							}
						}
					}
				}
			}
			T2.draw();*/
	// Move back to global frame of reference.
	glPopMatrix();
}