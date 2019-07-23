/**
  ******************************************************************************
  * @author  NguyenTranKha
  * @date    June-2019
  * @course  FGA-UIT training course
  ******************************************************************************
  * @attention
  * I wrote this libary to use in course only.
  * Any problem, please contact me at:
  *        https://github.com/NguyenTranKha
  ******************************************************************************
  */ 

#ifndef __STM8L15x_CLOCK_H
#define __STM8L15x_CLOCK_H

#include "stm8l152c6_clk.h"

//16Mhz
void InitClock_Source(CLK_SYSCLKSource_TypeDef CLK_SYSCLKSource, CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv);
//SystemClock
void InitClock_Timer(void);
//SystemClock
void InitClock_RTC(void);
//SystemClock
void InitClock_LCD_RTC(void);

#endif