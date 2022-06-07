#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);

String cpf = "";

void setup() {
  // Set the baud rate for the SerialSoftware object
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.println("Inicio concluido, digite o CPF:");

}

void loop() {
  if (Serial.available()) {
    cpf = Serial.readString();
    Serial.println(cpf);
    if (cpf.length() == 11) {
      delay(500);
      if (checkCPF(cpf)) {
        Serial.println("CPF VALIDO");
        writeString(cpf);
      } else {
        Serial.println("CPF INVALIDO");
      }
      delay(3000);
      cpf = "";
    }
  }
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    espSerial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass

  }
  Serial.println("CPF enviado");
}// end writeString

bool checkCPF(String cpf) {
  if (cpf.length() != 11) return false;
  int n1 = 0;
  int n2 = 0;
  bool equalNum = true;
  for (int i = 1; i <= 9; i++) {
    n1 += cpf.substring(i - 1, i).toInt() * (11 - i) ;
    n2 += cpf.substring(i - 1, i).toInt() * (12 - i) ;
    if (cpf.substring(i - 1, i).toInt() != cpf.substring(i, i + 1).toInt()) equalNum = false;
  }
  if (equalNum) return false;
  n1 = 11 - (n1 % 11);
  if (n1 > 9) n1 = 0;
  n2 += n1 * 2;
  n2 = 11 - (n2 % 11);
  if (n2 > 9) n2 = 0;
  if (cpf != cpf.substring(0, 9) + String(n1) + String(n2)) return false;
  return true;
}
