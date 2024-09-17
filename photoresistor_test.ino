int lux = 0;


void setup() {
  Serial.begin(9600);

}

void loop() {
  lux = analogRead(A0);
  Serial.println(lux);

  delay(1000);

}
