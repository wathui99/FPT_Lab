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
 
typedef struct Timer1
{
  uint8_t CR1;   /*!< control register 1 */
  uint8_t CR2;   /*!< control register 2 */
  uint8_t SMCR;  /*!< Synchro mode control register */
  uint8_t ETR;   /*!< external trigger register */
  uint8_t DER;   /*!< DMA requests enable register */
  uint8_t IER;   /*!< interrupt enable register*/
  uint8_t SR1;   /*!< status register 1 */
  uint8_t SR2;   /*!< status register 2 */
  uint8_t EGR;   /*!< event generation register */
  uint8_t CCMR1; /*!< CC mode register 1 */
  uint8_t CCMR2; /*!< CC mode register 2 */
  uint8_t CCMR3; /*!< CC mode register 3 */
  uint8_t CCMR4; /*!< CC mode register 4 */
  uint8_t CCER1; /*!< CC enable register 1 */
  uint8_t CCER2; /*!< CC enable register 2 */
  uint8_t CNTRH; /*!< counter high */
  uint8_t CNTRL; /*!< counter low */
  uint8_t PSCRH; /*!< prescaler high */
  uint8_t PSCRL; /*!< prescaler low */
  uint8_t ARRH;  /*!< auto-reload register high */
  uint8_t ARRL;  /*!< auto-reload register low */
  uint8_t RCR;   /*!< Repetition Counter register */
  uint8_t CCR1H; /*!< capture/compare register 1 high */
  uint8_t CCR1L; /*!< capture/compare register 1 low */
  uint8_t CCR2H; /*!< capture/compare register 2 high */
  uint8_t CCR2L; /*!< capture/compare register 2 low */
  uint8_t CCR3H; /*!< capture/compare register 3 high */
  uint8_t CCR3L; /*!< capture/compare register 3 low */
  uint8_t CCR4H; /*!< capture/compare register 3 high */
  uint8_t CCR4L; /*!< capture/compare register 3 low */
  uint8_t BKR;   /*!< Break Register */
  uint8_t DTR;   /*!< dead-time register */
  uint8_t OISR;  /*!< Output idle register */
  uint8_t DCR1;  /*!< DMA control register 1 */
  uint8_t DCR2;  /*!< DMA control register 2 */
  uint8_t DMAR;  /*!< DMA Address for brust mode */
}TIM1Reg;

#define TIM1            ((TIM1Reg *) 0x52B0)

void Quantumn_time_RoundRobin_10ms();

#endif