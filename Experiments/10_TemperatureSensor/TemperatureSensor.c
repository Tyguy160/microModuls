// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"

// Used for ADC sleep mode
#include <avr/sleep.h>

// Used for floor and round
#include <math.h>

#define REF_VCC 5.04
#define TEMP_OFFSET 0.5

// Initializes the ADC
void initADC(void) {

  // Set mux to ADC3
  ADMUX |= (0b00001111 & PC3);

  // Use AVCC as reference voltage
  ADMUX |= (1 << REFS0);

  // Set ADC clock prescaler to 64
  ADCSRA |= (1 << ADPS1) | (1 << ADPS2);

  // Enable ADC
  ADCSRA |= (1 << ADEN); /* enable ADC */
}

// Sets up the ADC sleep mode
void setupADCSleepmode(void) {
  set_sleep_mode(SLEEP_MODE_ADC); /* defined in avr/sleep.h */
  ADCSRA |= (1 << ADIE); /* enable ADC interrupt */
  sei(); /* enable global interrupts */
}

EMPTY_INTERRUPT(ADC_vect);

// Uses oversampling to obtain higher-precision sampling
uint16_t oversample16x(void) {
  uint16_t oversampledValue = 0;
  uint8_t i;

  for (i = 0; i < 16; i++) {
    sleep_mode(); /* chip to sleep, takes ADC sample */
    oversampledValue += ADC; /* add them up 16x */
  }
  return (oversampledValue >> 2); /* divide back down by four */
}

// Prints temperatre in the form NNN.NNN
void printTemperature(float number) {
  number = round(number * 1000) / 1000; /* round off to 3 decimal places */

  // Only display hundres place if that digit is not zero
  if ((int) number/100 != 0) {
  // Hundreds place
    transmitByte('0' + number / 100);
  }
  // Tens place
  transmitByte('0' + (number / 10 - floor(number/100)*10));

  // Ones place
  transmitByte('0' + number - 10 * floor(number / 10));

  // Print decimal place
  printString(".");

  // Tenths place
  transmitByte('0' + (number * 10) - floor(number) * 10);

  // Hundredths place
  transmitByte('0' + (number * 100) - floor(number * 10) * 10);

  // Thousandths place
  transmitByte('0' + (number * 1000) - floor(number * 100) * 10);

  printString("\r\n");
}

int main(void) {

  float voltage;
  float tempC;
  float tempF;

  // -------- Inits --------- //
  initUSART();
  printString("\r\nDigital Thermometer\r\n\r\n");
  initADC();
  setupADCSleepmode();

  // ------ Event loop ------ //
  while (1) {
    voltage = oversample16x() * REF_VCC / 4096;

    // Compute temperature in celsius
    tempC = (voltage-TEMP_OFFSET)*100;
    // Print temperature in celsius
    printString("Celsius: ");
    printTemperature(tempC);

    // Compute temperature in fahrenheit
    tempF = ((tempC * 9)/5 + 32);
    // Print temperature in fahrenheit
    printString("Fahrenheit: ");
    printTemperature(tempF);

    // Carriage return
    printString("\r\n");
    _delay_ms(500);
  }
  return (0);
}
