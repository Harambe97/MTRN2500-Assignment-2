#pragma once
#include "Shape.hpp"
#include "Cylinder.h"
//#include "Vehicle.hpp"


class Wheels : public Cylinder {
public:
	Wheels(double x_, double y_, double z_, double rotation_, double Radius, double Depth);

	// Functions below are used to set the rolling and steering of cylinders used to define the wheels of a vehicle 
	// if required (for example, when drawing other vehicles from the server).
	void setIfRolling(bool Rolling);
	void setIfSteering(bool Steering);

	// Functions below are used to obtain the steering and rolling of cylinders used to define the wheels of 
	// a vehicle to be sent to the server.
	bool getIfRolling();
	bool getIfSteering();

private: 
	double steering;
	double speed;

	bool isRolling; // Variable to check if a wheel on the custom vehicle is rolling.
	bool isSteering; // Variable to check if a wheel on the custom vehicle is steering.


};