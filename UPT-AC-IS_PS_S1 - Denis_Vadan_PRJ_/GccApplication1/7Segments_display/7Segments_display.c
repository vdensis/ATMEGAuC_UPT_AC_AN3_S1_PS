/*
* _7Segments_display.c
*
* Created: 05.01.2017 18:11:20
*  Author: Denis Vadan
*/

#include <avr/io.h>
#include "7Segments_display.h"
#include "../GeneralDefines.h"



/*F******************************************************************************************
** NAME:	SevenSegments_display_init
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function initialize the pins for 7 segments display and Show the number on display from start.
**
** RETURN :  -
**
** NOTES : Output Pins: 2,3,4,5,6,7 from PORTD
**						0,5 from PORTB
**
**F*****************************************************************************************/

_EXT void SevenSegments_display_init(void)
{
	//Set Output Pins[2-7 from PORTD, and 0,5 from PORTB] for display led
	DDRD |= (SET(3) | SET(4) | SET(5) | SET(6) | SET(7));
	DDRB |= (SET(5) | SET(0));

	//Show the number from start
	ShowAndIncrement_7SegmentDisplay();
}


/*F******************************************************************************************
** NAME:	ShowAndIncrement_7SegmentDisplay
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function increment and show the number on 7 segments display.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT void ShowAndIncrement_7SegmentDisplay(void)
{
	if(EEPROM_read(0x04) > 9)	//if memory is corrupted
	{
		EEPROM_write(0x04,0);	//reset the counter
	}
	
	switch(EEPROM_read(0x04))
	{
		
		case 0:
		{
			PORTD |= (SET(3) | SET(4) | SET(5) | SET(6) | SET(7));
			PORTB |= SET(5);
			PORTB &= 0xFE;	//reset bit 0 from PORTB
			EEPROM_write(0x04,0);
		}break;
		
		case 1:
		{
			PORTD |= (SET(3) | SET(4));
			PORTD &= 0x1F;	//clear f,e,d led
			PORTB &= 0xDE;	//reset bit 0 and 5 from PORTB
			EEPROM_write(0x04,1);
		}break;
		
		case 2:
		{
			PORTD = ( SET(3) | SET(5) | SET(6));
			PORTD &= 0x6F;	//clear f,c led
			PORTB |= (SET(5) | SET(0));	//set bit 0 and 5 from PORTB
			EEPROM_write(0x04,2);
		}break;
		
		case 3:
		{
			PORTD = ( SET(3) | SET(4) | SET(5));
			PORTD &= 0x3F;	//clear f,e
			PORTB |= (SET(0) | SET(5));
			EEPROM_write(0x04,3);
		}break;
		
		case 4:
		{
			PORTD = ( SET(3) | SET(4) | SET(7));
			PORTD &= 0x9F;	//clear e,d
			PORTB |= 0x01;
			PORTB &= 0xDF;	//clear a
			
			EEPROM_write(0x04,4);
		}break;
		
		case 5:
		{
			PORTD = ( SET(4) | SET(5) | SET(7));
			PORTD &= 0xB7;	//clear b,e
			PORTB |= (SET(0) | SET(5));
			EEPROM_write(0x04,5);
		}break;
		
		case 6:
		{
			PORTD = ( SET(4) | SET(5) | SET(6) | SET(7));
			PORTD &= 0xF7;	//clear b
			PORTB |= (SET(0) | SET(5));
			EEPROM_write(0x04,6);
		}break;
		
		case 7:
		{
			PORTD |= ( SET(3) | SET(4));
			PORTD &= 0x1F;		//Clear d,e,f
			PORTB |= SET(5);	//Set a
			PORTB &= 0xFE;		//Clear a
			EEPROM_write(0x04,7);
		}break;
		
		case 8:
		{
			PORTD = ( SET(4) | SET(5) | SET(6) | SET(7) | SET(3));
			PORTB |= (SET(0) | SET(5));
			EEPROM_write(0x04,8);
		}break;
		
		case 9:
		{
			PORTD |= ( SET(3) | SET(4) | SET(5) | SET(7) ) ;
			PORTD &= 0xBF;		//clear e
			PORTB |= (SET(5) | SET(0));
			EEPROM_write(0x04,9);
		}break;
	}
}


/*F******************************************************************************************
** NAME:	EEPROM_write
**
** PARAMETERS: uiAddress - address for the variable
**				  ucData - value of data to be write
**
** DESCRIPTION : This function write data in EEPROM memory to a specified address.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}


/*F******************************************************************************************
** NAME:	EEPROM_read
**
** PARAMETERS: uiAddress - address for the variable
**				  ucData - value of data to be write
**
** DESCRIPTION : This function read data from EEPROM memory from a specified address.
**
** RETURN : EEDR - data from Data Register
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}
