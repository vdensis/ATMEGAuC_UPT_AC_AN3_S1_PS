/*
 * Setial_transmission.h
 *
 * Created: 09.01.2017 10:25:16
 *  Author: Denis Vadan
 */ 

extern void Serial_transmission_USART_Transmit( unsigned char ub_data );

extern void Serial_transmission_init(void);

extern void Serial_transmission_Send_Helo(void);

extern void Serial_transmission_UsartWrite(char *data, unsigned char length);

