#ifndef __ZUMO_UTILITY_H__
#define __ZUMO_UTILITY_H__

#include <Zumo32U4.h>

// Enumarator to indicate zumo state, also to receive data from Xbee in integer format
enum ZumoMode {
  kZumoMode_Wait = 0,
  kZumoMode_Forward = 1,
  kZumoMode_Backward = 2,
  kZumoMode_TurnRight = 3,
  kZumoMode_TurnLeft = 4,
  kZumoMode_ScanRoom = 5,
  kZumoMode_Returning = 6
};

// Sets neccesary things for zumo to work
void InitializeZumo();

// Do all the neccessary checks and updates the zumo state
void UpdateZumo();

// Interpolates current speed to the given speed by parameter
void UpdateMotorSpeed(int speed_to_reach);
// Set directly a new speed for the motors
void SetMotorSpeed(int new_speed);
// Rotates the zumo robot to a given angle
void RotateToAngle(int angle);
// Rotates the zumo robot from its current rotation plus the given degrees
void RotateDegrees(int degrees);

// Detect if the sensors find any line and return true if it do
bool DetectLines();

// Plays the buzzer and turn on the led for its rescue operation
void PlayFollowMeGuide();

#endif //__ZUMO_UTILITY_H__
