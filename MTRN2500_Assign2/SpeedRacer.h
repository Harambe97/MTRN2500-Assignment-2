#pragma once
#include "Vehicle.hpp"
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidPrism.h"
#include "Cylinder.h"
#include "Messages.hpp"

// Code written by: Haydn St. James (z5118383) & Mei Yan Tang (z5129009)

// Class derived from the 'Vehicle' class that defines any vehicle of type 'SpeedRacer'.
class SpeedRacer : public Vehicle {
	protected:
		RectangularPrism * Body;
		TriangularPrism * Bumper;
		TrapezoidPrism * Spoiler;
		Cylinder * FrontLeftWheel;
		Cylinder * FrontRightWheel;
		Cylinder * BackLeftWheel;
		Cylinder * BackRightWheel;
		VehicleModel CustomVehicle;
		int AngularVelocity = 0;
	public:
		SpeedRacer(); // Default constructor to instantiate the local vehicle.
		~SpeedRacer();
		SpeedRacer(VehicleModel * RemoteVehicles); // Overload constructor to instantiate remote vehicles.
		void draw();
		VehicleModel * getCustomVehicleModel(); // Obtains the memory address for the model of the local vehicle.
};