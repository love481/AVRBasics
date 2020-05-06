/*
 * externalinterrupt.cpp
 *
 * Created: 27/03/2020 16:18:28
 * Author : Acer
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned int count=0;
int main(void)
{  DDRA|=(1<<PINA0);
	DDRD&=~(1<<PIND2);
	PORTD|=(1<<PIND2);
	GICR|=(1<<INT0);
    MCUCR=0x03;
	sei();
    while (1) 
    { if(count>3)
		{PORTA^=(1<<PINA0);
			count=0;}
		}
}
ISR(INT0_vect)
{
	count++;
	
}
