/*
 * ESP.c
 *
 * Created: 5/14/2024 12:53:43 AM
 * Author : Omar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



void USART_Init() {
	/* Set baud rate */
	UBRR0 = 103;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
}

unsigned char USART_Receive(void) {
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

int main(void) {
	USART_Init();
	DDRB |= (1 << PORTB5); // Set PB5 as output (Arduino Uno pin 13)

	while (1) {
		char command = USART_Receive();
		switch (command) {
			case 'U':
			PORTB |= (1 << PORTB5); // Set PB5 high
			break;
			case 'L':
			PORTB &= ~(1 << PORTB5); // Set PB5 low
			break;
		}
	}
}