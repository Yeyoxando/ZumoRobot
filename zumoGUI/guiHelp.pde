// Author: Diego Ochando Torres
// Date: 18/11/2020
// e-mail: c0022981@my.shu.ac.uk


// ------------------------- GUI HELPER VARIABLES ------------------------------

/**
* @brief:
*/
static String zumo_data_strings[] = {
// String 1
"Detected a wall in front of the robot.\nTurn Left or Right.",
// String 2
"Zumo is inspecting the room.",
// String 3
"Zumo has inspected the room. Information added below."
};

// ----------------------------------------------------------------------------

/**
* @brief:
*/
static String gui_help_strings[] = {
// String 1
"",
// String 2
"To start with task 2:\nSwitch the toggle to autonomous mode and then press forward button.",
// String 3
//"Task 3:\nTurn left or right and press 'completed' button, then the zumo robot will engage again task 2."
"Task 3&4:\nPress Left or Right buttons, then the zumo robot will rotate and engage again task 2.",
// String 4
"To start with task 5:\nWhen the zumo is about to enter a room you should press the 'Room!' button.\nThen press Turn Left or Turn Right buttons to indicate in which direction the room is.\nZumo will take care of the rest."
};

// ----------------------------------------------------------------------------

// -------------------------- GUI HELPER FUNCTIONS ----------------------------

/**
* @brief:
* @param button:
* @param enable_visibility:
*/
public static void EnableButton(GButton button, boolean enable_visibility){
  
  button.setEnabled(true);
  button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  
  if(enable_visibility) button.setVisible(true);
  
}

// ----------------------------------------------------------------------------

/**
* @brief:
* @param button:
* @param disable_visibility:
*/
public static void DisableButton(GButton button, boolean disable_visibility){
  
  button.setEnabled(false);
  button.setLocalColorScheme(GCScheme.RED_SCHEME);
  
  if(disable_visibility) button.setVisible(false);
  
}

// ----------------------------------------------------------------------------

/**
* @brief: Enable some buttons to trigger different click events 
*/
public static void SetButtonsToFireAllEvents(){
  
  forward_button.fireAllEvents(true);
  backward_button.fireAllEvents(true);
  left_button.fireAllEvents(true);
  right_button.fireAllEvents(true);
  
}

// ----------------------------------------------------------------------------

/**
* @brief: Set buttons that are not neccesary on the initial state of the GUI
*/
public static void SetInitialButtonsState(){
  
  room_button.setVisible(false);
  
}

// ----------------------------------------------------------------------------
