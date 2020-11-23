// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#ifndef __ZUMO_UTILITY_H__
#define __ZUMO_UTILITY_H__

#include <Zumo32U4.h>

/* ToDo
  - Check for the change between autonomous and manual, it may have some errors
  - Clean and improve line detector code
  - Maybe use sensor calibrated variables for max and min (calibratedMinimumOff, calibratedMaximumOff)
  - Try setting this values manually
  - Maybe do automatic calibration
  - Keep improving GUI messages system
  - Clean and refactorize the GUI code, make functions where possible
  - Adjust autonomous turn a bit more, not exactly 90 degrees, should be like 675 +-
*/

#define ZUMO_SPEED 200

// Enumerator to indicate current zumo state
enum ZumoState {
  kZumoState_Stopped = 0,
  kZumoState_Forwarding = 1,
  kZumoState_Backwarding = 2,
  kZumoState_TurningLeft = 3,
  kZumoState_TurningRight = 4,
  kZumoState_ScanningRoom = 5,
  kZumoState_Returning = 6
};

// Indicates all the data that could be received from the GUI to convert it to robot actions
enum ZumoData {
  kZumoData_NoDataReceived = 0,
  kZumoData_Stop = 1,                // Task 1
  kZumoData_ManualForward = 2,       // Task 1
  kZumoData_ManualBackward = 3,      // Task 1
  kZumoData_ManualTurnLeft = 4,      // Task 1
  kZumoData_ManualTurnRight = 5,     // Task 1
  kZumoData_SwitchManualMode = 6,
  kZumoData_AutonomousForward = 7,   // Task 2
  kZumoData_AutonomousTurnLeft = 8,  // Task 4
  kZumoData_AutonomousTurnRight = 9, // Task 4
};

// Indicates all the data that could be send from the Zumo to the GUI
enum GUIData{
  kGUIData_SwitchManualMode = 100,
  kGUIData_ReachedFrontWall = 101,
  kGUIData_FinishedAutoRotation = 102,
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

private:
  // --------------- Initialize functions ----------------------
  // Initializes and calibrates line sensors
  void InitLineSensors();
  // Initializes and calibrates proximity sensors
  void InitProximitySensors();
  // Initializes and calibrates the gyroscope
  void InitGyroscope();

  // ----------------- Utility functions -----------------------
  // Set directly a new speed for the motors
  void SetMotorSpeed(int new_speed, ZumoMotors zumo_motors);
  // Rotates the zumo robot until encoders reach a certain value
  void ReadRotationWithEncoders(bool left);
  // Detect if the sensors find any line and return true if it do
  void DetectLines();
  // Plays the buzzer and turn on the led for its rescue operation
  void PlayFollowMeGuide();
  // Reads the incoming data from the serial
  void ReadSerialData();

  // --------------------- Variables ---------------------------
  ZumoState current_state;
  int current_left_speed;
  int current_right_speed;
  int desired_left_encoder;
  int desired_right_encoder;
  uint16_t line_sensors_values[5];
  bool manual_mode;

  Zumo32U4Buzzer buzzer;
  Zumo32U4Motors motors;
  Zumo32U4Encoders encoders;
  Zumo32U4IMU imu; // Inertial Measurement Unit (Gyro)
  Zumo32U4LineSensors line_sensors;
  Zumo32U4ProximitySensors prox_sensors;
  
};

#endif //__ZUMO_UTILITY_H__
