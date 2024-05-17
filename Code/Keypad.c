#include <avr/io.h>
#include <util/delay.h>

#define ROWS 4
#define COLS 4

// Define the port and pins for the rows and columns
#define ROW1_PORT PORTD
#define ROW2_PORT PORTB
#define COL_PORT PORTC
#define ROW1_DDR DDRD
#define ROW2_DDR DDRB
#define COL_DDR DDRC
#define ROW1_PIN PIND
#define ROW2_PIN PINB
#define COL_PIN PINC

// Define the key values
char keys[ROWS][COLS] = {
    {'7', '8', '9', 'A'},
	{'4', '5', '6', 'B'},
	{'1', '2', '3', 'C'},
    {'*', '0', '#', 'D'}
};

void KPD_Init(){
    ROW1_DDR |= 0x0C; // Set PD2, PD3 as output
    ROW2_DDR |= 0x30; // Set PB4, PB5 as output
    COL_DDR &= ~0x0F; // Set PC0, PC1, PC2, PC3 as input
    COL_PORT |= 0x0F; // Enable pull-up resistors on PC0, PC1, PC2, PC3
}

unsigned char KPD_GetPressedKey(void) {
    for (int row = 0; row < ROWS; row++) {
        // Reset the row pins
        ROW1_PORT |= 0x0C;
        ROW2_PORT |= 0x30;

        switch (row) {
            case 0:
                ROW1_PORT &= ~(1 << 2); // Ground PD2
                break;
            case 1:
                ROW1_PORT &= ~(1 << 3); // Ground PD3
                break;
            case 2:
                ROW2_PORT &= ~(1 << 4); // Ground PB4
                break;
            case 3:
                ROW2_PORT &= ~(1 << 5); // Ground PB5
                break;
        }

        _delay_ms(5); // Debounce delay

        for (int col = 0; col < COLS; col++) {
            if (!(COL_PIN & (1 << col))) { // If a key is pressed
                while (!(COL_PIN & (1 << col))); // Wait for the key to be released
                _delay_ms(5); // Debounce delay
                return keys[row][col]; // Return the key value
            }
        }
    }

    return '\0'; // No key pressed
}