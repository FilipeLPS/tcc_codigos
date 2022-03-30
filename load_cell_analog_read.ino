#define loadcell A0
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int sensorValue = analogRead(loadcell);
  Serial.print("Valor lido: ");
  Serial.println(sensorValue);
  delay(2000);
}
