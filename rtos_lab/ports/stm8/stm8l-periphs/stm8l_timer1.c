#include "stm8l_timer1.h"

void Quantumn_time_RoundRobin_10ms()
{
  TIM1->PSCRH = 0x00;
  TIM1->PSCRL = 0x02;
  TIM1->IER = 0x01;
  TIM1->CR1 = 0x01; 
  TIM1->ARRH = 0xd0;       //d0
  TIM1->ARRL = 0xf9;       //f9
}