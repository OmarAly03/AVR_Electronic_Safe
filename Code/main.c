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
#include "UART.h"

#define NOOFATTEMPTS 3

unsigned char attempts = NOOFATTEMPTS;
char command = '\0';
unsigned char Local_u8Key;
unsigned char arr[5];
unsigned char *pass = "1234";
unsigned char breakCondition = 0;
unsigned char wifiCondition = 1;
unsigned char byPassLock = 0;
unsigned char unlocked = 0;

int main(void){
	LCD_Init();
	KPD_Init();
	Servo_Init();
	USART_Init();
	
    while (1){
		LCD_Clear();
		LCD_setPosition(ROW1, COL0);
		LCD_sendString("Welcome Choose a");
		LCD_setPosition(ROW2, COL0);
		LCD_sendString("Mode to Unlock");
		_delay_ms(1000);
		
		LCD_Clear();
		LCD_setPosition(ROW1, COL0);
		LCD_sendString("1. Normal Mode");
		LCD_setPosition(ROW2, COL0);
		LCD_sendString("2. WIFI Mode");
		
		do{
			Local_u8Key = KPD_GetPressedKey();
		} while((Local_u8Key != '1') && (Local_u8Key != '2'));

		switch (Local_u8Key){
			case '1':
				for(unsigned char j = 0 ; ((j < NOOFATTEMPTS) && (!breakCondition) && (attempts)) ; j++){
					LCD_Clear();
					LCD_setPosition(ROW1, COL0);
					LCD_sendString("Enter");
					LCD_setPosition(ROW2, COL0);
					LCD_sendString("Password: ");
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
						LCD_Clear();
						LCD_setPosition(ROW1, COL4);
						LCD_sendString("Welcome");
						ServoRotateZero();
						breakCondition = 1;
					}
					else{
						attempts--;
						LCD_Clear();
						LCD_setPosition(ROW1, COL0);
						LCD_sendString("Incorrect Pass");
						LCD_setPosition(ROW2, COL0);
						LCD_sendString("Attempts Left: ");
						LCD_sendData((unsigned char)(attempts + '0'));
						_delay_ms(800);
					}
				}
				break;
				
				case '2':
					LCD_Clear();
					LCD_setPosition(ROW1, COL3);
					LCD_sendString("Waiting...");
					while(wifiCondition){
						command = USART_Receive();
						switch (command) {
							case 'U':{
								LCD_Clear();
								LCD_setPosition(ROW1, COL4);
								LCD_sendString("Welcome");
								ServoRotateZero();
								_delay_ms(1000);
								command = '\0';
								unlocked = 1;
								break;
							}
							case 'L':{
								if(unlocked){
									LCD_Clear();
									LCD_setPosition(ROW1, COL4);
									LCD_sendString("LOCKED !");
									ServoRotateNegative90();
									command = '\0';
									wifiCondition = 0;
									byPassLock = 1;
									_delay_ms(1000);
									break;
								}
								command = '\0';
							}
							default:{
								break;
							}
						}
					}
					break;
					
				default:
					break;
		}
		
		if(!byPassLock){				
			if(attempts){
				LCD_setPosition(ROW2, COL0);
				LCD_sendString("Press C to Lock");
				
				do{
					Local_u8Key = KPD_GetPressedKey();
				} while(Local_u8Key != 'C');
				
				LCD_Clear();
				LCD_setPosition(ROW1, COL4);
				LCD_sendString("LOCKED !");
				ServoRotateNegative90();
				_delay_ms(1000);
				breakCondition = 0;
				attempts = NOOFATTEMPTS;
			}
			
			else if(!attempts){
				LCD_Clear();
				LCD_setPosition(ROW1, COL4);
				LCD_sendString("LOCKED !");
				LCD_setPosition(ROW2, COL0);
				LCD_sendString("Wild Button Only!");
				do{
					Local_u8Key = KPD_GetPressedKey();
				} while(Local_u8Key != '=');
				breakCondition = 0;
				attempts = NOOFATTEMPTS;
			}
		}
		
    }
}

