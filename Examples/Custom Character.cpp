#include <avr/io.h>
#include <util/delay.h>
#include <DevLCD.h>

LCD lcd;

int main()
{
  DDRD = 0xF0;
  DDRB = 0x03;

  lcd.init();  //initialize the LCD

  while(1)
  {
    lcd.drawBitmap(0x40,0,0,0x0E,0xFF,0x11,0x11,0xFF,0xFF,0xFF,0x00,0);  //drawBitmap(CG-RAM Address,x,y,8-bits,to print the character stored in corresponding address)
  }
}