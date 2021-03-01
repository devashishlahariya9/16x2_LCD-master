#include <avr/io.h>
#include <util/delay.h>
#include <DevLCD.h>

LCD lcd;

int main()
{
  DDRD = 0xF0;
  DDRB = 0x03;

  lcd.init();

  while(1)
  {
    lcd.setCursor(0,0);
    lcd.printText("Hello World!");
  }
}