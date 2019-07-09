#include "usart.h"

char Buff_Receive_USART[200];

void USART1_Init(void) {
  /* 1 start bit, 8 data bits */
  cbi(USART1->CR1, 4);
  /* 1 stop bit */
  USART1->CR3 = 0x00;
  /* 
  * baud rate, see config in page 533 reference manual 
  * Fsysclk = 16MHz
  */
  USART1->BRR2 = 0x03;
  USART1->BRR1 = 0x68;
  /*
  * enable transmitter
  * enable receiver
  */
  sbi(USART1->CR2, 2);
  sbi(USART1->CR2, 3);
}
/* send each character */
void USART1_Send_Char(char value) {
  while(!bit_is_set(USART1->SR, 7)) {} //wait until SDR empty -> able write to USART_DR without overwrite old data
  USART1->DR = value;
}
/* send string */
void USART1_Send_String(char *Str, uint8_t leng) {
  for (uint8_t i=0; i<leng; i++) {
    USART1_Send_Char(*(Str+i));
  }
  while(!bit_is_set(USART1->SR, 6)) {} //wait until last data shift-out completly
}
/*
* receive each char
* return RECEIVE_FAIL or !RECEIVE_FAIL
* new data receive will store in ch
*/
uint8_t USART1_Receive_Char(char *ch) {
  if(!bit_is_set(USART1->SR, 5)) return RECEIVE_FAIL;
  *ch=(char)USART1->DR;
  return !RECEIVE_FAIL;
}
/*
* receive string uart until see charDelim or reach enough leng
* new data string will store in Buff_Receive_USART
* <! leng least than 255
*/
void USART1_Receive_String(char charDelim, uint8_t leng) {
  uint8_t iLeng=0;
  char receiveChar=0x00;
  while(iLeng<leng) {
    if(USART1_Receive_Char(&receiveChar)==!(RECEIVE_FAIL)) {
      if(receiveChar==charDelim) {
        Buff_Receive_USART[iLeng]=0x00; //end of string
        return;
      } else {
        Buff_Receive_USART[iLeng++]=receiveChar;
      }
    }
  }
  Buff_Receive_USART[iLeng]=0x00;
}
/*
* receive string uart until see charDelim or reach enough leng or Timeout
* new data string will store in Buff_Receive_USART
<!need to provice an up-countable variable (timeCount)
*/
void USART1_Receive_String_TimeOut(char charDelim, uint8_t leng, unsigned long int timeOut) {
  uint8_t iLeng=0;
  char receiveChar=0x00;
  timeCount_TIM4=0;
  while(iLeng<leng && timeCount_TIM4<=timeOut) {
    if(USART1_Receive_Char(&receiveChar)==!(RECEIVE_FAIL)) {
      if(receiveChar==charDelim) {
        Buff_Receive_USART[iLeng]=0x00; //end of string
        return;
      } else {
        Buff_Receive_USART[iLeng++]=receiveChar;
      }
    }
  }
  Buff_Receive_USART[iLeng]=0x00;
}
/*
* receive string uart until see charDelim || reach enough leng || Time out
* new data string will store in Buff_Receive_USART
<!need to provice an up-countable variable (timeCount)
<!It will reset the timeCount everytime it receive new character, be carefull with timeOut
*/
void USART1_Receive_String_TimeOutReset(char charDelim, uint8_t leng, unsigned long int timeOut) {
  uint8_t iLeng=0;
  char receiveChar=0x00;
  timeCount_TIM4=0;
  while(iLeng<leng && timeCount_TIM4<=timeOut) {
    if(USART1_Receive_Char(&receiveChar)==!(RECEIVE_FAIL)) {
      timeCount_TIM4=0;
      if(receiveChar==charDelim) {
        Buff_Receive_USART[iLeng]=0x00; //end of string
        return;
      } else {
        Buff_Receive_USART[iLeng++]=receiveChar;
      }
    }
  }
  Buff_Receive_USART[iLeng]=0x00;
}