#include "motor_speed.h"
#include "sensing.h"

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

void statemachine_update(String msg) {
  if (msg == "start") {
    state = FIND_WALL;
  }
}

void statemachine_run() {
  Serial.println(state);
  if (state == START) {
    // do nothing, relies on message from user to continue

  } else if (state == FIND_WALL) {
    // stay in state until wall is detected
    Serial.println(sensing_readIRValue());
    if (sensing_readIRValue() > 625) {
      state = TURN_TO_RED;
    }

  } else if (state == TURN_TO_RED) {
    // stay in state until desired degrees of rotation is reached
  }
}

void stop_momentarily() {
  right_fwd(0);
  left_fwd(0);
  delay(10);
}
