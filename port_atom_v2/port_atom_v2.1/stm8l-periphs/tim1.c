#include "tim1.h"

unsigned long int timeCount_TIM1=0;

void Tim1_Init(void) {
  /* 
  * Auto-reload preload enable
  * only up or down mode
  * up counter
  * Counter is not stopped at update event
  * update from many source
  *  A UEV is generated
  * Counter disable temporary
  */
  TIM1->CR1=0x80;
  /* update interrupt enable */
  sbi(TIM1->IER, 0);
  /* clear Update interrupt flag (auto)*/
  /* reset couter register H and L (auto) */
  /* prescaler = 32000 */
  TIM1->PSCRH = 0x7D; //MSByte first
  TIM1->PSCRL = 0x00;
  /*
  * prescaler = 32000
  * Fsys = 16Mhz
  * Fcnt = 500
  Tovf = 100ms
  => (1/500) * (ARR) = 10ms
  => ARR = 5
  */
  TIM1->ARRH = 0x00;
  TIM1->ARRL = 0x05;
  /* enable tim1 */
  sbi(TIM1->CR1, 0);
}

void Change_Prescaler_Tim1 (uint16_t value) {
  TIM1->PSCRH = (uint8_t)(value>>8); //MSByte first
  TIM1->PSCRL = (uint8_t)(value&0x00FF);
}