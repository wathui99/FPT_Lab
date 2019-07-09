#include "clk.h"

void Clk_Init(void) {
  /*  Config clock  */
  System_Clock->CKDIVR = (uint8_t)CLK_SYSCLKDiv_32; // pre = 1 
  System_Clock->SWR = (uint8_t)CLK_SYSCLKSource_HSI; //switch to HSI clock
  while (!bit_is_set(System_Clock->ICKCR, 1)) {} //wait util HSI ready
  System_Clock->SWCR |= (uint8_t)(1<<1); // Set SWEN bit in CLK_SWCR to execute switch
  while (System_Clock->SCSR != CLK_SYSCLKSource_HSI) {} //wait util completed change to HSI
}