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
  
  uint8_t Add_P0[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
  uint8_t Add_P1[5] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
  uint8_t Add_TX[5] = {0x11, 0x11, 0x11, 0x11, 0x11};
  
  nRF_Config(nRF_MaskInterrupt_Disable, nRF_CRC_1Byte, nRF_Mode_RX, nRF_AA_Pipe_1, \
             nRF_EN_Pipe_1 | nRF_EN_Pipe_4, nRF_Add_Width_5Bytes, 0x02, 0x0F, \
             0x04, nRF_DataRate_1Mbps, nRF_OutPower_Tx_m6dBm, Add_P0, Add_P1, \
             0x02, 0x03, 0x04, 0x05, Add_TX, 10, 11, 12, 13, 14, 15);
  
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
  USART1_Send_String("REG:\n", 5);
  USART1_Print_Binary(nRF_Read_One_Reg(RX_PW_P4));
  sbi(EXTI->SR1, 0); //clear flag by set this bit
}
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}

