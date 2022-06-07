/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
   Settling time (number of samples) and data filtering can be adjusted in the config.h file
   For calibration and storing the calibration value in eeprom, see example file "Calibration.ino"

   The update() function checks for new data and starts the next conversion. In order to acheive maximum effective
   sample rate, update() should be called at least as often as the HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS.
   If you have other time consuming code running (i.e. a graphical LCD), consider calling update() from an interrupt routine,
   see example file "Read_1x_load_cell_interrupt_driven.ino".

   This is an example sketch on how to use this library
*/

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);

//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;
float limite_inf = 11.0;
float limite_sup = 21.0;
String cpf = "";

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(2, INPUT); // RX
  pinMode(3, OUTPUT);// TX
  pinMode(7, INPUT_PULLUP); // sensor indutivo
  delay(10);
  Serial.println();
  Serial.println("Iniciando...");

  LoadCell.begin();
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  //calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Inicio concluido");
    Serial.println("Insira a lata e digite seu CPF:");
  }
}

void loop() {
  int ind_sen = digitalRead(7);
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;
  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      if (Serial.available()) {
        cpf = Serial.readString();
        if ((i > limite_inf) && (i <= limite_sup)) {
          if (ind_sen == LOW) {
            if (cpf.length() == 11) {
              if (checkCPF(cpf)) {
                Serial.println("CPF: " + cpf);
                Serial.println("Material: Metálico");
                Serial.print("Massa: ");
                Serial.print(i);
                Serial.println(" gramas"); 
                writeString(cpf);
              }
              else {
                Serial.println("CPF INVALIDO");
              }
            } else Serial.println("CPF INVALIDO");
          }
          else {
            Serial.println("Material invalido");
          }
        }
        else {
          Serial.println("Massa invalida");
        }
        Serial.println("---");
        Serial.println("Insira a lata e digite seu CPF:");
      }
      newDataReady = 0;
      t = millis();
    }
  }
}

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

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    espSerial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass

  }
  Serial.println("1 ponto atribuido ao CPF");
}// end writeString
