
#pragma once
#include "vex.h"
//Call the namespace so you don't have to add vex:: in front of everything
using namespace vex;




void vexcodeInit(void);

extern vex::motor leftMotor;
extern vex::motor rightMotor;
extern vex::motor_group myDrivetrain;
extern vex::brain Brain;

controller controller1 = controller(controllerType::primary);

motor leftMotor = motor(PORT1);
motor RightMotor = motor(PORT2);
motor ClawMotor = motor(PORT8);
motor ArmMotor = motor(PORT7);
