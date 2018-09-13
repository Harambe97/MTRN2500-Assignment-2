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

#define SCALING_FACTOR 4.0

// Code written by: Haydn St. James (z5118383) & Mei Yan Tang (z5129009)

// Default constructor for the custom vehicle that sends the dimensions of the vehicle to the server and adds defined
// shapes to the shape vector to instantiate a local custom vehicle.
SpeedRacer::SpeedRacer() {
	
	// Any shapes to be sent to the server follow the same procedure as the rectangular prism below:

	// Send the body of the vehicle to the server.
	// Create a pointer to the instantiated shape to be sent to the server.
	// Add the instantiated shape to the shape vector defined in 'Vehicle.hpp'.
	Body = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
	addShape(Body);

	// Instantiate 'ShapeInit' to send information to the 'ShapeInit' data structure defined in 'Messages.hpp'.
	ShapeInit myVehicleShape;

	// Send the type of the previously instantiated shape to the server.
	myVehicleShape.type = RECTANGULAR_PRISM;

	// Send the position of the previously instantiated shape to the server.
	myVehicleShape.xyz[0] = Body->getX();
	myVehicleShape.xyz[1] = Body->getY();
	myVehicleShape.xyz[2] = Body->getZ();
	myVehicleShape.rotation = Body->getRotation();

	// Send the colour of the previously instantiated shape to the server.
	myVehicleShape.rgb[0] = Body->getRed();
	myVehicleShape.rgb[1] = Body->getGreen();
	myVehicleShape.rgb[2] = Body->getBlue();

	// Send the dimensions of the previously instantiated shape to the server.
	myVehicleShape.params.rect.xlen = Body->getX_length();
	myVehicleShape.params.rect.ylen = Body->getY_length();
	myVehicleShape.params.rect.zlen = Body->getZ_length();

	// Add the previously instantiated shape to the 'ShapeInit' vector in the 'VehicleModel' data structure 
	// defined in 'Messages.hpp'.
	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the bumper of the vehicle to the server.
	Bumper = new TriangularPrism(3, 0, 0, 0, 2, 2, 2, 90);
	addShape(Bumper);

	myVehicleShape.type = TRIANGULAR_PRISM;
	myVehicleShape.xyz[0] = Bumper->getX();
	myVehicleShape.xyz[1] = Bumper->getY();
	myVehicleShape.xyz[2] = Bumper->getZ();
	myVehicleShape.rotation = Bumper->getRotation();

	myVehicleShape.rgb[0] = Bumper->getRed();
	myVehicleShape.rgb[1] = Bumper->getGreen();
	myVehicleShape.rgb[2] = Bumper->getBlue();

	myVehicleShape.params.tri.alen = Bumper->getA_length();
	myVehicleShape.params.tri.angle = Bumper->getTheta();
	myVehicleShape.params.tri.blen = Bumper->getB_length();
	myVehicleShape.params.tri.depth = Bumper->getDepth();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the spoiler of the vehicle to the server.
	Spoiler = new TrapezoidPrism(-2, 2, 0, 180, 2, 2, 1, 2, 1);
	addShape(Spoiler);

	myVehicleShape.type = TRAPEZOIDAL_PRISM;
	myVehicleShape.xyz[0] = Spoiler->getX();
	myVehicleShape.xyz[1] = Spoiler->getY();
	myVehicleShape.xyz[2] = Spoiler->getZ();
	myVehicleShape.rotation = Spoiler->getRotation();

	myVehicleShape.rgb[0] = Spoiler->getRed();
	myVehicleShape.rgb[1] = Spoiler->getGreen();
	myVehicleShape.rgb[2] = Spoiler->getBlue();

	myVehicleShape.params.trap.alen = Spoiler->getA_length();
	myVehicleShape.params.trap.aoff = Spoiler->getA_offset();
	myVehicleShape.params.trap.blen = Spoiler->getB_length();
	myVehicleShape.params.trap.depth = Spoiler->getDepth();
	myVehicleShape.params.trap.height = Spoiler->getHeight();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the front left wheel to the server.
	FrontLeftWheel = new Cylinder(1, 0, -1, 0, 0.75, 1);
	addShape(FrontLeftWheel);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = FrontLeftWheel->getX();
	myVehicleShape.xyz[1] = FrontLeftWheel->getY();
	myVehicleShape.xyz[2] = FrontLeftWheel->getZ();
	myVehicleShape.rotation = FrontLeftWheel->getRotation();

	myVehicleShape.rgb[0] = FrontLeftWheel->getRed();
	myVehicleShape.rgb[1] = FrontLeftWheel->getGreen();
	myVehicleShape.rgb[2] = FrontLeftWheel->getBlue();

	myVehicleShape.params.cyl.depth = FrontLeftWheel->getDepth();
	myVehicleShape.params.cyl.isRolling = FrontLeftWheel->getIfRolling();
	myVehicleShape.params.cyl.isSteering = FrontLeftWheel->getIfSteering();
	myVehicleShape.params.cyl.radius = FrontLeftWheel->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the front right wheel to the server.
	FrontRightWheel = new Cylinder(1, 0, 1, 0, 0.75, 1);
	addShape(FrontRightWheel);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = FrontRightWheel->getX();
	myVehicleShape.xyz[1] = FrontRightWheel->getY();
	myVehicleShape.xyz[2] = FrontRightWheel->getZ();
	myVehicleShape.rotation = FrontRightWheel->getRotation();

	myVehicleShape.rgb[0] = FrontRightWheel->getRed();
	myVehicleShape.rgb[1] = FrontRightWheel->getGreen();
	myVehicleShape.rgb[2] = FrontRightWheel->getBlue();

	myVehicleShape.params.cyl.depth = FrontRightWheel->getDepth();
	myVehicleShape.params.cyl.isRolling = FrontRightWheel->getIfRolling();
	myVehicleShape.params.cyl.isSteering = FrontRightWheel->getIfSteering();
	myVehicleShape.params.cyl.radius = FrontRightWheel->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the back left wheel to the server.
	BackLeftWheel = new Cylinder(-1, 0, -1, 0, 0.75, 1);
	addShape(BackLeftWheel);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = BackLeftWheel->getX();
	myVehicleShape.xyz[1] = BackLeftWheel->getY();
	myVehicleShape.xyz[2] = BackLeftWheel->getZ();
	myVehicleShape.rotation = BackLeftWheel->getRotation();

	myVehicleShape.rgb[0] = BackLeftWheel->getRed();
	myVehicleShape.rgb[1] = BackLeftWheel->getGreen();
	myVehicleShape.rgb[2] = BackLeftWheel->getBlue();

	myVehicleShape.params.cyl.depth = BackLeftWheel->getDepth();
	myVehicleShape.params.cyl.isRolling = BackLeftWheel->getIfRolling();
	myVehicleShape.params.cyl.isSteering = BackLeftWheel->getIfSteering();
	myVehicleShape.params.cyl.radius = BackLeftWheel->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);

	// Send the back right wheel to the server.
	BackRightWheel = new Cylinder(-1, 0, 1, 0, 0.75, 1);
	addShape(BackRightWheel);

	myVehicleShape.type = CYLINDER;
	myVehicleShape.xyz[0] = BackRightWheel->getX();
	myVehicleShape.xyz[1] = BackRightWheel->getY();
	myVehicleShape.xyz[2] = BackRightWheel->getZ();
	myVehicleShape.rotation = BackRightWheel->getRotation();

	myVehicleShape.rgb[0] = BackRightWheel->getRed();
	myVehicleShape.rgb[1] = BackRightWheel->getGreen();
	myVehicleShape.rgb[2] = BackRightWheel->getBlue();

	myVehicleShape.params.cyl.depth = BackRightWheel->getDepth();
	myVehicleShape.params.cyl.isRolling = BackRightWheel->getIfRolling();
	myVehicleShape.params.cyl.isSteering = BackRightWheel->getIfSteering();
	myVehicleShape.params.cyl.radius = BackRightWheel->getRadius();

	CustomVehicle.shapes.push_back(myVehicleShape);
}

SpeedRacer::~SpeedRacer() {
	// Clear memory for shapes that were placed on the heap.
	delete Body;
	delete Bumper;
	delete Spoiler;
	delete FrontLeftWheel;
	delete FrontRightWheel;
	delete BackLeftWheel;
	delete BackRightWheel;

	ServerShapes.clear();
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

			// Store the pointer to the newly defined shape into a vector so that the memory for this newly defined shape
			// can be cleared once the program completes execution.
			ServerShapes.push_back(rect);
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
			ServerShapes.push_back(tri);
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
			ServerShapes.push_back(trap);
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
			ServerShapes.push_back(cyl);
		}
	}
}

// Iterate through the shape vector defined in 'Vehicle.hpp' and draw all the shapes contained in the vector.
void SpeedRacer::draw() {
	
	// Move to the vehicle’s local frame of reference.
	glPushMatrix();
		positionInGL();

			// Variable to check how many wheels were found in the shape vector.
			int numFrontWheels = 0;

			for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
				
				// Dynamic cast the iterator to be a pointer of type cylinder.
				Cylinder * cyl = dynamic_cast<Cylinder *>(*it);
				
				// Check that the dynamic cast succeeded and that the current iterator shape is a cylinder.
				if (cyl != NULL) {
					
					// Set the Boolean for steering of the 2 front wheels to be true if the steering angle is non - zero.
					if (steering != 0) {
						if (numFrontWheels < 2) {
							cyl->setIfSteering(true);
							numFrontWheels++;
						}
					}
					else {
						cyl->setIfSteering(false);
					}

					// Similarly, check if the speed is non - zero. If yes, set the Boolean for rolling of the wheels to
					// be true.
					if (speed != 0) {
						cyl->setIfRolling(true);
					}
					else {
						cyl->setIfRolling(false);
					}

					// Calculate the angular velocity of the wheels using w = v / r and update the value of the angular
					// velocity.
					AngularVelocity = AngularVelocity + (speed / cyl->getRadius()) / SCALING_FACTOR;
					
					// Draw the wheels of the vehicle with updated position and orientation.
					glPushMatrix();
						
						// Translate the coordinate axes to where the wheel is located.
						glTranslated(cyl->getX(), cyl->getRadius(), cyl->getZ());
						
						// Rotate the wheels about the y - axis by the same amount as the steering angle if the wheels
						// are being steered.
						if (cyl->getIfSteering() == true) {
							glRotatef(-steering, 0, 1, 0);
						}

						// Rotate the wheels about the z - axis by the same value as the calculated angular velocity.
						glRotated(-AngularVelocity, 0, 0, 1);

						// Return the coordinate axes back to where the vehicle is centred.
						glTranslated(-cyl->getX(), -cyl->getRadius(), -cyl->getZ());
						(*it)->draw();
					glPopMatrix();
				}
				else {

					// Draw other shapes normally.
					(*it)->draw();
				}
			}

	// Move back to global frame of reference.
	glPopMatrix();
}

// Obtain the memory address for the vehicle model of 'SpeedRacer' and return the address. 
VehicleModel * SpeedRacer::getCustomVehicleModel() {
	return &CustomVehicle;
}