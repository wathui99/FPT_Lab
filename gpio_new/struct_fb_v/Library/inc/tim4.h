#ifndef __TIM4_H
#define __TIM4_H

#include <stdint.h>
#include "mymacro.h"

typedef struct TIM4_struct
{
  volatile uint8_t CR1;   /*!< control register 1 */
  volatile uint8_t CR2;   /*!< control register 2 */
  volatile uint8_t SMCR;  /*!< Synchro mode control register */
  volatile uint8_t DER;   /*!< DMA requests enable register */
  volatile uint8_t IER;   /*!< interrupt enable register  */
  volatile uint8_t SR1;   /*!< status register 1    */
  volatile uint8_t EGR;   /*!< event generation register */
  volatile uint8_t CNTR;  /*!< counter register  */
  volatile uint8_t PSCR;  /*!< prescaler register */
  volatile uint8_t ARR;   /*!< auto-reload register */
}
TIM4_TypeDef;
#define TIM4_BASE                   (uint16_t)0x52E0
#define TIM4                        ((TIM4_TypeDef *) TIM4_BASE)

extern unsigned long int timeCount;
extern uint8_t test;

void Tim4_Init (void);

#endif /* __TIM4_H */