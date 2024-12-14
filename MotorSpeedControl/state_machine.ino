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


// Variables to define the actions required for the project demo
enum State {
  START,
  FIND_WALL,
  TURN_TO_RED,
  FIND_RED,
  TURN_TO_FOLLOW_RED,
  FOLLOW_RED,
  TURN_TO_YELLOW,
  FIND_YELLOW,
  TURN_TO_FOLLOW_YELLOW,
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

  String msg = wifi_getmessage();

  if (state == START) {
    // do nothing, relies on message from user to continue
    // state = FIND_WALL;
    if (msg == "start") {
      sensing_calculate_IR();
      state = FIND_WALL;
      wifi_sendmessage("New state: FIND_WALL");
    }

  } else if (state == FIND_WALL) {
    // stay in state until wall is detected
    motorspeed_set_direction(1);
    motorspeed_set_offset(0);
    int IR_value = sensing_readIRValue();
    Serial.print("IR Value: ");
    Serial.println(IR_value);
    if (IR_value > sensing_IR_th_calculated) {
      state = TURN_TO_RED;
      wifi_sendmessage(String(IR_value));
      wifi_sendmessage("New state: TURN_TO_RED");
      motorspeed_stop_momentarily();
      motorspeed_rotate(LEFT_DEGREES_180); // TODO: NEED TO GET CORRECT DEGREES
    }

  } else if (state == TURN_TO_RED) {
    // stay in state until desired degrees of rotation is reached

    // if we are done rotating, move to next state 
    if (!motorspeed_isrotating()) {
      state = FIND_RED;
      wifi_sendmessage("New state: FIND_RED");
      motorspeed_stop_momentarily();
      motorspeed_set_direction(1);
    }

  } else if (state == FIND_RED) {
    // stay in state until red is detected

    // check if left and right sensors are on red
    if (sensing_colorReady()) {
      SensorColor left = sensing_readLeftAverage();
      SensorColor right = sensing_readRightAverage();
      Serial.print("Left: ");
      DEBUG_PRINT_COLOR(left);
      Serial.print("\nRight: ");
      DEBUG_PRINT_COLOR(right);
      Serial.println();

      if (sensing_readLeftAverage() == COLOR_RED && sensing_readRightAverage() == COLOR_RED) {
        state = TURN_TO_FOLLOW_RED;
        motorspeed_stop_momentarily();
        motorspeed_rotate(LEFT_DEGREES_90);
        wifi_sendmessage("New state: TURN_TO_FOLLOW_RED");
      }

      sensing_startColors();
    }
  
  } else if (state == TURN_TO_FOLLOW_RED) {
    if (!motorspeed_isrotating()) {
      state = FOLLOW_RED;
      wifi_sendmessage("New state: FOLLOW_RED");
      motorspeed_stop_momentarily();
      motorspeed_set_direction(1);
    }

  } else if (state == FOLLOW_RED) {
    motorspeed_set_direction(1);
    // follow red line
    linefollow_loop();

    int IR_value = sensing_readIRValue();
    Serial.print("IR Value: ");
    Serial.println(IR_value);
    if (IR_value > sensing_IR_th_calculated) {
      state = TURN_TO_YELLOW;
      wifi_sendmessage("New state: TURN_TO_YELLOW");
      motorspeed_stop_momentarily();
      motorspeed_rotate(LEFT_DEGREES_90);
    }
    
  } else if (state == TURN_TO_YELLOW) {
    if (!motorspeed_isrotating()) {
      state = FIND_YELLOW;
      wifi_sendmessage("New state: FIND_YELLOW");
      motorspeed_stop_momentarily();
      motorspeed_set_direction(1);
    }
  } else if (state == FIND_YELLOW) {
    if (sensing_colorReady()) {
      SensorColor left = sensing_readLeftAverage();
      SensorColor right = sensing_readRightAverage();

      if (sensing_readLeftAverage() == COLOR_RED && sensing_readRightAverage() == COLOR_RED) {
        state = TURN_TO_FOLLOW_YELLOW;
        motorspeed_stop_momentarily();
        motorspeed_rotate(LEFT_DEGREES_90);
        wifi_sendmessage("New state: TURN_TO_FOLLOW_YELLOW");
      }

      sensing_startColors();
    }

  } else if (state == TURN_TO_FOLLOW_YELLOW) {
    if (!motorspeed_isrotating()) {
      state = FOLLOW_YELLOW;
      wifi_sendmessage("New state: FOLLOW_YELLOW");
      motorspeed_stop_momentarily();
      motorspeed_set_direction(1);
    }
  } else if (state == FOLLOW_YELLOW) {
  motorspeed_set_direction(1);
    // follow yellow line
    linefollow_loop();

    int IR_value = sensing_readIRValue();
    Serial.print("IR Value: ");
    Serial.println(IR_value);
    if (IR_value > sensing_IR_th_calculated) {
      state = TURN_TO_START;
      wifi_sendmessage("New state: TURN_TO_START");
      motorspeed_stop_momentarily();
      motorspeed_rotate(LEFT_DEGREES_90);
    }

  } else if (state == TURN_TO_START) {
    // stay in state until desired degrees of rotation is reached
    if (!motorspeed_isrotating()) {
      state = FIND_START;
      wifi_sendmessage("New state: FIND_START");
      motorspeed_stop_momentarily();
      motorspeed_set_direction(1);
    }

  } else if (state == FIND_START) {
    // stay in state until start is detected
    if (sensing_readIRValue() > sensing_IR_th_calculated) {
      state = START;
      wifi_sendmessage("New state: START");
      motorspeed_stop_momentarily();
      motorspeed_set_direction(0);
    }
  }

  if (msg == "reset") {
    state = START;
    motorspeed_set_direction(0);
    wifi_sendmessage("Reset to: START");
  }
}

