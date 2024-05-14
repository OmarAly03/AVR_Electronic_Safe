/*
 * LCD.c
 *
 * Created: 5/14/2024 8:26:45 PM
 *  Author: Omar
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

void send_Nibble(unsigned char data)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	CONTROL_PORT |= (1<<E);
	_delay_us(1);
	CONTROL_PORT &= ~(1<<E);
	_delay_us(200);
}

void send_Byte(unsigned char data)
{
	send_Nibble(data); // upper nibble first
	send_Nibble(data << 4); // then lower nibble
}

void LCD_sendCommand(unsigned char command)
{
	CONTROL_PORT &= ~(1<<RS);
	send_Byte(command);
	_delay_ms(2);
}

void LCD_sendData(unsigned char data)
{
	CONTROL_PORT |= (1<<RS);
	send_Byte(data);
	_delay_ms(2);
}

void LCD_Init()
{
	CONTROL_DDR |= (1<<RS) | (1<<RW) | (1<<E);
	LCD_DDR = 0xF0; // upper nibble as output
	CONTROL_PORT &= ~(1<<RW); // write mode
	_delay_ms(15);

	LCD_sendCommand(0x33); // initialization sequence
	LCD_sendCommand(0x32);
	LCD_sendCommand(0x28); // 4-bit mode, 2 lines, 5x7 font
	LCD_sendCommand(0x0C); // display on, cursor off, blink off
	LCD_sendCommand(0x06); // increment mode, entire shift off
	LCD_sendCommand(0x01); // clear display, set DDRAM address to 0
}

void LCD_sendString(char* str)
{
	while(*str)
	{
		LCD_sendData(*str++);
		_delay_ms(50);
	}
}

void LCD_Clear()
{
	LCD_sendCommand(0x01); // clear display, set DDRAM address to 0
	_delay_ms(2); // wait for the command to execute
}

void LCD_setPosition(unsigned char row, unsigned char col)
{
	unsigned char address;

	/* calculate DDRAM address */
	switch(row)
	{
		case 0: address = 0x00 + col; break; // 1st row
		case 1: address = 0x40 + col; break; // 2nd row
		default: return; // invalid row
	}

	LCD_sendCommand(0x80 | address); // set DDRAM address
}