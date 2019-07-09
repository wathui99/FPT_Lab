#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim4.h"
#include "lcd.h"
#include "gpio.h"
#include "exti.h"
#include "itc.h"

uint8_t count = 0;

/* delay ms */
void delay(unsigned long int n);
void Print_2_Digits(uint8_t value);

void main (void) {
  Clk_Init();
  GPIO_Init();
  Itc_Init();
  Exti_Init();
  LCD_Init();
  Tim4_Init();
  __enable_interrupt(); //enable global interrupt
  
  LCD_Clear_Digits();
  Print_2_Digits(count);
  while(1) {
    delay(100);
  }
}

void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}

void Print_2_Digits(uint8_t value) {
  if(value > 99) return;
  LCD_Print_Digits(0, (uint8_t)value/10);
  LCD_Print_Digits(1, (uint8_t)value%10);
}


#pragma vector = 11 //9+2
__interrupt void EXTI_Handle_Bit_1 (void) {
  count++;
  if(count>99) {
    count=0;
  }
  LCD_Clear_Digits();
  Print_2_Digits(count);
  delay(100);
  sbi(EXTI->SR1, 1); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}

