#include "XBoxController.h"
#include <iostream>
#include <math.h>
#define MAX_THUMBSTICK_RADIUS 32767

// All functions declared in the original header file that require accessing 'XInput' functions such as 'XInputGetState'
// have their inputs intercepted by the wrapper in order to allow autotesting of the now defined functions.
// 'State' is a private variable that was added into the 'XBoxController' class to obtain the current state of controllers.
// 'ControllerID' is a private variable that was added into the 'XBoxController' class to obtain the index of controllers.

// Creates an instantiation of the XBox Controller to allow access to the wrapper. 
GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id) {
	this->xinput = xinput;
	ControllerID = id;
}

// Methods which report information relating to the specific controller:

// The function below returns the index of a connected controller using a private variable that was added into the
// 'XBoxController' class.
DWORD GamePad::XBoxController::GetControllerId() {
	return ControllerID;
}

// Methods which report particular aspects of the controller status:

// The Boolean function below determines if a controller has been connected by checking to see if the 'XInputGetState'
// function successfully obtains the state of a controller. If yes, the return value is 'true'. If more than 4 controllers
// are connected (i.e: ControllerID is equal to or more than the maximum user count) or if the controller index is not  
// valid (i.e: Controller ID is less than 0), the function also returns 'false'.
bool GamePad::XBoxController::IsConnected() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	if ((ControllerID >= XUSER_MAX_COUNT) || (ControllerID < 0)) {
		return false;
	} 
	else {
		if (XInputGetState(ControllerID, &State) == ERROR_SUCCESS) {
			// Controller is connected.
			return true;
		} 
		else {
			// Controller is not connected.
			return false;
		}
	}
}

// The Boolean functions below determine which button has been pressed. They obtain the current controller state and check 
// if a button has been pressed via the 'XInput' library and also check if the corresponding bit for a button is non-zero.
// If yes, the functions return 'true'.
bool GamePad::XBoxController::PressedA() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedB() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedX() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedY() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedLeftShoulder() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedRightShoulder() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedLeftDpad() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedRightDpad() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedUpDpad() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedDownDpad() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0) {
		return true;
	} 
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedStart() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedBack() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedLeftThumb() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GamePad::XBoxController::PressedRightThumb() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);
	
	if ((State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0) {
		return true;
	}
	else {
		return false;
	}
}

// The trigger functions below check if the triggers have been pressed down by accessing the current controller state.
// If yes, the functions return the position of the trigger. Otherwise, the functions return a zero value to indicate
// that the triggers are in their unpressed, neutral positions.
BYTE GamePad::XBoxController::LeftTriggerLocation() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	if (State.Gamepad.bLeftTrigger) {
		return State.Gamepad.bLeftTrigger;
	}
	else {
		return 0;
	}
}

BYTE GamePad::XBoxController::RightTriggerLocation() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	if (State.Gamepad.bRightTrigger) {
		return State.Gamepad.bRightTrigger;
	}
	else {
		return 0;
	}
}

// The functions below define the coordinates returned by the left and right thumbsticks respectively and were defined with
// reference to the following sites:
// https://docs.microsoft.com/en-us/windows/desktop/xinput/getting-started-with-xinput#dead-zone
// http://www.third-helix.com/2013/04/12/doing-thumbstick-dead-zones-right.html
// All computations done within the thumbstick functions are done using 'float' type values. The thumbstick coordinates
// are typecast as 'float' values for more accurate computations before being reverted to the 'SHORT' type when they
// are returned. The thumbstick functions follow the following process:
// (1) The magnitude of the X and Y coordinates is obtained, if less than the deadzone radius, set the X and Y
//	   coordinates to zero. If more than zero, set the magnitude to be equal to the maximum possible radius.
// (2) The angle between the thumbstick location and the horizontal line is obtained.
// (3) The distance between the thumbstick location and the deadzone is obtained, also obtain the distance between
//     the maximum boundary of the thumbstick and the deadzone.
// (4) Obtain the ratio of of the first distance over the second distance and multiply by the magnitude to obtain
//     the scaled magnitude.
// (5) Using sines and cosines, obtain the scaled X and Y coordinates and return them.
		
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	float LX = (float) State.Gamepad.sThumbLX;
	float LY = (float) State.Gamepad.sThumbLY;

	// Determine how far the left thumbstick is pushed.
	float Radius = sqrt(LX * LX + LY * LY);

	if (Radius > MAX_THUMBSTICK_RADIUS) {
		Radius = MAX_THUMBSTICK_RADIUS;
	}
	else if (Radius < (float) DeadzoneRadius) {
		LX = 0.0;
		LY = 0.0;
	}
	else {
		float Theta = atan2f(LY,LX);
		float Deadzone2Point = Radius - (float) DeadzoneRadius;
		float Deadzone2Bound = MAX_THUMBSTICK_RADIUS - (float) DeadzoneRadius;
		float Ratio = Deadzone2Point / Deadzone2Bound;
		float ScaledRadius = Ratio * MAX_THUMBSTICK_RADIUS;
		LX = ScaledRadius * cos(Theta);
		LY = ScaledRadius * sin(Theta);
	}
	return GamePad::Coordinate((SHORT) LX, (SHORT) LY);
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() {
	this->xinput = xinput;
	xinput->XInputGetState(ControllerID, &State);

	float RX = (float) State.Gamepad.sThumbRX;
	float RY = (float) State.Gamepad.sThumbRY;
	
	// Determine how far the right thumbstick is pushed.
	float Radius = sqrt(RX * RX + RY * RY);

	if (Radius > MAX_THUMBSTICK_RADIUS) {
		Radius = MAX_THUMBSTICK_RADIUS;
	}
	else if (Radius < (float) DeadzoneRadius) {
		RX = 0.0;
		RY = 0.0;
	}
	else {
		float Theta = atan2f(RY, RX);
		float Deadzone2Point = Radius - (float) DeadzoneRadius;
		float Deadzone2Bound = MAX_THUMBSTICK_RADIUS - (float) DeadzoneRadius;
		float Ratio = Deadzone2Point / Deadzone2Bound;
		float ScaledRadius = Ratio * MAX_THUMBSTICK_RADIUS;
		RX = ScaledRadius * cos(Theta);
		RY = ScaledRadius * sin(Theta);
	}
	return GamePad::Coordinate((SHORT) RX, (SHORT) RY);
}

// Methods which set values that modify the behaviour of the controller:

// The function below sets the vibration of the left and right motors to be equal to the corresponding arguments of the
// function. These arguments are obtained from the main function when certain conditions are met.
// (i.e: when a specific button combination has been pressed, set the vibration of the motors to a desired value)
// 'Vibration' is a private variable that was added into the 'XBoxController' class to set controller vibrations.
void GamePad::XBoxController::Vibrate(WORD left, WORD right) {
	this->xinput = xinput;
	xinput->XInputSetState(ControllerID, &Vibration);

	Vibration.wLeftMotorSpeed = left;
	Vibration.wRightMotorSpeed = right;
}

// The function below sets the deadzone of the thumbsticks on the controllers using a private variable that was added to
// the 'XBoxController' class.
void GamePad::XBoxController::SetDeadzone(unsigned int radius) {
	DeadzoneRadius = radius;
}

// Additional methods not originally included in class:

// Method that prints out the currently connected controllers, checks if a controller is connected and prints the ID of the
// connected controller.
void GamePad::XBoxController::PrintController() {
	if (GamePad::XBoxController::IsConnected() == true) {
		std::cout << GamePad::XBoxController::GetControllerId() + 1 << " ";
	}
}

// Method that prints out which buttons have been pressed on connected controllers by checking if the button press
// functions defined above return a 'true' value.
void GamePad::XBoxController::PrintButtonsPressed() {
	if (GamePad::XBoxController::PressedA() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "A" << " ";
	}
	if (GamePad::XBoxController::PressedB() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "B" << " ";
	}
	if (GamePad::XBoxController::PressedX() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "X" << " ";
	}
	if (GamePad::XBoxController::PressedY() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "Y" << " ";
	}
	if (GamePad::XBoxController::PressedLeftShoulder() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "LB" << " ";
	}
	if (GamePad::XBoxController::PressedRightShoulder() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "RB" << " ";
	}
	if (GamePad::XBoxController::PressedLeftDpad() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "DL" << " ";
	}
	if (GamePad::XBoxController::PressedRightDpad() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "DR" << " ";
	}
	if (GamePad::XBoxController::PressedUpDpad() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "DU" << " ";
	}
	if (GamePad::XBoxController::PressedDownDpad() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "DD" << " ";
	}
	if (GamePad::XBoxController::PressedStart() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "Start" << " ";
	}
	if (GamePad::XBoxController::PressedBack() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "Back" << " ";
	}
	if (GamePad::XBoxController::PressedLeftThumb() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "LS" << " ";
	}
	if (GamePad::XBoxController::PressedRightThumb() == true) {
		std::cout << "C" << GamePad::XBoxController::GetControllerId() + 1 << "RS" << " ";
	}
}

// Method that prints out the trigger values on connected controllers, checks if the trigger values are more than zero.
// The trigger values are typecast as integers to prevent returning the ASCII characters of the trigger values.
void GamePad::XBoxController::PrintTriggerValues() {
	if (State.Gamepad.bLeftTrigger > 0) {
		std::cout << "LT" << GamePad::XBoxController::GetControllerId() + 1 << ": " << (int) GamePad::XBoxController::LeftTriggerLocation() << " ";
	}
	if (State.Gamepad.bRightTrigger > 0) {
		std::cout << "RT" << GamePad::XBoxController::GetControllerId() + 1 << ": " << (int) GamePad::XBoxController::RightTriggerLocation() << " ";
	}
}

// Method that prints out the coordinates of thumbsticks on connected controllers, checks if the value of the X or Y
// coordinates on any thumbstick is non-zero.
void GamePad::XBoxController::PrintThumbValues() {
	if (GamePad::XBoxController::LeftThumbLocation().GetX() != 0) {
		std::cout << "LX" << GamePad::XBoxController::GetControllerId() + 1 << " = " << GamePad::XBoxController::LeftThumbLocation().GetX() << " ";
	}
	if (GamePad::XBoxController::LeftThumbLocation().GetY() != 0) {
		std::cout << "LY" << GamePad::XBoxController::GetControllerId() + 1 << " = " << GamePad::XBoxController::LeftThumbLocation().GetY() << " ";
	}
	if (GamePad::XBoxController::RightThumbLocation().GetX() != 0) {
		std::cout << "RX" << GamePad::XBoxController::GetControllerId() + 1 << " = " << GamePad::XBoxController::RightThumbLocation().GetX() << " ";
	}
	if (GamePad::XBoxController::RightThumbLocation().GetY() != 0) {
		std::cout << "RY" << GamePad::XBoxController::GetControllerId() + 1 << " = " << GamePad::XBoxController::RightThumbLocation().GetY() << " ";
	}
}

// Method that returns the speed that the left motor vibrates at.
WORD GamePad::XBoxController::GetLeftMotor() {
	return Vibration.wLeftMotorSpeed;
}

// Method that returns the speed that the right motor vibrates at.
WORD GamePad::XBoxController::GetRightMotor() {
	return Vibration.wRightMotorSpeed;
}