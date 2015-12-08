/*
 * ToggleBlinkSpeed.c
 *
 * Created: 6/5/2015 5:37:36 AM
 *  Author: Tyler
 */

// Connect LED to PC0
#define LED_PORT PC0
// Connect button to PC3
#define BUTTON_PORT PC3
#define DELAY_TIME_1 100
#define DELAY_TIME_2 500
#define DELAY_TIME_3 1000
#define MAX_STATE 3
// External libraries
#include <avr/io.h>
#include <util/delay.h>

int is_pressed() {
	// Return the status of the button
	return ((PINC & (1 << BUTTON_PORT)) == 0);
}

int state;

int main()
{

	// Initialize BUTTON_PORT as an input
	DDRC &= ~(1 << BUTTON_PORT);

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
			state += 1;
			// Reset state after it reaches max value
			if (state == MAX_STATE) {
				state = 0;
			}
            // 1 second delay to prevent button press from being counted more than once
            _delay_ms(1000);
		}

		switch (state) {
			case 0:
				// Delay between toggle (in milliseconds)
				PORTC ^= (1 << LED_PORT);
				_delay_ms(DELAY_TIME_1);
				break;
			case 1:
				PORTC ^= (1 << LED_PORT);
				_delay_ms(DELAY_TIME_2);
				break;
			case 2:
				PORTC ^= (1 << LED_PORT);
				_delay_ms(DELAY_TIME_3);
				break;
		}
	}

	return 0;
}
