#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim4.h"
#include "mymacro.h"

/**************************Define struct gpio********************************/

typedef struct GPIO_struct
{
  volatile uint8_t ODR; /*!< Output Data Register */
  volatile uint8_t IDR; /*!< Input Data Register */
  volatile uint8_t DDR; /*!< Data Direction Register */
  volatile uint8_t CR1; /*!< Configuration Register 1 */
  volatile uint8_t CR2; /*!< Configuration Register 2 */
}
GPIO_TypeDef;
#define GPIOE_BASE                  (uint16_t)0x5014
#define GPIOE                       ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOC_BASE                  (uint16_t)0x500A
#define GPIOC                       ((GPIO_TypeDef *) GPIOC_BASE)

/**************************Define macro********************************/

#define ON 1
#define OFF 0
#define PRESS 1
#define UNPRESS 0

#define Togle_Led_Green() \
                 ((GPIOE->ODR&=128) ? (cbi(GPIOE->ODR,7)) : (sbi(GPIOE->ODR,7)))
#define Check_Btn()  \
                   ((bit_is_set(GPIOC->IDR, 1)) ? (UNPRESS) : (PRESS))
                 
/**************************Declare function********************************/
                     
/* config led green and user btn */
void Config_GPIO (void);
/* delay ms */
void delay(unsigned long int n);

/****************************main function********************************/

int main (void) {
  Config_GPIO();
  Clk_Init();
  Tim4_Init();
  __enable_interrupt(); //enable global interrupt
  while(1) {
    if(Check_Btn() == PRESS) {
      delay(10);
      if(Check_Btn() == PRESS) {
        while(Check_Btn() == PRESS);
        Togle_Led_Green();
        delay(1000);
        Togle_Led_Green();
      }
    }
  }
}

/**************************Define function********************************/

void Config_GPIO (void) {
  /* led green */
  sbi(GPIOE->DDR, 7); //output mode
  sbi(GPIOE->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOE->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOE->ODR, 7); //reset state
  /* user button */
  cbi(GPIOC->DDR, 1); //input mode
  cbi(GPIOC->CR1, 1); //floating(0), pull-up(1)
  cbi(GPIOC->CR2, 1); //interrupt en(1), interrupt dis(0)
}

void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}