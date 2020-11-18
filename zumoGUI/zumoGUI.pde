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
int value = 0;

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
  
}

// ----------------------------------------------------------------------------

public void draw(){
  background(230);
}

// ----------------------------------------------------------------------------

void serialEvent(Serial serialPort){
  //value = serialPort.read();
  //textarea1.setText(value + "");
  //println("Has entered here.");
}

// ----------------------------------------------------------------------------

// ------------------------------- GUI FUNCTIONS ------------------------------

// Use this method to add additional statements to customise the GUI controls
public void customGUI(){
  
}

// ----------------------------------------------------------------------------
