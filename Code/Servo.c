/*
 * Servo.c
 *
 * Created: 5/14/2024 8:36:38 PM
 *  Author: Omar
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
void Servo_Init(){
	DDRB |= (1<<PORTB1);	/* Make OC1A pin as output */
	TCNT1 = 0;				/* Set timer1 count zero */
	ICR1 = 4999;			/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
}

void ServoRotateNegative90(){
	OCR1A = 249;
}

void ServoRotateZero(){
	OCR1A = 374;
}

void ServoRotatePositive90(){
	OCR1A = 499;
}

void LockSafe(){
	ServoRotateNegative90();
}

void UnlockSafe(){
	ServoRotateZero();
}