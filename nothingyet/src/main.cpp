/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       1723A                                                     */
/*    Created:      12/8/2023, 4:14:31 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "customLib.h"
#include "iostream"

using namespace vex;
// A global instance of vex::brain used for printing to the V5 brain screen
brain       Brain; //After declaring vex namespace there is no need to use vex::brain
controller       controller1;

competition Competition; //Competition mode


void mtrProperties(){ //Starting motor Defaults
    backRight.setReversed(true);
    frontRight.setReversed(true);
    rightPlow.setReversed(true);
    leftArm.setReversed(true);
    plow.stop(hold);
    WheelDiamterCM = 10.58; //10.6 cm
}

void driver(){
   
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
        awd.stop(brake);
        //Brain.Screen.print("Coasting %f\n", Brain.Timer.value());
        //Brain.Screen.newLine();
   } 
}

void autonomous(void){//Autonomous code
    Brain.Screen.print("Autonomous code started!!! %f\n", Brain.Timer.value());
    Brain.Screen.newLine();

    moveCM(128);
    leftPointTurn();
    moveCM(-15);
    //Open arm
    //moveCM(However much to the net)
}

void armFling(){
    if (controller1.ButtonUp.pressing() == true){
        Arm.spin(directionType::rev, 12.0, volt);

        //Arm.spinFor(reverse, 105, degrees, false);
        Brain.Screen.print("Forwarding arm!!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
    else if(controller1.ButtonDown.pressing() == true){
        Arm.spin(directionType::fwd, 8.0, volt); 
        //Arm.spinFor(forward, 105, degrees, false);
        Brain.Screen.print("Reversing arm!!! %f\n", Brain.Timer.value());
        Brain.Screen.newLine();
    }
    else{
        Arm.stop(hold);
    }     
}

void plowControlls(){//L1 L2 for left plow R1/R2 for right
    if((controller1.ButtonL1.pressing() == true) && (controller1.ButtonR1.pressing() == true)){
     plow.spin(directionType::fwd, mtrVolt, volt);  
    }

    else if((controller1.ButtonL2.pressing() == true) && (controller1.ButtonR2.pressing() == true)){
        plow.spin(directionType::rev, mtrVolt, volt);
    }
    else if(controller1.ButtonL1.pressing() == true){
     leftPlow.spin(directionType::fwd, mtrVolt, volt);  
    }

    else if(controller1.ButtonL2.pressing() == true){
        leftPlow.spin(directionType::rev, mtrVolt, volt);
    }

    else if(controller1.ButtonR1.pressing() == true){
        rightPlow.spin(directionType::fwd, mtrVolt, volt);  
    }

    else if(controller1.ButtonR2.pressing() == true){
        rightPlow.spin(directionType::rev, mtrVolt, volt);
    }

    else{
        plow.stop(hold);
    }
}

void turoMode(){
    if(controller1.ButtonX.pressing() == true){
        mtrVolt = 12.0;
    }
    else{
        mtrVolt = 8.0;
    }
}

void buttons(){
    armFling(); //Arm movement
    plowControlls(); //Plow movement
    turoMode();
}
void controlls(){ //Umbrella COntrols module
    while(1){

        driver(); //Movement Controls
        buttons(); //Button Controls
    }
}

void consoleLog(){

    if(Brain.Screen.row() > 11){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 2);
       }
}
void init(){
    mtrProperties();
    Brain.Screen.printAt( 10, 50, "Awaiting orders Captain!!" );
    Brain.Screen.newLine();
}
int main() {
    Competition.autonomous(autonomous);
    Competition.drivercontrol(controlls);
    init(); //Pre-Autonomos motor configs
    while(1) {
        consoleLog(); //On screen debug console
        this_thread::sleep_for(1);
    }
}