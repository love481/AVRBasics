/*
 * hobbyServoControl.c
 *
 * Created: 04/12/2020 15:56:15
 * Author : Acer
 */ 
#define F_CPU 16000000UL
#include<stdio.h>
#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
uint16_t pulseperms=2000;
void servo_init()
{
		TCCR1A|=(1<<WGM11)|(1<<COM1A0)|(1<<COM1A1);
		TCCR1B|=(1<<CS11)|(1<<WGM12)| (1<<WGM13);
		ICR1=40000;
	
}
void servo_angle(uint16_t angle)
{
		
		// here 2000 count pulse rotates 90 degree so to rotate 1 degree we need 2000/90 pulse
		uint16_t time_ms=(pulseperms/90)*angle;
		//OCR1A=ICR1-pulseperms; //initialize the servo angle to 0 degree at 1ms
		OCR1A=ICR1-(pulseperms+time_ms);
		_delay_ms(20);
}


int main(void)
{
	DDRB|=(1<<PB5);
	servo_init();
	servo_angle(0);
	_delay_ms(1000);
	servo_angle(180);
	//_delay_ms(1000);
    while (1) 
    {
     /* OCR1A=36000;  //initialize the servo angle to 90 degree at 2ms
	  _delay_ms(1000);
	  OCR1A=34000;  //initialize the servo angle to 180 degree at 3ms
	  _delay_ms(1000);*/
	 
    }
	return 0;
}

