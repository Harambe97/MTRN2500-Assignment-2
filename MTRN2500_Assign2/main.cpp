
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

// Additional includes and '#defines' not included in base code:

// Include the header files for derived classes of shapes and vehicles.
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidPrism.h"
#include "Cylinder.h"
#include "SpeedRacer.h"

// Include the header file and '#defines' to process inputs from XBox controllers. The header file and its function
// definitions were obtained from Assignment 1.
#include "XBoxController.h"
#define CONTROLLER_DEADZONE 15000
#define MAX_THUMBSTICK_RADIUS 32767
#define CAMERA_STRAFE_DEADZONE 7000
#define CAMERA_DRAG_SCALING 2500

// Includes and '#defines' to perform mathematical operations.
#include <math.h>
#define PI 3.14159265358979323846264338327950
#define SERVER_VEHICLE_REACHED 4

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

// Additional global variables not originally in base code: 

// Create a pointer of type 'SpeedRacer' in order to access members of 'SpeedRacer'.
SpeedRacer * MyVehicle = new SpeedRacer();

// Create an instantiation of the wrapper for the controller.
XInputWrapper xinput;

// Create a new XBox controller object, passing in a pointer to the wrapper, you can now use the controller as normal.
GamePad::XBoxController controller(&xinput, 0);

// Additional global variables to determine the location of the server vehicle with ID 1:
float ServerVehicleX = 0.0;
float ServerVehicleZ = 0.0;
float Dist2SerVehicleX = 0.0;
float Dist2SerVehicleZ = 0.0;
float Dist2SerVehicle = 0.0;
float Angle2Serve = 0.0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new SpeedRacer();


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

// Additional function used to test and draw objects as described in the Week 6 Tutorial set-up.
// (function called above 'glutSwapBuffers()', around line 250)
void DrawTest() {
	RectangularPrism R1(20, 0, 20, 0, 10, 7, 5);
	R1.draw();
	TriangularPrism T1(-20, 0, 20, 45, 5, 5, 10, 90);
	T1.draw();
	TrapezoidPrism Prism1(-20, 0, -20, 0, 10, 5, 10, 10, 3);
	Prism1.draw();
	Cylinder C1(20, 0, -20, 90, 3, 10);
	C1.draw();
}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();
	
	// Additional function used to test and draw objects as described in the Week 6 Tutorial set-up.
	// (function definition around line 193)
	//DrawTest();
	
	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	// Added the ability to detect XBox Controller inputs to the base code.
	
	// Additional code written by: Haydn St. James (z5118383) & Mei Yan Tang (z5129009)

	// Set the deadzone of the thumbsticks.
	controller.SetDeadzone(CONTROLLER_DEADZONE);

	// Toggle the pursuit camera if the 'Y' button was been pressed.
	if (controller.PressedY()) {
		Camera::get()->togglePursuitMode();
	}

	// Set the camera at the origin of the digital world if the 'A' button was pressed.
	if (controller.PressedA()) {
		Camera::get()->jumpToOrigin();
	}

	// Quit the program if 'Back' was pressed.
	if (controller.PressedBack()) {
		exit(0);
	}

	// Strafe the camera using the right thumbstick if the left shouder button was not pressed or using the keys that were
	// originally set in the base code.
	// A 'secondary deadzone' was set for the right thumbsticks when strafing the camera as the motion of the camera was
	// not smooth when purely using the default thumbstick deadzones that were set.
	if (KeyManager::get()->isAsciiKeyPressed('a') || ((controller.RightThumbLocation().GetX() < -CAMERA_STRAFE_DEADZONE) && (controller.PressedLeftShoulder() == false))) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c') || ((controller.RightThumbLocation().GetY() < -CAMERA_STRAFE_DEADZONE) && (controller.PressedLeftShoulder() == false))) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ') || ((controller.RightThumbLocation().GetY() > CAMERA_STRAFE_DEADZONE) && (controller.PressedLeftShoulder() == false))) {
		Camera::get()->strafeUp();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d') || ((controller.RightThumbLocation().GetX() > CAMERA_STRAFE_DEADZONE) && (controller.PressedLeftShoulder() == false))) {
		Camera::get()->strafeRight();
	}

	// Move the camera front and back using the left and right triggers respectively.
	if (KeyManager::get()->isAsciiKeyPressed('s') || (controller.RightTriggerLocation() > 0)) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w') || (controller.LeftTriggerLocation() > 0)) {
		Camera::get()->moveForward();
	}

	// Drag the camera using the right thumbstick if the left shoulder button was pressed. The y - coordinates are
	// inverted to accurately reflect the direction the thumbstick is pushed in when dragging the camera view.
	if (controller.PressedLeftShoulder()) {
		int dx = 0;
		int dy = 0;

		if ((controller.RightThumbLocation().GetX() != 0) || (controller.RightThumbLocation().GetY() != 0)) {
			dx = controller.RightThumbLocation().GetX() / CAMERA_DRAG_SCALING;
			dy = -controller.RightThumbLocation().GetY() / CAMERA_DRAG_SCALING;
			Camera::get()->mouseRotateCamera(dx, dy);
		}
	}

	speed = 0;
	steering = 0;

	// Steer and accelerate the vehicle based on arrow key presses or the position of the left thumbstick on a controller.
	// The left thumb coordinates are statically cast as integers to prevent unintended behaviour when multiplied
	// with the constants for steering and speed defined in 'Vehicle.hpp'.
	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
	}
	else if (controller.LeftThumbLocation().GetX() <= 0) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * 1 * static_cast<int>(controller.LeftThumbLocation().GetX()) / MAX_THUMBSTICK_RADIUS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}
	else if (controller.LeftThumbLocation().GetX() > 0) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1 * static_cast<int>(controller.LeftThumbLocation().GetX()) / MAX_THUMBSTICK_RADIUS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}
	else if (controller.LeftThumbLocation().GetY() >= 0) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS * static_cast<int>(controller.LeftThumbLocation().GetY()) / MAX_THUMBSTICK_RADIUS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}
	else if (controller.LeftThumbLocation().GetY() < 0) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS * static_cast<int>(-controller.LeftThumbLocation().GetY()) / MAX_THUMBSTICK_RADIUS;
	}

	// Challenge: When 'l' is pressed, chase the server vehicle.
	// ** NEED TO CHASE PROPERLY, CAR KEEPS ZIGZAGGING
	if (MyVehicle->ReturnChaseMode() == true) {
		/*if ((Angle2Serve >= 0) && (Angle2Serve <= Vehicle::MAX_LEFT_STEERING_DEGS)) {
			Angle2Serve = Angle2Serve;
		}
		else if ((Angle2Serve < 0) && (Angle2Serve >= Vehicle::MAX_RIGHT_STEERING_DEGS)) {
			Angle2Serve = Angle2Serve;
		}*/
		if (Angle2Serve > 180) {
			while (Angle2Serve > 180) {
				Angle2Serve -= 360;
			}
		}
		else if (Angle2Serve < -180) {
			while (Angle2Serve < -180) {
				Angle2Serve += 360;
			}
		} 
		else if (Angle2Serve >= Vehicle::MAX_LEFT_STEERING_DEGS) {
			Angle2Serve = Vehicle::MAX_LEFT_STEERING_DEGS;
		}
		else if (Angle2Serve <= Vehicle::MAX_RIGHT_STEERING_DEGS) {
			Angle2Serve = Vehicle::MAX_RIGHT_STEERING_DEGS;
		}

		// If the local vehicle has reached the server vehicle, cease all motion.
		if (Dist2SerVehicle <= SERVER_VEHICLE_REACHED) {
			speed = 0;
			steering = 0;
		}
		else {

			// Set the speed of the local vehicle to its maximum forward speed and the steering to be equal to the 
			// post - processed angle to the server vehicle.
			speed = Vehicle::MAX_FORWARD_SPEED_MPS;
			steering = Angle2Serve;
		}
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					// Code written by: Haydn St. James (z5118383)
					
					// Send the address of the local vehicle model to the server.
					vm = *MyVehicle->getCustomVehicleModel();

					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles

								// Code written by: Haydn St. James (z5118383)

								// Using the overload constructor in 'SpeedRacer.h', draw remote vehicles from the server
								// by passing in the address of the vehicle model.
								otherVehicles[vm.remoteID] = new SpeedRacer(&vm);
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
									
									// Code written by: Haydn St. James (z5118383)

									// Challenge: When 'l' is pressed, chase the server vehicle.

									// Obtain the x and z - coordinates of the server vehicle, which is in 'states[0]'.
									ServerVehicleX = states[0].x;
									ServerVehicleZ = states[0].z;

									// Determine the distance and angle to the server vehicle.
									Dist2SerVehicleX = ServerVehicleX - vehicle->getX();
									Dist2SerVehicleZ = ServerVehicleZ - vehicle->getZ();
									Dist2SerVehicle = sqrt(Dist2SerVehicleX * Dist2SerVehicleX + Dist2SerVehicleZ * Dist2SerVehicleZ);
									Angle2Serve = (atan2f(Dist2SerVehicleZ, Dist2SerVehicleX) * 180 / PI) - vehicle->getRotation() - states[0].rotation;

									// The array index that holds information about the server vehicle was determined
									// using the debugging tool and the following code:

									/*if (vs.remoteID == 1) {
										ServerVehicleX = vs.x;
										ServerVehicleZ = vs.z;
										int index = i;
									}*/
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;

	// Code written by: Haydn St. James (z5118383)

	// Challenge: Press 'l' to give chase to the server vehicle with vehicle ID 1.
	case 'l':
		MyVehicle->ToggleChaseMode();
		break;
	}
};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};