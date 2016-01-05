/*
 * ToggleBlinkSpeed.c
 *
 * Created: 6/5/2015 5:37:36 AM
 *  Author: Tyler
 */

// Connect button to PC3
#define BUTTON_PORT PORTC
#define BUTTON PC3
#define BUTTON_PIN PINC
#define BUTTON_DDR DDRC
#define MAX_COUNT 9999

// External libraries
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "MAX7219.h"

uint8_t count;
uint8_t wasButtonPressed;
char digitsInUse = 4;

int main(void)
{

	// Initialize BUTTON_PORT as an input
	BUTTON_DDR &= ~(1 << BUTTON);

	// Initialize pull-up resistor on BUTTON_PORT
	BUTTON_PORT |= (1 << BUTTON);

	initUSART();
	printString("Welcome to the 7-seg button counter!\r\n");


	// SCK MOSI CS/LOAD/SS
	DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI) | (1 << PIN_SS);

	// SPI Enable, Master mode
	SPCR |= (1 << SPE) | (1 << MSTR)| (1<<SPR1);

	// Decode mode to "Font Code-B"
	MAX7219_writeData(MAX7219_MODE_DECODE, 0xFF);

	// Scan limit runs from 0.
	MAX7219_writeData(MAX7219_MODE_SCAN_LIMIT, digitsInUse - 1);

	// Set brightness of display to 2
	MAX7219_writeData(MAX7219_MODE_INTENSITY, 2);

	// Turn on the display
	MAX7219_writeData(MAX7219_MODE_POWER, ON);

	// Print initial count to seven segment display
	MAX7219_displayNumber(count);

	// Loop forever
	while(1) {

		if (bit_is_clear(BUTTON_PIN, BUTTON)) {
			if (!wasButtonPressed) {              /* if it's a new press ... */
				_delay_ms(20);
				count++;                          /* advance to next note */
				printByte(count);
				printString("\r\n");

				// Print count to seven segment display
				MAX7219_displayNumber(count);

				if (count == MAX_COUNT) {
					count = 0;
				}
				wasButtonPressed = 1;
			}

		}
		else {
			wasButtonPressed = 0;
		}
	}

	return 0;
}
