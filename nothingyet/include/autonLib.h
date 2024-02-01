#include <math.h>
#include <vex.h>
float WheelDiamterCM = 10.58;
float robotDiameterCM = 35.65;
using namespace vex;

/// MOTOR CONFIG

//Drive motors
motor leftDrive = motor(PORT20);
motor rightDrive = motor(PORT9);

//Arm Motor
motor rightArm = motor(PORT21);
motor leftArm = motor(PORT18);
//Plow Motor
motor leftPlow = motor(PORT12);
motor rightPlow = motor(PORT3);

//Elevate motors

motor leftElevate = motor(PORT19);
motor rightElevate = motor(PORT10);


//motor groups TANK layout :)1
motor_group awd(leftDrive, rightDrive);
motor_group plow(leftPlow, rightPlow);
motor_group Arm(leftArm, rightArm);
motor_group elevate(rightElevate, leftElevate);
int mtrVolt = 8; //MAX 12V DC
int plowVolt = 6; //MAX 12V DC
int elevateVolt = 1; //MAX 12V DC
bool defence = false;

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
    plow.stop(hold);
}

void closeArm(){
    /*rsMotors();
    rightPlow.spinToPosition(240, degrees, false);
    leftPlow.spinToPosition(240, degrees, true);*/
    plow.spin(directionType::fwd, 6.0, volt);
    wait(1.5, seconds);
    plow.stop(hold);
}


void pointTurn(int x){
    int vpointTurn=CalcRadToDeg(x);
    leftDrive.spinFor(-vpointTurn, degrees, 30, velocityUnits::pct, false);
    rightDrive.spinFor(vpointTurn, degrees, 30, velocityUnits::pct, true);
}