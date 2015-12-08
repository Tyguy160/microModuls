/*
 ADD DESCRIPTION HERE
 */

// Connect LED to PB0
#define LED_PORT PC0
#define DATA_DIRECTION_REGISTER DDRC
#define PORT PORTC
#define DELAY_TIME 10000

// External libraries
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	// Set LED_PORT to be an output
	DATA_DIRECTION_REGISTER |= (1 << LED_PORT);

	// Turn on the LED
	PORT |= (1 << LED_PORT);

	// Loop forever
    while(1)
    {
		// Toggle the status of LED_PORT
		PORT ^= (1 << LED_PORT);

		// Delay between toggle (in milliseconds)
		_delay_ms(DELAY_TIME);
    }

	return 0;
}
