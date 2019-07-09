#include "exti.h"

void Exti_Init() {
  /* mode exti 
  * portc bit 1 selected
  * falling edge
  */
  //bit 1
  sbi(EXTI->CR1, 3);
  cbi(EXTI->CR1, 2);
  //bit 0
  sbi(EXTI->CR1, 1);
  cbi(EXTI->CR1, 0);
}