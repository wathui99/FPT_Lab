#include "clk.h"

void Clk_Init(void) {
  /*  Config clock  */
  System_Clock->CKDIVR = (uint8_t)CLK_SYSCLKDiv_1; // pre = 1
  System_Clock->SWCR |= (uint8_t)0x02; // enable switch clock source
  System_Clock->SWR = (uint8_t)CLK_SYSCLKSource_LSI; //switch to LSI clock
  while (System_Clock->SCSR != CLK_SYSCLKSource_LSI) {} //wait util completed change to LSI
  cbi(System_Clock->ICKCR, 0); //turn off HSI clock
  /* => LSI = 38KHz */
  //System_Clock->PCKENR1 |= (1<<2); //enable clock for tim4
  System_Clock->PCKENR1 |= (1<<5); //enable usart
  System_Clock->PCKENR1 |= (1<<4); //enable clock for SPI
}