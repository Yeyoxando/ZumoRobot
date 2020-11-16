// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#include "zumoUtility.h"

// ----------------------------------------------------------------------------

ZumoRobot::ZumoRobot(){
  
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

  current_state = kZumoState_NoDataReceived;
  current_left_speed = 0;
  current_right_speed = 0;
  current_rotation = 0;
  enabled_read = true;

  InitLineSensors();
  InitProximitySensors();
  InitGyroscope();
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::UpdateZumo(){

  if(enabled_read){
    ReadSerialData();
  }

  // Check all nneccesary things and change mode or perform actions if needed
  switch(current_state){
  case kZumoState_NoDataReceived:{
    break;
  }
  case kZumoState_Stop:{
    break;
  }
  case kZumoState_Forward:{
    DetectLines();
    break;
  }
  case kZumoState_Backward:{
    //DetectLines();
    break;
  }
  case kZumoState_TurnRight:{
    // Should rotate until reaches desired rotation
    break;
  }
  case kZumoState_TurnLeft:{
    // Should rotate until reaches desired rotation
    break;
  }
  case kZumoState_ScanRoom:{
    // Do scanning room things
    break;
  }
  case kZumoState_Returning:{
    // Do returning things
    break;
  }
  default:{
    break;
  }
  };
  
}

// ----------------------------------------------------------------------------

void ZumoRobot::InitLineSensors(){
  
  line_sensors.initFiveSensors();
  *line_sensors_values = 0;
  
  ledYellow(1);

  for (uint16_t i = 0; i < 400; i++)
  {
    line_sensors.calibrate();
  }

  ledYellow(0);

}

// ----------------------------------------------------------------------------
  
void ZumoRobot::InitProximitySensors(){
  
}

// ----------------------------------------------------------------------------
  
void ZumoRobot::InitGyroscope(){
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::SetMotorSpeed(int new_speed, ZumoMotors zumo_motors){
  
  switch(zumo_motors){
  case kZumoMotors_Both:{
    motors.setSpeeds(new_speed, new_speed);
    current_right_speed = new_speed;
    current_left_speed = new_speed;
    break;
  }
  case kZumoMotors_Right:{
    motors.setRightSpeed(new_speed);
    current_right_speed = new_speed;
    break;
  }
  case kZumoMotors_Left:{
    motors.setLeftSpeed(new_speed);
    current_left_speed = new_speed;
    break;
  }
  default:{
    break;  
  }  
  };
  
}
 
// ----------------------------------------------------------------------------
 
void RotateToAngle(int angle){
  
  // Use gyro or wheel encoders
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::DetectLines(){
  
  line_sensors.readCalibrated(line_sensors_values);
  //Serial1.write(line_sensors_values[4]);
  
  if(line_sensors_values[4] > 150 && line_sensors_values[0] > 150){
    SetMotorSpeed(0, kZumoMotors_Both);
    ledYellow(0);
    enabled_read = true;
  }
  else if(line_sensors_values[0] > 150){
    //Serial1.write(line_sensors_values[0]);
    // Left sensor detected border
    ledYellow(1);
    SetMotorSpeed(0, kZumoMotors_Both);
    delay(50);
    SetMotorSpeed(100, kZumoMotors_Left);
    delay(100);
    SetMotorSpeed(200, kZumoMotors_Both);
  }
  else if(line_sensors_values[4] > 150){
    ledYellow(1);
    // Right sensor detected border
    SetMotorSpeed(0, kZumoMotors_Both);
    delay(50);
    SetMotorSpeed(100, kZumoMotors_Right);
    delay(100);
    SetMotorSpeed(200, kZumoMotors_Both);
  }
  else{
    // Do nothing  
    ledYellow(0);
  }
  
}
 
// ----------------------------------------------------------------------------

void ZumoRobot::PlayFollowMeGuide(){
  
}
 
// ----------------------------------------------------------------------------

void ZumoRobot::ReadSerialData(){
  
  int incoming_byte = Serial1.read();

  switch(incoming_byte){
  case 0:{
    current_state = kZumoState_NoDataReceived;
    break;
  }
  case 1:{
    current_state = kZumoState_Stop;
    SetMotorSpeed(0, kZumoMotors_Both);
    break;
  }
  case 2:{
    current_state = kZumoState_Forward;
    enabled_read = false;
    SetMotorSpeed(200, kZumoMotors_Both);
    break;
  }
  case 3:{
    current_state = kZumoState_Backward;
    SetMotorSpeed(-200, kZumoMotors_Both);
    break;
  }
  case 4:{
    current_state = kZumoState_TurnRight;
    SetMotorSpeed(100, kZumoMotors_Right);
    SetMotorSpeed(-100, kZumoMotors_Left);
    break;
  }
  case 5:{
    current_state = kZumoState_TurnLeft;
    SetMotorSpeed(-100, kZumoMotors_Right);
    SetMotorSpeed(100, kZumoMotors_Left);
    break;
  }
  case 6:{
    current_state = kZumoState_ScanRoom;
    break;
  }
  case 7:{
    current_state = kZumoState_Returning;
    break;
  }
  default:{
    current_state = kZumoState_NoDataReceived;
    break;
  }
  };
  
}
 
// ----------------------------------------------------------------------------
 
