/*
 * LCD.h
 *
 * Created: 5/14/2024 8:03:00 PM
 *  Author: Omar
 */ 

#ifndef LCD_H_
#define LCD_H_

/************************************ MACROs **************************************/
#define RS				PB0
#define RW				PB2
#define E				PB3

#define LCD_DDR			DDRD
#define LCD_PORT		PORTD
#define CONTROL_DDR		DDRB
#define CONTROL_PORT	PORTB
#define ROW1			0
#define ROW2			1

typedef enum{
	COL0,
	COL1,
	COL2,
	COL3,
	COL4,
	COL5,
	COL6,
	COL7,
	COL8,
	COL9,
	COL10,
	COL11,
	COL12,
	COL13,
	COL14,
	COL15
}COL_t;

/************************************ Functions Prototypes **************************************/
void send_Nibble(unsigned char data);
void send_Byte(unsigned char data);
void LCD_sendCommand(unsigned char command);
void LCD_sendData(unsigned char data);
void LCD_Init();
void LCD_sendString(char* str);
void LCD_Clear();
void LCD_setPosition(unsigned char row, unsigned char col);


#endif /* LCD_H_ */