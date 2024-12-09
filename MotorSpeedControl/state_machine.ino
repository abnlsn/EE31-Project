/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 11/21/2024
* 
* Function definitions for State Machine for mobile bot that line follows, 
* wall senses, and communicates with a server. Below is state logic that 
* accounts for the demonstration required for the final presentation.
*/
#include "motor_speed.h"
#include "sensing.h"
#include "wifi_client.h"

#define IR_THRESHOLD 120

// Variables to define the actions required for the project demo
enum State {
  START,
  FIND_WALL,
  TURN_TO_RED,
  FIND_RED,
  FOLLOW_RED,
  FIND_YELLOW,
  FOLLOW_YELLOW,
  TURN_TO_START,
  FIND_START
};

enum State state = START; // State variable

void statemachine_setup() {
  wifi_setup();
}


/* Function in order to receive commands from the server */
void statemachine_update(String msg) {
  if (msg == "start") {
    state = FIND_WALL;
  }
}

/* 
* Function to run through the solo / group demo that updates the state and goes
* through each required action. 
*/

void statemachine_run() {
  Serial.print("State: ");
  Serial.println(state);
  if (state == START) {
    // do nothing, relies on message from user to continue
    // state = FIND_WALL;
    if (wifi_getmessage() == "start") {
      state = FIND_WALL;
    }

  } else if (state == FIND_WALL) {
    // stay in state until wall is detected
    motorspeed_set_direction(1);
    motorspeed_set_offset(0);
    if (sensing_readIRValue() > 120) {
      state = TURN_TO_RED;
      motorspeed_stop_momentarily();
      motorspeed_rotate(DEGREES_90); // TODO: NEED TO GET CORRECT DEGREES
    }

  } else if (state == TURN_TO_RED) {
    // stay in state until desired degrees of rotation is reached

    // if we are done rotating, move to next state 
    if (!motorspeed_isrotating()) {
      state = FIND_RED;
    }

  } else if (state == FIND_RED) {
    // stay in state until red is detected

    // check if left and right sensors are on red
    if (sensing_colorReady()) {

      if (sensing_readLeftColor() == COLOR_RED && sensing_readRightColor() == COLOR_RED) {
        state = START;
      }

      sensing_startColors();
    }

  } else if (state == FOLLOW_RED) {
    // follow red line
    linefollow_loop();
    
  } else if (state == FIND_YELLOW) {
    // stay in state until yellow is detected

        if (sensing_colorReady()) {

      if (sensing_readLeftColor() == COLOR_YELLOW && sensing_readRightColor() == COLOR_YELLOW) {
        state = FOLLOW_YELLOW;
      }

      sensing_startColors();
    }

  } else if (state == FOLLOW_YELLOW) {
    // follow yellow line
    linefollow_loop();

  } else if (state == TURN_TO_START) {
    // stay in state until desired degrees of rotation is reached

  } else if (state == FIND_START) {
    // stay in state until start is detected
  }
}

