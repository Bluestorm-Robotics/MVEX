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
motor Arm = motor(PORT10);
//motor leftArm = motor(PORT20);
//Plow Motor
motor leftPlow = motor(PORT12);
motor rightPlow = motor(PORT3);

//motor groups TANK layout :)
motor_group leftDrive(frontLeft, backLeft);
motor_group rightDrive(frontRight, backRight);
motor_group awd(frontLeft, frontRight, backLeft, backRight);
motor_group plow(leftPlow, rightPlow);
//motor_group Arm(leftArm, rightArm);
int mtrVolt = 8; //MAX 12V DC
int plowVolt = 6; //MAX 12V DC


//throw functions below
void rsMotors(){
    awd.setPosition(0, degrees);
    plow.setPosition(0, degrees);
}

float convertCMToDegrees(float y){ //converts CM imput to wheel degrees
	return y/(M_PI*WheelDiamterCM)*360.0;
}

float CalcRadToDeg(float x){
	return x*(robotDiameterCM/WheelDiamterCM);
}

void moveCM(float y, int v){ //move given distance in CM (Y is CM imput Z is direction)
	float x=convertCMToDegrees(y);
    awd.spinFor(forward, x, degrees, v, velocityUnits::pct, true);
}

void openArm(){
    /*rsMotors();
    rightPlow.spinToPosition(240, degrees, false);
    leftPlow.spinToPosition(240, degrees, true);*/
    plow.spin(directionType::rev, 6.0, volt);
    wait(1.5, seconds);
    plow.stop(brake);
}


void pointTurn(int x){
    int vpointTurn=CalcRadToDeg(x);
    leftDrive.spinFor(-vpointTurn, degrees, 30, velocityUnits::pct, false);
    rightDrive.spinFor(vpointTurn, degrees, 30, velocityUnits::pct, true);
}