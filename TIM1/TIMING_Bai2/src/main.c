#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "gpio.h"
#include "itc.h"
#include "exti.h"
#include "tim1.h"

uint16_t currentPrescaler = 32000;

/*delay in 100ms/val*/
void delay_TIM1(unsigned long int value);

void main (void) {
  GPIO_Init();
  Clk_Init();
  Tim1_Init();
  Itc_Init();
  Exti_Init();
  __enable_interrupt(); //enable global interrupt
  while(1) {
  }
}

void delay_TIM1(unsigned long int value) {
  timeCount_TIM1=0;
  while(timeCount_TIM1<value) {}
}

/*User btn -> reduce prescaler (increase time) min=1*/
#pragma vector = 10 //8+2
__interrupt void EXTI_Handle_Bit_0 (void) {
  if(currentPrescaler > 1) {
    switch(currentPrescaler) {
    case 64000:
      currentPrescaler=32000;
      break;
    case 32000:
      currentPrescaler=16000;
      break;
    case 16000:
      currentPrescaler=8000;
      break;
    case 8000:
      currentPrescaler=4000;
      break;
    case 4000:
      currentPrescaler=2000;
      break;
    case 2000:
      currentPrescaler=1000;
      break;
    }
    Change_Prescaler_Tim1(currentPrescaler);
  }
  delay_TIM1(2);
  sbi(EXTI->SR1, 0); //clear flag by set this bit
}

/*User btn -> increase prescaler (reduce time) max=64000*/
#pragma vector = 11 //9+2
__interrupt void EXTI_Handle_Bit_1 (void) {
  if(currentPrescaler < 64000) {
    switch(currentPrescaler) {
    case 32000:
      currentPrescaler=64000;
      break;
    case 16000:
      currentPrescaler=32000;
      break;
    case 8000:
      currentPrescaler=16000;
      break;
    case 4000:
      currentPrescaler=8000;
      break;
    case 2000:
      currentPrescaler=4000;
      break;
    case 1000:
      currentPrescaler=2000;
      break;
    }
    Change_Prescaler_Tim1(currentPrescaler);
  }
  delay_TIM1(2);
  sbi(EXTI->SR1, 1); //clear flag by set this bit
}

#pragma vector = 25 //23+2
__interrupt void TIM1_Update (void) {
  timeCount_TIM1++;
  Togle_Led_Green();
  cbi(TIM1->SR1, 0); //clear UIF flag
}

