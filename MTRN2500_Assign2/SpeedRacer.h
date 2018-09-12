#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

// Code written by: Haydn St. James (z5118383)

// Class derived from the 'Vehicle' class that defines any vehicle of type 'SpeedRacer'.
class SpeedRacer : public Vehicle {
	protected:
		VehicleModel CustomVehicle;
	public:
		SpeedRacer(); // Default constructor to instantiate the local vehicle.
		SpeedRacer(VehicleModel * RemoteVehicles); // Overload constructor to instantiate remote vehicles.
		void draw();
		VehicleModel * getCustomVehicleModel(); // Obtains the memory address for the model of the local vehicle.
};