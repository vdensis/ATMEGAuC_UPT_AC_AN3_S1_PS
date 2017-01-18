/*
 * ADC_temp.h
 *
 * Created: 14.01.2017 11:03:04
 *  Author: Denis Vadan
 */ 
#define TEMP_SET 30


extern void ADC_temp_init(void);


extern unsigned short int ADC_temp_Read(unsigned char ub_ch);


extern unsigned char ADC_temp_CovertToCelsius(unsigned short int adc_read);


extern void ADC_temp_LED_ON_OFF(unsigned char lu8_temp);