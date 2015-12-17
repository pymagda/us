/*
 * lab5.c
 *
 * Created: 16.12.2015 16:24:33
 *  Author: magdalenapeksa
 */ 




#include <avr/io.h>
#include "HD44780.h"

int main(void)
{
	DDRA = 0xFF;
	LCD_Initalize();
	
	while(1)
	{
		//TODO:: Please write your application code
	}
}
