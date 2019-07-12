#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include "mymacro.h"

/************************GPIO struct*************************/

typedef struct GPIO_struct
{
  volatile uint8_t ODR; /*!< Output Data Register */
  volatile uint8_t IDR; /*!< Input Data Register */
  volatile uint8_t DDR; /*!< Data Direction Register */
  volatile uint8_t CR1; /*!< Configuration Register 1 */
  volatile uint8_t CR2; /*!< Configuration Register 2 */
}
GPIO_TypeDef;

#define GPIOA_BASE                  (uint16_t)0x5000
#define GPIOB_BASE                  (uint16_t)0x5005
#define GPIOC_BASE                  (uint16_t)0x500A
#define GPIOD_BASE                  (uint16_t)0x500F
#define GPIOE_BASE                  (uint16_t)0x5014
#define GPIOF_BASE                  (uint16_t)0x5019

#define GPIOA                       ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                       ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                       ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD                       ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE                       ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF                       ((GPIO_TypeDef *) GPIOF_BASE)

/**************************define option value************************/

#define ON 1
#define OFF 0
#define PRESS 1
#define UNPRESS 0

/***********************define macro onboard**************************/

#define Togle_Led_Green() \
          ((bit_is_set(GPIOE->ODR, 7)) ? (cbi(GPIOE->ODR, 7)) : (sbi(GPIOE->ODR, 7)))
#define Turn_Led_Green(state) \
          ((state) == (ON) ? (sbi(GPIOE->ODR, 7)) : (cbi(GPIOE->ODR, 7)))
#define Togle_Led_Blue() \
          ((bit_is_set(GPIOC->ODR, 7)) ? (cbi(GPIOC->ODR, 7)) : (sbi(GPIOC->ODR, 7)))
#define Turn_Led_Blue(state) \
          ((state) == (ON) ? (sbi(GPIOC->ODR, 7)) : (cbi(GPIOC->ODR, 7)))
#define Check_User_Btn()  \
                   ((GPIOC->IDR&=(1<<1)) ? (UNPRESS) : (PRESS))

/**************************declare function*************************/

void GPIO_Init();
void GPIO_Write_Bit(GPIO_TypeDef *GPIO, uint8_t bit, uint8_t state);
void GPIO_Write(GPIO_TypeDef *GPIO, uint8_t value);
uint8_t GPIO_Read_Bit(GPIO_TypeDef *GPIO, uint8_t bit);
uint8_t GPIO_Read(GPIO_TypeDef *GPIO);

#endif /* __GPIO_H */