                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRD |= (1 << 6);            /* Data Direction Register B:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    PORTD = (1 << 6);          /* Turn on first LED bit/pin in PORTB */
    _delay_ms(100);                                           /* wait */

    PORTD = 0b00000000;          /* Turn off all B pins, including LED */
    _delay_ms(100);                                           /* wait */

  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
