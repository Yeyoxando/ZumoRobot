// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#include "zumoUtility.h"

// ----------------------------------------------------------------------------

ZumoRobot::ZumoRobot(){

  current_state = kZumoState_NoDataReceived;
  current_left_speed = 0;
  current_right_speed = 0;
  
}

// ----------------------------------------------------------------------------

ZumoRobot::~ZumoRobot(){
  
}

// ----------------------------------------------------------------------------

void ZumoRobot::InitializeZumo(){

  // Initialize zumo board at baud rate 9600
  Serial.begin(9600);
  // Initialize XBee connection at baud rate 9600
  Serial1.begin(9600);
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::UpdateZumo(){
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::UpdateMotorSpeed(int speed_to_reach, ZumoMotors motors){
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::SetMotorSpeed(int new_speed, ZumoMotors motors){
  
}
 
// ----------------------------------------------------------------------------
 
void RotateToAngle(int angle){
  
}
 
// ----------------------------------------------------------------------------

void ZumoRobot::RotateDegrees(int degrees){
  
}
 
// ----------------------------------------------------------------------------
 
bool ZumoRobot::DetectLines(){
  
  return false;
}
 
// ----------------------------------------------------------------------------

void ZumoRobot::PlayFollowMeGuide(){
  
}
 
// ----------------------------------------------------------------------------
 
