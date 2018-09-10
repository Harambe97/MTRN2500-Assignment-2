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

		// Functions below are used to set new dimensions for a trapezoidal prism if required (for example, when drawing other 
		// vehicles from the server).
		void setA_length(double Bottom_length);
		void setB_length(double Top_length);
		void setHeight(double Height);
		void setDepth(double Depth);
		void setA_offset(double Offset);

		// Functions below are used to obtain the dimensions of a locally instantiated trapezoidal prism to be 
		// sent to the server. 
		double getA_length();
		double getB_length();
		double getHeight();
		double getDepth();
		double getA_offset();
};