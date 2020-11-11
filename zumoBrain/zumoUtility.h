// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#ifndef __ZUMO_UTILITY_H__
#define __ZUMO_UTILITY_H__

#include <Zumo32U4.h>

// Convert it to a class and add variables for the motors and all the robot things, plus needed variables

// Enumerator to indicate zumo state, also to receive data from Xbee in integer format
enum ZumoState {
  kZumoState_NoDataReceived = 0,
  kZumoState_Stop = 1,
  kZumoState_Forward = 2,
  kZumoState_Backward = 3,
  kZumoState_TurnRight = 4,
  kZumoState_TurnLeft = 5,
  kZumoState_ScanRoom = 6,
  kZumoState_Returning = 7
};

// Enumerator to indicate zumo motors
enum ZumoMotors {
  kZumoMotors_Both = 0,
  kZumoMotors_Right = 1,
  kZumoMotors_Left = 2  
};

class ZumoRobot{
public:
  ZumoRobot();
  ~ZumoRobot();

  // Sets neccesary things for zumo to work
  void InitializeZumo();
  
  // Do all the neccessary checks and updates the zumo state
  void UpdateZumo();
  
  // Interpolates current speed to the given speed by parameter
  void UpdateMotorSpeed(int speed_to_reach, ZumoMotors motors);
  // Set directly a new speed for the motors
  void SetMotorSpeed(int new_speed, ZumoMotors motors);
  // Rotates the zumo robot to a given angle
  void RotateToAngle(int angle);
  // Rotates the zumo robot from its current rotation plus the given degrees
  void RotateDegrees(int degrees);
  
  // Detect if the sensors find any line and return true if it do
  bool DetectLines();
  
  // Plays the buzzer and turn on the led for its rescue operation
  void PlayFollowMeGuide();

private:
  ZumoState current_state;
  int current_left_speed;
  int current_right_speed;

  Zumo32U4Buzzer buzzer;
  Zumo32U4Motors motors;
  Zumo32U4LineSensors line_sensors;
  Zumo32U4ProximitySensors prox_sensors;
  
};

#endif //__ZUMO_UTILITY_H__
