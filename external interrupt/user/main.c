#include <stdint.h>
#include <intrinsics.h>

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

#define STRINGVECTOR(x) #x
#define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
#define INTERRUPT_HANDLER( a, b )  \
_Pragma( VECTOR_ID( (b)+2 ) )        \
__interrupt void (a)( void )




#define INTERRUPT_HANDLER_TRAP(a) \
_Pragma( VECTOR_ID( 1 ) ) \
__interrupt void (a) (void)

#define INTERRUPT __interrupt
INTERRUPT void EXTI1_IRQHandler(void); /* EXTI PIN1 */


/************************************user define********************************/
#define Led_Green 7
#define Led_Blue 7
#define Btn 1
#define TRUE 1
#define FALSE 0

void delay(unsigned long int n) {
  while (n--) {};
}

int main (void) {
  //led blue
  sbi(GPIOC->DDR, 7); //output mode
  sbi(GPIOC->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOC->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOC->ODR, 7); //reset state
  //usr button
  cbi(GPIOC->DDR, 1); //input mode
  cbi(GPIOC->CR1, 1); //floating(0), pull-up(1)
  sbi(GPIOC->CR2, 1); //interrupt en(1), interrupt dis(0)
  //conf mode interrupt
  sbi(*(uint8_t*)(0x50A0), 3);
  cbi(*(uint8_t*)(0x50A0), 2);
  __enable_interrupt();
  
  while(1) {
  }
  return 0;
}

INTERRUPT_HANDLER(EXTI1_IRQHandler, 9)
{
  if(!bit_is_set(GPIOC->IDR, 1)) { //check again
    sbi(GPIOC->ODR, 7);
    delay(50000);
    cbi(GPIOC->ODR, 7);
    delay(50000);
  }
  cbi(*(uint8_t*)(0x0050A3), 1); //clear flag
}