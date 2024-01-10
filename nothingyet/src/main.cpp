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

// define your global instances of motors and other devices here
// Front motors
motor frontLeft = motor(PORT11);
motor frontRight = motor(PORT1);

//Rear Motors
motor backLeft = motor(PORT15);
motor backRight = motor(PORT5);

//Arm Motor
motor Arm = motor(PORT10);

//motor groups TANK layout :)
motor_group leftDrive(frontLeft, backLeft);
motor_group rightDrive(frontRight, backRight);
motor_group awd(frontLeft, frontRight, backLeft, backRight);
int mtrVolt = 8; //MAX 12V DC
void controlls(){
    /*leftDrive.spin(directionType::fwd, controller1.Axis4.position() + controller1.Axis3.position(), percentUnits::pct);
    rightDrive.spin(directionType::fwd, controller1.Axis4.position() - controller1.Axis3.position(), percentUnits::pct);*/
  // awd.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
  // leftDrive.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
   int lineNum = 1;
   
   if(controller1.Axis4.position() < -80){
        leftDrive.spin(directionType::rev, mtrVolt, volt);
        rightDrive.spin(directionType::fwd, mtrVolt, volt);
        Brain.Screen.print("Turning left %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
   }
    else if(controller1.Axis4.position() > 80){
        leftDrive.spin(directionType::fwd, mtrVolt, volt);
        rightDrive.spin(directionType::rev, mtrVolt, volt);
        Brain.Screen.print("Hard to Starboard!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
   }
   else if(controller1.Axis3.position() > 80){
        awd.spin(directionType::fwd, mtrVolt, volt);
        Brain.Screen.print("Full steam ahead! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
    else if(controller1.Axis3.position() < -80){
        awd.spin(directionType::rev, mtrVolt, volt); 
        Brain.Screen.print("Reverse!!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
   else{
        awd.stop(coast);
        //Brain.Screen.print("Coasting %f\n", Brain.Timer.value());
        //Brain.Screen.newLine();
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
    if (controller1.ButtonA.pressing() == true){
        Arm.spin(directionType::fwd, mtrVolt, volt); 
    }
    /*else if(controller1.ButtonB.PRESSED){
        Arm.setVelocity(100, percent);
        Arm.spin(reverse);
    }*/
}

int main() {
    Brain.Screen.printAt( 10, 50, "Awaiting orders Captain!!" );
    Brain.Screen.newLine();
    backRight.setReversed(true);
    frontRight.setReversed(true);
   
    while(1) {
       controlls();
       ArmFling();
       if(Brain.Screen.row() > 11){
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 2);
       }
       //ArmFling();
        // Allow other tasks to run
        //ArmCONTROL();
        this_thread::sleep_for(1);
    }
}
