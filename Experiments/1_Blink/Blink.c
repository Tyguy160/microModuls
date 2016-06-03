// Experiment 1: Blink an LED

// Definitions
#define LED PB0
#define DATA_DIRECTION_REGISTER DDRB
#define LED_PORT PORTB
#define DELAY_TIME 500

// External libraries
#include <avr/io.h>
#include <util/delay.h>

// Main method
int main(void) {
	// Set LED_PORT to be an output
	DATA_DIRECTION_REGISTER |= (1 << LED);

	// Turn on the LED
	LED_PORT |= (1 << LED);

		// Loop forever
    while(1) {
		// Toggle the status of LED_PORT
		LED_PORT ^= (1 << LED);

		// Delay between toggle (in milliseconds)
		_delay_ms(DELAY_TIME);
    }

	// This line will never be reached
	return 0;
}
