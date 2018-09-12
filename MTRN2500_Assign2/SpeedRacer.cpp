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

// Code written by: Haydn St. James (z5118383)

// Default constructor for the custom vehicle that sends the dimensions of the vehicle to the server and adds defined
// shapes to the shape vector to instantiate a local custom vehicle.
SpeedRacer::SpeedRacer() {
	
	// Any shapes to be sent to the server follow the same procedure as the rectangular prism below:

	// Send the body of the vehicle to the server.
	// Create a pointer to the instantiated shape to be sent to the server.
	// Add the instantiated shape to the shape vector defined in 'Vehicle.hpp'.
	RectangularPrism * rect = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
	addShape(rect);

	// Instantiate 'ShapeInit' to send information to the 'ShapeInit' data structure defined in 'Messages.hpp'.
	ShapeInit myVehicleShape;

	// Send the type of the previously instantiated shape to the server.
	myVehicleShape.type = RECTANGULAR_PRISM;

	// Send the position of the previously instantiated shape to the server.
	myVehicleShape.xyz[0] = rect->getX();
	myVehicleShape.xyz[1] = rect->getY();
	myVehicleShape.xyz[2] = rect->getZ();
	myVehicleShape.rotation = rect->getRotation();

	// Send the colour of the previously instantiated shape to the server.
	myVehicleShape.rgb[0] = rect->getRed();
	myVehicleShape.rgb[1] = rect->getGreen();
	myVehicleShape.rgb[2] = rect->getBlue();

	// Send the dimensions of the previously instantiated shape to the server.
	myVehicleShape.params.rect.xlen = rect->getX_length();
	myVehicleShape.params.rect.ylen = rect->getY_length();
	myVehicleShape.params.rect.zlen = rect->getZ_length();

	// Add the previously instantiated shape to the 'ShapeInit' vector in the 'VehicleModel' data structure 
	// defined in 'Messages.hpp'.
	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the bumper of the vehicle to the server.
	TriangularPrism * tri = new TriangularPrism(3, 0, 0, 0, 2, 2, 2, 90);
	addShape(tri);

	myVehicleShape.type = TRIANGULAR_PRISM;
	myVehicleShape.xyz[0] = tri->getX();
	myVehicleShape.xyz[1] = tri->getY();
	myVehicleShape.xyz[2] = tri->getZ();
	myVehicleShape.rotation = tri->getRotation();

	myVehicleShape.rgb[0] = tri->getRed();
	myVehicleShape.rgb[1] = tri->getGreen();
	myVehicleShape.rgb[2] = tri->getBlue();

	myVehicleShape.params.tri.alen = tri->getA_length();
	myVehicleShape.params.tri.angle = tri->getTheta();
	myVehicleShape.params.tri.blen = tri->getB_length();
	myVehicleShape.params.tri.depth = tri->getDepth();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the spoiler of the vehicle to the server.
	TrapezoidPrism * trap = new TrapezoidPrism(-2, 2, 0, 180, 2, 2, 1, 2, 1);
	addShape(trap);

	myVehicleShape.type = TRAPEZOIDAL_PRISM;
	myVehicleShape.xyz[0] = trap->getX();
	myVehicleShape.xyz[1] = trap->getY();
	myVehicleShape.xyz[2] = trap->getZ();
	myVehicleShape.rotation = trap->getRotation();

	myVehicleShape.rgb[0] = trap->getRed();
	myVehicleShape.rgb[1] = trap->getGreen();
	myVehicleShape.rgb[2] = trap->getBlue();

	myVehicleShape.params.trap.alen = trap->getA_length();
	myVehicleShape.params.trap.aoff = trap->getA_offset();
	myVehicleShape.params.trap.blen = trap->getB_length();
	myVehicleShape.params.trap.depth = trap->getDepth();
	myVehicleShape.params.trap.height = trap->getHeight();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the front left wheel to the server.
	Cylinder * cyl = new Cylinder(1, 0, -1, 0, 0.75, 1);
	addShape(cyl);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = cyl->getX();
	myVehicleShape.xyz[1] = cyl->getY();
	myVehicleShape.xyz[2] = cyl->getZ();
	myVehicleShape.rotation = cyl->getRotation();

	myVehicleShape.rgb[0] = cyl->getRed();
	myVehicleShape.rgb[1] = cyl->getGreen();
	myVehicleShape.rgb[2] = cyl->getBlue();

	myVehicleShape.params.cyl.depth = cyl->getDepth();
	myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
	myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
	myVehicleShape.params.cyl.radius = cyl->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the front right wheel to the server.
	cyl = new Cylinder(1, 0, 1, 0, 0.75, 1);
	addShape(cyl);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = cyl->getX();
	myVehicleShape.xyz[1] = cyl->getY();
	myVehicleShape.xyz[2] = cyl->getZ();
	myVehicleShape.rotation = cyl->getRotation();

	myVehicleShape.rgb[0] = cyl->getRed();
	myVehicleShape.rgb[1] = cyl->getGreen();
	myVehicleShape.rgb[2] = cyl->getBlue();

	myVehicleShape.params.cyl.depth = cyl->getDepth();
	myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
	myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
	myVehicleShape.params.cyl.radius = cyl->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the back left wheel to the server.
	cyl = new Cylinder(-1, 0, -1, 0, 0.75, 1);
	addShape(cyl);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = cyl->getX();
	myVehicleShape.xyz[1] = cyl->getY();
	myVehicleShape.xyz[2] = cyl->getZ();
	myVehicleShape.rotation = cyl->getRotation();

	myVehicleShape.rgb[0] = cyl->getRed();
	myVehicleShape.rgb[1] = cyl->getGreen();
	myVehicleShape.rgb[2] = cyl->getBlue();

	myVehicleShape.params.cyl.depth = cyl->getDepth();
	myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
	myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
	myVehicleShape.params.cyl.radius = cyl->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the back right wheel to the server.
	cyl = new Cylinder(-1, 0, 1, 0, 0.75, 1);
	addShape(cyl);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = cyl->getX();
	myVehicleShape.xyz[1] = cyl->getY();
	myVehicleShape.xyz[2] = cyl->getZ();
	myVehicleShape.rotation = cyl->getRotation();

	myVehicleShape.rgb[0] = cyl->getRed();
	myVehicleShape.rgb[1] = cyl->getGreen();
	myVehicleShape.rgb[2] = cyl->getBlue();

	myVehicleShape.params.cyl.depth = cyl->getDepth();
	myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
	myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
	myVehicleShape.params.cyl.radius = cyl->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);
}

// Overload constructor to instantiate remote vehicles from the server.
SpeedRacer::SpeedRacer(VehicleModel * RemoteVehicles) {
	
	// Iterate through the 'ShapeInit' vector defined in 'Messages.hpp' to obtain information about vehicles in the server.
	for (std::vector<ShapeInit>::iterator it = RemoteVehicles->shapes.begin(); it != RemoteVehicles->shapes.end(); it++) {
		if (it->type == RECTANGULAR_PRISM) {

			// Create a pointer to access information about the current vehicle and the shapes used to define it from 
			// the server.
			RectangularPrism * rect = new RectangularPrism(0, 0, 0, 0, 0, 0, 0);

			// Set the dimensions of the obtained shape to what was given by a user.
			rect->setX_length(it->params.rect.xlen);
			rect->setY_length(it->params.rect.ylen);
			rect->setZ_length(it->params.rect.zlen);

			// Set the colour of the obtained shape to what was given by a user.
			rect->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

			// Set the position of the obtained shape to what was given by a user.
			rect->setX(it->xyz[0]);
			rect->setY(it->xyz[1]);
			rect->setZ(it->xyz[2]);
			rect->setRotation(it->rotation);

			// Add the newly defined shape to be drawn into the shape vector defined in 'Vehicle.hpp'
			addShape(rect);
		}
		else if (it->type == TRIANGULAR_PRISM) {
			TriangularPrism * tri = new TriangularPrism(0, 0, 0, 0, 0, 0, 0, 0);

			tri->setA_length(it->params.tri.alen);
			tri->setTheta(it->params.tri.angle);
			tri->setB_length(it->params.tri.blen);
			tri->setDepth(it->params.tri.depth);

			tri->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

			tri->setX(it->xyz[0]);
			tri->setY(it->xyz[1]);
			tri->setZ(it->xyz[2]);
			tri->setRotation(it->rotation);

			addShape(tri);
		}
		else if (it->type == TRAPEZOIDAL_PRISM) {
			TrapezoidPrism * trap = new TrapezoidPrism(0, 0, 0, 0, 0, 0, 0, 0, 0);

			trap->setA_length(it->params.trap.alen);
			trap->setA_offset(it->params.trap.aoff);
			trap->setB_length(it->params.trap.blen);
			trap->setDepth(it->params.trap.depth);
			trap->setHeight(it->params.trap.height);

			trap->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

			trap->setX(it->xyz[0]);
			trap->setY(it->xyz[1]);
			trap->setZ(it->xyz[2]);
			trap->setRotation(it->rotation);

			addShape(trap);
		}
		else if (it->type == CYLINDER) {
			Cylinder * cyl = new Cylinder(0, 0, 0, 0, 0, 0);

			cyl->setRadius(it->params.cyl.radius);
			cyl->setDepth(it->params.cyl.depth);
			cyl->setIfRolling(it->params.cyl.isRolling);
			cyl->setIfSteering(it->params.cyl.isSteering);

			cyl->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

			cyl->setX(it->xyz[0]);
			cyl->setY(it->xyz[1]);
			cyl->setZ(it->xyz[2]);
			cyl->setRotation(it->rotation);

			addShape(cyl);
		}
	}
}

// Iterate through the shape vector defined in 'Vehicle.hpp' and draw all the shapes contained in the vector.
void SpeedRacer::draw() {
	
	// Move to the vehicle’s local frame of reference.
	glPushMatrix();
		positionInGL();

			// Variable to check how many wheels were found in the shape vector.
			int numWheels = 0;

			for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
				
				// Dynamic cast the iterator to be a pointer of type cylinder.
				Cylinder * cyl = dynamic_cast<Cylinder *>(*it);
				
				if (cyl != NULL) {
					
					// Check that the dynamic cast succeeded and set the rotations of the 2 front wheels to be equal to 
					// the steering angle if the steering angle is non - zero.
					if (steering != 0) {
						if (numWheels < 2) {
							cyl->setIfSteering(true);
							cyl->setRotation(steering);
							numWheels++;
						}
					}
					else {
						cyl->setIfSteering(false);
					}

					// Similarly, check if the speed is non - zero. If yes, allow the wheels to roll.
					// ** NEED TO IMPLEMENT
					if (speed != 0) {
						cyl->setIfRolling(true);
					}
					else {
						cyl->setIfRolling(false);
					}
				}
				(*it)->draw();
			}

	// Move back to global frame of reference.
	glPopMatrix();
}

// Obtain the memory address for the vehicle model of 'SpeedRacer' and return the address. 
VehicleModel * SpeedRacer::getCustomVehicleModel() {
	return &CustomVehicle;
}