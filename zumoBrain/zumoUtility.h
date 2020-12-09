// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#ifndef __ZUMO_UTILITY_H__
#define __ZUMO_UTILITY_H__

#include <Zumo32U4.h>

/* ToDo
  - Check for the change between autonomous and manual, it may have some errors
  - Do automatic line sensor calibration
  - Keep improving GUI messages system
*/

/// @brief: Default zumo speed
#define ZUMO_SPEED 200
/// @brief: indicates how much the encoders should advance to perform a 90 degree turn
#define ZUMO_TURN_90 700
/// @brief: indicates how much the encoders should advance to displace an amount equal to the zumo size
#define ZUMO_SIZE_MOVE 800
/// @brief: max number that zumo can visit (Instead of a vector or a collection structure to initialize an array)
#define MAX_ROOMS 5

/// @brief: Enumerator to indicate current zumo state
enum ZumoState {
  kZumoState_Stopped = 0,
  kZumoState_Forwarding = 1,
  kZumoState_Backwarding = 2,
  kZumoState_TurningLeft = 3,
  kZumoState_TurningRight = 4,
  kZumoState_ScanningRoom = 5,
  kZumoState_Returning = 6
};

/// @brief: Indicates all the data that could be received from the GUI to convert it to Zumo actions
enum ZumoData {
  kZumoData_NoDataReceived = 0,
  kZumoData_Stop = 1,                // Task 1
  kZumoData_ManualForward = 2,       // Task 1
  kZumoData_ManualBackward = 3,      // Task 1
  kZumoData_ManualTurnLeft = 4,      // Task 1
  kZumoData_ManualTurnRight = 5,     // Task 1
  kZumoData_SwitchManualMode = 6,
  kZumoData_AutonomousForward = 7,   // Task 2
  kZumoData_AutonomousTurnLeft = 8,  // Task 4 & 5
  kZumoData_AutonomousTurnRight = 9, // Task 4 & 5
  kZumoData_FoundRoom = 10,          // Task 5
};

/// @brief: Indicates all the data that could be send from the Zumo to the GUI
enum GUIData{
  kGUIData_SwitchManualMode = 100,
  kGUIData_ReachedFrontWall = 101,
  kGUIData_FinishedAutoRotation = 102,
  kGUIData_EmptyRoom = 103,
  kGUIData_ObjectInRoom = 104,
};

/// @brief: Enumerator to indicate zumo motors
enum ZumoMotors {
  kZumoMotors_Both = 0,
  kZumoMotors_Right = 1,
  kZumoMotors_Left = 2  
};

/// @brief: All the different actions that zumo performs to scan a room
enum ZumoScanningAction{
  kZumoScanningAction_None = 0,
  kZumoScanningAction_Entering = 1,
  kZumoScanningAction_Positioning = 2,
  kZumoScanningAction_MeasuringLength = 3,
  kZumoScanningAction_MeasuringWidth = 4,
  kZumoScanningAction_Wandering = 5,
  kZumoScanningAction_Returning = 6
};

/// @brief: structure to save visited rooms data
struct MazeRoom{
  int room_number = -1; // If equal to -1 is not initialized
  int room_length = 0;
  bool is_at_left = false;
  bool has_people = false;  
};

/// @brief: Implements all the neccesary actions for a ZumoRobot to simulate a search and rescue operation
class ZumoRobot{
public:
  ZumoRobot();
  ~ZumoRobot();

  /// @brief: Initializes variables and sensors for zumo to work
  void InitializeZumo();
  
  /// @brief: Do all the neccessary checks and updates the zumo state
  void UpdateZumo();

private:
  // --------------- Initialize functions ----------------------
  /// @brief: Initializes and calibrates line sensors
  void InitLineSensors();
  /// @brief: Initializes and calibrates proximity sensors
  void InitProximitySensors();
  /// @brief: Initializes and calibrates the gyroscope
  void InitGyroscope();

  // ----------------- Utility functions -----------------------
  /**
   *  @brief: Sets a new speed for the motors
   *  @param new_speed: speed to set on the motors, max is 400
   *  @param zumo_motors: tells which motors has to change their speed
   */
  void SetMotorSpeed(int new_speed, ZumoMotors zumo_motors);

  /** 
   * @brief: starts a turn to left or right, ReachedEncodersRotation has to be called after to check if the turn is completed
   * @param left: says if it has to turn to the left, if false turns to the right
   * @param turn_value: amount that the encoder on the turn side has to reach
   */
  void InitTurn(bool left, int turn_value);
  /** 
   * @brief: check the current rotation of the encoders
   * @param left: if true checks a rotation to the left, if false checks to the right
   * @return: true if the encoders has reached the rotation set before with a call to InitTurn
   */
  bool ReachedEncodersRotation(bool left);
  /** 
   * @brief: rotates the zumo instantly and waits to be completed
   * @param left: indicates in which direction is turning
   * @param degrees: amount of degrees to turn
   */
  void RotateWithGyro(bool left, int degrees);
  
  /** 
   * @brief: starts a forward movement, ReachedEncodersPosition has to be called after to check if the move is completed
   * @param move_value: encoders value to move forward
   */
  void InitMove(int move_value);
  /** 
   * @brief: check the current position of the encoders
   * @return: true if the encoders has reached the position set before with a call to InitMove
   */
  bool ReachedEncodersPosition();
  
  /** 
   * @brief: Detect if the sensors find any line, if a side is detected it will rotate a bit to avoid it
   * @param check_only_front: will only check the front sensor
   * @return: true if it hits the front sensor
   */
  bool DetectLines(bool check_only_front = false);
  
  /// @brief:
  void ScanRoom();
  
  /// @brief: Plays the buzzer and turn on the led for its rescue operation
  void PlayFollowMeGuide();
  
  /// @brief: Reads the incoming data from the serial
  void ReadSerialData();

  // --------------------- Variables ---------------------------
  /// @brief: indicates the current state in which zumo is
  ZumoState current_state;
  /// @brief: indicates in which scanning room action zumo is
  ZumoScanningAction current_scanning_action;
  /// @brief: 
  int current_left_speed;
  /// @brief: 
  int current_right_speed;
  /// @brief: 
  int current_left_encoder;
  /// @brief: 
  int current_right_encoder;
  /// @brief: 
  int desired_left_encoder;
  /// @brief: 
  int desired_right_encoder;
  /// @brief: stores the values readen by the line sensors
  uint16_t line_sensors_values[5];
  /// @brief: 
  bool manual_mode;
  /// @brief:
  int found_rooms_count;
  /// @brief:
  int wandering_repetitions;
  /// @brief:
  bool measured_width;
  /// @brief:
  bool length_wandering;
  /// @brief:
  bool left_wandering;
  /// @brief:
  MazeRoom found_rooms[MAX_ROOMS]; // Wish it could be a vector :( (Tried with arv_stl but it didn't compile)


  /// @brief: 
  Zumo32U4Buzzer buzzer;
  /// @brief: 
  Zumo32U4Motors motors;
  /// @brief: 
  Zumo32U4Encoders encoders;
  /// @brief: Inertial Measurement Unit (Gyro)
  Zumo32U4IMU imu;
  /// @brief: 
  Zumo32U4LineSensors line_sensors;
  /// @brief: 
  Zumo32U4ProximitySensors prox_sensors;
  
};

#endif // __ZUMO_UTILITY_H__
