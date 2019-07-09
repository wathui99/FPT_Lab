#include <stdint.h>

/************************************user macro********************************/
//clear and set bit
#define sbi(port,bit) \
	(port) |= (1 << (bit))
#define cbi(port,bit) \
	(port) &= ~(1 << (bit))
//check bit
#define bit_is_set(sfr,bit) \
	((uint8_t)sfr & (uint8_t)(1<<bit)) 

/************************************system define********************************/
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
#define GPIOC_BASE                  (uint16_t)0x500A

#define GPIOE                       ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOC                       ((GPIO_TypeDef *) GPIOC_BASE)

#define GPIO_Pin_7                  (uint8_t)0x80
#define GPIO_Pin_1                  (uint8_t)0x02

/************************************user define********************************/
#define Led_Green 7
#define Led_Blue 7
#define Btn 1
#define TRUE 1
#define FALSE 0

#define b  (*(uint8_t*)0x0005);

void delay(unsigned long int n) {
  while (n--) {};
}

int main (void) {
  //led green
  sbi(GPIOE->DDR, 7); //output mode
  sbi(GPIOE->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOE->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOE->ODR, 7); //reset state
  //led blue
  sbi(GPIOC->DDR, 7); //output mode
  sbi(GPIOC->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOC->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOC->ODR, 7); //reset state
  //usr button
  cbi(GPIOC->DDR, 1); //input mode
  cbi(GPIOC->CR1, 1); //floating(0), pull-up(1)
  cbi(GPIOC->CR2, 1); //interrupt en(1), interrupt dis(0)
  while(1) {
    if(!bit_is_set(GPIOC->IDR, Btn)) { //btn press
      uint8_t checkShort = FALSE;
      unsigned int timeCheck=100000; //define the time for long press
      while(timeCheck--) {
        if(bit_is_set(GPIOC->IDR, Btn)) { //btn release
          checkShort = TRUE;
          break;
        }
      }
      if(checkShort) { //short press
        sbi(GPIOC->ODR, Led_Blue);
        delay(20000);
        cbi(GPIOC->ODR, Led_Blue);
        delay(10000);
      } else { //long press
        sbi(GPIOE->ODR, Led_Green);
        delay(20000);
        cbi(GPIOE->ODR, Led_Green);
        delay(10000);
      }
    }
  }
  return 0;
}