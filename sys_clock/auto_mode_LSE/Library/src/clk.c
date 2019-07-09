#include "clk.h"

void Clk_Init(void) {
  /*  Config clock  */
  //while (bit_is_set(System_Clock->ICKCR, 1)) {}; //wait for HSI ready
  //sbi(System_Clock->ECKCR, 2); //turn on LSE
  //while (bit_is_set(System_Clock->ECKCR, 3)) {}; //wait for LSE ready
  System_Clock->CKDIVR = (uint8_t)CLK_SYSCLKDiv_1; // pre = 1
  System_Clock->SWCR |= (uint8_t)0x02; // enable switch clock source
  System_Clock->SWR = (uint8_t)CLK_SYSCLKSource_LSE; //switch to LSE clock
  while (System_Clock->SCSR != CLK_SYSCLKSource_LSE) {} //wait util completed change to LSE
}