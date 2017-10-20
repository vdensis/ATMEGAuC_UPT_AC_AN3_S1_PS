/*
 * _7Segments_display.h
 *
 * Created: 05.01.2017 18:11:31
 *  Author: Denis Vadan
 */ 


/*		_________		G   F  GND  A   B
*	   |\____a__/|		.   .   .   .   .
*	   |f|     |b|
*	   | |_____| |
*	   |-\__g__/-|
*	   |e|	   |c|
*	   | |_____| |
*	   |/___d___\|		.   .   .   .   
*						E	D  GND  C
*
*	A - Pin 13 [PB5]
*	B - Pin 3 [PD3]
*	C - Pin 4 [PD4]
*	D - Pin 5 [PD5]
*	E - Pin 6 [PD6]
*	F - Pin 7 [PD7]
*	G - Pin 8 [PB0]
*	
*		[1 - b c]            [2 - a b g e d]     [3 - a b c d g ]       [4 - f b c g ]       [5 - a c d f g] 
*		[6 - a c d e f g]    [7 - a b c]         [8 - a b c d e f g]    [9 - a b c d f g]    [0 - a b c d e f]
*/

extern void SevenSegments_display_init(void);	


extern void ShowAndIncrement_7SegmentDisplay(void);


extern void EEPROM_write(unsigned int uiAddress, unsigned char ucData);


extern unsigned char EEPROM_read(unsigned int uiAddress);