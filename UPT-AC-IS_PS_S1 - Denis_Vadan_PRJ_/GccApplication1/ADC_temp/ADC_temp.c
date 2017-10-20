/*
* ADC_temp.c
*
* Created: 14.01.2017 11:02:56
*  Author: Denis Vadan
*/

#include <avr/io.h>
#include "../GeneralDefines.h"
#include "ADC_temp.h"


/*F******************************************************************************************
** NAME:	ADC_temp_init
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function init the Analog Digital Converter.
**
** RETURN :  -
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT void ADC_temp_init(void)
{
	//set PORTB[4] as output (RED LED) - PIN 12
	DDRB |= SET(4);

	//SET 128 prescaler
	//ADC reference clock = 125Khz and start ADC (ADEN = 1)
	ADCSRA |= ( SET(ADPS2) | SET(ADPS1) | SET(ADPS0) | SET(ADEN));

	//Set Reference to 5V (VCC)
	ADMUX |= SET(REFS0);
	
	ADCSRA |= SET(ADSC);			//Start conversion	
}


/*F******************************************************************************************
** NAME:	ADC_temp_Read
**
** PARAMETERS: Pin -> the tin where is connected the temperature sensor
**
** DESCRIPTION : This function read the digital voltage[0-1024] from PIN.
**
** RETURN :  ADCW - (0 -> 5V = [0 -> 1023] )
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT unsigned short int ADC_temp_Read(unsigned char Pin)
{
	ADMUX |= Pin;					//Set ADC Pin to be read
	ADCSRA |= SET(ADSC);			//Start conversion

	while(ADCSRA & SET(ADSC));		//Wait until the conversion is done
	ADCSRA |= SET(ADIF);			//conversion complete (Clear ADIF by writing one to it)

	return ADCW;					//return the ADC(Word)
}


/*F******************************************************************************************
** NAME:	ADC_temp_CovertToCelsius
**
** PARAMETERS: NONE
**
** DESCRIPTION : This function returns the temperature after conversion in Celsius degree.
**
** RETURN :  (5 * adc_read * 100) / 1024  -> temperature in Celsius
**
** NOTES :
**
**
**F*****************************************************************************************/

_EXT unsigned char ADC_temp_CovertToCelsius(unsigned short int adc_read)
{
	return ((5 * adc_read * 100) / 1024);
}


/*F******************************************************************************************
** NAME:	ADC_temp_LED_ON_OFF
**
** PARAMETERS: lu8_temp - temperature in Celsius degree
**
** DESCRIPTION : This function turn on/off the led if temperature is higher/lower then TEMP_SET.
**
** RETURN :  -
**
** NOTES :		TEMP_SET is defined in ADC_temp.h
**
**
**F*****************************************************************************************/

_EXT void ADC_temp_LED_ON_OFF(unsigned char lu8_temp)
{
	if(lu8_temp <= (TEMP_SET - 1))
	{
		PORTB &= 0xEF;		//LED OFF
	}
	else
	{
		if(lu8_temp >= (TEMP_SET + 1))
		{
			PORTB |= SET(4);	//LED ON
		}
	}
}