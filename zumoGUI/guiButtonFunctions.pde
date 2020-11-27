// Author: Diego Ochando Torres
// Date: 27/11/2020
// e-mail: c0022981@my.shu.ac.uk

// -------------------------- GUI BUTTON FUNCTIONS ----------------------------

/**
* @brief:
* @param event:
*/
void forwardButton(GEvent event){
  
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
      gui_help_fill_label.setText(gui_help_strings[3]);
      EnableButton(room_button, true);
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
      DisableButton(forward_button, false);
    }
  }
  
}

// ----------------------------------------------------------------------------

/**
* @brief:
* @param event:
*/
void backwardButton(GEvent event){

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

}

// ----------------------------------------------------------------------------

/**
* @brief:
* @param event:
*/
void leftButton(GEvent event){

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

}

// ----------------------------------------------------------------------------

/**
* @brief:
* @param event:
*/
void rightButton(GEvent event){

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

}

// ----------------------------------------------------------------------------

/**
* @brief:
*/
void modeToggleButton(){

  // Indicate the zumo to change its behavior
  //zumoGUI.serialPort.write(6);
  
  if(mode_toggle.getState() == 0){
    mode_label.setText("Manual mode");
    println("Zumo changed to manual mode");
    current_task_label.setText("Current performing: Task 1");
    zumoGUI.manual_mode = true;
    // Enable usable buttons
    zumoGUI.EnableButton(forward_button, false);
    zumoGUI.EnableButton(backward_button, false);
    zumoGUI.EnableButton(left_button, false);
    zumoGUI.EnableButton(right_button, false);
  }
  else{
    mode_label.setText("Autonomous mode");
    println("Zumo changed to autonomous mode");
    zumoGUI.manual_mode = false;
    // Disable not usable buttons
    zumoGUI.DisableButton(backward_button, false);
    zumoGUI.DisableButton(left_button, false);
    zumoGUI.DisableButton(right_button, false);
  }

}

// ----------------------------------------------------------------------------

/**
* @brief:
*/
void roomButton(){
  
  zumoGUI.serialPort.write(10);
  current_task_label.setText("Current performing: Task 5");
  DisableButton(room_button, true);
  EnableButton(left_button, false);
  EnableButton(right_button, false);
  
}

// ----------------------------------------------------------------------------
