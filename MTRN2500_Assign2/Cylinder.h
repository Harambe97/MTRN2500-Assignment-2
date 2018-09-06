#pragma once
#include "Shape.hpp"

// Code written by: Haydn St. James (z5118383)

// Class derived from the 'Shape' class that defines a closed cylinder.
// Uses the variables outlined in the server specifications for shapes, which can be found on the Moodle page of MTRN2500.
class Cylinder : public Shape {
	private:
		double radius;
		double depth;
		bool isRotating; // Variable to check if a wheel on the custom vehicle is rotating.
		bool isSteering; // Variable to check if a wheel on the custom vehicle is steering.
	public:
		Cylinder(double x_, double y_, double z_, double rotation_, double Radius, double Depth);
		void draw();
		bool setIfRotating(); // Function to check if a wheel on the custom vehicle is rotating.
		bool setIfSteering(); // Function to check if a wheel on the custom vehicle is steering.
};