/*
* main.c
*
* Created: 25.11.2016 23:00:39
*  Author: Denis Vadan
*/
#define F_CPU 16000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "GeneralDefines.h"
#include "Timer2_Blick_1s/Timer2_Blink_1s.h"
#include "Timer0_fPWM_dimming/Timer0_fPWM_dimming.h"
#include "Serial_transmission/Serial_transmission.h"
#include "7Segments_display/7Segments_display.h"
#include "Button/button.h"
#include "ADC_temp/ADC_temp.h"


/*V*******************************************************************************************/
/* BEGIN GLOBAL VARIABLE DECLARATION */
/*V*******************************************************************************************/

static T_E_LED_STATE E_LedState;
volatile int St_Ct = 0;
volatile unsigned char timer_blick_ct = 0;
static unsigned char SevenSengemntCT;
unsigned char ct_button;
unsigned short int ru16_analog_temp;
unsigned char ru8_celsius_temp;

/*F******************************************************************************************
** NAME:	temperature_function
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function read the analog voltage, convert to Celsius, send the temperature to USART and
**				 turn the Red LED On/Off.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

void temperature_function(void)
{
	char lu8_buff_transmit[3];

	ru16_analog_temp = ADC_temp_Read(0);
	ru8_celsius_temp = ADC_temp_CovertToCelsius(ru16_analog_temp);

	itoa(ru8_celsius_temp,lu8_buff_transmit,10);
	Serial_transmission_UsartWrite("\nTemperatura: ",14);
	Serial_transmission_UsartWrite(lu8_buff_transmit, 3);
	
	ADC_temp_LED_ON_OFF(ru8_celsius_temp);
}


/*F******************************************************************************************
** NAME:	Reset_ButtonCounter_3sec
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function reset the button counter if button is pressed more than 3 sec.
**
**
** RETURN :  -
**
** NOTES :	ct_button most to be incremented on every one second.
**
**
**F*****************************************************************************************/

void Reset_ButtonCounter_3sec(void)
{
		if (ct_button >= 3 && ((PIND & SET(PD2))))
		{
			//Write 0 on 7Segments display
			PORTD |= (SET(3) | SET(4) | SET(5) | SET(6) | SET(7));
			PORTB |= SET(5);
			PORTB &= 0xFE;	//reset bit 0 from PORTB
			
			//write 0 on EEPROM
			EEPROM_write(0x04,0);
		}
}

/*F******************************************************************************************
** NAME:	SETUP
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function initialize all modules.
**
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

void SETUP(void)
{
	//init the timer 2 for LED blinking every 1 second
	Timer2_Blink_1s_Timer_init();
	
	
	Timer0_fPWM_dimming_init();
	
	//Init the 7 segments display
	SevenSegments_display_init();

	//Init the serial communication
	Serial_transmission_init();
	
	//Init ADC
	ADC_temp_init();

	//init the button
	button_init();
}


/*F******************************************************************************************
** NAME:	main
**
** PARAMETERS: NONE
**
** DESCRIPTION : main function.
**
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

int main()
{
	//initialize all modules
	SETUP();

	while (1)
	{
		//read and transmit temperature
		temperature_function();

		_delay_ms(1000);
	}
}

//ISR for USART Rx
ISR(USART_RX_vect)
{
	unsigned char ub_read;
	ub_read = UDR0;
	
	switch(ub_read)
	{
		case 'a':
		{
			//turn on white LED
			//set Pin 11 [PORTB_3]
			PORTB |= SET(3);
		}break;
		case 's':
		{
			//turn of white LED
			//reset Pin 11 [PORTB_3]
			PORTB &= 0xF7;
		}break;
	}
}


//ISR for short button push
ISR(INT0_vect)
{
	SevenSengemntCT = EEPROM_read(0x04);
	if(SevenSengemntCT < 9)
	{
		SevenSengemntCT++;
		
	}
	else
	{
		SevenSengemntCT = 0;
	}
	
	EEPROM_write(0x04,SevenSengemntCT);
	
	ct_button = 0;						//reset the counter

	switch(EEPROM_read(0x04))
	{
		
		case 0:
		{
			PORTD |= (SET(3) | SET(4) | SET(5) | SET(6) | SET(7));
			PORTB |= SET(5);
			PORTB &= 0xFE;	//reset bit 0 from PORTB
		}break;
		
		case 1:
		{
			PORTD |= (SET(3) | SET(4));
			PORTD &= 0x1F;	//clear f,e,d led
			PORTB &= 0xDE;	//reset bit 0 and 5 from PORTB
		}break;
		
		case 2:
		{
			PORTD = ( SET(3) | SET(5) | SET(6));
			PORTD &= 0x6F;	//clear f,c led
			PORTB |= (SET(5) | SET(0));	//set bit 0 and 5 from PORTB
		}break;
		
		case 3:
		{
			PORTD = ( SET(3) | SET(4) | SET(5));
			PORTD &= 0x3F;	//clear f,e
			PORTB |= (SET(0) | SET(5));
		}break;
		
		case 4:
		{
			PORTD = ( SET(3) | SET(4) | SET(7));
			PORTD &= 0x9F;	//clear e,d
			PORTB |= 0x01;
			PORTB &= 0xDF;	//clear a
		}break;
		
		case 5:
		{
			PORTD = ( SET(4) | SET(5) | SET(7));
			PORTD &= 0xB7;	//clear b,e
			PORTB |= (SET(1) | SET(5));
		}break;
		
		case 6:
		{
			PORTD = ( SET(4) | SET(5) | SET(6) | SET(7));
			PORTD &= 0xF7;	//clear b
			PORTB |= (SET(0) | SET(5));
		}break;
		
		case 7:
		{
			PORTD |= ( SET(3) | SET(4));
			PORTD &= 0x1F;		//Clear d,e,f
			PORTB |= SET(5);	//Set a
			PORTB &= 0xFE;		//Clear a
		}break;
		
		case 8:
		{
			PORTD = ( SET(4) | SET(5) | SET(6) | SET(7) | SET(3));
			PORTB |= (SET(0) | SET(5));
		}break;
		
		case 9:
		{
			PORTD |= ( SET(3) | SET(4) | SET(5) | SET(7) ) ;
			PORTD &= 0xBF;		//clear e
			PORTB |= (SET(5) | SET(0));
		}break;
	}
}


//ISR led Blink 1 sec - Timer 2
//Increment 7 segments display
ISR(TIMER2_COMPA_vect)
{
	timer_blick_ct++;
	
	if(timer_blick_ct == 61)
	{
		timer_blick_ct = 0;				//reset the counter
		PORTB ^= SET(2);				//toggle
		
		ct_button++;	//increment the button counter (for 3 seconds)
		
		//reset the counter if button is pressed more than 3 seconds
		Reset_ButtonCounter_3sec();

		//ShowAndIncrement_7SegmentDisplay();
	}
}

//ISR led dimming effect
ISR(TIMER0_OVF_vect)
{
	St_Ct++;
	
	switch(E_LedState)
	{
		case E_LED_STATE_FADE_IN:
		{
			// Set pwm value in OCR1A
			OCR1A = 255/60 + OCR1A;
		}break;
		
		case E_LED_STATE_STAY_HIGH:
		{
			OCR1A = 255;
		}break;
		
		case E_LED_STATE_FADE_OUT:
		{
			OCR1A = OCR1A - 255/60;
		}break;
		
		case E_LED_STATE_STAY_LOW:
		{
			OCR1A = 0;
		}break;
		
	}
	
	switch(St_Ct)
	{
		case 60:
		{
			E_LedState = E_LED_STATE_FADE_IN;
		}break;
		
		case 120:
		{
			E_LedState = E_LED_STATE_STAY_HIGH;
		}break;
		
		case 180:
		{
			E_LedState = E_LED_STATE_FADE_OUT;
		}break;
		
		case 240:
		{
			//Reset
			St_Ct = 0;
			OCR1A = 0;
			E_LedState = 0;
		}break;
	}
}

