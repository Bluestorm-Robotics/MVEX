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
brain       Brain;
controller       controller1;

#pragma config(Motor,  PORT5,           backRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  PORT1,           frontRight,      tmotorVex393_MC29, openLoop, reversed)
// define your global instances of motors and other devices here
// Front motors
motor frontLeft = motor(PORT11);
//motor frontRight = motor(PORT1);

//Rear Motors
motor backLeft = motor(PORT15);
//motor backRight = motor(PORT5);

//Arm Motor
motor Arm = motor(PORT10);

//motor groups TANK layout :)
motor_group leftDrive(frontLeft, backLeft);
motor_group rightDrive(frontRight, backRight);
motor_group awd(frontLeft, frontRight, backLeft, backRight);
void controlls(){
  // awd.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
  // leftDrive.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
   if(controller1.Axis4.position() > -25){
        leftDrive.spin(directionType::fwd);
        rightDrive.spin(directionType::fwd);
   }
    else if(controller1.Axis4.position() < 25){
        leftDrive.spin(directionType::rev);
        rightDrive.spin(directionType::rev);
   }
   else if(controller1.Axis3.position() < 25){
    awd.spin(directionType::fwd)
    }
  else{
    awd.stop(coast);
   }
}

void ArmCONTROL(){

    while (true) {

    Arm.setVelocity(100, percent);
    Arm.spin(forward);

    wait(1, seconds);

    Arm.setVelocity(100, percent);
    Arm.spin(reverse);

    wait(1, seconds);




    }
}

void ArmFling(){
    if(controller1.ButtonA.PRESSED){
        Arm.setVelocity(100, percent);
        Arm.spin(forward);
    }
    else if(controller1.ButtonB.PRESSED){
        Arm.setVelocity(100, percent);
        Arm.spin(reverse);
    }
}

int main() {
    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
       controlls();
       ArmFling();
        // Allow other tasks to run
        //ArmCONTROL();
        this_thread::sleep_for(10);
    }
}
