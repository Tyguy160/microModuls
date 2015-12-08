/*
 * ToggleBlinkSpeed.cpp
 *
 * Created: 6/5/2015 5:37:36 AM
 *  Author: Tyler
 */


// Connect LED to PB0
#define LED_PORT PC0
#define BUTTON_PORT PC3
#define DELAY_TIME_1 100
#define DELAY_TIME_2 1000

// External libraries
#include <avr/io.h>
#include <util/delay.h>

int ButtonPressed() {
	// Return the status of the button
	return (PINC & (1 << BUTTON_PORT));
}

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
		// Toggle the status of LED_PORT
		//PORTC ^= (1 << LED_PORT);

		// If button is pressed, blink at rate of DELAY_TIME_1
		if (!ButtonPressed()) {
			// Delay between toggle (in milliseconds)
			_delay_ms(DELAY_TIME_1);
			PORTC &= ~(1 << LED_PORT);
			_delay_ms(DELAY_TIME_1);
			PORTC |= (1 << LED_PORT);
		}
		// Otherwise blink at rate of DELAY_TIME_2
		else {
			// Delay between toggle (in milliseconds)
			_delay_ms(DELAY_TIME_2);
			PORTC &= ~(1 << LED_PORT);
			_delay_ms(DELAY_TIME_2);
			PORTC |= (1 << LED_PORT);
		}
	}

	return 0;
}
