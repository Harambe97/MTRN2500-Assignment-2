#pragma once
#include "Shape.hpp"

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

