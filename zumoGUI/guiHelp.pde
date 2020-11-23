// Author: Diego Ochando Torres
// Date: 18/11/2020
// e-mail: c0022981@my.shu.ac.uk


// ------------------------------ VARIABLES -----------------------------------

String zumo_data_strings[] = {
// String 1
"Detected a wall in front of the robot.\nTurn Left or Right.",
// String 2
"Zumo data 2"
};

// ----------------------------------------------------------------------------

String gui_help_strings[] = {
// String 1
"",
// String 2
"To start with task 2: \nSwitch the toggle to autonomous mode and then press forward button.",
// String 3
//"Task 3:\nTurn left or right and press 'completed' button, then the zumo robot will engage again task 2."
"Task 3&4:\nPress Left or Right buttons, then the zumo robot will rotate and engage again task 2."
};

// ----------------------------------------------------------------------------

// --------------------------- JAVA FUNCTIONS ---------------------------------

public static void EnableButton(GButton button){
  
  button.setEnabled(true);
  button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  
}

// ----------------------------------------------------------------------------

public static void DisableButton(GButton button){
  
  button.setEnabled(false);
  button.setLocalColorScheme(GCScheme.RED_SCHEME);
  
}

// ----------------------------------------------------------------------------
