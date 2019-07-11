#include <stdint.h>
#include <intrinsics.h>
#include <string.h>
#include "clk.h"
#include "gpio.h"
#include "itc.h"
#include "exti.h"
#include "tim4.h"
#include "usart.h"
#include "lcd.h"

/* delay ms */
void delay(unsigned long int n);

void main (void) {
  GPIO_Init();
  Clk_Init();
  Tim4_Init();
  Itc_Init();
  Exti_Init();
  USART1_Init();
  LCD_Init();
  Lcd_Clear();
  __enable_interrupt(); //enable global interrupt
  while(1) {
    
    USART1_Receive_String_TimeOutReset('.', 10, 2);
    if(strlen(Buff_Receive_USART) > 0) {
      if(strcmp(Buff_Receive_USART, "AGAIN") == 0) {
        Lcd_Print_String("AGAIN", 2);
      }
    }
    
    /*
    USART1_Receive_String_TimeOutReset('.', 10, 2);
    if(strlen(Buff_Receive_USART) > 0) {
      if(strcmp(Buff_Receive_USART, "HELLO") == 0) {
        Lcd_Print_String("HELLO", 2);
      }
    }
    */
  }
}

void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}

#pragma vector = 11 //9+2
__interrupt void EXTI_Handle_Bit_1 (void) {
  Togle_Led_Green();
  
  USART1_Send_String("HELLO", 5);
  Lcd_Clear();
  
  /*
  USART1_Send_String("AGAIN", 5);
  Lcd_Clear();
  */
  sbi(EXTI->SR1, 1); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}

