// External libraries
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "MAX7219.h"

#define ASCII_OFFSET 48

uint8_t count;
uint8_t ascii_count;
char digitsInUse = 4;

int main(void)
{
	initUSART();
	printString("This is the unread email count display!\r\n");

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
        ascii_count = receiveByte(); //this function will wait for a number
        transmitByte(ascii_count);
        //_delay_ms(1000);
        count = ascii_count;
        MAX7219_displayNumber(count);
	}

	return 0;
}
