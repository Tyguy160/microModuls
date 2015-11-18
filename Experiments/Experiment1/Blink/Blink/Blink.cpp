/*
 * Blink.cpp
 *
 * Created: 5/31/2015 4:28:21 PM
 *  Author: Tyler
 */ 

// Connect LED to PB0
#define LED_PORT PB0
#define DELAY_TIME 500

// External libraries
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	// Set LED_PORT to be an output
	DDRB |= (1 << LED_PORT);
	
	// Turn on the LED
	PORTB |= (1 << LED_PORT);
	
	// Loop forever
    while(1)
    {
		// Toggle the status of LED_PORT
		PORTB ^= (1 << LED_PORT);
		
		// Delay between toggle (in milliseconds)
		_delay_ms(DELAY_TIME);
    }
	
	return 0;
}