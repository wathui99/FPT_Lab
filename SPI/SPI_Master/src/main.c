#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim4.h"
#include "lcd.h"
#include "gpio.h"
#include "exti.h"
#include "itc.h"
#include "spi.h"

uint8_t ch = 'A';

/* delay ms */
void delay(unsigned long int n);

void main (void) {
  Clk_Init();
  GPIO_Init();
  Itc_Init();
  Exti_Init();
  Tim4_Init();
  LCD_Init();
  SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Master, SPI_CPOL_Low, \
           SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);
  SPI->CR3 |= (1<<6);
  SPI_Cmd(ENABLE);
  __enable_interrupt(); //enable global interrupt
  while(1) {
  }
}


void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}

#pragma vector = 11 //9+2
__interrupt void EXTI_Handle_Bit_1 (void) {
  if(ch>90) ch='A';
  Lcd_Print_Char(ch, 1);
  SPI_Transfer(ch++);
  sbi(EXTI->SR1, 1); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}
#pragma vector=28 //25+2
__interrupt void SPI_Receive_IRQ(void) {
  uint8_t data_read = SPI->DR;
  Lcd_Print_Char(data_read, 2);
}

