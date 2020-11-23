// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

// Need G4P library for GUI creation
import g4p_controls.*;
// Need Serial for communication over XBee
import processing.serial.*;

// ----------------------------------------------------------------------------

// ------------------------------ VARIABLES -----------------------------------

// XBee
public static Serial serialPort;

//Zumo
public static boolean manual_mode = true;

// ----------------------------------------------------------------------------

// --------------------------- JAVA FUNCTIONS ---------------------------------

public void setup(){
  // Java window
  size(480, 320, JAVA2D);
  
  // G4P GUI
  createGUI();
  customGUI();
  
  // Serial connection
  // Serial is on my COM4 port
  String portName = "COM4";
  serialPort = new Serial(this, portName, 9600);
  
  //GUI
  gui_help_fill_label.setText(gui_help_strings[1]);
  
}

// ----------------------------------------------------------------------------

public void draw(){
  
  background(255);

}

// ----------------------------------------------------------------------------

void serialEvent(Serial serialPort){
  int value = serialPort.read();
  println("Received data");
  
  switch(value){
    case 100:{ // kGUIData_SwitchManualMode
      break;
    }
    case 101:{ // kGUIData_ReachedFrontWall
      //serialPort.write(6);
      //mode_toggle.setState(0);
      //mode_label.setText("Manual mode");
      //println("Zumo changed to manual mode");
      //manual_mode = true;
      // Enable usable buttons
      //EnableButton(backward_button);
      EnableButton(left_button);
      EnableButton(right_button);
      
      current_task_label.setText("Currently performing: Task 3 & 4");
      zumo_msg_fill_label.setText(zumo_data_strings[0]);
      gui_help_fill_label.setText(gui_help_strings[2]);
      //completed_button.setVisible(true);
      break;
    }
    case 102:{
      zumo_msg_fill_label.setText("");
      gui_help_fill_label.setText("");
      DisableButton(left_button);
      DisableButton(right_button);
      
      zumoGUI.serialPort.write(7);
      current_task_label.setText("Current performing: Task 2");
      break;
    }
    default:{
      break;
    }
  };
  
}

// ----------------------------------------------------------------------------

// ------------------------------- GUI FUNCTIONS ------------------------------

// Use this method to add additional statements to customise the GUI controls
public void customGUI(){
  
}

// ----------------------------------------------------------------------------

/* Pasted here to know values easily
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

enum GUIData{
  kGUIData_SwitchManualMode = 100,
  kGUIData_ReachedFrontWall = 101,
  kGUIData_FinishedAutoRotation = 102,
};

*/
