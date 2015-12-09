/*
 * klawiaturka.c
 *
 * Created: 2015-12-08 16:08:55
 *  Author: trzepka
 */
 
 
#define F_CPU 16000000UL
#define s_tasks 10
#define N_COLUMN 4
#define N_ROW 4
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
 
typedef void(*FUNC_PTR)(void);
uint8_t displays[4] = {0xFE, 0xFD, 0xFB, 0xF7};
uint8_t tab[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8_t display_nr = 0;
uint8_t row = 0x00;
uint8_t column = 0x00;
 
typedef struct
{
        uint16_t interval;
        uint16_t counter;
        uint8_t ready;
        FUNC_PTR f;
       
} task_t;
 
typedef struct
{
        task_t array[s_tasks];
        uint8_t used;
       
} task_a;
 
task_a tasks;
 
void scheduler_add_task(task_t* element) {
        if (tasks.used < s_tasks)
        {
                tasks.array[tasks.used++] = *element;
        }
}
 
void scheduler_process()
{
        int i;
        for(i = 0 ; i < tasks.used ; i++)
        {
               
                if(tasks.array[i].ready > 0)
                {
                        tasks.array[i].f();
                        tasks.array[i].ready--;
                }
               
        }
       
}
void scheduler_tick()
{
        int i;
        for(i = 0 ; i < tasks.used ; i++)
        {
                tasks.array[i].counter++;
                if(tasks.array[i].counter == tasks.array[i].interval)
                {
                        tasks.array[i].ready++;
                        tasks.array[i].counter = 0;
                }
               
        }
}
 
void init_timer()
{
        OCR0 = 10;
        TCCR0 = (1 << WGM21) | (1 << CS22);
        TIMSK |= (1 << OCIE0);
        DDRB = 0xFF;
        DDRD = 0xFF;
        PORTD = 0xFF;
        PORTB = 0xFF;
}
 
 
ISR (TIMER0_COMP_vect)
{
        scheduler_tick();
}
 
void check_button(void)
{
        // read column
        DDRA = 0xF0;
        PORTA = 0x0F;
                                 
        int i;
        for(i = 0 ; i < 100 ; i++);
        column = PINA|0xF0;
       
        // read row
        DDRA = 0x0F;
        PORTA = 0xF0;
       
        for(i = 0 ; i < 100 ; i++);
        row = (PINA>>4)|0xF0;
}
 
uint8_t log2_(uint8_t n)
{
        return log(n) / log(2);
}
 
 
void display_button(void)
{      
        uint8_t l_row = 0;
        uint8_t l_column = 0;

        if((~row | ~column) & 0xFF)
	{
                l_row = 3-log2_(~row);
                l_column = 4-log2_(~column);
        }

        uint8_t button = 4*(l_row)+l_column;
       
        PORTD = 0xFF;

        int i;
        for(i = 0 ; i < 100 ; i++);

        switch (display_nr)
        {
                case 0:
                        PORTB = tab[button%10];
                        break;
                case 1:
                        PORTB = tab[(button/10)%10];
        }
       
        PORTD = displays[display_nr];
       
        display_nr = (display_nr+1) % 2;
}
 
 
int main(void)
{
 
        task_t task1;
        task1.interval = 50;
        task1.ready = 0;
        task1.counter = 0;
        task1.f = check_button;
        scheduler_add_task(&task1);
       
        task_t task2;
        task2.interval = 25;
        task2.ready = 0;
        task2.counter = 0;
        task2.f = display_button;
        scheduler_add_task(&task2);
       
        init_timer();
 
        sei();
        while(1)
        {
                scheduler_process();
        }
 
}
