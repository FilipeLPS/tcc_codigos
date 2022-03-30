void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ind_sen = digitalRead(10);
  if (ind_sen == HIGH){
    Serial.println("Sem deteccao de metal");
    }
  else{Serial.println("Deteccao de metal");}
  delay(1000);
}
