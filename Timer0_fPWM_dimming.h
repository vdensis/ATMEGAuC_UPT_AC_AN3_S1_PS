/*
 * Timer0_fPWM_dimming.h
 *
 * Created: 26.11.2016 10:31:34
 *  Author: Denis Vadan
 */ 


//////////////////////////////////////////////////////////
//  Extern functions declaration
//////////////////////////////////////////////////////////
extern void Timer0_fPWM_dimming_init(void);




//////////////////////////////////////////////////////////
//  Enumeration for led dimming state
//////////////////////////////////////////////////////////
typedef enum E_LED_STATE
{
	E_LED_STATE_FADE_IN = 1,
	E_LED_STATE_STAY_HIGH,
	E_LED_STATE_FADE_OUT,
	E_LED_STATE_STAY_LOW
	
}T_E_LED_STATE;