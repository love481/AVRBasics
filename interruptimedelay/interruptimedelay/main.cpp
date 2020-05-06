/*
 * interruptimedelay.cpp
 *
 * Created: 27/03/2020 12:31:34
 * Author : love
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
void interrupt_initTIMER1(uint16_t T1)
{   TCNT1=64560;
	TCCR1B=(1<<CS10)|(1<<CS12);
	TIMSK|=(1<<TOIE1);
	sei();	
}
void interrupt_initTIMER2(uint16_t T2)
{TCCR1B=(1<<CS10)|(1<<CS12)|(1<<WGM12);
	OCR1A=(((F_CPU/1024)*T2)/1000.0);
	TCNT1=0;
	TIMSK=(1<<OCIE1A);
	sei();	
}
int main(void)
{ DDRA|=(1<<PINA0);
	DDRA|=(1<<PINA1);
	PORTA|=(1<<PINA0);
	PORTA&=~(1<<PINA1);
	interrupt_initTIMER1(100);
    while (1) 
    {   }
}
ISR(TIMER1_COMPA_vect)
{
	
		PORTA^=(1<<PINA0);
}
ISR(TIMER1_OVF_vect)
{	
	PORTA^=(1<<PINA1);
	TCNT1=64560;
}

