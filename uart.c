/*
 * uart.c
 *
 *  Created on: 03-07-2015
 *      Author: someone
 */


#include "uart.h"
#include <avr/io.h>

//#define F_CPU 20000000
#define BAUD 19200
#define MYUBRR F_CPU/16/BAUD-1

uint8_t DebugCompilation	=		1;

void USART_Init(void)
{
	if(DebugCompilation)
	{
		// Set baud rate
		UBRR0H = (MYUBRR>>8);
		UBRR0L = MYUBRR;

		UCSR0C = (3<<UCSZ00); // Asynchronous 8 N 1

		//Enable The receiver and transmitter
		UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	}

}

void USART_Write_Number(long number)
{
	uint8_t i;

	if(DebugCompilation)
	{
		for(i=0; i<4; i++)
		{
			USART_Write((number>>(i*8)) & 0xff);
		}
	}
}

void USART_Write(char data)
{
	if(DebugCompilation)
	{
		// Wait for empty transmit buffer
	    while ( !(UCSR0A & (_BV(UDRE0))) );
	    // Start transmission
	    UDR0 = data;
	}
}

void USART_String(const char* str)
{
	if(DebugCompilation)
	{
		while(*str)
		{
			USART_Write(*str++);
		}
	}
}
