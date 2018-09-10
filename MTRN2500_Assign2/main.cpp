
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
<<<<<<< HEAD
#include <math.h>
=======
>>>>>>> z5118383

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
<<<<<<< HEAD
					
					// Code written by: Haydn St. James (z5118383)

					// Sends the model of 'SpeedRacer' to the server by adding the shapes used to draw 'SpeedRacer' into
					// the vector list declared in 'Vehicle.hpp'.
					Shape *s = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
				    // Dynamic cast to convert from shape pointer into the respective shape pointer.
					RectangularPrism *rect = dynamic_cast<RectangularPrism*>(s);  
					vehicle->addShape(rect);

					s = new TriangularPrism(3, 0, 0, 0, 2, 2, 2, 90);
					TriangularPrism *tri = dynamic_cast<TriangularPrism*>(s);
					vehicle->addShape(tri);

					s = new TrapezoidPrism(-2, 2, 0, 0, 2, 2, 1, 2, 1);
					TrapezoidPrism *trap = dynamic_cast<TrapezoidPrism*>(s);
					vehicle->addShape(trap);

					s = new Cylinder(1, 0, -1, steering, 0.75, 1);
					Cylinder *cyl = dynamic_cast<Cylinder*>(s);
					vehicle->addShape(cyl);

					s = new Cylinder(1, 0, 1, steering, 0.75, 1);
					cyl = dynamic_cast<Cylinder*>(s);
					vehicle->addShape(cyl);

					s = new Cylinder(-1, 0, -1, 0, 0.75, 1);
					cyl = dynamic_cast<Cylinder*>(s);
					vehicle->addShape(cyl);

					s = new Cylinder(-1, 0, 1, 0, 0.75, 1);
					cyl = dynamic_cast<Cylinder*>(s);
					vehicle->addShape(cyl);
					
=======

					// Code written by: Haydn St. James (z5118383)

					// Any shapes to be added into the shape vector and sent to the server follow the same procedure as the
					// rectangular prism below.

					// Add the body of the vehicle to the shape vector.
					// Create a pointer to the instantiated shape to be added into the shape vector 
					// defined in 'Vehicle.hpp'.
					RectangularPrism * rect = new RectangularPrism(0, 0, 0, 90, 2, 2, 4);
					vehicle->addShape(rect);

					// Instantiate 'ShapeInit' to send information to the 'ShapeInit' data structure 
					// defined in 'Messages.hpp'.
					ShapeInit myVehicleShape;

					// Send the type of the previously instantiated shape to the server.
					myVehicleShape.type = RECTANGULAR_PRISM;
					
					// Send the position of the previously instantiated shape to the server.
					myVehicleShape.xyz[0] = rect->getX();
					myVehicleShape.xyz[1] = rect->getY();
					myVehicleShape.xyz[2] = rect->getZ();
					myVehicleShape.rotation = rect->getRotation();

					// Send the colour of the previously instantiated shape to the server.
					myVehicleShape.rgb[0] = rect->getRed();
					myVehicleShape.rgb[1] = rect->getGreen();
					myVehicleShape.rgb[2] = rect->getBlue();
					
					// Send the dimensions of the previously instantiated shape to the server.
					myVehicleShape.params.rect.xlen = rect->getX_length();
					myVehicleShape.params.rect.ylen = rect->getY_length();
					myVehicleShape.params.rect.zlen = rect->getZ_length();

					// Add the previously instantiated shape to the 'ShapeInit' vector in the 'VehicleModel'
					// data structure defined in 'Messages.hpp'.
					vm.shapes.push_back(myVehicleShape);

					// Add the bumper of the vehicle to the shape vector.
					TriangularPrism * tri = new TriangularPrism(3, 0, 0, 0, 2, 2, 2, 90);
					vehicle->addShape(tri);

					myVehicleShape.type = TRIANGULAR_PRISM;
					myVehicleShape.xyz[0] = tri->getX();
					myVehicleShape.xyz[1] = tri->getY();
					myVehicleShape.xyz[2] = tri->getZ();
					myVehicleShape.rotation = tri->getRotation();

					myVehicleShape.rgb[0] = tri->getRed();
					myVehicleShape.rgb[1] = tri->getGreen();
					myVehicleShape.rgb[2] = tri->getBlue();

					myVehicleShape.params.tri.alen = tri->getA_length();
					myVehicleShape.params.tri.angle = tri->getTheta();
					myVehicleShape.params.tri.blen = tri->getB_length();
					myVehicleShape.params.tri.depth = tri->getDepth();

					vm.shapes.push_back(myVehicleShape);

					// Add the spoiler of the vehicle to the shape vector.
					TrapezoidPrism * trap = new TrapezoidPrism(-2, 2, 0, 0, 2, 2, 1, 2, 1);
					vehicle->addShape(trap);

					myVehicleShape.type = TRAPEZOIDAL_PRISM;
					myVehicleShape.xyz[0] = trap->getX();
					myVehicleShape.xyz[1] = trap->getY();
					myVehicleShape.xyz[2] = trap->getZ();
					myVehicleShape.rotation = trap->getRotation();

					myVehicleShape.rgb[0] = trap->getRed();
					myVehicleShape.rgb[1] = trap->getGreen();
					myVehicleShape.rgb[2] = trap->getBlue();

					myVehicleShape.params.trap.alen = trap->getA_length();
					myVehicleShape.params.trap.aoff = trap->getA_offset();
					myVehicleShape.params.trap.blen = trap->getB_length();
					myVehicleShape.params.trap.depth = trap->getDepth();
					myVehicleShape.params.trap.height = trap->getHeight();
					
					vm.shapes.push_back(myVehicleShape);
					
					// Add the front left wheel to the shape vector.
					Cylinder * cyl = new Cylinder(1, 0, -1, steering, 0.75, 1);
					vehicle->addShape(cyl);
					
					myVehicleShape.type = CYLINDER;
					myVehicleShape.xyz[0] = cyl->getX();
					myVehicleShape.xyz[1] = cyl->getY();
					myVehicleShape.xyz[2] = cyl->getZ();
					myVehicleShape.rotation = cyl->getRotation();

					myVehicleShape.rgb[0] = cyl->getRed();
					myVehicleShape.rgb[1] = cyl->getGreen();
					myVehicleShape.rgb[2] = cyl->getBlue();

					myVehicleShape.params.cyl.depth = cyl->getDepth();
					myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
					myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
					myVehicleShape.params.cyl.radius = cyl->getRadius();
					
					vm.shapes.push_back(myVehicleShape);

					// Add the front right wheel to the shape vector.
					cyl = new Cylinder(1, 0, 1, steering, 0.75, 1);
					vehicle->addShape(cyl);

					myVehicleShape.type = CYLINDER;
					myVehicleShape.xyz[0] = cyl->getX();
					myVehicleShape.xyz[1] = cyl->getY();
					myVehicleShape.xyz[2] = cyl->getZ();
					myVehicleShape.rotation = cyl->getRotation();

					myVehicleShape.rgb[0] = cyl->getRed();
					myVehicleShape.rgb[1] = cyl->getGreen();
					myVehicleShape.rgb[2] = cyl->getBlue();
					
					myVehicleShape.params.cyl.depth = cyl->getDepth();
					myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
					myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
					myVehicleShape.params.cyl.radius = cyl->getRadius();

					vm.shapes.push_back(myVehicleShape);

					// Add the back left wheel to the shape vector.
					cyl = new Cylinder(-1, 0, -1, 0, 0.75, 1);
					vehicle->addShape(cyl);

					myVehicleShape.type = CYLINDER;
					myVehicleShape.xyz[0] = cyl->getX();
					myVehicleShape.xyz[1] = cyl->getY();
					myVehicleShape.xyz[2] = cyl->getZ();
					myVehicleShape.rotation = cyl->getRotation();

					myVehicleShape.rgb[0] = cyl->getRed();
					myVehicleShape.rgb[1] = cyl->getGreen();
					myVehicleShape.rgb[2] = cyl->getBlue();

					myVehicleShape.params.cyl.depth = cyl->getDepth();
					myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
					myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
					myVehicleShape.params.cyl.radius = cyl->getRadius();

					vm.shapes.push_back(myVehicleShape);

					// Add the back right wheel to the shape vector.
					cyl = new Cylinder(-1, 0, 1, 0, 0.75, 1);
					vehicle->addShape(cyl);

					myVehicleShape.type = CYLINDER;
					myVehicleShape.xyz[0] = cyl->getX();
					myVehicleShape.xyz[1] = cyl->getY();
					myVehicleShape.xyz[2] = cyl->getZ();
					myVehicleShape.rotation = cyl->getRotation();

					myVehicleShape.rgb[0] = cyl->getRed();
					myVehicleShape.rgb[1] = cyl->getGreen();
					myVehicleShape.rgb[2] = cyl->getBlue();

					myVehicleShape.params.cyl.depth = cyl->getDepth();
					myVehicleShape.params.cyl.isRolling = cyl->getIfRolling();
					myVehicleShape.params.cyl.isSteering = cyl->getIfSteering();
					myVehicleShape.params.cyl.radius = cyl->getRadius();

					vm.shapes.push_back(myVehicleShape);

>>>>>>> z5118383
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
<<<<<<< HEAD
								// Create a pointer to access information about the vehicles and shapes from the server.
								ShapeInit * ServerShape = new ShapeInit;
								/*if (ServerShape->type = RECTANGULAR_PRISM) {
									// Set the dimensions of the obtained shape to what was given by another user.
									ServerShape->params.rect.xlen;
									ServerShape->params.rect.ylen;
									ServerShape->params.rect.zlen;
									
									// Set the colour of the obtained shape to what was given by another user.
									vehicle->setColor(ServerShape->rgb[0], ServerShape->rgb[1], ServerShape->rgb[2]);
									
									// Set the position of the obtained shape to what was given by another user.
									vehicle->setX(ServerShape->xyz[0]);
									vehicle->setY(ServerShape->xyz[1]);
									vehicle->setZ(ServerShape->xyz[2]);
									vehicle->setRotation(ServerShape->rotation);
								} else if (ServerShape->type = TRIANGULAR_PRISM) {
									ServerShape->params.tri.alen;
									ServerShape->params.tri.angle;
									ServerShape->params.tri.blen;
									ServerShape->params.tri.depth;
									
									vehicle->setColor(ServerShape->rgb[0], ServerShape->rgb[1], ServerShape->rgb[2]);

									vehicle->setX(ServerShape->xyz[0]);
									vehicle->setY(ServerShape->xyz[1]);
									vehicle->setZ(ServerShape->xyz[2]);
									vehicle->setRotation(ServerShape->rotation);
								} else if(ServerShape->type = TRAPEZOIDAL_PRISM) {
									ServerShape->params.trap.alen;
									ServerShape->params.trap.aoff;
									ServerShape->params.trap.blen;
									ServerShape->params.trap.depth;
									ServerShape->params.trap.height;
									
									vehicle->setColor(ServerShape->rgb[0], ServerShape->rgb[1], ServerShape->rgb[2]);

									vehicle->setX(ServerShape->xyz[0]);
									vehicle->setY(ServerShape->xyz[1]);
									vehicle->setZ(ServerShape->xyz[2]);
									vehicle->setRotation(ServerShape->rotation);
								} else if (ServerShape->type = CYLINDER) {
									ServerShape->params.cyl.depth;
									ServerShape->params.cyl.isRolling;
									ServerShape->params.cyl.isSteering;
									ServerShape->params.cyl.radius;
									
									vehicle->setColor(ServerShape->rgb[0], ServerShape->rgb[1], ServerShape->rgb[2]);

									vehicle->setX(ServerShape->xyz[0]);
									vehicle->setY(ServerShape->xyz[1]);
									vehicle->setZ(ServerShape->xyz[2]);
									vehicle->setRotation(ServerShape->rotation);
								}*/
=======
								for (std::vector<ShapeInit>::iterator it = vm.shapes.begin(); it != vm.shapes.end(); it++) {							
									if (it->type = RECTANGULAR_PRISM) {
										
										// Create a pointer to access information about the current vehicle and the
										// shapes used to define it from the server.
										RectangularPrism * rect = new RectangularPrism(0, 0, 0, 0, 0, 0, 0);

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

										// Add the newly defined shape to be drawn into the shape vector 
										// defined in 'Vehicle.hpp'
										otherVehicles[vm.remoteID]->addShape(rect);
									}
									// ** ADDS TRIANGLES INCORRECTLY, RECEIVES THEM AS REALLY LONG RECTANGLES
									else if (it->type = TRIANGULAR_PRISM) {
										TriangularPrism * tri = new TriangularPrism(0, 0, 0, 0, 0, 0, 0, 0);

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
									// ** ADDS TRAPEZOIDS INCORRECTLY, RECEIVES THEM AS RECTANGLES
									else if (it->type = TRAPEZOIDAL_PRISM) {
										TrapezoidPrism * trap = new TrapezoidPrism(0, 0, 0, 0, 0, 0, 0, 0, 0);

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
									// ** ADDS CYLINDERS INCORRECTLY, RECEIVES THEM AS RECTANGLES
									else if (it->type = CYLINDER) {
										Cylinder * cyl = new Cylinder(0, 0, 0, 0, 0, 0);

										cyl->setRadius(it->params.cyl.radius);
										cyl->setDepth(it->params.cyl.depth);
										cyl->setIfRolling(it->params.cyl.isRolling);
										cyl->setIfSteering(it->params.cyl.isSteering);

										cyl->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);

										cyl->setX(it->xyz[0]);
										cyl->setY(it->xyz[1]);
										cyl->setZ(it->xyz[2]);
										cyl->setRotation(it->rotation);
										
										otherVehicles[vm.remoteID]->addShape(cyl);
									}
								}
>>>>>>> z5118383
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


