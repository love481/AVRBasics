/*
 * delayfunction.cpp
 *
 * Created: 27/03/2020 11:27:05
 * Author : love
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <math.h>
void delay_ms1(uint16_t T1)
{ TCNT1=65535-(((F_CPU/1024)*T1)/1000.0);//using formula to calulate the requires TCNT1
	TCCR1B=(1<<CS10)|(1<<CS12);
	while((TIFR&(1<<TOV1))==0);//wait until overflow occurs at max 65535
	TIFR|=(1<<TOV1);
}
void delay_ms2(uint16_t T2)
{   TCNT1=0;
	OCR1A=(((F_CPU/1024)*T2)/1000.0);//using formula to calulate the requires OCR1A
	TCCR1B=(1<<CS10)|(1<<CS12);
	while((TIFR&(1<<OCF1A))==0); //wait until output compare overflow  occurs
	TIFR|=(1<<OCF1A);
	
}
int main(void)
{ DDRA|=(1<<PINA0);
 
    while (1) 
    { 
		PORTA^=(1<<PINA0);
	    delay_ms2(1000);
    }
}

