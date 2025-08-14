/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       PAT                                                       */
/*    Created:      7/24/2025, 9:35:03 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
//sensors
inertial in = inertial(PORT1);
rotation vert = rotation(PORT2); //add ,true if wheel is on backwards
rotation horiz = rotation(PORT3);

//motors
motor right = motor(PORT4);
motor left = motor(PORT5);
// define your global instances of motors and othwher devices here

double xGlobalPosition=0;
double yGlobalPosition=0;
double globalRotationRad=0;
float vertoffset=0;
float horizoffset=0;
float wheelcircum = 1.95*M_PI;

//deg to rad
double degtorad(float degrees){
  double radians = degrees*M_PI/180;
  return radians;
}
//rotations the wheel spins convert to distance
double calcdistance(float inputrotation){
  float distancetraveled = inputrotation*wheelcircum;
  return distancetraveled;
}

// void odonprint(void){
// Brain.Screen.print("current position(");
// }

double vertPrevPosition=0;
double horizPrevPosition=0;
double prevRotation=0;

void odomupdatepos(void){
  //current position
double vertCurrent = vert.position(rev);
double horizCurrent = horiz.position(rev);
double rotationCurrent = in.angle(deg);
//change in position from prev to current
double vertChange= vertCurrent-vertPrevPosition;
double horizChange = horizCurrent-horizPrevPosition;
double rotationChangeRad=degtorad(rotationCurrent)-prevRotation;
//update the current position
vertPrevPosition=vertCurrent;
horizPrevPosition=horizCurrent;
prevRotation=degtorad(rotationCurrent);
//account for wraparound errors
//left turn
if(rotationChangeRad > M_PI){
  rotationChangeRad -= 2*M_PI;
}
//right turn
else if (rotationChangeRad<-M_PI){
  rotationChangeRad+= 2*M_PI;
}

//makes a variable for vertical or horizonal change
double localVertChange = calcdistance(vertChange);
double localHorChange = calcdistance(horizChange);

//calc local xy change 
double localXPosition=localHorChange-(horizoffset*rotationChangeRad);
double localYPosition=localVertChange-(vertoffset*rotationChangeRad);

//polar(positive) angle and length variables
double localPolarAngle;
double localPolarLength;

//if the robot stayed in the same spot, then polar angle and length are 0
if(localXPosition==0 and localYPosition==0){
  localPolarAngle=0;               //== is to check if a value is something
  localPolarLength=0;              //= is to set a value
}
else{
  //polar angle is calc by arctan, input x and y, output angle
  localPolarAngle = atan2(localYPosition, localXPosition); //atan2=arctan
  //use pythagorean thoerorm to get polar length
  localPolarLength = sqrt(pow(localXPosition,2)+pow(localYPosition,2));
}
 //calc global angle, angle that your robot is globally
 double globalPolarAngle = (localPolarAngle-degtorad(rotationCurrent));

 //use global angle and local length to get change in xy
 double xChangeGlobal=localPolarLength*cos(globalPolarAngle);
 double yChangeGlobal=localPolarLength*sin(globalPolarAngle);
 //add change to global position
 xGlobalPosition+=xChangeGlobal;
 yGlobalPosition+=yChangeGlobal;
 globalRotationRad=globalPolarAngle;
 wait(5,msec);
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
