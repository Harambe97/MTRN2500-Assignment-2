#pragma once
#include "Shape.hpp"

// Code written by: Haydn St. James (z5118383)

// Class derived from the 'Shape' class that defines a closed cylinder.
// Uses the variables outlined in the server specifications for shapes, which can be found on the Moodle page of MTRN2500.
class Cylinder : public Shape {
	private:
		double radius;
		double depth;
<<<<<<< HEAD
		bool isRotating; // Variable to check if a wheel on the custom vehicle is rotating.
=======
		bool isRolling; // Variable to check if a wheel on the custom vehicle is rolling.
>>>>>>> z5118383
		bool isSteering; // Variable to check if a wheel on the custom vehicle is steering.
	public:
		Cylinder(double x_, double y_, double z_, double rotation_, double Radius, double Depth);
		void draw();
<<<<<<< HEAD
		bool setIfRotating(); // Function to check if a wheel on the custom vehicle is rotating.
		bool setIfSteering(); // Function to check if a wheel on the custom vehicle is steering.
=======

		// Functions below are used to set new dimensions for a cylinder if required (for example, when drawing other 
		// vehicles from the server).
		void setRadius(double Radius);
		void setDepth(double Depth);

		// Functions below are used to set the rolling and steering of cylinders used to define the wheels of a vehicle 
		// if required (for example, when drawing other vehicles from the server).
		void setIfRolling(bool Rolling); 
		void setIfSteering(bool Steering);

		// Functions below are used to obtain the dimensions of a locally instantiated cylinder to be sent to the server. 
		double getRadius();
		double getDepth();

		// Functions below are used to obtain the steering and rolling of cylinders used to define the wheels of 
		// a vehicle to be sent to the server.
		bool getIfRolling();
		bool getIfSteering();
>>>>>>> z5118383
};