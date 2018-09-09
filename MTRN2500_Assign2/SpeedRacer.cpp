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

// Iterate through the shape vector defined in 'Vehicle.hpp' and draw all the shapes contained in the vector.
void SpeedRacer::draw() {
	// Move to the vehicle’s local frame of reference.
	glPushMatrix();
		positionInGL();

			// Instantiate the shapes that were derived from the shape class and draw the shapes relative to the vehicle's
			// local frame of reference. Each shape was given a name to represent their function/location on the vehicle.
			/*RectangularPrism Body(0, 0, 0, 90, 2, 2, 4);
			Body.draw();
			TriangularPrism Bumper(3, 0, 0, 0, 2, 2, 2, 90);
			Bumper.draw();
			TrapezoidPrism Spoiler(-2, 2, 0, 0, 2, 2, 1, 2, 1);
			Spoiler.draw();

			// Set the rotation of the front wheels about their respective y - axes to be equal to the steering angle.
			Cylinder FrontWheelLeft(1, 0, -1, steering, 0.75, 1);
			FrontWheelLeft.draw();
			Cylinder FrontWheelRight(1, 0, 1, steering, 0.75, 1);
			FrontWheelRight.draw();
			Cylinder BackWheelLeft(-1, 0, -1, 0, 0.75, 1);
			BackWheelLeft.draw();
			Cylinder BackWheelRight(-1, 0, 1, 0, 0.75, 1);
			BackWheelRight.draw();*/

			/*Shape * newShape = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
			// Dynamic cast to convert from shape pointer into the respective shape pointer.
			RectangularPrism *rect = dynamic_cast<RectangularPrism*>(newShape);
			SpeedRacer::addShape(rect);

			newShape = new TriangularPrism (3, 0, 0, 0, 2, 2, 2, 90);
			TriangularPrism *tri = dynamic_cast<TriangularPrism*>(newShape);
			SpeedRacer::addShape(tri);

			newShape = new TrapezoidPrism(-2, 2, 0, 0, 2, 2, 1, 2, 1);
			TrapezoidPrism *trap = dynamic_cast<TrapezoidPrism*>(newShape);
			SpeedRacer::addShape(trap);

			newShape = new Cylinder(1, 0, -1, steering, 0.75, 1);
			Cylinder *cyl = dynamic_cast<Cylinder*>(newShape);
			SpeedRacer::addShape(cyl);

			newShape = new Cylinder(1, 0, 1, steering, 0.75, 1);
			cyl = dynamic_cast<Cylinder*>(newShape);
			SpeedRacer::addShape(cyl);

			newShape = new Cylinder(-1, 0, -1, 0, 0.75, 1);
			cyl = dynamic_cast<Cylinder*>(newShape);
			SpeedRacer::addShape(cyl);

			newShape = new Cylinder(-1, 0, 1, 0, 0.75, 1);
			cyl = dynamic_cast<Cylinder*>(newShape);
			SpeedRacer::addShape(cyl);*/

			for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
				(*it)->draw();
			}
			
			// Check if the vehicle is moving forward or backward. If yes, set that the cylinders representing the wheels
			// are rotating using the variable 'isRotating' in 'Cylinder.h'.
			/*if (speed != 0) {
				FrontWheelLeft.setIfRotating(true);
				FrontWheelRight.setIfRotating(true);
				BackWheelLeft.setIfRotating(true);
				BackWheelRight.setIfRotating(true);
			}
			else {
				FrontWheelLeft.setIfRotating(false);
				FrontWheelRight.setIfRotating(false);
				BackWheelLeft.setIfRotating(false);
				BackWheelRight.setIfRotating(false);
			}

			// Check if the vehicle is steering left or right. If yes, set that the cylinders representing the front wheels
			// are steering using the variable 'isSteering' in 'Cylinder.h'.
			if (steering != 0) {
				FrontWheelLeft.setIfSteering(true);
				FrontWheelRight.setIfSteering(true);
			}
			else {
				FrontWheelLeft.setIfSteering(false);
				FrontWheelRight.setIfSteering(false);
			}*/

	// Move back to global frame of reference.
	glPopMatrix();
}