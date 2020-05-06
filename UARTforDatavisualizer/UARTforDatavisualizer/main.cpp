/*
 * UARTforDatavisualizer.cpp
 *
 * Created: 30/03/2020 18:41:50
 * Author : Love
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#define baud 9600
#define sbr ((F_CPU/16/baud)-1)

unsigned char a;
unsigned char b,c;
//Function for character receiving on Rx pin

unsigned char uart_receive ()
{
	while((UCSRA&(1<<RXC)) == 0);
	// wait untill 8-bit of a character receive
	return UDR;
}

//Functions transmit data

void uart_transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));
	// wait for the register to free from data
	UDR = data;
	// load data in the register
}

//Main function

int main(void)
{
  DDRA|=(1<<PINA0);
	//UART initialization
	UBRRH=(uint8_t)(sbr>>8);
	UBRRL=(uint8_t)sbr; // To set the Buad rate to 9600.. get value through above formula
	UCSRB=(1<<RXCIE) | (1<<RXEN) | (1<<TXEN);
	UCSRC=(1<<UCSZ1) | (1<<UCSZ0)|(1<<USBS) ;

	while(1){
		a=uart_receive(); // MC will wait here infinitly to get a 8-bit character
       if(a=='1')
	   {  PORTA^=(1<<PINA0);
		   _delay_ms(1000);
		   
	   }

		
	}
}
