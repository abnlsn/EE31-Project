
int left_motorA = 5;
int left_motorB = 6;
int right_motorA = 7;
int right_motorB = 8;

int state = 0; // State variable

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
void right_rev(int duty) {
  digitalWrite(right_motorA, LOW);
  analogWrite(right_motorB, duty);

}

void setup() {
  // put your setup code here, to run once:
  pinMode(left_motorA, OUTPUT);
  pinMode(right_motorA, OUTPUT);
  pinMode(left_motorB, OUTPUT);
  pinMode(right_motorB, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  String msg;
  Serial.println("Enter Command: ");

  while (Serial.available() == 0) { }
  
  msg = Serial.readString();
  msg.trim();

  if(msg == "Go to 0") {
    state = 0;
  } else if(msg == "Go to 1") {
    state = 1;
  } else if(msg == "Go to 2") {
    state = 2;
  } else if(msg == "Go to 3") {
    state = 3;
  } else if(msg == "Go to 4") {
    state = 4;
  } else if(msg == "Go to 5") {
    state = 5;
  } else if(msg == "Go to 6") {
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


