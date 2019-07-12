#ifndef __EXTI_H
#define __EXTI_H

#include "mymacro.h"
#include <stdint.h>

typedef struct EXTI_struct
{
  volatile uint8_t CR1;           /*!<  The four LSB EXTI  pin sensitivity */
  volatile uint8_t CR2;           /*!<  The four MSB EXTI  pin sensitivity */
  volatile uint8_t CR3;           /*!<  EXTI port B & port D sensitivity */
  volatile uint8_t SR1;           /*!<  Pins Status flag register 1 */
  volatile uint8_t SR2;           /*!<  Ports Status flage register 2 */
  volatile uint8_t CONF1;         /*!<  Port interrupt selector */
}
EXTI_TypeDef;

#define EXTI_BASE                   (uint16_t)0x50A0
#define EXTI                        ((EXTI_TypeDef *) EXTI_BASE)

void Exti_Init(void);

#endif /* __EXTI_H */