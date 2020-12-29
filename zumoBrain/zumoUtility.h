// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

/** @file zumoUtility.h
 *  @brief Implements ZumoRobot class, MazeRoom struct and all other components to perform the rescue op.
 *  
 *  Details.
 *  \n Zumo is controlled by a state machine made with different enums.
 *  \n It communicates via a XBee module with a GUI made for the operation, it will receive and send info.
*/

#ifndef __ZUMO_UTILITY_H__
#define __ZUMO_UTILITY_H__

#include <Zumo32U4.h>

/* ToDo
  - Check for the change between autonomous and manual, it may have some errors.
  - Do automatic line sensor calibration.
  - Keep improving GUI messages system.
*/

/// @brief Default zumo speed.
#define ZUMO_SPEED 200
/// @brief Indicates how much the encoders should advance to perform a 90 degree turn.
#define ZUMO_TURN_90 700
/// @brief Indicates how much the encoders should advance to displace an amount equal to the zumo size.
#define ZUMO_SIZE_MOVE 800
/// @brief Max number that zumo can visit (Instead of a vector or a collection structure to initialize an array).
#define MAX_ROOMS 5

/// @brief Enumerator to indicate current zumo state
enum ZumoState {
  kZumoState_Stopped = 0,       /**< Zumo is stopped. */
  kZumoState_Forwarding = 1,    /**< Zumo is moving forward. */
  kZumoState_Backwarding = 2,   /**< Zumo is moving backward. */
  kZumoState_TurningLeft = 3,   /**< Zumo is turning left. */
  kZumoState_TurningRight = 4,  /**< Zumo is turning right. */
  kZumoState_ScanningRoom = 5,  /**< Zumo is scanning a room. */
  kZumoState_Returning = 6      /**< Zumo is returning to base. */
};

/** @brief Indicates all the data that could be received
 *           from the GUI to convert it to Zumo actions
 */
enum ZumoData {
  kZumoData_NoDataReceived = 0,       /**< Task 0. No data has been received. */
  kZumoData_Stop = 1,                 /**< Task 1. Tell the zumo to stop. */
  kZumoData_ManualForward = 2,        /**< Task 1. Tell the zumo to go forward manually. */
  kZumoData_ManualBackward = 3,       /**< Task 1. Tell the zumo to go backward manually. */
  kZumoData_ManualTurnLeft = 4,       /**< Task 1. Tell the zumo to turn left manually. */
  kZumoData_ManualTurnRight = 5,      /**< Task 1. Tell the zumo to turn right manually. */
  kZumoData_SwitchManualMode = 6,     /**< Task 0. Switch manual and autonomous mode. */
  kZumoData_AutonomousForward = 7,    /**< Task 2. Tell the zumo to move autonomous forward. */
  kZumoData_AutonomousTurnLeft = 8,   /**< Tasks 3/4 & 5. Turn left autonomously or scan a room in the left. */
  kZumoData_AutonomousTurnRight = 9,  /**< Tasks 3/4 & 5. Turn right autonomously or scan a room in the right. */
  kZumoData_FoundRoom = 10,           /**< Task 5. Starts scanning a room. */
};

/// @brief Indicates all the data that could be send from the Zumo to the GUI
enum GUIData{
  kGUIData_SwitchManualMode = 100,      /**< Send the GUI to return to manual mode. */
  kGUIData_ReachedFrontWall = 101,      /**< Send the GUI that a border has been detected in front of the robot. */
  kGUIData_FinishedAutoRotation = 102,  /**< Send the GUI that zumo has finished the autonomous rotation. */
  kGUIData_EmptyRoom = 103,             /**< Send the GUI that the scanned room is empty. */
  kGUIData_ObjectInRoom = 104,          /**< Send the GUI that the scanned room has objects. */
};

/// @brief Enumerator to indicate zumo motors
enum ZumoMotors {
  kZumoMotors_Both = 0,   /**< Both motors. */
  kZumoMotors_Right = 1,  /**< Right motor. */
  kZumoMotors_Left = 2    /**< Left motor. */
};

/// @brief All the different actions that zumo has to perform to scan a room.
enum ZumoScanningAction{
  kZumoScanningAction_None = 0,             /**< Zumo hasn't started scanning the room. */
  kZumoScanningAction_Entering = 1,         /**< Zumo is entering to the room */
  kZumoScanningAction_Positioning = 2,      /**< Zumo is positioning himself to scan the room. */
  kZumoScanningAction_MeasuringLength = 3,  /**< Zumo is measuring the length of the room. */
  kZumoScanningAction_MeasuringWidth = 4,   /**< Zumo is measuring the width of the room. */
  kZumoScanningAction_Wandering = 5,        /**< Zumo is scanning the rest of the room. */
  kZumoScanningAction_Returning = 6         /**< Zumo is returning to the corridor after sanning the room. */
};

/// @brief Saves visited rooms data for later steps.
struct MazeRoom{
  /// @brief Stores the number of the room when is visited, If equal to -1 is not visited.
  int room_number = -1;
  /// @brief Stores the room length in wheel encoder units.
  int room_length = 0;
  /// @brief Stores if the room is at left when true, or at right when is false.
  bool is_at_left = false;
  /// @brief Stores if the room has people or is empty.
  bool has_people = false;  
};

/// @brief Implements all the neccesary actions for a ZumoRobot to simulate a search and rescue operation.
class ZumoRobot{
public:
  ZumoRobot();
  ~ZumoRobot();

  /// @brief Initializes variables and sensors for zumo to work.
  void InitializeZumo();
  
  /// @brief Do all the neccessary checks and updates the zumo state at baud rate.
  void UpdateZumo();

private:
  // --------------- Initialize functions ----------------------
  /// @brief Initializes and calibrates line sensors.
  void InitLineSensors();
  /// @brief Initializes and calibrates proximity sensors.
  void InitProximitySensors();
  /// @brief Initializes and calibrates the IMU (for the gyroscope).
  void InitGyroscope();

  // ----------------- Utility functions -----------------------
  /**
   *  @brief Sets a new speed for the motors.
   *  @param new_speed: speed to set on the motors, max is 400.
   *  @param zumo_motors: tells which motors has to change their speed.
   */
  void SetMotorSpeed(int new_speed, ZumoMotors zumo_motors);

  /** 
   * @brief Starts a turn to left or right, ReachedEncodersRotation has to be called after to check if the turn is completed.
   * @param left: says if it has to turn to the left, if false turns to the right.
   * @param turn_value: amount that the encoder on the turn side has to reach.
   */
  void InitTurn(bool left, int turn_value);
  /** 
   * @brief Check the current rotation of the encoders
   * @param left: if true checks a rotation to the left, if false checks to the right
   * @return true if the encoders has reached the rotation set before with a call to InitTurn
   */
  bool ReachedEncodersRotation(bool left);
  /** 
   * @brief rotates the zumo instantly and waits to be completed.
   * @param left: indicates in which direction is turning.
   * @param degrees: amount of degrees to turn.
   */
  void RotateWithGyro(bool left, int degrees);
  
  /** 
   * @brief Starts a forward movement, ReachedEncodersPosition has to be called after to check if the move is completed.
   * @param move_value: encoders value to move forward.
   */
  void InitMove(int move_value);
  /** 
   * @brief Check the current position of the encoders.
   * @return true if the encoders has reached the position set before with a call to InitMove.
   */
  bool ReachedEncodersPosition();
  
  /** 
   * @brief Detect if the sensors find any line, if a side is detected it will rotate a bit to avoid it.
   * @param check_only_front: will only check the front sensor.
   * @return true if it hits the front sensor.
   */
  bool DetectLines(bool check_only_front = false);
  
  /// @brief Enter a room and roam on it with proximity sensors to detect objects and store room information.
  void ScanRoom();
  
  /// @brief Plays the buzzer and turn on the led for its returning operation.
  void PlayFollowMeGuide();
  
  /// @brief Returns to the initial position visiting the rooms with people.
  void ReturnToBase();
  
  /// @brief Reads the incoming data from the serial GUI.
  void ReadSerialData();

  // --------------------- Variables ---------------------------

  // -- Zumo brain --
  /// @brief Indicates the current state which Zumo is executing.
  ZumoState current_state;
  /// @brief Indicates which scanning room action Zumo is executing.
  ZumoScanningAction current_scanning_action;
  /// @brief Current position on the left encoder when retrieved by a function.
  int current_left_encoder;
  /// @brief Current position on the right encoder when retrieved by a function.
  int current_right_encoder;
  /// @brief Desired value on the left encoder to reach for a movement.
  int desired_left_encoder;
  /// @brief Desired value on the right encoder to reach for a movement.
  int desired_right_encoder;
  /// @brief Stores the values readen by the line sensors.
  uint16_t line_sensors_values[5];
  /// @brief Indicates if zumo is in manual mode and can be controlled .
  bool manual_mode;
  /// @brief Number of rooms visited on the operation.
  int found_rooms_count;
  /// @brief Number of times that zumo has to roam the room to complete the scan.
  int wandering_repetitions;
  /// @brief Indicates if zumo has measured the room width to start with its wandering routine.
  bool measured_width;
  /// @brief Indicates if zumo is wandering in length on room scanning.
  bool length_wandering;
  /// @brief Indicates if zumo is wandering to the left on room scanning.
  bool left_wandering;
  /// @brief Stores the data of visited rooms on the maze, for a possibility to return later.
  MazeRoom found_rooms[MAX_ROOMS]; // Wish it could be a vector :( (Tried with arv_stl but it didn't compile).

  // -- Zumo body (components) --
  /// @brief Buzzer to play the return alarm.
  Zumo32U4Buzzer buzzer;
  /// @brief Zumo motors to put it in movement.
  Zumo32U4Motors motors;
  /// @brief Wheel encoders to measure traveled distances.
  Zumo32U4Encoders encoders;
  /// @brief Inertial Measurement Unit (Only Gyro is used).
  Zumo32U4IMU imu;
  /// @brief Line sensors for border detection, needs to be calibrated at the beginning.
  Zumo32U4LineSensors line_sensors;
  /// @brief Proximity sensors for object detection on room scanning.
  Zumo32U4ProximitySensors prox_sensors;
  
};

#endif // __ZUMO_UTILITY_H__
