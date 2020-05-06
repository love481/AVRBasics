/*
 * fastpwmtimer0.cpp
 *
 * Created: 28/03/2020 12:14:19
 * Author : Acer
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile uint8_t dutycycle=50;
volatile uint8_t analogV=200;
void set_dutycycle(uint8_t per)
{ 
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);//set fast pwm mode and compare match output mode
	while(1)
	{OCR0=(per*255)/100;}	
}
void analogread(uint8_t An)
{   
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);//set fast pwm mode and compare match output mode
	while(1){
	OCR0=An;
	}
	}
void interrupt_init(uint8_t pwm)
{TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
  TIMSK|=(1<<TOIE0);	
   OCR0=(pwm*255)/100;
	sei();
}
void timerflag(uint8_t pwmvalue)
{
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
	  OCR0=(pwmvalue*255)/100;
	  while(1)
	  {  while((TIFR&0x01)==0);//wait until timer overflow occurs and resets TCNT0
		    OCR0=(pwmvalue*255)/100;
		  TIFR|=0x01;		    //clear timer overflow flag
	  }
}
int main(void)
{  
	DDRB|=(1<<PB3);
	timerflag(dutycycle);
    while (1) 
    { 
    }
}
ISR(TIMER0_OVF_vect)///interrupt service routine
{
	 OCR0=(dutycycle*255)/100;
}



