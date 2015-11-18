/*
 * RGBFade.c
 *
 * Created: 7/1/2015 6:02:18 AM
 *  Author: Tyler
 */ 

#define LED_PORT PORTB
#define LED_DDR DDRB

#define RED_PIN PB0
#define GREEN_PIN PB1
#define BLUE_PIN PB2

#define RED 0
#define BLUE 1
#define GREEN 2
#define NUMBER_OF_COLORS 3

#include <avr/io.h>
#include <util/delay.h>

void pwmAllPins(uint8_t brightness, int *pin, int port) {
	
	
	port |= (1 << *pin);
	for (uint8_t i = 0; i < 255; i++) {
		if (i >= brightness) {
			port = 0;
		}
		_delay_us(20);
	}
}

void testLED(int* pin, int* port) {
	*port |= (1 << *pin);
	_delay_ms(500);
	*port = 0;
	_delay_ms(500);
}

int main() {
	
	// Set LED pins to be outputs
	LED_DDR |= (1 << RED_PIN);
	LED_DDR |= (1 << GREEN_PIN);
	LED_DDR |= (1 << BLUE_PIN);
	
	uint8_t brightness = 0;
	int8_t direction = 1;
	uint8_t color = -1;
	
	LED_DDR |= ((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN));
	
	// Loop forever
	while(1) {	
		
        if (brightness == 0) {
			direction = 1;
			color++;
			if (color >= NUMBER_OF_COLORS) {
				color = RED;
			}
		}
		if (brightness == 255) {
			direction = -1;
		}
		brightness += direction;
		
		if (color == RED) {
			LED_PORT |= (1 << RED_PIN);
			for (uint8_t i = 0; i < 255; i++) {
				if (i >= brightness) {
					LED_PORT = 0;
				}
				_delay_us(20);
			}
		}
		
		if (color == GREEN) {
			LED_PORT |= (1 << GREEN_PIN);
			for (uint8_t i = 0; i < 255; i++) {
				if (i >= brightness) {
					LED_PORT = 0;
				}
				_delay_us(20);
			}
		}
		
		if (color == BLUE) {
			LED_PORT |= (1 << BLUE_PIN);
			for (uint8_t i = 0; i < 255; i++) {
				if (i >= brightness) {
					LED_PORT = 0;
				}
				_delay_us(20);
			}
		}
		
    }
}