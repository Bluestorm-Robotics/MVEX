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

//Plow Motor
motor leftPlow = motor(PORT12);
motor rightPlow = motor(PORT3);

//motor groups TANK layout :)
motor_group leftDrive(frontLeft, backLeft);
motor_group rightDrive(frontRight, backRight);
motor_group awd(frontLeft, frontRight, backLeft, backRight);
motor_group plow(leftPlow, rightPlow);
int mtrVolt = 8; //MAX 12V DC

void mtrProperties(){ //Starting motor Defaults
    backRight.setReversed(true);
    frontRight.setReversed(true);
    rightPlow.setReversed(true);
    plow.stop(brake);
}
void driver(){

   int lineNum = 1; // Console logging
   
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


void armFling(){
    if (controller1.ButtonUp.pressing() == true){
        Arm.spin(directionType::rev, 12.0, volt);
        Brain.Screen.printAt( 10, 50, "Forwarding arm!" );
    }
    else if(controller1.ButtonDown.pressing() == true){
        Arm.spin(directionType::fwd, 12.0, volt); 
        Brain.Screen.printAt( 10, 50, "Reversing Arm!" );
    }
    else{
        Arm.stop(brake);
    }     
}

void plowControlls(){
    if(controller1.ButtonR1.pressing() == true){
     plow.spin(directionType::fwd);  
    }
    else if(controller1.ButtonL1.pressing() == true){
        plow.spin(directionType::rev);
    }
    else{
        plow.stop(brake);
    }
}


void buttons(){
    armFling(); //Arm movement
    plowControlls(); //Plow movement
}
void controlls(){ //Umbrella COntrols module
    driver(); //Movement Controls
    buttons(); //Button Controls
}

void consoleLog(){

    if(Brain.Screen.row() > 11){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 2);
       }
}

int main() {
    Brain.Screen.printAt( 10, 50, "Awaiting orders Captain!!" );
    Brain.Screen.newLine();
   
    while(1) {
        consoleLog();
        controlls();
        this_thread::sleep_for(1);
    }
}
