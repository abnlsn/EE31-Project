
int state = 0; // State variable

// Duty cycle is int from 0 - 1024
void left_fwd(int duty) {
  digitalWrite(left_motorB, LOW);
  analogWrite(left_motorA, duty);
}

// Duty cycle is int from 0 - 1024
void left_rev(int duty) {
  Serial.println("left_rev");
  digitalWrite(left_motorA, LOW);
  analogWrite(left_motorB, duty);

}

// Duty cycle is int from 0 - 1024
void right_fwd(int duty) {
  Serial.println("right_fwd");
  digitalWrite(right_motorB, LOW);
  analogWrite(right_motorA, duty);

}

// Duty cycle is int from 0 - 1024
void right_rev(int duty) {
  Serial.println("right_rev");
  digitalWrite(right_motorA, LOW);
  analogWrite(right_motorB, duty);

}

void statemachine_setup() {
  // put your setup code here, to run once:
  // Serial.println("Setting up state machine...");
  pinMode(left_motorA, OUTPUT);
  pinMode(right_motorA, OUTPUT);
  pinMode(left_motorB, OUTPUT);
  pinMode(right_motorB, OUTPUT);

}

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
    right_fwd(0);
    left_fwd(0);
  } else if(state == 1) {
    right_fwd(1024);
    left_fwd(1024);
  } else if(state == 2) {
    right_rev(1024);
    left_rev(1024);
  } else if(state == 3) {
    right_rev(1024);
    left_fwd(1024);
  } else if(state == 4) {
    right_fwd(1024);
    left_rev(1024);
  } else if(state == 5) {
    right_fwd(0);
    left_fwd(1024);
  } else if(state == 6) {
    right_fwd(1024);
    left_fwd(0);
  } 
  

}


