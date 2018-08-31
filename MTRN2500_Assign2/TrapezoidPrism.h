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
		TrapezoidPrism(double x1, double x2, double y, double z, double theta1);
		void draw();
};

