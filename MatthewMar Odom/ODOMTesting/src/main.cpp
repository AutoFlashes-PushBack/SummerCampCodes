/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       user                                                      */
/*    Created:      7/24/2025, 10:10:38 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
motor m1=motor(PORT15,ratio6_1,true);
motor m2=motor(PORT16,ratio6_1);
motor_group all=motor_group(m1,m2);

controller player= controller();

//Measures where the robot goes
inertial spinner = inertial(PORT8); 
//These are the little tracking wheels
rotation xaxiswheel = rotation(PORT7);
rotation yaxiswheel = rotation(PORT9);
//These are the drive train motors
motor Left = motor(PORT1);
motor Right = motor(PORT2);

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//Odom

double xGlobalPosition=0;
double yGLobalPosition=0;

double GlobalRotationRad=0;

//Float variables change with editing
float xaxiswheeloffset=0;
float yaxiswheeloffset=0;

float trackingWheel = 1.95*M_PI;

double degToRad(float degrees){

double radians =degrees * M_PI/180;

return radians;
}

double caldist(float imputRotation){

float disTraveled = (imputRotation)*trackingWheel;
return disTraveled;
}

// void Odomprint(void){
// while(true){
// Brain.Screen.print.clearScreen();

// Brain.Screen.setCursor(1,1);
// Brain.Screen.print("Current Position ()");


// }
// }

double yaxisPrePosition=0;
double xaxisPrePosition=0;
double preRotationRad=0;

void odomUpdatePosition(void){

double yaxisCurrent = yaxiswheel.position(rev);
double xaxisCurrent = xaxiswheel.position(rev);
double rotationCurrent=spinner.angle(deg);



double yaxiswheelChange = yaxisCurrent-yaxisPrePosition;
double xaxiswheelChange = xaxisCurrent-xaxisPrePosition;
double rotationChange=degToRad(rotationCurrent)-preRotationRad;
//We are doing this to reset the process
yaxisPrePosition=yaxisCurrent;
xaxisPrePosition=xaxisCurrent;
preRotationRad=degToRad(rotationCurrent);

  if (rotationChange>M_PI){
    rotationChange -= 2 * M_PI;
}

  else if (rotationChange<-M_PI){
  rotationChange += 2 * M_PI;
}

double localVertchange = disTraveled(vertChange);
double localHorChange = disTraveled(horChange);

//Makes it to where when you spin you can calculate for the offset due to the wheels not being directly in the center
double localXPosition=localVertChange-(xaxiswheeloffset*rotationChange);
double localYPosition=localHorChange-(yaxiswheeloffset*rotationChange);

double localPolarAngle;
double localPolarLength;

if (localXPosition==0 and localYPosition==0){
    localPolarAngle=0;
    localPolarLength=0;
}

else{
  localPolarAngle = atan2(localYPosition, localXPosition);

  localPolarLength = sqrt(pow(localXPosition,2) + pow(localYPosition,2));
}

double globalPolarAngle = (localPolarAngle-degToRad(rotationCurrent));


double xChangeGlobal=localPolarLength*cos(globalPolarAngle);
double yChangeGlobal=localPolarLength*sin(globalPolarAngle);

xGlobalPosition+=xChangeGlobal;
yGlobalPosition+=yChangeGlobal;
globalRotationRad=globalPolarAngle;
wait(5,msec);
}














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
void spinAll(void){
  all.spin(fwd);
}
void stopAll(void){
  all.stop();
}
void usercontrol(void) {
  all.setVelocity(100,pct);
  // User control code here, inside the loop
  while (1) {
    player.ButtonX.pressed(spinAll);
    player.ButtonX.released(stopAll);
    
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
