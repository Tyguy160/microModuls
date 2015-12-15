#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "organ.h"
#include "scale.h"

#define SPEAKER PD6
#define SPEAKER_DDR DDRD
#define ASCII_OFFSET 48
#define NOTE_LENGTH 16000
int main(void) {


  const uint16_t keyboard[] = {
    C4, Cx4, D4, Dx4, E4, F4,	Fx4, G4, Gx4, A4, Ax4, B4
  };

  uint8_t key;
  uint8_t newKey;
  // -------- Inits --------- //
  SPEAKER_DDR |= (1 << SPEAKER);                 /* speaker for output */
  initUSART();
  printString("Welcome to the Digital Keyboard!\r\n");
  printString("Press a key from the number now to get started!\r\n");
  // while (nameLength == 48) {
  //  nameLength += receiveByte();
  // }
  //char serialCharacter[nameLength];

  // ------ Event loop ------ //
  while (1) {
    key = receiveByte();
    switch (key) {
      case 1+ASCII_OFFSET:
        playNote(keyboard[0],NOTE_LENGTH);
        break;
      case 2+ASCII_OFFSET:
        playNote(keyboard[1],NOTE_LENGTH);
        break;
      case 3+ASCII_OFFSET:
        playNote(keyboard[2],NOTE_LENGTH);
        break;
      case 4+ASCII_OFFSET:
        playNote(keyboard[3],NOTE_LENGTH);
        break;
      case 5+ASCII_OFFSET:
        playNote(keyboard[4],NOTE_LENGTH);
        break;
      case 6+ASCII_OFFSET:
        playNote(keyboard[5],NOTE_LENGTH);
        break;
      case 7+ASCII_OFFSET:
        playNote(keyboard[6],NOTE_LENGTH);
        break;
      case 8+ASCII_OFFSET:
        playNote(keyboard[7],NOTE_LENGTH);
        break;
      case 9+ASCII_OFFSET:
        playNote(keyboard[8],NOTE_LENGTH);
        break;
      case ASCII_OFFSET: // Zero key
        playNote(keyboard[9],NOTE_LENGTH);
        break;
      case (ASCII_OFFSET-3): // Minus key
        playNote(keyboard[10],NOTE_LENGTH);
        break;
      case (ASCII_OFFSET+13): // Plus key
        playNote(keyboard[11],NOTE_LENGTH);
        break;

    }
    //transmitByte(key);
  }
  return 0;
}
