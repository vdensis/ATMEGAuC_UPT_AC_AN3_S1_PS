/*
 * button.c
 *
 * Created: 06.01.2017 11:41:17
 *  Author: Denis Vadan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../GeneralDefines.h"

void button_init(void)
{

	    DDRD &= ~SET(2);						// Clear the PD2 pin
	    // PD2 (PCINT0 pin) is now an input

	   // PORTD |= SET(PORTD2);					// turn On the Pull-up
	    // PD2 is now an input with pull-up enabled

	    EICRA |= ( SET(ISC01) | SET(ISC00));    // set INT0 to trigger on the falling edge of INT0
	    EIMSK |= SET(INT0);						// Turns on INT0

	//    sei();								// turn on interrupts
	
	}