#include "motor_speed.h"

int state = 0; // State variable

void statemachine_update(String msg) {

  if(msg == "0") {
    state = 0;
  } else if(msg == "1") {
    state = 1;
  } else if(msg == "2") {
    state = 2;
  } else if(msg == "3") {
    state = 3;
  } else if(msg == "4") {
    state = 4;
  } else if(msg == "5") {
    state = 5;
  } else if(msg == "6") {
    state = 6;
  }
  
  if(state == 0) {
    // stop
    right_fwd(0);
    left_fwd(0);
  } else if(state == 1) {
    // fwd
    motorspeed_fwd();
  } else if(state == 2) {
    // reverse
    motorspeed_rev();
  } else if(state == 3) {
    // circle right
    right_rev(1024);
    left_fwd(1024);
  } else if(state == 4) {
    // circle left
    right_fwd(1024);
    left_rev(1024);
  } else if(state == 5) {
    // turn right
    right_fwd(0);
    left_fwd(1024);
  } else if(state == 6) {
    // turn left
    right_fwd(1024);
    left_fwd(0);
  } 
  

}


