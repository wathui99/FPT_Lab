/**
  ******************************************************************************
  * @author  NguyenLuongDuyKhanh
  * @date    June-2019
  * @course  FGA-UIT training course
  ******************************************************************************
  * @attention
  * I wrote this libary to use in course only.
  * Any problem, please contact me at:
  *        https://github.com/NguyenLuongDuyKhanh
  ******************************************************************************
  */ 
#ifndef __timer1_h__
#define __timer1_h__

#include <stdint.h>
#include "intrinsics.h"


#define TIM1   ((TIM1Reg*)0x52B0) 
typedef struct Timer1
{
  uint8_t       TIM1_CR1;       //52B0
  uint8_t       TIM1_CR2;
  uint8_t       TIM1_SMCR;
  uint8_t       TIM1_ETR;
  uint8_t       TIM1_DER;
  uint8_t       TIM1_IER;
  uint8_t       TIM1_SR1;
  uint8_t       TIM1_SR2;       //52B7
  
  uint8_t       TIM1_EGR;       //52B8 
  uint8_t       TIM1_CCMR1;
  uint8_t       TIM1_CCMR2;
  uint8_t       TIM1_CCMR3;
  uint8_t       TIM1_CCMR4;
  uint8_t       TIM1_CCER1;
  uint8_t       TIM1_CCER2;
  uint8_t       TIM1_CNTRH;     //52BF
  
  uint8_t       TIM1_CNTRL;     //52C0
  uint8_t       TIM1_PSCRH;
  uint8_t       TIM1_PSCRL;
  uint8_t       TIM1_ARRH;
  uint8_t       TIM1_ARRL;
  uint8_t       TIM1_RCR;
  uint8_t       TIM1_CCR1H;
  uint8_t       TIM1_CCR1L;     //52C7
  
  uint8_t       TIM1_CCR2H;     //52C8
  uint8_t       TIM1_CCR2L;
  uint8_t       TIM1_CCR3H;
  uint8_t       TIM1_CCR3L;
  uint8_t       TIM1_CCR4H;
  uint8_t       TIM1_CCR4L;
  uint8_t       TIM1_BKR;
  uint8_t       TIM1_DTR;       //52CF
  
  uint8_t       TIM1_OISR;      //52D0
  uint8_t       TIM1_DCR1;
  uint8_t       TIM1_DCR2;
  uint8_t       TIM1_DMA1R;     //52D3
}TIM1Reg;

void Quantumn_time_RoundRobin_10ms();

#endif