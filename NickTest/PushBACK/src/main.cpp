/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nwilhelm                                                  */
/*    Created:      7/23/2025, 9:38:17 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

motor Arm = motor(PORT1, ratio18_1, true);
motor LF = motor(PORT18, ratio6_1, true);
motor LM = motor(PORT15, ratio6_1, true);
motor LB = motor(PORT5, ratio6_1, true);
motor RF = motor(PORT16, ratio6_1);
motor RM = motor(PORT19, ratio6_1);
motor RB = motor(PORT13, ratio6_1);
controller remote = controller(primary);

motor_group leftAll = motor_group(LF, LM, LB);
motor_group rightAll = motor_group(RF, RM, RB);

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

void armUP(void) {
  Arm.spin(fwd);
}

void armStop(void) {
  Arm.stop();
}

void armDown(void) {
  Arm.spin(reverse);
}
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    remote.ButtonA.pressed(armUP);

    remote.ButtonA.released(armStop);

    remote.ButtonB.pressed(armDown);

    remote.ButtonB.released(armStop);
    
    float Lpower = remote.Axis3.position();
    float Rpower = remote.Axis2.position();

    leftAll.spin(fwd, Lpower*.12, volt);
    rightAll.spin(fwd, Rpower*.12, volt);
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
