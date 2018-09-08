
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

// Include the header files for derived classes of shapes to be drawn for Assessment 1
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidPrism.h"
#include "Cylinder.h"
#include "SpeedRacer.h"
#include <math.h>

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

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

// ** An additional function added to the main file called 'DrawTest()' was used to test and draw shapes. 
// ** (function definition around line 168)

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

	vehicle = new SpeedRacer(0, 0, 0, 0);


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
// (function called above 'glutSwapBuffers()', around line 223)
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
	// (function definition around line 168)
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

	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;   
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
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
					
					// Create a pointer of 'Shape' type that adds shapes into the shape vector defined in 'Vehicle.hpp'.
					// Add the body of the vehicle to the shape vector.
					Shape * newShape = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
					// Dynamic cast to convert from a pointer of type 'Shape' into a pointer of type 'RectangularPrism'.
					// Similar casts were done for other shapes used to define the vehicle.
					RectangularPrism *rect = dynamic_cast<RectangularPrism*>(newShape);
					vehicle->addShape(rect);

					// Add the bumper of the vehicle to the shape vector.
					newShape = new TriangularPrism (3, 0, 0, 0, 2, 2, 2, 90);
					TriangularPrism *tri = dynamic_cast<TriangularPrism*>(newShape);
					vehicle->addShape(tri);

					// Add the spoiler of the vehicle to the shape vector.
					newShape = new TrapezoidPrism(-2, 2, 0, 0, 2, 2, 1, 2, 1);
					TrapezoidPrism *trap = dynamic_cast<TrapezoidPrism*>(newShape);
					vehicle->addShape(trap);
					
					// Add the front wheels to the shape vector.
					newShape = new Cylinder(1, 0, -1, steering, 0.75, 1);
					Cylinder *cyl = dynamic_cast<Cylinder*>(newShape);
					vehicle->addShape(cyl);

					newShape = new Cylinder(1, 0, 1, steering, 0.75, 1);
					cyl = dynamic_cast<Cylinder*>(newShape);
					vehicle->addShape(cyl);

					// Add the back wheels to the shape vector.
					newShape = new Cylinder(-1, 0, -1, 0, 0.75, 1);
					cyl = dynamic_cast<Cylinder*>(newShape);
					vehicle->addShape(cyl);

					newShape = new Cylinder(-1, 0, 1, 0, 0.75, 1);
					cyl = dynamic_cast<Cylinder*>(newShape);
					vehicle->addShape(cyl);

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
								otherVehicles[vm.remoteID] = new SpeedRacer(0, 0, 0, 0);

								// Code written by: Haydn St. James (z5118383)

								// Obtain shapes and dimensions of the vehicles of other users and draw them.
								// Create a pointer to access information about the vehicles and shapes from the server.
								for (std::vector<ShapeInit>::iterator it = vm.shapes.begin(); it != vm.shapes.end(); it++) {
									RectangularPrism * rect = new RectangularPrism(0, 0, 0, 0, 0, 0, 0);
									TriangularPrism *tri = new TriangularPrism(0, 0, 0, 0, 0, 0, 0, 0);
									TrapezoidPrism *trap = new TrapezoidPrism(0, 0, 0, 0, 0, 0, 0, 0, 0);
									Cylinder * cyl = new Cylinder(0, 0, 0, 0, 0, 0);
									
									if (it->type = RECTANGULAR_PRISM) {
										// Set the dimensions of the obtained shape to what was given by another user.
										rect->setX_length(it->params.rect.xlen);
										rect->setY_length(it->params.rect.ylen);
										rect->setZ_length(it->params.rect.zlen);

										// Set the colour of the obtained shape to what was given by another user.
										rect->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

										// Set the position of the obtained shape to what was given by another user.
										rect->setX(it->xyz[0]);
										rect->setY(it->xyz[1]);
										rect->setZ(it->xyz[2]);
										rect->setRotation(it->rotation);
										otherVehicles[vm.remoteID]->addShape(rect);
									}
									else if (it->type = TRIANGULAR_PRISM) {
										tri->setA_length(it->params.tri.alen);
										tri->setTheta(it->params.tri.angle);
										tri->setB_length(it->params.tri.blen);
										tri->setDepth(it->params.tri.depth);

										tri->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

										tri->setX(it->xyz[0]);
										tri->setY(it->xyz[1]);
										tri->setZ(it->xyz[2]);
										tri->setRotation(it->rotation);
										otherVehicles[vm.remoteID]->addShape(tri);
									}
									else if (it->type = TRAPEZOIDAL_PRISM) {
										trap->setA_length(it->params.trap.alen);
										trap->setA_offset(it->params.trap.aoff);
										trap->setB_length(it->params.trap.blen);
										trap->setDepth(it->params.trap.depth);
										trap->setHeight(it->params.trap.height);

										trap->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

										trap->setX(it->xyz[0]);
										trap->setY(it->xyz[1]);
										trap->setZ(it->xyz[2]);
										trap->setRotation(it->rotation);
										otherVehicles[vm.remoteID]->addShape(trap);
									}
									else if (it->type = CYLINDER) {
										cyl->setRadius(it->params.cyl.radius);
										cyl->setDepth(it->params.cyl.depth);
										cyl->setIfRotating(it->params.cyl.isRolling);
										cyl->setIfSteering(it->params.cyl.isSteering);

										cyl->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

										cyl->setX(it->xyz[0]);
										cyl->setY(it->xyz[1]);
										cyl->setZ(it->xyz[2]);
										cyl->setRotation(it->rotation);
										otherVehicles[vm.remoteID]->addShape(cyl);
									}
								}
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
	// Challenge: Press 'L' to give chase to the server vehicle with vehicle ID 1.
	/*case 'l':
		VehicleState ServerVehicle;
		Camera::get()->togglePursuitMode();
		if (ServerVehicle.remoteID == 1) {
			vehicle.setSpeed();
		}
		break;*/
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


