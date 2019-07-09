#include "tim4.h"

unsigned long int timeCount=0;


void Tim4_Init (void) {
  /*
  **Config timer4
  * f = f_clk/prescale = 16Mhz/64
  * T=0.001 => TOP=250-1
  */
  TIM4->PSCR = (uint8_t)0x06; //prescaler = 64
  TIM4->ARR = 249; //auto reload value
  TIM4->EGR = 0x01; //generate update event -> reload counter
  cbi(TIM4->SR1, 0); //clear interrupt flag
  TIM4->IER |= (1<<0); //enable interrupt update
  TIM4->CR1 |= (1<<0); //enable timer4
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler, 25) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}