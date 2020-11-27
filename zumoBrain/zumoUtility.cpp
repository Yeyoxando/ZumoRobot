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
  desired_left_encoder = 0;
  desired_right_encoder = 0;
  manual_mode = true;

  InitLineSensors();
  InitProximitySensors();
  InitGyroscope();
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::UpdateZumo(){

  ReadSerialData();

  // Check all neccesary things and change mode or perform actions if needed
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
    // If on autonomous should check rotation
    if(!manual_mode){
      ReadRotationWithEncoders(true);
    }
    break;
  }
  case kZumoState_TurningRight:{
    // If on autonomous should check rotation
    if(!manual_mode){
      ReadRotationWithEncoders(false);
    }
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

  ledGreen(0);

}

// ----------------------------------------------------------------------------
  
void ZumoRobot::InitProximitySensors(){
  
}

// ----------------------------------------------------------------------------
  
void ZumoRobot::InitGyroscope(){
  
  imu.init();
  imu.enableDefault();
  
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
 
void ZumoRobot::ReadRotationWithEncoders(bool left){
  
  // Using wheel encoders
  int16_t counts_left = encoders.getCountsLeft();
  int16_t counts_right = encoders.getCountsRight();

  if(left){
    if(counts_left < desired_left_encoder){ // about 90 degrees to the left
        motors.setSpeeds(0, 0);
        Serial1.write((int)kGUIData_FinishedAutoRotation);
        current_state = kZumoState_Stopped;
    }
  }
  else{
    if(counts_right < desired_right_encoder){ // about 90 degrees to the right
        motors.setSpeeds(0, 0);
        Serial1.write((int)kGUIData_FinishedAutoRotation);
        current_state = kZumoState_Stopped;
    } 
  }
  
}
 
// ----------------------------------------------------------------------------
 
void ZumoRobot::DetectLines(){
  
  line_sensors.readCalibrated(line_sensors_values);
  
  if(line_sensors_values[2] > 300){ // Center
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    current_state = kZumoState_Stopped;
    ledYellow(0);
    // Send message to GUI
    ledGreen(1);
    Serial1.write((int)kGUIData_ReachedFrontWall);
    delay(100);
    ledGreen(0);
  }
  else if(line_sensors_values[0] > 300){ // Left
    // Left sensor detected border
    ledYellow(1);
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    delay(50);
    // Turn a bit to the left
    SetMotorSpeed(ZUMO_SPEED / 2, kZumoMotors_Left);
    delay(100);
    // Continue forward
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
  }
  else if(line_sensors_values[4] > 300){ // Right
    // Right sensor detected border
    ledYellow(1);
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    delay(50);
    // Turn a bit to the right
    SetMotorSpeed(ZUMO_SPEED / 2, kZumoMotors_Right);
    delay(100);
    // Continue forward
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
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
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
    break;
  }
  case kZumoData_ManualBackward:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_Backwarding;
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Both);
    break;
  }
  case kZumoData_ManualTurnLeft:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_TurningLeft;
    SetMotorSpeed(ZUMO_SPEED / 2, kZumoMotors_Right);
    SetMotorSpeed(-ZUMO_SPEED / 2, kZumoMotors_Left);
    break;
  }
  case kZumoData_ManualTurnRight:{
    ledRed(0);
    manual_mode = true;
    
    current_state = kZumoState_TurningRight;
    SetMotorSpeed(-ZUMO_SPEED / 2, kZumoMotors_Right);
    SetMotorSpeed(ZUMO_SPEED / 2, kZumoMotors_Left);
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
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
    break;
  }
  case kZumoData_AutonomousTurnLeft: {
    // Perform Task 4
    ledRed(1);
    manual_mode = false;
    
    current_state = kZumoState_TurningLeft;
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Left);
    // Calculate left encoder expected value for 90 degrees left turn (-675 is about 90 degrees)
    desired_left_encoder = encoders.getCountsLeft() - 675;
    break;
  }
  case kZumoData_AutonomousTurnRight: {
    // Perform Task 4
    ledRed(1);
    manual_mode = false;
    
    current_state = kZumoState_TurningRight;
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Left);
    // Calculate right encoder expected value for 90 degrees right turn (-675 is about 90 degrees)
    desired_right_encoder = encoders.getCountsRight() - 675;
    break;
  }
  default:{
    break;
  }
  };
  
}
 
// ----------------------------------------------------------------------------
 
