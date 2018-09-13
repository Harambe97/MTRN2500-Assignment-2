#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include "XInputWrapper.h"

/*
* For MTRN2500 Students - These methods and their respective signatures must not be changed. If
* they are and human intervention is required then marks will be deducted. You are more than
* welcome to add member variables and methods to the provided classes, or create
* your own underlying classes to provide the requested functionality as long as all of the
* functionality for the XBoxController can be accessed using the methods in the provided classes.
*/

namespace GamePad {
	class Coordinate {
	public:
		Coordinate(SHORT x, SHORT y) : x(x), y(y) {}
		~Coordinate() = default;

		SHORT GetX() { return this->x; }
		SHORT GetY() { return this->y; }
		void SetX(SHORT x) { this->x = x; }
		void SetY(SHORT y) { this->y = y; }

	private:
		SHORT x;
		SHORT y;
	};

	class XBoxController {
	public:
		XBoxController(XInputWrapper* xinput, DWORD id);
		~XBoxController() = default;

		// Methods which report information relating to the specific controller:
		DWORD GetControllerId();

		// Methods which report particular aspects of the controller status:
		bool IsConnected();
		bool PressedA();
		bool PressedB();
		bool PressedX();
		bool PressedY();
		bool PressedLeftShoulder();
		bool PressedRightShoulder();
		bool PressedLeftDpad();
		bool PressedRightDpad();
		bool PressedUpDpad();
		bool PressedDownDpad();
		bool PressedStart();
		bool PressedBack();
		bool PressedLeftThumb();
		bool PressedRightThumb();
		BYTE LeftTriggerLocation();
		BYTE RightTriggerLocation();

		GamePad::Coordinate LeftThumbLocation();
		GamePad::Coordinate RightThumbLocation();

		// Methods which set values that modify the behaviour of the controller:
		void Vibrate(WORD left, WORD right);
		void SetDeadzone(unsigned int radius);

		// Additional methods not originally included in class:
		void PrintController(); // Method that prints out the currently connected controllers.
		void PrintButtonsPressed(); // Method that prints out which buttons have been pressed on connected controllers.
		void PrintTriggerValues(); // Method that prints out the trigger values on connected controllers.
		void PrintThumbValues(); // Method that prints out the coordinates of thumbsticks on connected controllers.
		WORD GetLeftMotor(); // Method that obtains the speed that the left motor vibrates at.
		WORD GetRightMotor(); // Method that obtains the speed that the right motor vibrates at.

	private:
		// NOTE: All XInput function calls must be made through the XInputWrapper class.
		XInputWrapper * xinput;

		// Additional variables not originally included in class:
		DWORD ControllerID; // Variable to obtain the index of the controller.
		XINPUT_STATE State; // Variable to obtain controller states.
		XINPUT_VIBRATION Vibration; // Variable to set vibration of the controllers.
		unsigned int DeadzoneRadius; // Variable to set the deadzone of the thumbsticks.
	};
};

#endif // XBOX_CONTROLLER_H