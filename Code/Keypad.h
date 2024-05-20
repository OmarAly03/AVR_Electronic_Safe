#ifndef KEYPAD_H_
#define KEYPAD_H_

/* Configuration Pins & Ports */
/*Rows*/
#define KPD_R0_DDR			DDRD
#define KPD_R0_PORT			PORTD
#define KPD_R0_PINPORT		PIND
#define KPD_R0_PIN			2

#define KPD_R1_DDR			DDRD
#define KPD_R1_PORT			PORTD
#define KPD_R1_PINPORT		PIND
#define KPD_R1_PIN			3
	
#define KPD_R2_DDR			DDRB
#define KPD_R2_PORT			PORTB
#define KPD_R2_PINPORT		PINB
#define KPD_R2_PIN			4

#define KPD_R3_DDR			DDRB
#define KPD_R3_PORT			PORTB
#define KPD_R3_PINPORT		PINB
#define KPD_R3_PIN			5

/*Columns*/
#define KPD_C0_DDR			DDRC
#define KPD_C0_PORT			PORTC
#define KPD_C0_PINPORT		PINC
#define KPD_C0_PIN			0

#define KPD_C1_DDR			DDRC
#define KPD_C1_PORT			PORTC
#define KPD_C1_PINPORT		PINC
#define KPD_C1_PIN			1

#define KPD_C2_DDR			DDRC
#define KPD_C2_PORT			PORTC
#define KPD_C2_PINPORT		PINC
#define KPD_C2_PIN			2

#define KPD_C3_DDR			DDRC
#define KPD_C3_PORT			PORTC
#define KPD_C3_PINPORT		PINC
#define KPD_C3_PIN			3

/**/
#define KPD_PRESSED_KEY 0
#define KPD_NOTPRESSED_KEY 0xFF

/* To Avoid Magic Numbers*/
#define ROW_NUMBER       4
#define COL_NUMBER       4


/* Prototypes */
void KPD_Init();
unsigned char KPD_GetPressedKey(void);


#endif /* KEYPAD_H_ */
