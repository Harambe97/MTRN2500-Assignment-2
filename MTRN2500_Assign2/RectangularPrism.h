#pragma once
#include "Shape.hpp"

//Code written by: Mei Yan Tang (z5129009)

//Class is derived by 'Shape' class that defines a Rectangular Prism.
//variables were obtained by the shape specification from Moodle.
class RectangularPrism : public Shape
{
private:
	double x_length;
	double y_length;
	double z_length;

public:
	RectangularPrism(double x_, double y_, double z_, double rotation_, double Lx, double Ly, double Lz);
	void draw();

};
