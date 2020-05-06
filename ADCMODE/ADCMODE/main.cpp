/*
 * ADCMODE.cpp
 *
 * Created: 29/03/2020 14:48:43
 * Author : Love
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define sbi(x,y) x|=(1<<y) // set the macro
volatile  uint8_t analogvalue;
void analogToPWM8Bit()
{
	
	sei();
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00); // initialization of fast mode pwm  for 8 bit
	ADMUX|=(1<<REFS0)|(1<<ADLAR);   // choose the ADC channel ,bit and reference volatage
	ADCSRA|=(1<<ADIE)|(1<<ADEN)|(1<<ADPS0)|(0<<ADPS1)|(0<<ADPS2); // adc interrupt enable and set the prescalar
	ADCSRA|=(1<<ADSC); ///start the ADC first conversion
	while (1)
	{ OCR0=analogvalue; //Note: for  the 10 bit ADC,we should either initialize 10 bit PWM mode or choose the ICR1 value for 16 bit PWM Mode to 1024 
	}
	
}
int main(void)
{ sbi(DDRB,PB3);
	sbi(PORTB,PB3);
	printf("hello");
	
}

ISR(ADC_vect)
{    
	analogvalue=ADCH;   // 8 bit adc value
	//analogvalue=ADCH<<2|ADCL>>2; //10 bit ADC
	ADCSRA|=(1<<ADSC); // do again and again the adc conversion
	
}