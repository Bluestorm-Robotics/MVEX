/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       will                                                      */
/*    Created:      11/7/2023, 4:40:49 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

controller controller1 = controller(controllerType::primary);

motor leftMotor = motor(PORT1);
motor RightMotor = motor(PORT2);
motor ClawMotor = motor(PORT8);
motor ArmMotor = motor(PORT7);

int main() {

    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
       if(controller1.ButtonA.pressing()){
    ClawMotor.spin(forward);
}
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
