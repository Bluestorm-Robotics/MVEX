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

digital_in  d1(Brain.ThreeWirePort.B);

void mtrProperties(){ //Starting motor Defaults
    rightDrive.setReversed(true);
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
        awd.stop(brake);
        //Brain.Screen.print("Coasting %f\n", Brain.Timer.value());
        //Brain.Screen.newLine();
   } 
}


void autonomous(void){//Autonomous code
    Brain.Screen.print("Autonomous code started!!! %f\n", Brain.Timer.value());
    Brain.Screen.newLine();
// Has tendency to slip side of net
    if(defence == true){

        moveCM(43, 40);
        closeArm();
        pointTurn(25);
        moveCM(97, 40);
        pointTurn(-25);
        pointTurn(-90);
        wait(1, seconds);
        openArm();
        moveCM(55, 60);
    }
    else{
        moveCM(43, 40);
        closeArm();
        pointTurn(-25);
        moveCM(97, 40);
        pointTurn(25);
        pointTurn(90);
        wait(1, seconds);
        openArm();
        moveCM(55, 60);
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
        Arm.spin(directionType::fwd, 12, volt); 
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
        mtrVolt = 8.0;
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
        driver(); //Movement Controls
        buttons(); //Button Controls
    }
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

void init(){ //First code to run
    autonModeCheck();
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