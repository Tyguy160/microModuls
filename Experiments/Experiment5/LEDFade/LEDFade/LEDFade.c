/*
 * LEDFade.c
 *
 * Created: 7/21/2015 5:01:44 PM
 *  Author: Tyler
 */ 

#define LED_PORT PORTB
#define LED_DDR DDRB

#define LED_PIN PB0

#include <avr/io.h>
#include <util/delay.h>

void pwm(uint8_t brightness) {
	uint8_t i;
	LED_PORT |= (1 << LED_PIN);
	for (i = 0; i < 255; i++) {
		if (i >= brightness) {
			LED_PORT = 0;
		}
		_delay_us(20);
	}
}

int main() {
	
	// Set LED pins to be outputs
	LED_DDR |= (1 << LED_PIN);
	
	uint8_t brightness = 0;
	int8_t direction = 1;
	
	LED_DDR |= (1 << LED_PIN);
	
	// Loop forever
	while(1) {
        if (brightness == 0) {
			direction = 1;	
		}
		if (brightness == 255) {
			direction = -1;	
		}
		brightness += direction;
		pwm(brightness);
    }
}