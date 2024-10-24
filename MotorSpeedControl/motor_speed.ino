const int left_motor_encoder = 3;
const int right_motor_encoder = 4;
const int left_motorA = 5;
const int left_motorB = 6;
const int right_motorA = 7;
const int right_motorB = 8;

int last_millis = 0;

int left_count = 0;
int right_count = 0;
int left_duty = 255;
int right_duty = 255;
float sum = 0;

const int NUM_ROTATIONS = 50;

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

void motorspeed_loop() {
  delay(100);
  

  int difference = left_count - right_count;

  Serial.print(difference);
  Serial.print(" ");
  Serial.print(left_count);
  Serial.print(" ");
  Serial.println(right_count);

  if (difference > 10) {
    // slow down left
    left_fwd(200 + LEFT_DUTY_OFFSET);
    right_fwd(255 + RIGHT_DUTY_OFFSET);
    Serial.println("Slow left");
  } else if (difference < -10) {
    // slow down right
    right_fwd(200 + RIGHT_DUTY_OFFSET);
    left_fwd(255 + LEFT_DUTY_OFFSET);
    Serial.println("Slow right");
  } else {
    right_fwd(255 + RIGHT_DUTY_OFFSET);
    left_fwd(255 + LEFT_DUTY_OFFSET);
  }
}

void motorspeed_fwd() {

}

void motorspeed_rev() {

}

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