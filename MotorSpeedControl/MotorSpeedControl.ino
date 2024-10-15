int left_motor_encoder = 3;

void setup() {
    Serial.begin(9600);
    pinMode(left_motor_encoder, INPUT);

    Serial.println("HI");

    attachInterrupt(digitalPinToInterrupt(left_motor_encoder), rotation, RISING);
}

void loop() {
}

int last_millis = 0;

void rotation() {
  int current = millis();
  int diff_time = current - last_millis;
  float mps = 0.5 * 3.1415 / diff_time;
  Serial.println(mps);
  last_millis = current;


}