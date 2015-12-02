/*
 * lab_3.c
 *
 * Created: 25.11.2015 15:08:20
 *  Author: magdalenapeksa
 */ 

/*
Wyklad:
1. Wyswietlacz siedmiosegmentowy ma osiem segmentow, dochodzi kropka.
	a
f		b
	g
e		c
	d

Uwaga: diody swieca sterowane zerem na wszystkich plytkach
2. Zaswiecenie jedynki:
PORTA = 0011111001 (mozna stosowac negacje)

3. Podlaczenie: linie segemntow zwiera sie ze soba i wyprowadza do mikrokontorela.
Z kadnego segmentu wychodzi jedna linia wlacz/wylacz, podlaczamy je np. do PORTB.

4. Obsluga: timer zrzuca przerwanie, przelaczamy sie na kolejny segment i wyswietlamy odpowiednia cyfre.

5. _delay_ms(100) F_CPU while(100){for(i=0;i<F_CPU;i++) NOP} 16MgH
	
	
*/
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <math.h>

uint8_t tab[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8_t displays[4] = {0xFE, 0xFD, 0xFB, 0xF7};
uint16_t time = 0;
uint16_t counter = 0;
uint8_t display_nr = 0;

ISR(TIMER0_COMP_vect)
{
	
	PORTB = 0xFF;
	switch (display_nr)
	{
	case 0:
		PORTA = tab[time % 10];
		break;
	case 1:
		PORTA = tab[(time/10) % 10];
		break;
	case 2:
		PORTA = tab[(time/100) % 10];
		break;
	case 3:
		PORTA = tab[(time/1000) % 10];
		break;
	}
	
	PORTB = displays[display_nr];
	
	display_nr = (display_nr+1) % 4;
	
	if(++counter >= 1000)
	{
		++time;
		counter = 0;
	}
}
void cfg()
{
	OCR0 = 125;
	TCCR0 = (1 << WGM21) | (1 << CS22); // ctc, prescaler 64
	TIMSK |= (1 << OCIE0);
	DDRA = 0xFF;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0xFF;
}

int main(void)
{
	sei();
	cfg();
	
    while(1)
    {
		
    }
}

