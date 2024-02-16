/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       1723A                                                     */
/*    Created:      12/8/2023, 4:14:31 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "autonLib.h"
#include "iostream"

using namespace vex;
// A global instance of vex::brain used for printing to the V5 brain screen
brain       Brain; //After declaring vex namespace there is no need to use vex::brain
controller       controller1;

competition Competition; //Competition mode

digital_in  d1(Brain.ThreeWirePort.A);

void mtrProperties(){ //Starting motor Defaults
    frontRightDrive.setReversed(true);
    backRightDrive.setReversed(true);
    rightPlow.setReversed(true);
    leftArm.setReversed(true);
    rightElevate.setReversed(true);
    plow.stop(hold);
    WheelDiamterCM = 10.58; //10.6 cm
}

void driver(){
   
   if((controller1.Axis4.position() < -80) || (controller1.ButtonLeft.pressing() == true)){ //Turn left
        leftDrive.spin(directionType::rev, mtrVolt, volt);
        rightDrive.spin(directionType::fwd, mtrVolt, volt);
        Brain.Screen.print("Turning left %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
   }
    else if((controller1.Axis4.position() > 80) || (controller1.ButtonRight.pressing() == true)){ //Turn right
        leftDrive.spin(directionType::fwd, mtrVolt, volt);
        rightDrive.spin(directionType::rev, mtrVolt, volt);
        Brain.Screen.print("Hard to Starboard!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
   }
   else if((controller1.Axis3.position() > 80) || (controller1.ButtonUp.pressing() == true)){ //Forward
        awd.spin(directionType::fwd, mtrVolt, volt);
        Brain.Screen.print("Full steam ahead! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
    else if((controller1.Axis3.position() < -80) || (controller1.ButtonDown.pressing() == true)){ //Reverse
        awd.spin(directionType::rev, mtrVolt, volt); 
        Brain.Screen.print("Reverse!!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
   else{ //If not imput brake
        awd.stop(hold);
        //Brain.Scr een.print("Coasting %f\n", Brain.Timer.value());
        //Brain.Screen.newLine();
   } 
}
void arcadeDrive(){
  int deadband = 5;

    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int leftMotorSpeed =
        controller1.Axis3.position() + controller1.Axis4.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int rightMotorSpeed =
        controller1.Axis3.position() - controller1.Axis4.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      leftDrive.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      leftDrive.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      rightDrive.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      rightDrive.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    leftDrive.spin(forward);
    rightDrive.spin(forward);

    wait(25, msec);
}

void autonModeCheck(){ //Sets autonomous mode for Defence/Offence side
    if(d1.value() == 1){
        defence = false; // Autonomous mode
        Brain.Screen.print("Switch to offense %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
    else{
        defence = true;  
        Brain.Screen.print("Switch to Defence %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
}

void autonomous(void){//Autonomous code
    Brain.Screen.print("Taking the Helm captain! %f\n", Brain.Timer.value());
    Brain.Screen.newLine();
    bool skills = false;
    if(skills == false){
        matchAuton();
    }
    else{
        skillsAuton();
    }
}


void armFling(){ // Legacy code no longer in use
    if(controller1.ButtonA.pressing() == true){
        Arm.spin(directionType::rev, 5, volt); 
        //Arm.spinFor(forward, 105, degrees, false);
        Brain.Screen.print("Reversing arm!!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
    if(controller1.ButtonY.pressing() == true){
        Arm.spin(directionType::fwd, 10, volt); 
        //Arm.spinFor(forward, 105, degrees, false);
        Brain.Screen.print("forwarding arm!!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine(); 
    }
    else{
        Arm.stop(hold);
    }     
}

void plowControlls(){//L1 L2 for left plow R1/R2 for right
    if((controller1.ButtonL1.pressing() == true) && (controller1.ButtonR1.pressing() == true)){
     plow.spin(directionType::fwd, plowVolt, volt);  
    }

    else if((controller1.ButtonL2.pressing() == true) && (controller1.ButtonR2.pressing() == true)){
        plow.spin(directionType::rev, plowVolt, volt);
    }

    else if(controller1.ButtonL1.pressing() == true){
     leftPlow.spin(directionType::fwd, plowVolt, volt);  
    }

    else if(controller1.ButtonL2.pressing() == true){
        leftPlow.spin(directionType::rev, plowVolt, volt);
    }

    else if(controller1.ButtonR1.pressing() == true){
        rightPlow.spin(directionType::fwd, plowVolt, volt);  
    }

    else if(controller1.ButtonR2.pressing() == true){
        rightPlow.spin(directionType::rev, plowVolt, volt);
    }

    else{
        plow.stop(hold);
    }
}

void turboMode(){
    if(controller1.ButtonX.pressing() == true){
        mtrVolt = 12.0;
        elevateVolt = 100;
    }
    else{
        mtrVolt = 9.0;
        elevateVolt = 20;
    }
}

void noclip(){ //arm thingy thing thingy-ma bob / doohickey
    if(controller1.Axis2.position() > 80){
        //noclip go uppy up
        elevate.setVelocity(elevateVolt, percent);
        elevate.spin(forward);
      }
    else if(controller1.Axis2.position() < -80){
        // noclip go uppy up
        elevate.setVelocity(elevateVolt, percent);
        elevate.spin(reverse);
      }
    else{
        elevate.stop(hold);
    }
}

void buttons(){
    armFling(); //Arm movement
    plowControlls(); //Plow movement
    turboMode();
    noclip();
}

void consoleLog(){
// Code for moving cursor to new line for console log
    if(Brain.Screen.row() > 11){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 2);
    }
}
void controlls(){ //Umbrella COntrols module
    while(1){
        consoleLog();
        //arcadeDrive(); terrible
        driver(); //Movement Controls
        buttons(); //Button Controls
    }
}


void init(){ //First code to run
    //autonModeCheck();
    mtrProperties();
    Brain.Screen.printAt( 10, 50, "Awaiting orders Captain!!" );
    Brain.Screen.newLine();
}
int main() {
    init(); //Pre-Autonomos motor configs
    Competition.autonomous(autonomous);
    Competition.drivercontrol(controlls);
    this_thread::sleep_for(1);
}