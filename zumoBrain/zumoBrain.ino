// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#include "zumoUtility.h"

ZumoRobot zumo;

void setup() {

  // Setup and initialize zumo variables and sensors
  zumo.InitializeZumo();

}

void loop() {

  // Update current zumo state and performs all neccesary actions for the rescue operation
  zumo.UpdateZumo();

}
