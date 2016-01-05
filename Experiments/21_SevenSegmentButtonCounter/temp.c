/* MAX7219 Interaction Code
 * ---------------------------
 * For more information see
 * http://www.adnbr.co.uk/articles/max7219-and-7-segment-displays
 *
 * 668 bytes - ATmega168 - 16MHz
 */

// 16MHz clock
// #define F_CPU 16000000UL



#include <avr/io.h>
#include <util/delay.h>
#include "MAX7219.c"

char digitsInUse = 4;

int main(void) {
    // SCK MOSI CS/LOAD/SS
    DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI) | (1 << PIN_SS);

    // SPI Enable, Master mode
    SPCR |= (1 << SPE) | (1 << MSTR)| (1<<SPR1);

    // Decode mode to "Font Code-B"
    MAX7219_writeData(MAX7219_MODE_DECODE, 0xFF);

    // Scan limit runs from 0.
    MAX7219_writeData(MAX7219_MODE_SCAN_LIMIT, digitsInUse - 1);
    MAX7219_writeData(MAX7219_MODE_INTENSITY, 2);
    MAX7219_writeData(MAX7219_MODE_POWER, ON);

    int i = 9990;
    while(1)
    {
        MAX7219_displayNumber(++i);
        _delay_ms(1000);

        if (i == 9999) {
            i = 0;
        }
    }
}
