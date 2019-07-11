#include "exti.h"

void Exti_Init() {
  /* mode exti 
  * portc bit 1 selected
  * falling edge
  */
  sbi(EXTI->CR1, 1);
  cbi(EXTI->CR1, 0);
}