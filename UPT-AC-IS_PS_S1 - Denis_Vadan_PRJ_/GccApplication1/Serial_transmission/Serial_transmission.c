/*
* Serial_transmission.c
*
* Created: 09.01.2017 10:24:41
*  Author: Denis Vadan
*/

#include <avr/io.h>
#include <string.h>
#include "../GeneralDefines.h"
#include "Serial_transmission.h"


/*F******************************************************************************************
** NAME:	Serial_transmission_init
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function init the serial communication and LED pin as output.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT void Serial_transmission_init(void)
{
	DDRB |= SET(3);	//set pin11 [PORTB3] as output for white LED
	
	//set Baud Rate 9600
	UBRR0H = 0;
	UBRR0L = 103; 
	
	// 8-bit data
	UCSR0C |= SET(UCSZ01) | SET(UCSZ00);				
	// Enable RX and TX
	UCSR0B |= SET(RXCIE0) | SET(RXEN0) | SET(TXEN0);	
}


/*F******************************************************************************************
** NAME:	Serial_transmission_USART_Transmit
**
** PARAMETERS: ub_data - character to be transmitted on USART
**
** DESCRIPTION : This function send to USART a character.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT void Serial_transmission_USART_Transmit( unsigned char ub_data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & SET(UDRE0)) );
	
	/* Put data into buffer, sends the data */
	UDR0 = ub_data;
}


/*F******************************************************************************************
** NAME:	Send_Helo
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function send to Serial communication words "hello world!"
**
** RETURN :  -
**
** NOTES :		unused function in project.
**
**
**F*****************************************************************************************/

_EXT void Send_Helo(void)
{
	int i = 0;
	unsigned char ub_Send[] = "hello world\n";
	
	
	for(i = 0; i < strlen(ub_Send); i++)
	{
		Serial_transmission_USART_Transmit(ub_Send[i]);
	}
}


/*F******************************************************************************************
** NAME:	Serial_transmission_UsartWrite
**
** PARAMETERS: data - pointer to a buffer(who wants to be sent on serial) 
**			   length - buffer length
**
** DESCRIPTION : This function send a word to serial communication from a buffer, by specified length.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT void Serial_transmission_UsartWrite(char *data, unsigned char length)
{
	unsigned char i = 0;
	while (length > 0)
	{
		// Wait for buffers to be free
		if (UCSR0A & SET(UDRE0))
		
		{
			UDR0 = data[i++];
			length--;
		}

	}
	
	// Wait for transmission to be ready
	while (!(UCSR0A & (1<<TXC0)));
}