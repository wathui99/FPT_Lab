#include "gpio.h"

/*   example devices on board
  * led green
  GPIOE->DDR.DDR7 = ON; //output mode
  GPIOE->CR1.CR17 = ON; //push-pull(1), open-drain(0)
  GPIOE->CR2.CR27 = ON; //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  GPIOE->ODR.ODR7 = OFF; //reset state
  * led blue
  GPIOC->DDR.DDR7 = ON; //output mode
  GPIOC->CR1.CR17 = ON; //push-pull(1), open-drain(0)
  GPIOC->CR2.CR27 = ON; //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  GPIOC->ODR.ODR7 = OFF; //reset state
  * user button
  GPIOC->DDR.DDR1 = OFF; //input mode
  GPIOC->CR1.CR11 = OFF; //floating(0), pull-up(1)
  GPIOC->CR2.CR21 = OFF; //interrupt en(1), interrupt dis(0)
*/

void GPIO_Init() {
  /* user button */
  cbi(GPIOC->DDR, 1); //input mode
  cbi(GPIOC->CR1, 1); //floating(0), pull-up(1)
  sbi(GPIOC->CR2, 1); //interrupt en(1), interrupt dis(0)
  /* SPI Init GPIO */
  sbi(GPIOB->DDR, 6);   // PA6 - MOSI - OUTPUT
  sbi(GPIOB->CR1, 6);   // push-pull
  sbi(GPIOB->CR2, 6);   // fast
  
  cbi(GPIOB->DDR, 7);   // PA2 - MISO - INPUT
  sbi(GPIOB->CR1, 7);   // pull-up
  cbi(GPIOB->CR2, 7);   // disable interrupt
  
  sbi(GPIOB->DDR, 5);   // PC6 - SCK - OUTPUT
  sbi(GPIOB->CR1, 5);   // push-pull
  sbi(GPIOB->CR2, 5);   // fast mode
  cbi(GPIOB->ODR, 5);   // pull low SCK
  
  sbi(GPIOB->DDR, 4);   // PE7 - NSS - OUTPUT
  sbi(GPIOB->CR1, 4);   // push-pull
  sbi(GPIOB->CR2, 4);   // high
  sbi(GPIOB->ODR, 4);   // pull high
}
void GPIO_Write_Bit(GPIO_TypeDef *GPIO, uint8_t bit, uint8_t state) {
	if(state == ON) {
		sbi(GPIO->ODR, bit);
	} else {
		cbi(GPIO->ODR, bit);
	}
}
void GPIO_Write(GPIO_TypeDef *GPIO, uint8_t value) {
	GPIO->ODR = value;
}
uint8_t GPIO_Read_Bit(GPIO_TypeDef *GPIO, uint8_t bit) {
	return ( (GPIO->IDR &= (1<<bit)) ? (ON) : (OFF) );
}
uint8_t GPIO_Read(GPIO_TypeDef *GPIO) {
	return GPIO->IDR;
}