/*
* Timer2_Blink_1s.c
*
* Created: 25.11.2016 23:48:49
*  Author: Denis Vadan
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../GeneralDefines.h"
#include "Timer2_Blink_1s.h"


/*F******************************************************************************************
** NAME:	Timer2_Blink_1s_Timer_init
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function initialize the timer 2 for LED blinking on every 1/61 second,
**				  using the 1024 prescaler.
**
** RETURN :  -
**
** NOTES :  - This function most to be called in main to init the timer and PORT
**			- For 1 second, the interrupt routine most to be called for 61 time
**			- The LED is connected to Digital PIN 10 [BIT 2 from PORTB]
**
**F*****************************************************************************************/

_EXT void Timer2_Blink_1s_Timer_init(void)
{
	//16 000 000 / 1024 = 15625
	//15625 / 255 = 61 => we need 61 compare interrupts for 1 second
	OCR2A = 255;		
	
	DDRB |= SET(2);		//set the BIT 2 from PORTB as output

	TCCR2A |= SET(WGM21);
	// Set to CTC Mode

	TIMSK2 |= SET(OCIE2A);
	//Set interrupt on compare match

	TCCR2B |= (SET(CS21) | SET(CS20) | SET(CS22));
	// set prescaler to 1024

	sei();
	// enable interrupts
}