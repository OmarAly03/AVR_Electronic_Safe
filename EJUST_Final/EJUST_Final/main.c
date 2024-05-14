/*
 * FinalProject_2.c
 *
 * Created: 5/15/2024 12:25:20 AM
 * Author : Omar
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "Servo.h"
#include "Keypad.h"

unsigned char Local_u8Key;

int main(void){
	LCD_Init();
	KPD_Init();

    while (1){
		// Get the pressed key
		Local_u8Key = KPD_GetPressedKey();

		if (Local_u8Key != '\0') {
			// A key was pressed, print it to the serial port
			LCD_sendData(Local_u8Key);
		}

		_delay_ms(50); // Add a small delay to reduce CPU usage
    }
}

