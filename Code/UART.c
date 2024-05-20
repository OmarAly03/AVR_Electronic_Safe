/*
 * UART.c
 *
 * Created: 5/16/2024 1:07:55 AM
 *  Author: Omar
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void USART_Init() {
	DDRB |= (1 << PORTB5); 
	UBRR0 = 103;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

unsigned char USART_Receive(void) {
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}