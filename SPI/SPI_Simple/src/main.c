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
  SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Master, SPI_CPOL_Low, \
           SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);
  SPI_Cmd(ENABLE);
  __enable_interrupt(); //enable global interrupt
  uint8_t i=0;
  while(1) {
    SPI_Transfer(i);
    delay(100);
    i++;
    if(i==90) i=0;
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
  //LCD_Clear_Digits();
  SPI_Transfer(count);
  delay(100);
  sbi(EXTI->SR1, 1); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}
