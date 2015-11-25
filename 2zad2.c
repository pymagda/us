/*
 * lab_2.c
 *
 * Created: 25.11.2015 00:56:05
 *  Author: magdalenapeksa
 */ 


#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>


void cfg()
{
	DDRA = 0xff;
	DDRD = 0x00;
	PORTA = 0xFF;
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
	DDRB = 0x08;
	OCR0 = 0x7F;
}

int main(void)
{

	sei();
	cfg();
	
	while(1)
	{
		PORTA|=0x03;
		if(~PIND&0x01)
		{
			OCR0+=1;	
			PORTA &= 0xFE;
		}
		if(~PIND&0x02)
		{
			OCR0-=1;
			PORTA &= 0xFD;
		}
		
		_delay_ms(1);
	}
}




