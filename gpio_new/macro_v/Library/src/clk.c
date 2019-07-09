#include <stdint.h>
#include "clk.h"

void Clk_Init(void) {
  /*  Config clock  */
  System_Clock->CKDIVR = (uint8_t)0x00; // pre = 1
  System_Clock->SWCR|=(uint8_t)0x02; // enable switch clock source
  System_Clock->SWR = (uint8_t)0x01; //switch to HSI clock
  while (System_Clock->SCSR != 0x01) {} //wait util completed change to HSI
  System_Clock->PCKENR1 |= (1<<2); //enable clock for tim4
}