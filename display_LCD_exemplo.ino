#include<LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // criando objeto
void setup()
{
 lcd.begin(16, 2); // iniciando matriz disponível para utilização
}

void loop()
{
  lcd.setCursor(4,0); // definindo coluna 5 na linha 1
  lcd.print("Teste do");
  lcd.setCursor(2,1); // definindo coluna 3 na linha 2
  lcd.print("display LCD!");
}
