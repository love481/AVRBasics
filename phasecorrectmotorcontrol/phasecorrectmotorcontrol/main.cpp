/*
 * phasecorrectmotorcontrol.cpp
 *
 * Created: 28/03/2020 16:07:32
 * Author : Love
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t frequency=8000;
unsigned int Pwm=20;
volatile uint16_t comparevalue;
void fastpwm1()
{int pre_scale=1;
	TCCR1A|=(1<<COM1A1)|(0<<WGM10)|(1<<WGM11);
	TCCR1B|=(1<<WGM13)|(1<<CS10)|(1<<WGM12);
	ICR1=(F_CPU/(2*pre_scale*frequency));
	comparevalue=ICR1;
	TIMSK|=(1<<TOIE1);
	sei();
	
}
void phasecorrectpwm1()
{
	int pre_scale=1;
	TCCR1A|=(1<<COM1A1);
	TCCR1B|=(1<<WGM13)|(1<<CS10);
	ICR1=(F_CPU/(2*pre_scale*frequency));
	comparevalue=ICR1;
	while(1)
	{  do
		{
		OCR1A=(Pwm*comparevalue)/100;
		TIFR|=1<<OCF1A;}while((TIFR&(1<<OCF1A))==0);
	}
}
int main(void)
{  DDRD|=(1<<PIND5);
	phasecorrectpwm1();
    while (1) 
    { 	
		
    }
}
ISR(TIMER1_OVF_vect)
{
	
OCR1A=(Pwm*comparevalue)/100;
	
	
}

