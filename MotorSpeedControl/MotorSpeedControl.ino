#include "EE31_motor_drive.h"

int left_motor_encoder = 3;
int right_motor_encoder = 4;

int last_millis = 0;

int left_count = 0;
int right_count = 0;
int left_duty = 255;
int right_duty = 255;
float sum = 0;

const int NUM_ROTATIONS = 50;

void setup() {
  statemachine_setup();
  Serial.begin(9600);
  pinMode(left_motor_encoder, INPUT);
  pinMode(right_motor_encoder, INPUT);

  Serial.println("Duty Cycle,ms per rev");

  attachInterrupt(digitalPinToInterrupt(left_motor_encoder), rotation_left, RISING);
  attachInterrupt(digitalPinToInterrupt(right_motor_encoder), rotation_right, RISING);
  left_fwd(left_duty);
  right_fwd(right_duty);
}

void rotation_left() {
  int current = millis();
  int diff_time = current - last_millis;

  last_millis = current;

  if (last_millis == 0) return;

  float mps = 0.5 * 3.1415 / diff_time;
  // Serial.println(mps);

  sum += diff_time;

  left_count++;
}

void rotation_right() {
  right_count++;
}

void loop() {
  delay(100);
  

  int difference = left_count - right_count;

  Serial.print(difference);
  Serial.print(" ");
  Serial.print(left_count);
  Serial.print(" ");
  Serial.println(right_count);

  if (difference > 100) {
    // slow down left
    left_fwd(150);
    right_fwd(255);
    Serial.println("Slow left");
  } else if (difference < -100) {
    // slow down right
    right_fwd(100);
    left_fwd(255);
    Serial.println("Slow right");
  }
}

