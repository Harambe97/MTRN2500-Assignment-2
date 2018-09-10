#pragma once
#include "Shape.hpp"

// Code written by: Haydn St. James (z5118383)

// Class derived from the 'Shape' class that defines a trapezoidal prism.
// Uses the variables outlined in the server specifications for shapes, which can be found on the Moodle page of MTRN2500.
class TrapezoidPrism : public Shape {
	private:	
		double a_length; 
		double b_length; 
		double height;
		double depth;
		double a_offset;
	public:
		TrapezoidPrism(double x_, double y_, double z_, double rotation_, double Bottom_length, double Top_length, double Height, double Depth, double Offset);
		void draw();
};