#include <Keypad.h>

const byte rows = 4; // quatro linhas
const byte cols = 4; // quatro colunas
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};
// criando objeto teclado
Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols); 

void setup() { Serial.begin(9600); }

void loop() {
  char tecla = teclado.getKey(); // método para obter a tecla pressionada

  if (tecla){
    Serial.print("Tecla pressionada: ");
    Serial.println(tecla);
  }}
