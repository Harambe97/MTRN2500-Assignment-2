#include "Wheels.h"

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

Wheels::Wheels(double x_, double y_, double z_, double rotation_, double Radius, double Depth) :Cylinder(x_, y_, z_, rotation_, Radius, Depth) {
	isRolling = false;
	isSteering = false;
}; 

// Functions below are used to set the rolling and steering of cylinders used to define the wheels of a vehicle if required
// (for example, when drawing other vehicles from the server).
void Wheels::setIfRolling(bool Rolling) {
	isRolling = Rolling;
}

void Wheels::setIfSteering(bool Steering) {
	isSteering = Steering;
}

// Functions below are used to obtain the steering and rolling of cylinders used to define the wheels of a vehicle to be
// sent to the server.
bool Wheels::getIfRolling() {
	return isRolling;
}

bool Wheels::getIfSteering() {
	return isSteering;

}