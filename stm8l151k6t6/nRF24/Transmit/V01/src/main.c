#include <stdint.h>
#include <intrinsics.h>
#include <string.h>
#include "clk.h"
#include "gpio.h"
#include "itc.h"
#include "exti.h"
#include "tim4.h"
#include "usart.h"
#include "spi.h"
#include "mymacro.h"
#include "nRF24.h"

/* delay ms */
void delay(unsigned long int n);
void USART1_Print_Binary(uint8_t value);

void main (void) {
  GPIO_Init();
  Clk_Init();
  Tim4_Init();
  Itc_Init();
  Exti_Init();
  USART1_Init();
  SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Master, SPI_CPOL_Low, \
           SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);
  SPI_Cmd(ENABLE);
  __enable_interrupt(); //enable global interrupt
  while(1) {
    
  }
}

void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}

void USART1_Print_Binary(uint8_t value) {
  USART1_Send_String("0b ", 3);
  for(int8_t i=7; i>=0; i--) {
    if(bit_is_set(value, i)) {
      USART1_Send_Char('1');
    } else {
      USART1_Send_Char('0');
    }
  }
  USART1_Send_Char('\n');
}

#pragma vector = 10 //8+2
__interrupt void EXTI_Handle_Bit_0 (void) {
  USART1_Send_String("STATUS:\n", 8);
  USART1_Print_Binary(nRF_Get_Status_Reg());
  sbi(EXTI->SR1, 0); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}

