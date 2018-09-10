#pragma once
#include "Shape.hpp"

//Code written by: Mei Yan Tang (z5129009)

//Class is derived by 'Shape' class that defines a Rectangular Prism.
//variables were obtained by the shape specification from Moodle.
class RectangularPrism : public Shape {
	private:
		double x_length;
		double y_length;
		double z_length;

	public:
		RectangularPrism(double x_, double y_, double z_, double rotation_, double Lx, double Ly, double Lz);
		void draw();
<<<<<<< HEAD
=======

		// Functions below written by: Haydn St. James (z5118383)

		// Functions below are used to set new dimensions for a rectangular prism if required (for example, when drawing 
		// other vehicles from the server).
		void setX_length(double Lx);
		void setY_length(double Ly);
		void setZ_length(double Lz);

		// Functions below are used to obtain the dimensions of a locally instantiated rectangular prism 
		// to be sent to the server. 
		double getX_length();
		double getY_length();
		double getZ_length();
>>>>>>> z5118383
};