/*
 * LEDBrightnessButton.c
 *
 * Created: 7/25/2015 7:31:32 PM
 *  Author: Tyler
 */ 


#define LED_PORT PORTB
#define LED_DDR DDRB

#define RED_LED PB0
#define GREEN_LED PB1
#define BLUE_LED PB2

#define BUTTON_DDR DDRC
#define BUTTON_PULL_UP PORTC
#define PIN_STATUS PINC
#define BUTTON PC0
#define DEBOUNCE_TIME 10000
#define MAX_COUNT 8

#include <avr/io.h>
#include <util/delay.h>

void initTimers() {
	TCCR1A |= (1 << WGM10);
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);
	
	//TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);
	//
	//TCCR2A |= ((1 << WGM20) | (1 << WGM21) | (1 << COM2A1));
	//TCCR2B |= (1 << CS21);
}

int ButtonPressed() {
	// Return the status of the button
	return (PIN_STATUS & (1 << BUTTON));
}

int main() {
	
	// Variable initialization
	uint8_t buttonWasPressed = 0;
	uint8_t count = 0;
	
	// Initialize BUTTON_PORT as an input
	BUTTON_DDR &= ~(1 << BUTTON);
	
	// Initialize pull-up resistor on BUTTON_PORT
	BUTTON_PULL_UP |= (1 << BUTTON);
	
	// Set LED pins to be outputs
	LED_DDR |= (1 << BLUE_LED);
	
	initTimers();
	
	uint8_t brightness = 0;
	
	
	
	
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
		
		brightness = pow(2, count) - 2;
		OCR1B = brightness;
	}
	return 0;
}