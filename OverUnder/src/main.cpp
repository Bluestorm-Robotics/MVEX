/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       will                                                      */
/*    Created:      11/7/2023, 4:40:49 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Robot.h"



vex::motor_group myDrivetrain(leftMotor, RightMotor);

controller controller1 = controller(controllerType::primary);


using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here



int main() {

    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
       if (controller1.ButtonA.pressing()) {
        turnRight(90);
    }

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
