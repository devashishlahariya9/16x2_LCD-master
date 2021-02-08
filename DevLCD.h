#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

/*
    CONNECTIONS:
    LCD => MCU

    EN  => PB0
    RS  => PB1
    R/W => GND
    D7  => PD7
    D6  => PD6
    D5  => PD5
    D4  => PD4
*/

int bitmap_addr;

void command(unsigned char cmd)
{
  _delay_ms(1);

  PORTD = (PORTD & 0x0F) | (cmd & 0xF0);  //Higher Nibble

  PORTB = 0x01;  //Enable pulse
  _delay_ms(1);
  PORTB = 0x00;

  PORTD = (PORTD & 0x0F) | ((cmd & 0x0F) << 4);  //Lower Nibble

  PORTB = 0x01;  //Enable pulse
  _delay_ms(1);
  PORTB = 0x00;
}

void datawrt(unsigned char data)
{
  _delay_ms(1);

  PORTD = (PORTD & 0x0F) | (data & 0xF0);  //Higher Nibble

  PORTB = 0x03;  //Enable pulse
  _delay_ms(1);
  PORTB = 0x02;

  PORTD = (PORTD & 0x0F) | ((data & 0x0F) << 4);  //Lower Nibble

  PORTB = 0x03;  //Enable pulse
  _delay_ms(1);
  PORTB = 0x02;
}

void setCursorLCD(int locx, int locy)
{
  PORTB = 0x00;  //Set LCD to Command Mode

  if(locx >= 0 & locy == 0)   //To set cursor in 1st Line
  {
    command(0x80);
    locx = locx-1;

    for(int x=0; x<=locx; x++)  //To set cursor in X-Axis
    {
      command(0x14);
    }
  }
  
  if(locx >= 0 & locy == 1)  //To set cursor on 2nd Line
  {
    command(0xC0);
    locx = locx-1;

    for(int x=0; x<=locx; x++)  //To set cursor in X-Axis
    {
      command(0x14);
    }
  }
}

void lcdPrintNumber(int number)
{
  char numStr[100];
  itoa(number,numStr,10);

  lcdPrintText(numStr);
}

void lcdPrintText(char *ptr)
{
  for ( ; *ptr != 0; ptr++)
  {
    datawrt(*ptr);
  }
}

void clearLCD()
{
  command(0x01);
}

void drawBitmap(char addr, int locationx, int locationy, char b0, char b1, char b2, char b3, char b4, char b5, char b6, char b7, char bitmap_addr)
{
  PORTB = 0x00;   //Set LCD to Command Mode
  command(addr);  //Set Pointer to CGRAM
  PORTB = 0x02;   //Set LCD to Data Mode
  datawrt(b0);    //Write Hex value to this Address
  datawrt(b1);
  datawrt(b2);
  datawrt(b3);
  datawrt(b4);
  datawrt(b5);
  datawrt(b6);
  datawrt(b7);

  PORTB = 0x00;
  setCursorLCD(locationx,locationy);  //To set cursor for bitmap on LCD
  PORTB = 0x02;
  datawrt(bitmap_addr);  //To display the Bitmap
}

void initLCD()
{
  _delay_ms(50);  //Give some time to LCD For Booting up
  command(0x28);  //Set to 4-Bit mode
  command(0x02);  //Return Home
  command(0x0C);  //Display on, cursor blinking(0E) (0C for cursor off)
  command(0x01);  //Clear display
  _delay_us(50);  //Give some time after clearing LCD
}