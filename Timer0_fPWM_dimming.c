/*
* Timer0_fPWM_dimming.c
*
* Created: 26.11.2016 10:31:20
*  Author: Denis Vadan
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include "../GeneralDefines.h"
#include "Timer0_fPWM_dimming.h"


/*F******************************************************************************************
** NAME:	Timer0_fPWM_dimming_timer
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function init the timer for dimming effect.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_LOC void Timer0_fPWM_dimming_timer (void)
{
	//Set-up the prescaler - 1024
	TCCR0B = (SET(CS00) | SET(CS02));
	
	// timer interrupt enabled
	TIMSK0 |= SET(TOIE0);
	
	//TOV0 set timer overflow
	TIFR0 |= SET(TOV0);
	
	//Timer init
	TCNT0 = 0;
}


/*F******************************************************************************************
** NAME:	Timer0_fPWM_dimming_pwm
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function config the timer in fast PWM mode.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_LOC void Timer0_fPWM_dimming_pwm (void)
{
	TCCR1A = SET(WGM10) | SET(COM1A1);
	TCCR1B = SET(CS10) | SET(WGM12);   //Config Pwm
	
	//Init bit 1 from port B as output
	DDRB |= SET(1);
	
	sei(); //enable global interrupts
	// PORTB &=  0xFB;
}



/*F******************************************************************************************
** NAME:	Timer0_fPWM_dimming_init
**
** PARAMETERS: NONE
**																			         			         _       _
** DESCRIPTION : This function initialize the timer 0 and PWM LED for dimming in the following way:  _ /   \ _ /   \ _
**																	         					    |1|2|3|4|5|6|7|8|9| sec.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/
_EXT void Timer0_fPWM_dimming_init(void)
{
	Timer0_fPWM_dimming_timer();
	Timer0_fPWM_dimming_pwm();
}
