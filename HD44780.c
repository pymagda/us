/*
 * HD44780.c
 *
 * Created: 16.12.2015 16:26:02
 *  Author: magdalenapeksa
 */ 
#include "HD44780.h"
#define E 1
#define S_DATA 4

// PORTA - R/S,E,X,X,D4,D5,D6,D7


void WriteNibble(unsigned char nibbleToWrite)
{
	PORTA |= 1<<E;
	PORTA &= 0x0F;
	PORTA |= nibbleToWrite<<S_DATA;
	PORTA &= ~(1<<E);
}


void WriteByte(unsigned char dataToWrite)
{
	WriteNibble(dataToWrite>>S_DATA);
	WriteNibble(dataToWrite);
	
}


void LCD_Command(unsigned char x)
{
	PORTA &= 0xFE;
	WriteByte(x);
};

void LCD_Text(char *x)
{
	PORTA |= 0x01;
	
	while(*x)
	{
		WriteByte(*x++);
		_delay_us(50);
	}
	
};
void LCD_GoToXY(unsigned char x, unsigned char z)
{
	LCD_Home();
	LCD_Command((z*0x40+x) | (0x80));
};

void LCD_Clear(void)
{
	LCD_Command(HD44780_CLEAR);
	_delay_ms(2);
};

void LCD_Home(void)
{
	LCD_Command(HD44780_HOME);
	_delay_ms(2);
};

void LCD_Off(void)
{
	LCD_Command(HD44780_DISPLAY_ONOFF);
	_delay_ms(2);
};

void LCD_Initalize(void)
{
	_delay_ms(50);
	int i;
	for(i = 0 ; i < 3 ; i++)
	{
		WriteNibble(0x03);
		_delay_ms(5);
	}
	LCD_Home();
	LCD_Command(0x2F);
	LCD_Off();
	LCD_Clear();
	
	LCD_Command(0x06);
	_delay_ms(5);
	LCD_Command(0x0F);
	
	LCD_GoToXY(0,0);
	_delay_ms(1);
	char* x = "test";
	LCD_Text(x);
};

