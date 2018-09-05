#pragma once
#include "Vehicle.hpp"

// Code written by: Haydn St. James (z5118383) & Mei Yan Tang (z5129009)

// Class derived from the 'Vehicle' class that defines any vehicle of type 'SpeedRacer'.
class SpeedRacer : public Vehicle {
	public:
		SpeedRacer(double x_, double y_, double z_, double rotation_);
		void draw();
};