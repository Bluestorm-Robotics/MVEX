#include <math.h>
#include <vex.h>
float WheelDiamterCM = 10.064;
float robotDiameterCM = 34.3;
using namespace vex;

/// MOTOR CONFIG

//Drive motors
motor frontLeftDrive = motor(PORT20);
motor frontRightDrive = motor(PORT9);

motor backLeftDrive = motor(PORT17);
motor backRightDrive = motor(PORT8);

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
motor_group leftDrive(backLeftDrive, frontLeftDrive);
motor_group rightDrive(backRightDrive, frontRightDrive);
motor_group awd(frontLeftDrive, backLeftDrive, frontRightDrive, backRightDrive);
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

void moveCM(float y, int v){ //move given distance in CM (Y is CM imput v is mtr power)
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

void closeLeftArm(){
    leftPlow.spin(directionType::fwd, 2.0, volt);
    wait(1.5, seconds);
    plow.stop(hold);
}
void closeRightArm(){
    rightPlow.spin(directionType::fwd, 2.0, volt);
    wait(1.5, seconds);
    plow.stop(hold);
}

void pointTurn(int x){
    int vpointTurn=CalcRadToDeg(x);
    leftDrive.spinFor(-vpointTurn, degrees, 30, velocityUnits::pct, false);
    rightDrive.spinFor(vpointTurn, degrees, 30, velocityUnits::pct, true);
}
void rightPointTurn(int x){
    int vpointTurn=CalcRadToDeg(x);
    leftDrive.spinFor(vpointTurn, degrees, 30, velocityUnits::pct, true);
}

void matchAuton(){
    if(defence == true){
    closeRightArm();
    moveCM(45.72, 35);
    closeArm();
    pointTurn(25);
    moveCM(92, 40);
    pointTurn(-25);
    pointTurn(-90);
    wait(1, seconds);
    openArm();
    moveCM(55, 60);
    moveCM(-15, 60);
    }
    else{
    closeLeftArm();
    moveCM(45.72, 35);
    closeArm();
    pointTurn(-25);
    moveCM(92, 40);
    pointTurn(25);
    pointTurn(90);
    wait(1, seconds);
    openArm();
    moveCM(55, 60);
    moveCM(-15, 60);
    }
}
void noFriends(){ //function for automatic triball firing
    Arm.spin(directionType::fwd, 12.0, volt); 
}

void skillsAuton(){//Autonomous skills matches
    moveCM(21.59, 100); //Roughly 8.5 in
    moveCM(-21.59, 50);
    moveCM(21.59, 100);
    moveCM(-66, 50);
    rightPointTurn(40);
    //awd.brake(hold);
    noFriends();

}