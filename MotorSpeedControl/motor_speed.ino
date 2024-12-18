/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 11/21/2024
* 
* Motor Control functionality, function definitions for moving the robot,
* turning the robot, reversing, in addition to managing the speed to make both
* motors move at equal speeds. 
*/

#include "motor_speed.h"
#include "sensing.h"
#include "motor_calibration.h"

// Pin Numbers for Arduino Connections
const int left_motor_encoder = 12;
const int right_motor_encoder = 13;
const int left_motorA = 5;
const int left_motorB = 6;
const int right_motorA = 10;
const int right_motorB = 3;

// Motor Speed Control Variables
int left_count = 0;
int right_count = 0;
int left_duty = 255;
int right_duty = 255;

int offset = 0;
int direction_right = 0; // positive = forward, negative = backwards
int direction_left = 0;

int rotate_amount = 0; // positive = right, negative = left

const int NUM_ROTATIONS = 50;

int lineLeftCount = 0;
int lineRightCount = 0;

int batteryOffset = BATTERY_LEVEL_OFFSET;

// State Definitions for Driving and Rotating
typedef enum {
  IDLE,
  DRIVE,
  ROTATE,
  FOLLOW_COLOR
} SpeedState;

SpeedState motorspeed_state = DRIVE;

void motorspeed_setup() {
  pinMode(left_motor_encoder, INPUT);
  pinMode(right_motor_encoder, INPUT);

  attachInterrupt(digitalPinToInterrupt(left_motor_encoder), rotation_left, RISING);
  attachInterrupt(digitalPinToInterrupt(right_motor_encoder), rotation_right, RISING);
  
  pinMode(left_motorA, OUTPUT);
  pinMode(right_motorA, OUTPUT);
  pinMode(left_motorB, OUTPUT);
  pinMode(right_motorB, OUTPUT);
}

// Interrupt to be attached to the left motor encoder's pin
void rotation_left() {
  left_count++;
}

// Interrupt to be attached to the right motor encoder's pin
void rotation_right() {
  right_count++;
}

void motor_drive_loop() {
  int difference = left_count - right_count;

  int left_calculated = LEFT_DUTY_OFFSET - batteryOffset;
  int right_calculated = RIGHT_DUTY_OFFSET - batteryOffset;

  Serial.print("Encoders: ");
  Serial.print(difference);
  Serial.print(" ");
  Serial.print(left_count);
  Serial.print(" ");
  Serial.println(right_count);

  if (difference > (THRESHOLD + offset)) {
    // slow down left
    left_duty = 255 - (difference - offset) * 3 + left_calculated;
    right_duty = 255 + right_calculated;
    Serial.println("Slow left");
  } else if (difference < (-THRESHOLD + offset)) {
    // slow down right
    right_duty = 255 + (difference - offset) * 3 + right_calculated;
    left_duty = 255 + left_calculated;
    Serial.println("Slow right");
  } else {
    right_duty = 255 + right_calculated;
    left_duty = 255 + left_calculated;
  }

  if (left_duty < 0 || left_duty > 255) left_duty = 0;
  if (right_duty < 0 || right_duty > 255) right_duty = 0;

  Serial.print("Left Duty: ");
  Serial.print(left_duty);
  Serial.print(" Right Duty: ");
  Serial.println(right_duty);

  if (direction_left < 0) {
    left_rev(left_duty);
  } else if (direction_left > 0) {
    left_fwd(left_duty);
  } else {
    left_fwd(0);
  }
  
  if (direction_right < 0) {
    right_rev(right_duty);
  } else if (direction_right > 0) {
    right_fwd(right_duty);
  } else {
    right_fwd(0);
  }

}

void motor_rotate_loop() {
  if (rotate_amount > 0) { // turn right
    left_fwd(left_duty);
    right_rev(right_duty);

  } else if (rotate_amount < 0) { // turn left
    left_rev(left_duty);
    right_fwd(right_duty);

  } else {
    motorspeed_state = IDLE;
  }

  if (right_count > rotate_amount) {
    right_fwd(0);
  }
  if (left_count > rotate_amount) {
    left_fwd(0);
  }

  if (right_count > rotate_amount && left_count > rotate_amount) {
    rotate_amount = 0;
  }
}

bool rotate_done() {
  return rotate_amount == 0;
}

// amount > 0 => turn right
// amount < 0 => turn left
void motorspeed_rotate(int amount) {
  batteryOffset = 50;
  if (amount > 0) {
    direction_left = 1;
    direction_right = -1;
  } else {
    direction_left = -1;
    direction_right = 1;
  }
  if (amount < 0) amount = -amount;
  rotate_amount = amount;
  motorspeed_state = ROTATE;
  left_count = 0;
  right_count = 0;
}

void motorspeed_loop() {

  if (motorspeed_state == DRIVE) {
    motor_drive_loop();
  } else if (motorspeed_state == ROTATE) {
    motor_drive_loop();
    if (left_count > rotate_amount && right_count > rotate_amount) {
      Serial.println("Rotate stop");
      left_count = 0;
      right_count = 0;
      motorspeed_state = IDLE;
    } else if (left_count > rotate_amount) {
      Serial.println("Left stop");
      left_fwd(0);
    } else if (right_count > rotate_amount) {
      Serial.println("Right stop");
      right_fwd(0);
    }
  }
  else if (motorspeed_state == FOLLOW_COLOR) {
    // linefollow_loop();
    motor_drive_loop();
  } else {
    // IDLE
    right_fwd(0);
    left_fwd(0);
  }
}

// offset < 0 => go left
// offset > 0 => go right
void motorspeed_set_offset(int new_offset) {
  offset = new_offset;
}

bool motorspeed_isrotating() {
  return motorspeed_state == ROTATE;
}

// 0 = off, <0 backwards, >0 forwards
void motorspeed_set_direction(int new_direction) {
  batteryOffset = BATTERY_LEVEL_OFFSET;
  if (new_direction == 0) {
    motorspeed_state = IDLE;
  } else {
    motorspeed_state = DRIVE;
    direction_left = new_direction;
    direction_right = new_direction;
  }
}

void linefollow_loop() {
  if (!sensing_colorReady()) return; // line following colors are not ready, try again next loop

  SensorColor left_color = sensing_readLeftColor();
  SensorColor right_color = sensing_readRightColor();

  if (left_color != COLOR_BLACK && right_color != COLOR_BLACK) {
    // We are on track, both sensors are reading a color
    lineLeftCount = 0;
    lineRightCount = 0;
  } else if (left_color == COLOR_BLACK && right_color != COLOR_BLACK) {
    Serial.println("Left black");
    // We are too far left
    lineLeftCount++;
  } else if (left_color != COLOR_BLACK && right_color == COLOR_BLACK) {
    Serial.println("Right black");
    // We are too far right
    lineRightCount++;
  } // otherwise we are off track, rely on the previous counts to correct

  if (lineLeftCount != 0) {
    motorspeed_set_offset(LINEFOLLOW_OFFSET * lineLeftCount);
  } else if (lineRightCount != 0) {
    motorspeed_set_offset(-LINEFOLLOW_OFFSET * lineRightCount);
  } else {
    motorspeed_set_offset(0);
  }

  Serial.print("Left offset: ");
  Serial.println(lineLeftCount);
  Serial.print("Right offset: ");
  Serial.println(lineRightCount);

  sensing_startColors();
}

// void follow_color(Color threshold) {
//   colorThreshold = threshold;
//   motorspeed_state = FOLLOW_COLOR; 
// }

void left_fwd(int duty) {
  digitalWrite(left_motorB, LOW);
  analogWrite(left_motorA, duty);
}

void left_rev(int duty) {
  digitalWrite(left_motorA, LOW);
  analogWrite(left_motorB, duty);

}

void right_fwd(int duty) {
  digitalWrite(right_motorB, LOW);
  analogWrite(right_motorA, duty);

}

void right_rev(int duty) {
  digitalWrite(right_motorA, LOW);
  analogWrite(right_motorB, duty);

}

/* 
*  TODO: use this within the implementation above
*  Function to keep the motors from getting damaged from moving forward then 
*  backwards to quickly. 
*/
void motorspeed_stop_momentarily() {
  left_count = 0;
  right_count = 0;
  right_fwd(0);
  left_fwd(0);
  delay(2);
}
