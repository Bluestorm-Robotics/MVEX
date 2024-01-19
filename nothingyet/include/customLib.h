#include <math.h>
#include <vex.h>
float WheelDiamterCM = 10.58;
float robotDiameterCM = 35.65;

using namespace vex;

/// MOTOR CONFIG
motor frontLeft = motor(PORT11);
motor frontRight = motor(PORT1);

//Rear Motors
motor backLeft = motor(PORT15);
motor backRight = motor(PORT5);

//Arm Motor
motor rightArm = motor(PORT10);
motor leftArm = motor(PORT20);
//Plow Motor
motor leftPlow = motor(PORT12);
motor rightPlow = motor(PORT3);

//motor groups TANK layout :)
motor_group leftDrive(frontLeft, backLeft);
motor_group rightDrive(frontRight, backRight);
motor_group awd(frontLeft, frontRight, backLeft, backRight);
motor_group plow(leftPlow, rightPlow);
motor_group Arm(leftArm, rightArm);
int mtrVolt = 8; //MAX 12V DC


//throw functions below
void rsMotors(){
    awd.setPosition(0, degrees);
}

float convertCMToDegrees(float y){ //converts CM imput to wheel degrees
	return y/(M_PI*WheelDiamterCM)*360.0;
}

float CalcRadToDeg(float x){
	return x*(robotDiameterCM/WheelDiamterCM);
}

void moveCM(float y){ //move given distance in CM (Y is CM imput Z is direction)
	float x=convertCMToDegrees(y);
	rsMotors();
    awd.spinToPosition(x, degrees, true);
}



void leftPointTurn(){
    int vpointTurn=CalcRadToDeg(90);
    rsMotors();
    leftDrive.spinToPosition(-vpointTurn, degrees, false);
    rightDrive.spinToPosition(vpointTurn, degrees, true);
    rsMotors();

}

void rightPointTurn(){
    int vpointTurn=CalcRadToDeg(90);
    rsMotors();
    leftDrive.spinToPosition(vpointTurn, degrees, false);
    rightDrive.spinToPosition(-vpointTurn, degrees, true);
    rsMotors();

}