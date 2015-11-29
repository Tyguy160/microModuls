#define LED_PORT PORTB
#define LED_DDR DDRB

#define LED_PIN PB0

#include <avr/io.h>
#include <util/delay.h>

#define MAX_VALUE 255

static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);     /* ADC clock prescaler /8 */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}

void pwm(uint8_t brightness) {
  uint8_t i;
  LED_PORT |= (1 << LED_PIN);
  for (i = 0; i < MAX_VALUE; i++) {
    if (i >= brightness) {
      LED_PORT = 0;
    }
    _delay_us(20);
  }
}

int main() {
  
  initADC0();
  
  // Set LED pins to be outputs
  LED_DDR |= (1 << LED_PIN);
  
  uint16_t brightness = 0;
  uint16_t adcValue = 0;
  // Loop forever
  while(1) {

    ADCSRA |= (1 << ADSC);                     /* start ADC conversion */
    loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done */
    brightness = MAX_VALUE-ADC/2;                                     /* read ADC in */
    
    pwm(brightness);
  }
}
