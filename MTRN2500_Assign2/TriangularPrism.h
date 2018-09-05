#pragma once
#include "Shape.hpp"

// Code written by: Mei Yan Tang (z5129009)

class TriangularPrism : public Shape {
private:
	double a_length;
	double b_length;
	double depth;
	double theta;

public:
	TriangularPrism(double x_, double y_, double z_, double rotation_, double length_a, double length_b, double length_d, double angle);
	void draw();
};