/*
 * RGBLEDColorClicker.c
 *
 * Created: 7/26/2015 5:43:22 PM
 *  Author: Tyler
 */ 

#define LED_PORT PORTB
#define LED_DDR DDRB

#define RED_LED PB1
#define GREEN_LED PB2
#define BLUE_LED PB3

#define BUTTON_DDR DDRC
#define BUTTON_PULL_UP PORTC
#define PIN_STATUS PINC
#define RED_BUTTON PC0
#define GREEN_BUTTON PC1
#define BLUE_BUTTON PC2
#define DEBOUNCE_TIME 10000
#define MAX_COUNT 8

int redButtonPressCount = 0;
int redButtonWasPressed = 0;
int greenButtonPressCount = 0;
int greenButtonWasPressed = 0;
int blueButtonPressCount = 0;
int blueButtonWasPressed = 0;

#include <avr/io.h>
#include <util/delay.h>

void initTimers() {
	// Timer 1 A,B
	TCCR1A |= (1 << WGM10);
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);
	TCCR1B |= (1 << WGM11);
	TCCR1B |= (1 << CS11);
	
	// Timer 2
	TCCR2A |= (1 << WGM20);
	//TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS21);
	TCCR2A |= (1 << COM2A1);
}

int RedButtonPressed() {
	// Return the status of the button
	return (PIN_STATUS & (1 << RED_BUTTON));
}

int GreenButtonPressed() {
	// Return the status of the button
	return (PIN_STATUS & (1 << GREEN_BUTTON));
}

int BlueButtonPressed() {
	// Return the status of the button
	return (PIN_STATUS & (1 << BLUE_BUTTON));
}

int checkRedButton() {
	
	// If button is pressed, debounce, then change LEDs
	if (RedButtonPressed()) {
		
		// Debounce the button with a time delay (microseconds)
		_delay_us(DEBOUNCE_TIME);
		
		// Check for bouncing
		if (redButtonWasPressed == 0) {
			
			// Set flag for button press
			redButtonWasPressed = 1;
			
			// Increment button press count
			redButtonPressCount++;
			
			// Reset the button press count
			if (redButtonPressCount == MAX_COUNT) {
				redButtonPressCount = 0;
			}
		}		
	}
	// Clear flag for button press
	else {
		redButtonWasPressed = 0;
	}
	
	return (pow(2, redButtonPressCount) - 2);
}

int checkGreenButton() {
	
	// If button is pressed, debounce, then change LEDs
	if (GreenButtonPressed()) {
		
		// Debounce the button with a time delay (microseconds)
		_delay_us(DEBOUNCE_TIME);
		
		// Check for bouncing
		if (greenButtonWasPressed == 0) {
			
			// Set flag for button press
			greenButtonWasPressed = 1;
			
			// Increment button press count
			greenButtonPressCount++;
			
			// Reset the button press count
			if (greenButtonPressCount == MAX_COUNT) {
				greenButtonPressCount = 0;
			}
		}
	}
	// Clear flag for button press
	else {
		greenButtonWasPressed = 0;
	}
	
	return (pow(2, greenButtonPressCount) - 2);
}

int checkBlueButton() {
	
	// If button is pressed, debounce, then change LEDs
	if (BlueButtonPressed()) {
		
		// Debounce the button with a time delay (microseconds)
		_delay_us(DEBOUNCE_TIME);
		
		// Check for bouncing
		if (blueButtonWasPressed == 0) {
			
			// Set flag for button press
			blueButtonWasPressed = 1;
			
			// Increment button press count
			blueButtonPressCount++;
			
			// Reset the button press count
			if (blueButtonPressCount == MAX_COUNT) {
				blueButtonPressCount = 0;
			}
		}
	}
	// Clear flag for button press
	else {
		blueButtonWasPressed = 0;
	}
	
	return (pow(2, blueButtonPressCount) - 2);
}

int main() {
	
	// Initialize BUTTON_DDR as inputs
	BUTTON_DDR &= ~(1 << RED_BUTTON);
	BUTTON_DDR &= ~(1 << GREEN_BUTTON);
	BUTTON_DDR &= ~(1 << BLUE_BUTTON);
	
	// Initialize pull-up resistor on BUTTON_PORT
	BUTTON_PULL_UP |= (1 << RED_BUTTON);
	BUTTON_PULL_UP |= (1 << GREEN_BUTTON);
	BUTTON_PULL_UP |= (1 << BLUE_BUTTON);
	
	// Set LED pins to be outputs
	LED_DDR |= (1 << RED_LED);
	LED_DDR |= (1 << GREEN_LED);
	LED_DDR |= (1 << BLUE_LED);
	
	initTimers();
	
	uint8_t redBrightness = 0;
	uint8_t greenBrightness = 0;
	uint8_t blueBrightness = 0;
	
	// Loop forever
	while(1) {
		
		
		redBrightness = checkRedButton();
		OCR1A = redBrightness;
		
		greenBrightness = checkGreenButton();
		OCR1B = greenBrightness;
		
		blueBrightness = checkBlueButton();
		OCR2A = blueBrightness;
	}
	return 0;
}