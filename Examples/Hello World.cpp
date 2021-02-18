#include <avr/io.h>
#include <util/delay.h>
#include <DevLCD.h>

int main()
{
  DDRD = 0xF0;
  DDRB = 0x03;

  initLCD();

  while(1)
  {
    setCursorLCD(1,1);
    lcdPrintText("Hello World!");
  }
}