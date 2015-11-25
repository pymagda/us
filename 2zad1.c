/*
 * przerwania.c
 *
 * Created: 2015-11-18 16:24:27
 *  Author: trzepka
 */

//#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

int value = 0x00;

ISR(INT0_vect)
{
	count();
}

void cfg()
{
	DDRA = 0xff;
	DDRD = 0x00;
	//DDRB = 0x00;
	//PORTD = 0x00;
	PORTA = 0xFF;
	GICR = 1<<INT0;
	MCUCR = 1<<ISC01 | 1<<ISC00;
}

int main(void)
{
	//DDRA = 0xff;
	//DDRB = 0x00;
	//PORTA = 0xFF;
	cfg();
	sei();
	while(1)
	{

		blink();
	}
}

void blink()
{
	PORTA |= 0x80;
	_delay_ms(100);
	PORTA &= 0x7F;
	_delay_ms(100);
}
void count()
{
	value++;
	value%=128;
	PORTA|=0x7F;
	PORTA &= (0x80 | ~value);
}

