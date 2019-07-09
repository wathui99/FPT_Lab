#include "clk.h"

void Clk_Init(void) {
  /*  Config clock  */
  System_Clock->CKDIVR = (uint8_t)CLK_SYSCLKDiv_1; // pre = 1
  System_Clock->SWCR |= (uint8_t)0x02; // enable switch clock source
  System_Clock->SWR = (uint8_t)CLK_SYSCLKSource_HSI; //switch to HSI clock
  while (System_Clock->SCSR != CLK_SYSCLKSource_HSI) {} //wait util completed change to HSI
  /* Config RTC clock */
  System_Clock->CRTCR &= (uint8_t)0x01;
  System_Clock->CRTCR |= (uint8_t)0x10; //RCT clock source/1, LSE
  while (bit_is_set(System_Clock->CRTCR, 0)) {} //wait until RTC change completed
  /* LCD clock
  * clock lcd = 16.384 kHz
  */ 
  System_Clock->PCKENR2 |= (1<<3); //enable clock for lcd
  System_Clock->PCKENR2 |= (1<<1); //enable tim1
}