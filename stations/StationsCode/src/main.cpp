/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       zgriz                                                     */
/*    Created:      8/12/2025, 10:38:45 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
// define your global instances of motors and other devices here

controller mainControl = controller(primary);

//drivetrain motors
//each one of these motors has a name corresponding with its position (ex: RM- Right Middle)
//each motor also has the port it's plugged into(PORT1), its cartrige(ratio6_1), and if it's reversed (true)
motor RF = motor(PORT1,ratio6_1,true);
motor RM = motor(PORT2,ratio6_1);
motor RB = motor(PORT3,ratio6_1);
motor LF = motor(PORT4,ratio6_1);
motor LM = motor(PORT5,ratio6_1,true);
motor LB = motor(PORT6,ratio6_1,true);

//Since we'll never need to spin a specific motor, it's eaiser to split up the motors into groups,
//One for the left side, and one for the right.
motor_group rAll = motor_group(RF,RM,RB);
motor_group lAll = motor_group(LF,LM,LB);

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
void driveFor(directionType direction,float distance){
//The wheelcircum shows that our wheel circumference is 9.625 inches
float wheelcircum = 9.625;
//The gearRatio is showing that every 36 turns of the motor is 48 rotations of the wheel
float gearRatio=48/36;
//The calcdeg is doing the math that turns the rotations to inches
float calcdeg = (distance/wheelcircum)*gearRatio*360;
//The rall makes all of the motors on the right side of the drive train move a certain amount of inches
  rAll.spinFor(direction,calcdeg,deg,false);
  //The lall makes all of the motors on the left side of the drive train move a certain amount of inches  
  lAll.spinFor(direction,calcdeg,deg);
}    
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

    //Drivetrain code
    //this line reads the joystick value as a percentage
    float rSpeed = mainControl.Axis2.position(pct);
    float lSpeed = mainControl.Axis3.position(pct);

    //this line spins the motors of the drivetrain based on the speed calculated above
    //the unit is voltage, which is why it's being multipled by .12
    rAll.spin(forward,rSpeed*.12,volt);
    lAll.spin(forward,lSpeed*.12,volt);

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
