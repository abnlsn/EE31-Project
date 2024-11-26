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

  } else if (state == FIND_WALL) {
    // stay in state until wall is detected
    if (sensing_readIRValue() > 625) {
      state = TURN_TO_RED;
    }

  } else if (state == TURN_TO_RED) {
    // stay in state until desired degrees of rotation is reached
    Color left_color = sensing_readLeftColor();
    Color right_color = sensing_readRightColor();

  } else if (state == FIND_RED) {
    // stay in state until red is detected

  } else if (state == FOLLOW_RED) {
    // follow red line

  } else if (state == FIND_YELLOW) {
    // stay in state until yellow is detected

  } else if (state == FOLLOW_YELLOW) {
    // follow yellow line

  } else if (state == TURN_TO_START) {
    // stay in state until desired degrees of rotation is reached

  } else if (state == FIND_START) {
    // stay in state until start is detected
  }
}

