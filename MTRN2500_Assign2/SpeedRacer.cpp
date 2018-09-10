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

			/*RectangularPrism *rect = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
			SpeedRacer::addShape(rect);

			TriangularPrism *tri = new TriangularPrism(3, 0, 0, 0, 2, 2, 2, 90);
			SpeedRacer::addShape(tri);

			TrapezoidPrism *trap = new TrapezoidPrism(-2, 2, 0, 180, 2, 2, 1, 2, 1);
			SpeedRacer::addShape(trap);

			Cylinder *cyl = new Cylinder(1, 0, -1, steering, 0.75, 1);
			SpeedRacer::addShape(cyl);

			cyl = new Cylinder(1, 0, 1, steering, 0.75, 1);
			SpeedRacer::addShape(cyl);

			cyl = new Cylinder(-1, 0, -1, 0, 0.75, 1);
			SpeedRacer::addShape(cyl);

			cyl = new Cylinder(-1, 0, 1, 0, 0.75, 1);
			SpeedRacer::addShape(cyl);*/

			for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
				(*it)->draw();
			}
			//shapes.clear();

	// Move back to global frame of reference.
	glPopMatrix();
}