// Need G4P library for GUI creation
import g4p_controls.*;
// Need Serial for communication over XBee
import processing.serial.*;

// ----------------------------------------------------------------------------

// ------------------------------ VARIABLES -----------------------------------

// XBee
Serial serialPort;
int value = 0;

// GUI controls
GButton button0; 
GButton button1; 
GButton button2; 
GButton button3; 
GButton button4;
GTextArea textarea1; 
GTextField textfield1; 

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

void serialEvent(Serial serialPort){
  //value = serialPort.read();
  //textarea1.setText(value + "");
  //println("Has entered here.");
}
// ----------------------------------------------------------------------------

// ------------------------------- GUI FUNCTIONS ------------------------------

public void button0_click1(GButton source, GEvent event) { // Stop button

  println("button0 - GButton >> GEvent." + event + " @ " + millis());
  
  // Write 1 on Xbee module to indicate the zumo to stop
  serialPort.write(1);
  
} // Stop button

public void button1_click1(GButton source, GEvent event) { // Forward button

  println("button1 - GButton >> GEvent." + event + " @ " + millis());
  
  // Write 2 on Xbee module to indicate the zumo to move forward
  serialPort.write(2);
  
} // Forward button

// ----------------------------------------------------------------------------

public void button2_click1(GButton source, GEvent event) { // Backward button

  println("button2 - GButton >> GEvent." + event + " @ " + millis());
  
  // Write 3 on Xbee module to indicate the zumo to move backward
  serialPort.write(3);
  
} // Backward button

// ----------------------------------------------------------------------------

public void button3_click1(GButton source, GEvent event) { // Turn right button

  println("button3 - GButton >> GEvent." + event + " @ " + millis());
  
  // Write 4 on Xbee module to indicate the zumo to turn right
  serialPort.write(4);
  
} // Turn right button

// ----------------------------------------------------------------------------

public void button4_click1(GButton source, GEvent event) { // Turn left button

  println("button4 - GButton >> GEvent." + event + " @ " + millis());
  
  // Write 5 on Xbee module to indicate the zumo to turn left
  serialPort.write(5);
  
} // Turn left button

// ----------------------------------------------------------------------------

public void textarea1_change1(GTextArea source, GEvent event) { // Display zumo info
  println("textarea1 - GTextArea >> GEvent." + event + " @ " + millis());
} // Display zumo info

// ----------------------------------------------------------------------------

public void textfield1_change1(GTextField source, GEvent event) { //_CODE_:textfield1:357450:
  //println("textfield1 - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:textfield1:357450:

// ----------------------------------------------------------------------------

// Create all the GUI controls. 
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  button0 = new GButton(this, 200, 200, 80, 30);
  button0.setText("Stop");
  button0.setLocalColorScheme(GCScheme.RED_SCHEME);
  button0.addEventHandler(this, "button0_click1");
  button1 = new GButton(this, 200, 150, 80, 30);
  button1.setText("Forward");
  button1.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button1.addEventHandler(this, "button1_click1");
  button2 = new GButton(this, 200, 250, 80, 30);
  button2.setText("Backward");
  button2.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button2.addEventHandler(this, "button2_click1");
  button3 = new GButton(this, 300, 200, 80, 30);
  button3.setText("Turn Right");
  button3.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button3.addEventHandler(this, "button4_click1");
  button4 = new GButton(this, 100, 200, 80, 30);
  button4.setText("Turn Left");
  button4.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button4.addEventHandler(this, "button3_click1");
  textarea1 = new GTextArea(this, 150, 20, 200, 80, G4P.SCROLLBARS_NONE);
  textarea1.setOpaque(true);
  textarea1.addEventHandler(this, "textarea1_change1");
  textfield1 = new GTextField(this, 150, 2, 120, 15, G4P.SCROLLBARS_NONE);
  textfield1.setText("Zumo messages");
  textfield1.setOpaque(true);
  textfield1.addEventHandler(this, "textfield1_change1");
}

// ----------------------------------------------------------------------------

// Use this method to add additional statements to customise the GUI controls
public void customGUI(){
  
}

// ----------------------------------------------------------------------------
