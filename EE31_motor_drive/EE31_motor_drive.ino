int left_motorA = 5;
int left_motorB = 6;
int right_motorA = 7;
int right_motorB = 8;

// Duty cycle is int from 0 - 1024
void left_fwd(int duty) {
  digitalWrite(left_motorB, LOW);
  analogWrite(left_motorA, duty);

}

// Duty cycle is int from 0 - 1024
void left_rev(int duty) {
  digitalWrite(left_motorA, LOW);
  analogWrite(left_motorB, duty);

}

// Duty cycle is int from 0 - 1024
void right_fwd(int duty) {
  digitalWrite(right_motorB, LOW);
  analogWrite(right_motorA, duty);

}

// Duty cycle is int from 0 - 1024
void right_fwd(int duty) {
  digitalWrite(right_motorA, LOW);
  analogWrite(right_motorB, duty);

}

void setup() {
  // put your setup code here, to run once:
  pinMode(left_motorA, OUTPUT);
  pinMode(right_motorA, OUTPUT);
  pinMode(left_motorB, OUTPUT);
  pinMode(right_motorB, OUTPUT);

}

void loop() {
  right_fwd(1024);
  left_rev(1024);

  delay(3);

  left_fwd(1024);
  right_rev(1024);
}


