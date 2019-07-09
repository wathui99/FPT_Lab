#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim4.h"
#include "lcd.h"
#include "gpio.h"
#include "exti.h"
#include "itc.h"
#include "spi.h"

uint8_t count = 5;

/* delay ms */
void delay(unsigned long int n);
void Print_2_Digits(uint8_t value);

uint8_t dr = 0;

void main (void) {
  Clk_Init();
  GPIO_Init();
  Itc_Init();
  Exti_Init();
  Tim4_Init();
  SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Slave, SPI_CPOL_Low, \
           SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);
  SPI_Cmd(ENABLE);
  __enable_interrupt(); //enable global interrupt
  while(1) {
    if(bit_is_set(SPI->SR, 0)) {
      dr = SPI->DR;
      if(dr == 1) {
        sbi(GPIOE->ODR, 7);
      } else {
        cbi(GPIOE->ODR, 7);
      }
    }
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
  delay(100);
  sbi(EXTI->SR1, 1); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}
