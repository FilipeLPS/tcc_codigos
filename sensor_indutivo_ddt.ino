void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  int sensorVal = digitalRead(7);
  if (sensorVal == HIGH) {
    digitalWrite(13, HIGH);
    Serial.println("Deteccao de metal");
  } else {
    digitalWrite(13, LOW);
    Serial.println("Sem deteccao de metal");
  }
  delay(250);
}
