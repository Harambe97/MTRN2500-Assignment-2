#pragma once
#include "Shape.hpp"

// Code written by: Haydn St. James (z5118383)

// Class derived from the 'Shape' class that defines a closed cylinder.
// Uses the variables outlined in the server specifications for shapes, which can be found on the Moodle page of MTRN2500.
class Cylinder : public Shape {
private:
	double radius;
	double depth;

public:
	Cylinder(double x_, double y_, double z_, double rotation_, double Radius, double Depth);
	void draw();

	// Functions below are used to set new dimensions for a cylinder if required (for example, when drawing other 
	// vehicles from the server).
	void setRadius(double Radius);
	void setDepth(double Depth);

	// Functions below are used to obtain the dimensions of a locally instantiated cylinder to be sent to the server. 
	double getRadius();
	double getDepth();

};