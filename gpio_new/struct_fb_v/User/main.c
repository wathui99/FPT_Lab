#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim4.h"
#include "mymacro.h"

/**************************Define struct gpio********************************/
typedef struct GPIO_ODR_struct
{
  uint8_t ODR0 :1;
  uint8_t ODR1 :1;
  uint8_t ODR2 :1;
  uint8_t ODR3 :1;
  uint8_t ODR4 :1;
  uint8_t ODR5 :1;
  uint8_t ODR6 :1;
  uint8_t ODR7 :1;
}
GPIO_ODR_TypeDef;
typedef struct GPIO_IDR_struct
{
  uint8_t IDR0 :1;
  uint8_t IDR1 :1;
  uint8_t IDR2 :1;
  uint8_t IDR3 :1;
  uint8_t IDR4 :1;
  uint8_t IDR5 :1;
  uint8_t IDR6 :1;
  uint8_t IDR7 :1;
}
GPIO_IDR_TypeDef;
typedef struct GPIO_DDR_struct
{
  uint8_t DDR0 :1;
  uint8_t DDR1 :1;
  uint8_t DDR2 :1;
  uint8_t DDR3 :1;
  uint8_t DDR4 :1;
  uint8_t DDR5 :1;
  uint8_t DDR6 :1;
  uint8_t DDR7 :1;
}
GPIO_DDR_TypeDef;
typedef struct GPIO_CR1_struct
{
  uint8_t CR10 :1;
  uint8_t CR11 :1;
  uint8_t CR12 :1;
  uint8_t CR13 :1;
  uint8_t CR14 :1;
  uint8_t CR15 :1;
  uint8_t CR16 :1;
  uint8_t CR17 :1;
}
GPIO_CR1_TypeDef;
typedef struct GPIO_CR2_struct
{
  uint8_t CR20 :1;
  uint8_t CR21 :1;
  uint8_t CR22 :1;
  uint8_t CR23 :1;
  uint8_t CR24 :1;
  uint8_t CR25 :1;
  uint8_t CR26 :1;
  uint8_t CR27 :1;
}
GPIO_CR2_TypeDef;
typedef struct GPIO_struct
{
  GPIO_ODR_TypeDef ODR; /*!< Output Data Register */
  GPIO_IDR_TypeDef IDR; /*!< Input Data Register */
  GPIO_DDR_TypeDef DDR; /*!< Data Direction Register */
  GPIO_CR1_TypeDef CR1; /*!< Configuration Register 1 */
  GPIO_CR2_TypeDef CR2; /*!< Configuration Register 2 */
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
          ((GPIOE->ODR.ODR7==ON) ? (GPIOE->ODR.ODR7=OFF) : (GPIOE->ODR.ODR7=ON))
#define Turn_Led_Green(state) \
          ((state) == (ON) ? (GPIOE->ODR.ODR7=ON) : (GPIOE->ODR.ODR7=OFF))
#define Togle_Led_Blue() \
          ((GPIOC->ODR.ODR7==ON) ? (GPIOC->ODR.ODR7=OFF) : (GPIOC->ODR.ODR7=ON))
#define Turn_Led_Blue(state) \
          ((state) == (ON) ? (GPIOC->ODR.ODR7=ON) : (GPIOC->ODR.ODR7=OFF))
#define Check_Btn()  \
                   ((GPIOC->IDR.IDR1==ON) ? (UNPRESS) : (PRESS))
                 
#define GREEN 0
#define BLUE 1
uint8_t turn = GREEN;

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
    //check btn change turn
    if(Check_Btn() == PRESS) {
      delay(10);
      if(Check_Btn() == PRESS) {
        while(Check_Btn() == PRESS);
        turn = (turn==GREEN) ? (BLUE) : (GREEN);
      }
    }
    //enforce state
    if(turn == GREEN) {
      Turn_Led_Blue(OFF);
      Togle_Led_Green();
      delay(100);
    }
    if(turn == BLUE) {
      Turn_Led_Green(OFF);
      Togle_Led_Blue();
      delay(100);
    }
  }
}

/**************************Define function********************************/

void Config_GPIO (void) {
  /* led green */
  GPIOE->DDR.DDR7 = ON; //output mode
  GPIOE->CR1.CR17 = ON; //push-pull(1), open-drain(0)
  GPIOE->CR2.CR27 = ON; //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  GPIOE->ODR.ODR7 = OFF; //reset state
  /* led blue */
  GPIOC->DDR.DDR7 = ON; //output mode
  GPIOC->CR1.CR17 = ON; //push-pull(1), open-drain(0)
  GPIOC->CR2.CR27 = ON; //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  GPIOC->ODR.ODR7 = OFF; //reset state
  /* user button */
  GPIOC->DDR.DDR1 = OFF; //input mode
  GPIOC->CR1.CR11 = OFF; //floating(0), pull-up(1)
  GPIOC->CR2.CR21 = OFF; //interrupt en(1), interrupt dis(0)
}

void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}