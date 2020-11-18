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

  current_state = kZumoState_Stopped;
  current_left_speed = 0;
  current_right_speed = 0;
  current_rotation = 0;
  manual_mode = true;

  InitLineSensors();
  InitProximitySensors();
  InitGyroscope();
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::UpdateZumo(){

  ReadSerialData();

  // Check all nneccesary things and change mode or perform actions if needed
  switch(current_state){
  case kZumoState_Stopped:{
    break;
  }
  case kZumoState_Forwarding:{
    // Only check for lines if it is on autonomous mode
    if(!manual_mode){
      DetectLines();
    }
    break;
  }
  case kZumoState_Backwarding:{
    break;
  }
  case kZumoState_TurningLeft:{
    // If on autonomous should check rotation with gyro
    break;
  }
  case kZumoState_TurningRight:{
    // If on autonomous should check rotation with gyro
    break;
  }
  case kZumoState_ScanningRoom:{
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
  
  ledGreen(1);

  for (uint16_t i = 0; i < 400; i++)
  {
    line_sensors.calibrate();
  }

  // Retrieve max and min values from the calibration for debug purposes
  Serial.write(line_sensors.calibratedMinimumOff);
  Serial.write(line_sensors.calibratedMaximumOff);

  ledGreen(0);

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
  
  if(line_sensors_values[2] > 150){ // Center
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    ledGreen(1);
    delay(100)
    ledGreen(0);
    // Send message to GUI
  }
  else if(line_sensors_values[0] > 150){ // Left
    // Left sensor detected border
    ledYellow(1);
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    delay(50);
    // Turn a bit to the left
    SetMotorSpeed(100, kZumoMotors_Left);
    delay(100);
    // Continue forward
    SetMotorSpeed(200, kZumoMotors_Both);
  }
  else if(line_sensors_values[4] > 150){ // Right
    // Right sensor detected border
    ledYellow(1);
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    delay(50);
    // Turn a bit to the right
    SetMotorSpeed(100, kZumoMotors_Right);
    delay(100);
    // Continue forward
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
  
  ZumoData incoming_data = (ZumoData)Serial1.read();

  switch(incoming_data){
  case kZumoData_NoDataReceived:{
    
    break;
  }
  case kZumoData_Stop:{
    ledRed(0);
    manual_mode = true;

    current_state = kZumoState_Stopped;
    SetMotorSpeed(0, kZumoMotors_Both);
    break;
  }
  case kZumoData_ManualForward:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_Forwarding;
    SetMotorSpeed(200, kZumoMotors_Both);
    break;
  }
  case kZumoData_ManualBackward:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_Backwarding;
    SetMotorSpeed(-200, kZumoMotors_Both);
    break;
  }
  case kZumoData_ManualTurnLeft:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_TurningLeft;
    SetMotorSpeed(100, kZumoMotors_Right);
    SetMotorSpeed(-100, kZumoMotors_Left);
    break;
  }
  case kZumoData_ManualTurnRight:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_TurningRight;
    SetMotorSpeed(-100, kZumoMotors_Right);
    SetMotorSpeed(100, kZumoMotors_Left);
    break;
  }
  case kZumoData_SwitchManualMode:{
    // Turn on or off the led red, if it is on is on autonomous
    ledRed(manual_mode);
    manual_mode = !manual_mode;
    break;
  }
  case kZumoData_AutonomousForward:{
    // Perform Task 2
    ledRed(1);
    manual_mode = false;

    current_state = kZumoState_Forwarding;
    SetMotorSpeed(200, kZumoMotors_Both);
    break;
  }
  case kZumoData_AutonomousTurnLeft: {
    // Perform Task 4
    ledRed(1);
    manual_mode = false;
    
    current_state = kZumoState_TurningLeft;
    break;
  }
  case kZumoData_AutonomousTurnRight: {
    // Perform Task 4
    ledRed(1);
    manual_mode = false;
    
    current_state = kZumoState_TurningRight;
    break;
  }
  default:{
    break;
  }
  };
  
}
 
// ----------------------------------------------------------------------------
 
