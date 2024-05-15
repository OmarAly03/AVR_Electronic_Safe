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
unsigned char arr[5];
unsigned char *pass = "1234";

int main(void){
	LCD_Init();
	KPD_Init();

    while (1){
		for(unsigned char i = 0 ; i < 4 ; i++){
			do{
				Local_u8Key = KPD_GetPressedKey();
			} while(Local_u8Key == '\0');
			
			arr[i] = Local_u8Key;
			LCD_sendData(Local_u8Key);
		}
		arr[4] = '\0';
		
		unsigned char cond = 1;
		
		for(unsigned char i = 0 ; i < 5 ; i++){
			if(arr[i] != pass[i]){
				cond = 0;
			}
		}
		
		LCD_Clear();
		if(cond){
			LCD_sendString("Welcome");
		}
		else{
			LCD_sendString("Incorrect");
		}

		_delay_ms(50); // Add a small delay to reduce CPU usage
    }
}

