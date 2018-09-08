#pragma once
#include "Shape.hpp"

//Code written by: Mei Yan Tang (z5129009)

//Class is derived by 'Shape' class that defines a Triangular Prism.
//variables were obtained by the shape specification from Moodle.
class TriangularPrism : public Shape {
	private:
		double a_length;
		double b_length;
		double depth;
		double theta;
	public:
		TriangularPrism(double x_, double y_, double z_, double rotation_, double length_a, double length_b, double length_d, double angle);
		void draw();
		// Functions written by: Haydn St. James (z5118383)
		void setA_length(double length_a);
		void setB_length(double length_b);
		void setDepth(double length_d);
		void setTheta(double angle);
};