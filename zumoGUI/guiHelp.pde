// Author: Diego Ochando Torres
// Date: 18/11/2020
// e-mail: c0022981@my.shu.ac.uk

/** @file guiHelp_doxy.java
 *  @brief GUI helper variables and functions.\n(Real name -> guiHelp.pde). 
 *  
 *  Details.
 *  \n Stores premade strings with help tips that will be displayed on the GUI to help the user.
 *  \n Also to show information of events to the user.
 *  \n Functions to help with the GUI responisvityare included here.
*/

// ------------------------- GUI HELPER VARIABLES ------------------------------

/**
* @brief Data that will be displayed on the GUI to give feedback to the user of what is happening.
*/
public static String zumo_data_strings[] = {
// String 1 - Detected wall
"Detected a wall in front of the robot.\nTurn Left or Right.", 
// String 2 - Start inspecting the room
"Zumo is inspecting the room.", 
// String 3 - Finished inspecting the room
"Zumo has inspected the room. Information added below.", 
};

// ----------------------------------------------------------------------------

/**
* @brief Help information to the user on how to perform tasks with the GUI.
*/
public static String gui_help_strings[] = {
// String 1 - Blank
"",
// String 2 - Task 2 start help
"To start with task 2:\nSwitch the toggle to autonomous mode and then press forward button.",
// String 3 - Task 3&4 start help
//"Task 3:\nTurn left or right and press 'completed' button, then the zumo robot will engage again task 2."
"Task 3&4:\nPress Left or Right buttons, then the zumo robot will rotate and engage again task 2.",
// String 4 - Task 5 start help
"To start with task 5:\nWhen the zumo is about to enter a room you should press the 'Room!' button.\nThen press Turn Left or Turn Right buttons to indicate in which direction the room is.\nZumo will take care of the rest."
};

// ----------------------------------------------------------------------------

// -------------------------- GUI HELPER FUNCTIONS ----------------------------

/**
* @brief Enables a button of the GUI.
* @param button on which button will affect the function.
* @param enable_visibility should enable button visibility too.
*/
public static void EnableButton(GButton button, boolean enable_visibility){
  
  button.setEnabled(true);
  button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  
  if(enable_visibility) button.setVisible(true);
  
}

// ----------------------------------------------------------------------------

/**
* @brief Disables a button of the GUI.
* @param button on which button will affect the function.
* @param disable_visibility should disable button visibility too.
*/
public static void DisableButton(GButton button, boolean disable_visibility){
  
  button.setEnabled(false);
  button.setLocalColorScheme(GCScheme.RED_SCHEME);
  
  if(disable_visibility) button.setVisible(false);
  
}

// ----------------------------------------------------------------------------

/**
* @brief Enable some buttons to trigger different click events, not only when pressed. 
*/
public static void SetButtonsToFireAllEvents(){
  
  forward_button.fireAllEvents(true);
  backward_button.fireAllEvents(true);
  left_button.fireAllEvents(true);
  right_button.fireAllEvents(true);
  
}

// ----------------------------------------------------------------------------

/**
* @brief Set button states and layouts on the initial state of the GUI.
*/
public static void SetInitialButtonsState(){
  
  room_button.setVisible(false);
  
}

// ----------------------------------------------------------------------------
