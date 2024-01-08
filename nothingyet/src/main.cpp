/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       MA                                                        */
/*    Created:      12/8/2023, 4:14:31 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "iostream"

using namespace vex;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller       controller1;


// define your global instances of motors and other devices here
// Front motors
motor frontLeft = motor(PORT11);
motor frontRight = motor(PORT1);

//Rear Motors
motor backLeft = motor(PORT16);
motor backRight = motor(PORT5);

//motor groups TANK layout :)
motor_group leftDrive(frontLeft, backRight);
motor_group rightDrive(frontRight, backRight);
motor_group awd(frontLeft, frontRight, backLeft, backRight);
void controlls(){
  // awd.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
  // leftDrive.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
   if(controller1.Axis4.position() > 25){
        leftDrive.spin(directionType::fwd);
        rightDrive.spin(directionType::rev);
   }
    if(controller1.Axis4.position() < -25){
        leftDrive.spin(directionType::rev);
        rightDrive.spin(directionType::fwd);
   }
   else{
    awd.stop(coast);
   }
}


int main() {
    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
       controlls();
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
