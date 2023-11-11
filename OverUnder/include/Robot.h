
#pragma once
#include "vex.h"
#ifndef ROBOT_H
#define ROBOT_H

using namespace vex;




extern vex::motor_group myDrivetrain;
extern vex::brain Brain;
extern controller controller1;

void vexcodeInit(void);

void driveForward(float inches);
void driveBackward(float inches);
void turnRight(float degrees);
void turnLeft(float degrees);

#endif

motor leftMotor = motor(PORT1);
motor RightMotor = motor(PORT2);
motor ClawMotor = motor(PORT8);
motor ArmMotor = motor(PORT7);

void driveForward(float inches);
void driveBackward(float inches);
void turnRight(float degrees);
void turnLeft(float degrees);  

// Drive Function Definition Section
const float GEAR_RATIO = 1.0; // replace with your actual gear ratio.
const int AUTON_DRIVE_PCT = 50; // replace with your % of 100% Speed
//Turn Function Declaration Section
// distance (in inches) from top-left wheel to bottom-right wheel
const float TURNING_DIAMETER = 30; // replace with your value
const float WHEEL_DIAMETER = 4.125; // replace with your value
const float WHEEL_RADIUS = WHEEL_DIAMETER / 2;
const float WHEEL_CIRCUMFERENCE = 2*3.14159*WHEEL_RADIUS; // replace with your value

//Function Definition Section
void driveForward(float inches){
    float inchesPerDegree = WHEEL_CIRCUMFERENCE / 360;  //change first number to wheel circumference
    float degrees = inches / inchesPerDegree;
    // startRotate doesn't wait for completion
    // this way, the other wheel can turn at same time
    myDrivetrain.spinFor(
        degrees * GEAR_RATIO, rotationUnits::deg, 
        AUTON_DRIVE_PCT, velocityUnits::pct
    );}
    void driveBackward(float inches){
    //The number of inches traveled per degree of rotation.
    float inchesPerDegree = WHEEL_CIRCUMFERENCE / 360;  //change first number to wheel circumference
    float degrees = inches / inchesPerDegree;
    myDrivetrain.spinFor(
        -degrees * GEAR_RATIO, rotationUnits::deg, 
        AUTON_DRIVE_PCT, velocityUnits::pct
    );}
    void turnRight( float degrees ) {
    // Note: +90 degrees is a right turn
    float turningRatio = TURNING_DIAMETER / WHEEL_DIAMETER;
    float wheelDegrees = turningRatio * degrees;    
    // Divide by two because each wheel provides half the rotation
        leftMotor.spinFor(
        wheelDegrees * GEAR_RATIO / 2, rotationUnits::deg, 
        AUTON_DRIVE_PCT, velocityUnits::pct, false);//false means don't wait for completion
        RightMotor.spinFor(
        -wheelDegrees * GEAR_RATIO / 2, rotationUnits::deg, 
        AUTON_DRIVE_PCT, velocityUnits::pct);}
    
    void turnLeft( float degrees ) {
    // Note: +90 degrees is a right turn
    float turningRatio = TURNING_DIAMETER / WHEEL_DIAMETER;
    float wheelDegrees = turningRatio * degrees;  
    RightMotor.spinFor(
        -wheelDegrees * GEAR_RATIO / 2, rotationUnits::deg,
        AUTON_DRIVE_PCT, velocityUnits::pct,false);
    leftMotor.spinFor( 
        wheelDegrees * GEAR_RATIO / 2, rotationUnits::deg,
        AUTON_DRIVE_PCT, velocityUnits::pct);}
