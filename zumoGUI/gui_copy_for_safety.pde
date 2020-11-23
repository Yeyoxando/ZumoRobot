/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void forwardButtonClick(GButton source, GEvent event) { //_CODE_:forward_button:221725:
  
  if(event == GEvent.PRESSED){
    println("Clicked forward button");
    if(zumoGUI.manual_mode){
      // Send move forward to zumo until button is released
      zumoGUI.serialPort.write(2);
    }
    else{
      // Activate task 2 if zumo is autonomous
      zumoGUI.serialPort.write(7);
      current_task_label.setText("Current performing: Task 2");
      gui_help_fill_label.setText("");
    }
  }
  if(event == GEvent.RELEASED || event == GEvent.CLICKED){
    println("Released forward button");
    if(zumoGUI.manual_mode){
      // Tell zumo to stop
      zumoGUI.serialPort.write(1);
    }
    else{
      // Disable the button when is autonomous forwarding
      DisableButton(forward_button);
    }
  }
  
} //_CODE_:forward_button:221725:

public void backwardButtonClick(GButton source, GEvent event) { //_CODE_:backward_button:819618:
  
  if(event == GEvent.PRESSED){
    println("Clicked backward button");
    if(zumoGUI.manual_mode){
      // Send move backward to zumo until button is released
      zumoGUI.serialPort.write(3);
    }
    else{
      // Do nothing for now
    }
  }
  if(event == GEvent.RELEASED || event == GEvent.CLICKED){
    println("Released backward button");
    if(zumoGUI.manual_mode){
      // Tell zumo to stop
      zumoGUI.serialPort.write(1);
    }
  }
  
} //_CODE_:backward_button:819618:

public void leftButtonClick(GButton source, GEvent event) { //_CODE_:left_button:590894:
  
  if(event == GEvent.PRESSED){
    println("Clicked left button");
    if(zumoGUI.manual_mode){
      // Send turn left to zumo until button is released
      zumoGUI.serialPort.write(4);
    }
    else{
      // Activate task 4 if zumo is autonomous
      zumoGUI.serialPort.write(8);
    }
  }
  if(event == GEvent.RELEASED || event == GEvent.CLICKED){
    println("Released left button");
    if(zumoGUI.manual_mode){
      // Tell zumo to stop
      zumoGUI.serialPort.write(1);
    }
  }
  
} //_CODE_:left_button:590894:

public void rightButtonClick(GButton source, GEvent event) { //_CODE_:right_button:761249:
    
  if(event == GEvent.PRESSED){
    println("Clicked right button");
    if(zumoGUI.manual_mode){
      // Send turn right to zumo until button is released
      zumoGUI.serialPort.write(5);
    }
    else{
      // Activate task 4 if zumo is autonomous
      zumoGUI.serialPort.write(9);
    }
  }
  if(event == GEvent.RELEASED || event == GEvent.CLICKED){
    println("Released right button");
    if(zumoGUI.manual_mode){
      // Tell zumo to stop
      zumoGUI.serialPort.write(1);
    }
  }
  
} //_CODE_:right_button:761249:

public void modeToggleClick(GImageToggleButton source, GEvent event) { //_CODE_:mode_toggle:529271:
  
  // Indicate the zumo to change its behavior
  //zumoGUI.serialPort.write(6);
  
  if(mode_toggle.getState() == 0){
    mode_label.setText("Manual mode");
    println("Zumo changed to manual mode");
    current_task_label.setText("Current performing: Task 1");
    zumoGUI.manual_mode = true;
    // Enable usable buttons
    zumoGUI.EnableButton(forward_button);
    zumoGUI.EnableButton(backward_button);
    zumoGUI.EnableButton(left_button);
    zumoGUI.EnableButton(right_button);
  }
  else{
    mode_label.setText("Autonomous mode");
    println("Zumo changed to autonomous mode");
    zumoGUI.manual_mode = false;
    // Disable not usable buttons
    zumoGUI.DisableButton(backward_button);
    zumoGUI.DisableButton(left_button);
    zumoGUI.DisableButton(right_button);
  }
  
} //_CODE_:mode_toggle:529271:

public void completedButtonClick(GButton source, GEvent event) { //_CODE_:completed_button:605471:

  println("Clicked completed button");
  // Tell zumo to continue
  completed_button.setVisible(false);
  zumo_msg_fill_label.setText("");
  gui_help_fill_label.setText("");
  
  mode_toggle.setState(1);
  mode_label.setText("Autonomous mode");
  println("Zumo changed to autonomous mode");
  zumoGUI.manual_mode = false;
  // Disable not usable buttons
  DisableButton(backward_button);
  DisableButton(left_button);
  DisableButton(right_button);
  
  zumoGUI.serialPort.write(7);
  current_task_label.setText("Current performing: Task 2");
  
} //_CODE_:completed_button:605471:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  forward_button = new GButton(this, 300, 212, 80, 30);
  forward_button.setText("Forward");
  forward_button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  forward_button.fireAllEvents(true);
  forward_button.addEventHandler(this, "forwardButtonClick");
  backward_button = new GButton(this, 300, 280, 80, 30);
  backward_button.setText("Backward");
  backward_button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  backward_button.fireAllEvents(true);
  backward_button.addEventHandler(this, "backwardButtonClick");
  left_button = new GButton(this, 215, 246, 80, 30);
  left_button.setText("Turn Left");
  left_button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  left_button.fireAllEvents(true);
  left_button.addEventHandler(this, "leftButtonClick");
  right_button = new GButton(this, 385, 246, 80, 30);
  right_button.setText("Turn Right");
  right_button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  right_button.fireAllEvents(true);
  right_button.addEventHandler(this, "rightButtonClick");
  mode_toggle = new GImageToggleButton(this, 321, 25);
  mode_toggle.addEventHandler(this, "modeToggleClick");
  mode_label = new GLabel(this, 280, 80, 120, 20);
  mode_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  mode_label.setText("Manual mode");
  mode_label.setOpaque(false);
  zumo_msg_label = new GLabel(this, 6, 2, 100, 20);
  zumo_msg_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  zumo_msg_label.setText("Zumo messages");
  zumo_msg_label.setOpaque(false);
  current_task_label = new GLabel(this, 240, 120, 200, 20);
  current_task_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  current_task_label.setText("Current performing: Task 1");
  current_task_label.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  current_task_label.setOpaque(true);
  gui_help_label = new GLabel(this, 6, 188, 80, 20);
  gui_help_label.setTextAlign(GAlign.LEFT, GAlign.MIDDLE);
  gui_help_label.setText("GUI help");
  gui_help_label.setOpaque(false);
  completed_button = new GButton(this, 300, 150, 80, 30);
  completed_button.setText("Completed");
  completed_button.setLocalColorScheme(GCScheme.YELLOW_SCHEME);
  completed_button.addEventHandler(this, "completedButtonClick");
  completed_button.setVisible(false);
  zumo_msg_fill_label = new GLabel(this, 6, 24, 200, 150);
  zumo_msg_fill_label.setTextAlign(GAlign.LEFT, GAlign.TOP);
  zumo_msg_fill_label.setOpaque(true);
  gui_help_fill_label = new GLabel(this, 6, 212, 200, 100);
  gui_help_fill_label.setTextAlign(GAlign.LEFT, GAlign.TOP);
  gui_help_fill_label.setOpaque(true);
}

// Variable declarations 
// autogenerated do not edit
GButton forward_button; 
GButton backward_button; 
GButton left_button; 
GButton right_button; 
GButton completed_button; 
public static GImageToggleButton mode_toggle; 
public static GLabel mode_label; 
GLabel zumo_msg_label; 
GLabel gui_help_label; 
public static GLabel current_task_label; 
public static GLabel zumo_msg_fill_label; 
public static GLabel gui_help_fill_label; 
