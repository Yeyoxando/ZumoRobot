// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#include "zumoUtility.h"
#include "Wire.h"

// ----------------------------------------------------------------------------

ZumoRobot::ZumoRobot(){
  
}

// ----------------------------------------------------------------------------

ZumoRobot::~ZumoRobot(){
  
}

// ----------------------------------------------------------------------------

void ZumoRobot::InitializeZumo(){

  // Initialize zumo board at baud rate 9600
 // Serial.begin(9600);
  // Initialize XBee connection at baud rate 9600
  Serial1.begin(9600);

  current_state = kZumoState_Stopped;
  current_scanning_action = kZumoScanningAction_None;
  current_left_speed = 0;
  current_right_speed = 0;
  current_left_encoder = 0;
  current_right_encoder = 0;
  desired_left_encoder = 0;
  desired_right_encoder = 0;
  manual_mode = true;
  found_rooms_count = 0;
  wandering_repetitions = 0;
  length_wandering = false;
  left_wandering = false;
  measured_width = false;

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
      if(DetectLines()){
        current_state = kZumoState_Stopped;
        // Send message to GUI
        Serial1.write((int)kGUIData_ReachedFrontWall);
      }
    }
    break;
  }
  case kZumoState_Backwarding:{
    break;
  }
  case kZumoState_TurningLeft:{
    // If on autonomous should check rotation
    if(!manual_mode){
      if(ReachedEncodersRotation(true)){
        SetMotorSpeed(0, kZumoMotors_Both);
        Serial1.write((int)kGUIData_FinishedAutoRotation);
        current_state = kZumoState_Stopped;
      }
    }
    break;
  }
  case kZumoState_TurningRight:{
    // If on autonomous should check rotation
    if(!manual_mode){
      if(ReachedEncodersRotation(false)){
        SetMotorSpeed(0, kZumoMotors_Both);
        Serial1.write((int)kGUIData_FinishedAutoRotation);
        current_state = kZumoState_Stopped;
      }
    }
    break;
  }
  case kZumoState_ScanningRoom:{
    // Do scanning room things
    ScanRoom();
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

  // Used InertialSensors example from Zumo32U4 library
  Wire.begin();
  
  if (!imu.init())
  {
    // Failed to detect the compass.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to initialize IMU sensors."));
      delay(100);
    }
  }
  
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

void ZumoRobot::InitTurn(bool left, int turn_value){

  if(left){
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Left);
    // Calculate left encoder expected value for 90 degrees left turn (-700 is about 90 degrees)
    desired_left_encoder = encoders.getCountsLeft() - turn_value;
  }
  else{
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Left);
    // Calculate right encoder expected value for 90 degrees right turn (-700 is about 90 degrees)
    desired_right_encoder = encoders.getCountsRight() - turn_value;
  }
  
}
 
// ----------------------------------------------------------------------------

bool ZumoRobot::ReachedEncodersRotation(bool left){
  
  // Using wheel encoders
  int16_t counts_left = encoders.getCountsLeft();
  int16_t counts_right = encoders.getCountsRight();

  if(left){
    if(counts_left < desired_left_encoder){ // about 90 degrees to the left
      return true;
    }
  }
  else{
    if(counts_right < desired_right_encoder){ // about 90 degrees to the right
      return true;
    } 
  }

  return false;
  
}

// ----------------------------------------------------------------------------

void ZumoRobot::RotateWithGyro(bool left, int degrees){
  
  float gyro_speed = 0.0f; // Calculated gyro speed
  int desired_rot_time = 0; //ms to stop rotation

  // Init turn
  if(left){
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Left);
  }
  else{
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Left);
  }
  
  // Wait a bit to let the gyro get some values
  delay(200);
  imu.readGyro();

  // For some reason my zumo turns faster to the left so it needs an extra check
  // 114.0f = 10285 / 90 dps (Looked at InertialSensors example to get this value, 10285 gyro value for 90dps)
  // to the left is 116.1f to reduce a bit the turning time

  // Calculate the gyro speed
  if(left){
    gyro_speed = (abs((float)imu.g.z)) / 118.5f; //Turning left
  }
  else{
    gyro_speed = (abs((float)imu.g.z)) / 121.5f; //Turning right
  }

  // 1000 ms at 90dps for 90 degrees return 1000 ms of rotating time, 
  // so this formula calculates the rotation time with the given degrees and the current gyro speed
  desired_rot_time = (int)(1000.0f / (gyro_speed / (float)degrees));

  // Wait the indicated time substracting the initial 200 ms to wait for the gyro to get values
  delay(desired_rot_time - 200);

  // Stop
  SetMotorSpeed(0, kZumoMotors_Both);
  
}

// ----------------------------------------------------------------------------

void ZumoRobot::InitMove(int move_value){

  SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
  desired_left_encoder = encoders.getCountsLeft() + move_value;
  desired_right_encoder = encoders.getCountsRight() + move_value;
  
}

// ----------------------------------------------------------------------------

bool ZumoRobot::ReachedEncodersPosition(){
  // Using wheel encoders
  int16_t counts_left = encoders.getCountsLeft();
  int16_t counts_right = encoders.getCountsRight();
  
  if(counts_left > desired_left_encoder || counts_right > desired_right_encoder){ 
    return true;
  }

  return false;
  
}

// ----------------------------------------------------------------------------
 
bool ZumoRobot::DetectLines(bool check_only_front){
  
  line_sensors.readCalibrated(line_sensors_values);
  
  if(line_sensors_values[2] > 300){ // Center
    // Stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    ledYellow(0);
    return true;
  }
  else if(line_sensors_values[0] > 300 && !check_only_front){ // Left
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
  else if(line_sensors_values[4] > 300 && !check_only_front){ // Right
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

  return false;
  
}
 
// ----------------------------------------------------------------------------

void ZumoRobot::ScanRoom(){
  
  MazeRoom current_room = found_rooms[found_rooms_count - 1];
  
  switch(current_scanning_action){
    case kZumoScanningAction_None:{
      break;  
    }
    case kZumoScanningAction_Entering:{
      if(ReachedEncodersPosition()){
        RotateWithGyro(current_room.is_at_left, 90);
        current_scanning_action = kZumoScanningAction_Positioning;
      }
      break;  
    }
    case kZumoScanningAction_Positioning:{
      delay(100);
      current_left_encoder = encoders.getCountsLeft();
      current_right_encoder = encoders.getCountsRight();
      SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
      current_scanning_action = kZumoScanningAction_MeasuringLength;
      break;  
    }
    case kZumoScanningAction_MeasuringLength:{
      // Store room length when hit a line in the front
      if(DetectLines(true)){
        
        if(current_room.is_at_left){
          current_room.room_length = encoders.getCountsLeft() - current_left_encoder;
          // Calculate how many times should wander the room to scan it completely with half zumo size
          wandering_repetitions = current_room.room_length / 700;
          // Set zumo to turn right
          RotateWithGyro(false, 90);
        }
        else{
          current_room.room_length = encoders.getCountsRight() - current_right_encoder;
          // Calculate how many times should wander the room to scan it completely with half zumo size
          wandering_repetitions = current_room.room_length / 700;
          // Set the zumo to turn left
          RotateWithGyro(true, 90);
        }
        
        SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
        current_scanning_action = kZumoScanningAction_MeasuringWidth;
      }
      break;  
    }
    case kZumoScanningAction_MeasuringWidth:{
      if(DetectLines(true)){
        measured_width = true;
        length_wandering = true;
        
        if(current_room.is_at_left){
          left_wandering = true;
          RotateWithGyro(false, 90);
        }
        else{
          left_wandering = false;
          RotateWithGyro(true, 90);
        }
        
        InitMove(700);
        current_scanning_action = kZumoScanningAction_Wandering;
      }
      break;  
    }
    case kZumoScanningAction_Wandering:{
      // Displace in zig zag with half zumo size to scan completely with the total repeat number caculated in the measure length action
      if(length_wandering && ReachedEncodersPosition()){
        wandering_repetitions--;
        if(wandering_repetitions <= 0){
          SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
          current_scanning_action = kZumoScanningAction_Returning;
          break;
        }
        
        if(!left_wandering){
          RotateWithGyro(true, 90);
        }
        else{
          RotateWithGyro(false, 90);
        }    
        
        length_wandering = false;
        SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
      }
      else if(!length_wandering && DetectLines(true)){
        // Turn left
        length_wandering = true;
        
        if(left_wandering){
          left_wandering = false;
          RotateWithGyro(true, 90);
        }
        else{
          left_wandering = true;
          RotateWithGyro(false, 90);
        }

        InitMove(700);
      }
      break;  
    }
    case kZumoScanningAction_Returning:{
      // Return to corridor
      if(DetectLines(true)){
        measured_width = false;
        length_wandering = false;
        left_wandering = false;
        if(current_room.is_at_left){
          RotateWithGyro(true, 90);
        }
        else{
          RotateWithGyro(false, 90);
        }
        
        // Send to serial 1 if there are people or not
        if(current_room.has_people){
          Serial1.write((int)kGUIData_ObjectInRoom);
        }
        else{
          Serial1.write((int)kGUIData_EmptyRoom);
        }
        
        current_scanning_action = kZumoScanningAction_None;
        current_state = kZumoState_Stopped;
      }
      break;  
    }
    default:{
      break;
    }
  }
    
}
 
// ----------------------------------------------------------------------------

void ZumoRobot::PlayFollowMeGuide(){
  
}

// ----------------------------------------------------------------------------

void ZumoRobot::ReturnToBase(){
  
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

    SetMotorSpeed(0, kZumoMotors_Both);
    current_state = kZumoState_Stopped;
    break;
  }
  case kZumoData_ManualForward:{
    ledRed(0);
    manual_mode = true;
    
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
    current_state = kZumoState_Forwarding;
    break;
  }
  case kZumoData_ManualBackward:{
    ledRed(0);
    manual_mode = true;
    
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Both);
    current_state = kZumoState_Backwarding;
    break;
  }
  case kZumoData_ManualTurnLeft:{
    ledRed(0);
    manual_mode = true;

    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Left);
    current_state = kZumoState_TurningLeft;
    break;
  }
  case kZumoData_ManualTurnRight:{
    ledRed(0);
    manual_mode = true;

    SetMotorSpeed(-ZUMO_SPEED, kZumoMotors_Right);
    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Left);
    current_state = kZumoState_TurningRight;
    break;
  }
  case kZumoData_SwitchManualMode:{
    // Turn on or off the led red, on if it is on autonomous mode
    ledRed(manual_mode);
    manual_mode = !manual_mode;
    break;
  }
  case kZumoData_AutonomousForward:{
    // Perform Task 2
    ledRed(1);
    manual_mode = false;

    SetMotorSpeed(ZUMO_SPEED, kZumoMotors_Both);
    current_state = kZumoState_Forwarding;
    break;
  }
  case kZumoData_AutonomousTurnLeft: {
    // Perform Task 4
    ledRed(1);
    manual_mode = false;
    
    if(current_state == kZumoState_ScanningRoom){
      // Store that the room is at left
      found_rooms[found_rooms_count - 1].is_at_left = true;
      
      InitMove(ZUMO_SIZE_MOVE);
      current_scanning_action = kZumoScanningAction_Entering;
    }
    else{
      InitTurn(true, ZUMO_TURN_90);
      current_state = kZumoState_TurningLeft;
    }
    break;
  }
  case kZumoData_AutonomousTurnRight: {
    // Perform Task 4
    ledRed(1);
    manual_mode = false;

    if(current_state == kZumoState_ScanningRoom){
      // Store that the room is at right
      found_rooms[found_rooms_count - 1].is_at_left = false;
      
      InitMove(ZUMO_SIZE_MOVE);
      current_scanning_action = kZumoScanningAction_Entering;
    }
    else{
      InitTurn(false, ZUMO_TURN_90);
      current_state = kZumoState_TurningRight;
    }
    break;
  }
  case kZumoData_FoundRoom: {
    // Perform Task 5
    ledRed(1);
    manual_mode = false;

    // Set new state and stop zumo
    SetMotorSpeed(0, kZumoMotors_Both);
    InitGyroscope();
    if(found_rooms_count < MAX_ROOMS){
      // Add a new room to the array, set only the number, rest of the data will be filled while scanning the room
      MazeRoom new_room;
      new_room.room_number = found_rooms_count;
      found_rooms[found_rooms_count] = new_room;
      found_rooms_count++;
    }
    current_state = kZumoState_ScanningRoom;
    break;  
  }
  default:{
    break;
  }
  };
  
}
 
// ----------------------------------------------------------------------------
 
