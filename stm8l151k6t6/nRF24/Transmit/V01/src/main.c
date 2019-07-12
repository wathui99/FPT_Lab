#include <stdint.h>
#include <intrinsics.h>
#include <string.h>
#include "clk.h"
#include "gpio.h"
#include "itc.h"
#include "exti.h"
//#include "tim4.h"
#include "usart.h"
#include "spi.h"
#include "mymacro.h"
#include "nRF24.h"

#define BT0 11
#define BT1 12
#define BT2 13
#define BT3 14

uint8_t payloadRF[2];
uint8_t state[4];

/* delay ms */
//void delay(unsigned long int n);
void USART1_Print_Binary(uint8_t value);

void main (void) {
  state[0]=state[1]=state[2]=state[3]=200;
  GPIO_Init();
  Clk_Init();
  //Tim4_Init();
  Itc_Init();
  Exti_Init();
  USART1_Init();
  SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Master, SPI_CPOL_Low, \
           SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);
  SPI_Cmd(ENABLE);
  
  uint8_t Add_P0[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
  uint8_t Add_P1[5] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
  uint8_t Add_TX[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7};
  
  nRF_Config(nRF_MaskInterrupt_Disable, nRF_CRC_Disable, nRF_Mode_TX, nRF_AA_Pipe_1, \
             nRF_Pipe_Disable, nRF_Add_Width_5Bytes, 0x00, 0x00, \
             0x02, nRF_DataRate_1Mbps, nRF_OutPower_Tx_0dBm, Add_P0, Add_P1, \
             0x02, 0x03, 0x04, 0x05, Add_TX, 0, 0, 0, 0, 0, 0);
  
  __enable_interrupt(); //enable global interrupt
  __halt();
  while(1) {
  }
}

/*
void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}
*/

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
  nRF_Delay(2);
  USART1_Send_String("BT0\n",4);
  
  payloadRF[0]=BT0;
  payloadRF[1]=state[0]=((state[0]==200)?(100):(200));
  User_nRF_Send(payloadRF,2);

  sbi(EXTI->SR1, 0); //clear flag by set this bit
  nRF_Delay(5);
  __halt();
}
#pragma vector = 11 //9+2
__interrupt void EXTI_Handle_Bit_1 (void) {
  nRF_Delay(2);
  USART1_Send_String("BT1\n",4);

  payloadRF[0]=BT1;
  payloadRF[1]=state[1]=((state[1]==200)?(100):(200));
  User_nRF_Send(payloadRF,2);

  sbi(EXTI->SR1, 1); //clear flag by set this bit
  nRF_Delay(5);
  __halt();
}
#pragma vector = 12 //10+2
__interrupt void EXTI_Handle_Bit_2 (void) {
  nRF_Delay(2);
  USART1_Send_String("BT2\n",4);

  payloadRF[0]=BT2;
  payloadRF[1]=state[2]=((state[2]==200)?(100):(200));
  User_nRF_Send(payloadRF,2);

  sbi(EXTI->SR1, 2); //clear flag by set this bit
  nRF_Delay(5);
  __halt();
}
#pragma vector = 13 //11+2
__interrupt void EXTI_Handle_Bit_3 (void) {
  nRF_Delay(2);
  USART1_Send_String("BT3\n",4);

  payloadRF[0]=BT3;
  payloadRF[1]=state[3]=((state[3]==200)?(100):(200));
  User_nRF_Send(payloadRF,2);

  sbi(EXTI->SR1, 3); //clear flag by set this bit
  nRF_Delay(5);
  __halt();
}
/*
#pragma vector=27 //25+2
__interrupt void TIM4_UPD_OVF_TRG_IRQHandler(void) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}
*/

