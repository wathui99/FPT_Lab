#include "timer1.h"
#include <timer1.h>

void Quantumn_time_RoundRobin_10ms()
{
  TIM1->TIM1_PSCRH = 0x00;
  TIM1->TIM1_PSCRL = 0x02;
  
  TIM1->TIM1_IER = 0x01;
  TIM1->TIM1_CR1 = 0x01;
  
  TIM1->TIM1_ARRH = 0xd0;
  TIM1->TIM1_ARRL = 0xf9;
}

// Interrupt of TIM1 is 23 + 2 (REST and TRAP)
