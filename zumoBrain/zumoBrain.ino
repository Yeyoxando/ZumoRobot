// Author: Diego Ochando Torres
// Date: 10/11/2020
// e-mail: c0022981@my.shu.ac.uk

#include "zumoUtility.h"

ZumoRobot zumo;

void setup() {
  
  zumo.InitializeZumo();

}

void loop() {
  
  zumo.UpdateZumo();

}
