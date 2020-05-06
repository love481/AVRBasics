/*
 * TIMERexercise.cpp
 *
 * Created: 26/03/2020 15:31:18
 * Author : Love
 */ 
#define F_CPU 1000000UL
#include<avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{    DDRA|=(1<<PINA0);
	OCR1A=975;
	   TCNT1=0;
	TCCR1B=(1<<CS10)|(1<<CS12); //set the precsalar pf 1024
	while(1)
	{while((TIFR & (1<<OCF1A))==0);// wait until output compare overflow occurs
		PORTA^=(1<<PINA0);
		  TCNT1=0;
		  TIFR|=(1<<OCF1A);  //clear output compare overflow flag
		  }

   
  
}

