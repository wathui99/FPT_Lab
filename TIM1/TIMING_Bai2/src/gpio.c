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
  /* led green */
  sbi(GPIOE->DDR, 7); //output mode
  sbi(GPIOE->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOE->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOE->ODR, 7); //reset state
  /* led blue */
  sbi(GPIOC->DDR, 7); //output mode
  sbi(GPIOC->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOC->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOC->ODR, 7); //reset state
  /* user button */
  cbi(GPIOC->DDR, 1); //input mode
  cbi(GPIOC->CR1, 1); //floating(0), pull-up(1)
  sbi(GPIOC->CR2, 1); //interrupt en(1), interrupt dis(0)
  /* GPIOF -> btn2 */
  cbi(GPIOF->DDR, 0); //input mode
  sbi(GPIOF->CR1, 0); //floating(0), pull-up(1)
  sbi(GPIOF->CR2, 0); //interrupt en(1), interrupt dis(0)
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