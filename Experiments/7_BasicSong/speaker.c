// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale.h"
#include "pinDefines.h"

#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))

int main(void) {
  const uint16_t song[] = {
    C0, Cx0, D0, Dx0, E0, F0,	Fx0, G0, Gx0, A0, Ax0, B0,
    C1, Cx1, D1, Dx1, E1, F1,	Fx1, G1, Gx1, A1, Ax1, B1,
    C2, Cx2, D2, Dx2, E2, F2,	Fx2, G2, Gx2, A2, Ax2, B2,
    C3, Cx3, D3, Dx3, E3, F3,	Fx3, G3, Gx3, A3, Ax3, B3,
    C4, Cx4, D4, Dx4, E4, F4,	Fx4, G4, Gx4, A4, Ax4, B4,
    C5, Cx5, D5, Dx5, E5, F5,	Fx5, G5, Gx5, A5, Ax5, B5,
    C6, Cx6, D6, Dx6, E6, F6,	Fx6, G6, Gx6, A6, Ax6, B6,
    C7, Cx7, D7, Dx7, E7, F7,	Fx7, G7, Gx7, A7, Ax7, B7,
    C8, Cx8, D8, Dx8, E8, F8,	Fx8, G8, Gx8, A8, Ax8, B8,
    B8 ,Ax8 ,A8 ,Gx8 ,G8 ,Fx8	,F8 ,E8 ,Dx8 ,D8 ,Cx8 ,C8,
    B7 ,Ax7 ,A7 ,Gx7 ,G7 ,Fx7	,F7 ,E7 ,Dx7 ,D7 ,Cx7 ,C7,
    B6 ,Ax6 ,A6 ,Gx6 ,G6 ,Fx6	,F6 ,E6 ,Dx6 ,D6 ,Cx6 ,C6,
    B5 ,Ax5 ,A5 ,Gx5 ,G5 ,Fx5	,F5 ,E5 ,Dx5 ,D5 ,Cx5 ,C5,
    B4 ,Ax4 ,A4 ,Gx4 ,G4 ,Fx4	,F4 ,E4 ,Dx4 ,D4 ,Cx4 ,C4,
    B3 ,Ax3 ,A3 ,Gx3 ,G3 ,Fx3	,F3 ,E3 ,Dx3 ,D3 ,Cx3 ,C3,
    B2 ,Ax2 ,A2 ,Gx2 ,G2 ,Fx2	,F2 ,E2 ,Dx2 ,D2 ,Cx2 ,C2,
    B1 ,Ax1 ,A1 ,Gx1 ,G1 ,Fx1	,F1 ,E1 ,Dx1 ,D1 ,Cx1 ,C1,
    B0 ,Ax0 ,A0 ,Gx0 ,G0 ,Fx0	,F0 ,E0 ,Dx0 ,D0 ,Cx0 ,C0
                                                                /* etc */
  };
  /* starting at end b/c routine starts by incrementing and then playing
     this makes the song start at the beginning after reboot */
  uint8_t currentNote = SONG_LENGTH - 1;

  // -------- Inits --------- //
  DDRD |= (1 << SPEAKER);                 /* speaker for output */

  // ------ Event loop ------ //
  while (1) {
        currentNote++;                           /* advance to next note */
        _delay_ms(1000);                          /* but don't run over the end */
        if (currentNote == SONG_LENGTH) {
          currentNote = 0;
        }
      playNote(song[currentNote], 160000);
  }                                                  /* End event loop */
  return (0);
}
