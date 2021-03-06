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
		// Variables to allocate memory for shapes used to define the local vehicle.
		RectangularPrism * Body;
		TriangularPrism * Bumper;
		TrapezoidPrism * Spoiler;
		Cylinder * FrontLeftWheel;
		Cylinder * FrontRightWheel;
		Cylinder * BackLeftWheel;
		Cylinder * BackRightWheel;
		VehicleModel CustomVehicle;

		// Variable to obtain the angular veloctiy of the wheels of the local vehicle.
		double AngularVelocity = 0.0;

		// Vector that stores pointers to server shapes, allows for memory to be freed after program completes.
		std::vector<Shape *> ServerShapes;

		// Variable to toggle between manual and autonomous chase modes.
		bool manualChase;
	public:
		SpeedRacer(); // Default constructor to instantiate the local vehicle.
		~SpeedRacer();
		SpeedRacer(VehicleModel * RemoteVehicles); // Overload constructor to instantiate remote vehicles.
		void draw();
		VehicleModel * getCustomVehicleModel(); // Obtains the memory address for the model of the local vehicle.
		void ToggleChaseMode(); // Toggles the autonomous pursuit of the server vehicle.
		bool ReturnChaseMode(); // Returns whether the chase mode is on or off.
};