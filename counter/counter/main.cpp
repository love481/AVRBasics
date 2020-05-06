/*
 * counter.cpp
 *
 * Created: 27/03/2020 15:59:49
 * Author : love
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>

int main(void)
{   DDRA|=(1<<PINA0);
	DDRB&=~(1<<PINB0);//press switch 5 times to on led and counter increses ccoreespondingly;
	PORTB|=(1<<PINB0);
	TCNT0=0;
	TCCR0=0x06;
    /* Replace with your application code */
    while (1) 
    { if(TCNT0>5)
		{PORTA^=(1<<PINA0);
			TCNT0=0;
    }
}
}

