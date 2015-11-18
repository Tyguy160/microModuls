/*
 * BinaryButtonCounter.cpp
 *
 * Created: 6/11/2015 6:23:50 AM
 *  Author: Tyler
 */ 


// Connect LED to PB0
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_0 PB0
#define LED_1 PB1
#define LED_2 PB2
#define BUTTON_DDR DDRC
#define BUTTON_PULL_UP PORTC
#define PIN_STATUS PINC
#define BUTTON PC0
#define DEBOUNCE_TIME 10000
#define MAX_COUNT 8

// External libraries
#include <avr/io.h>
#include <util/delay.h>

int ButtonPressed() {
	// Return the status of the button
	return (PIN_STATUS & (1 << BUTTON));
}

int main() {
	
	// Variable initialization
	uint8_t buttonWasPressed;
	uint8_t count = 0;
	
	// Initialize BUTTON_PORT as an input
	BUTTON_DDR &= ~(1 << BUTTON);
	
	// Initialize pull-up resistor on BUTTON_PORT
	BUTTON_PULL_UP |= (1 << BUTTON);
	
	// Set LED pins to be outputs
	LED_DDR |= (1 << LED_0);
	LED_DDR |= (1 << LED_1);
	LED_DDR |= (1 << LED_2);
	
	// Loop forever
	while(1) {
		
		// If button is pressed, debounce, then change LEDs
		if (ButtonPressed()) {
			
			// Debounce the button with a time delay (microseconds)
			_delay_us(DEBOUNCE_TIME);
			
			// Check for bouncing
			if (buttonWasPressed == 0) {
				
				// Set flag for button press
				buttonWasPressed = 1;
				
				// Increment button press count
				count++;
				
				// Set the first LED (LSB), depending on the value of count
				if (count & 0b001) {
					LED_PORT |= (1 << LED_0);	
				}
				else {
					LED_PORT &= ~(1 << LED_0);
				}
				
				// Set the second LED, depending on the value of count
				if (count & 0b010) {
					LED_PORT |= (1 << LED_1);
				}
				else {
					LED_PORT &= ~(1 << LED_1);
				}
				
				// Set the third LED (MSB), depending on the value of count
				if (count & 0b100) {
					LED_PORT |= (1 << LED_2);
				}
				else {
					LED_PORT &= ~(1 << LED_2);
				}
				
				// Reset the button press count
				if (count == MAX_COUNT) {
					count = 0;
				}			
			}
		}
		
		// Clear flag for button press
		else {
			buttonWasPressed = 0;
		}
	}
	
	return 0;
}