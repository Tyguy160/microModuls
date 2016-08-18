/*
 * ToggleBlinkSpeed.c
 *
 * Created: 6/5/2015 5:37:36 AM
 *  Author: Tyler
 */


// Connect LED to PB0
#define LED_PORT PC0
// Connect button to PC3
#define BUTTON_PORT PC3
#define DELAY_TIME_1 100
#define DELAY_TIME_2 1000

// External libraries
#include <avr/io.h>
#include <util/delay.h>

int is_pressed() {
	// Returns TRUE if button is pressed (BUTTON_PORT is equal to 0)
	return ((PINC & (1 << BUTTON_PORT)) == 0);
}

int main()
{
	// Initialize pull-up resistor on BUTTON_PORT
	PORTC |= (1 << BUTTON_PORT);

	// Set LED_PORT to be an output
	DDRC |= (1 << LED_PORT);

	// Turn on the LED
	PORTC |= (1 << LED_PORT);

	// Loop forever
	while(1)
	{
		// If button is pressed, blink at rate of DELAY_TIME_1
		if (is_pressed()) {
		    // Toggle the status of LED_PORT
			PORTC ^= (1 << LED_PORT);
			// Delay between toggle (in milliseconds)
			_delay_ms(DELAY_TIME_1);
		}

		// Otherwise blink at rate of DELAY_TIME_2
		else {
		    // Toggle the status of LED_PORT
			PORTC ^= (1 << LED_PORT);
			// Delay between toggle (in milliseconds)
			_delay_ms(DELAY_TIME_2);
		}
	}

	return 0;
}
