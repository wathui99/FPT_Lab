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

/********************************system define*********************************/
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

typedef struct CLK_struct
{
  volatile uint8_t CKDIVR;      /*!< Clock Master Divider Register */
  volatile uint8_t CRTCR;  /*!< RTC Clock selection Register */
  volatile uint8_t ICKCR;     /*!< Internal Clocks Control Register */
  volatile uint8_t PCKENR1;  /*!< Peripheral Clock Gating Register 1 */
  volatile uint8_t PCKENR2;  /*!< Peripheral Clock Gating Register 2 */
  volatile uint8_t CCOR;       /*!< Configurable Clock Output Register */
  volatile uint8_t ECKCR;     /*!< External Clocks Control Register */
  volatile uint8_t SCSR;     /*!< System clock status Register */
  volatile uint8_t SWR;      /*!< System clock Switch Register */
  volatile uint8_t SWCR;     /*!< Switch Control Register */
  volatile uint8_t CSSR;     /*!< Clock Security Sytem Register */
  volatile uint8_t CBEEPR;     /*!< Clock BEEP Register */
  volatile uint8_t HSICALR;     /*!< HSI Calibration Register */
  volatile uint8_t HSITRIMR; /*!< HSI clock Calibration Trimmer Register */
  volatile uint8_t HSIUNLCKR; /*!< HSI Unlock  Register */
  volatile uint8_t REGCSR;  /*!< Main regulator control status register */
  volatile uint8_t PCKENR3;  /*!< Peripheral Clock Gating Register 3 */
}
CLK_TypeDef;
#define System_Clock_BASE                    (uint16_t)0x50C0
#define System_Clock                         ((CLK_TypeDef *) System_Clock_BASE)
#define CLK_SYSCLKDiv_1      (uint8_t)0x00   /*!< Time base Prescaler = 2^0 */
#define CLK_SYSCLKSource_HSI   (uint8_t)0x01   /*!< System Clock Source HSI */

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
#define TIM4_Pre_64    (uint8_t)0x06

#define STRINGVECTOR(x) #x
#define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
#define INTERRUPT_HANDLER( a, b )  \
_Pragma( VECTOR_ID( (b)+2 ) )        \
__interrupt void (a)( void )

#define INTERRUPT __interrupt
INTERRUPT void TIM4_UPD_OVF_TRG_IRQHandler(void); /* TIM4 UPDATE,OF,TRIG */

/************************************user define*******************************/
#define Led_Green 7
#define Led_Blue 7
#define Btn 1
#define TRUE 1
#define FALSE 0
volatile unsigned long int timeCount=0;
void delay(unsigned long int n);

int main(void) {
  /*  Config clock  */
  System_Clock->CKDIVR = CLK_SYSCLKDiv_1; // clk/1
  System_Clock->SWCR|=(uint8_t)0x02; // enable switch clock source
  System_Clock->SWR = CLK_SYSCLKSource_HSI; //switch to HSI clock
  while (System_Clock->SCSR != CLK_SYSCLKSource_HSI) {} //wait util complete
  System_Clock->PCKENR1 |= (1<<2); //enable clock for tim4
  /* led green */
  sbi(GPIOE->DDR, 7); //output mode
  sbi(GPIOE->CR1, 7); //push-pull(1), open-drain(0)
  sbi(GPIOE->CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(GPIOE->ODR, 7); //reset state
  /*
  **Config timer4
  * f = f_clk/prescale = 16Mhz/64
  * T=0.001 => TOP=250-1
  */
  TIM4->PSCR = TIM4_Pre_64; //prescaler = 64
  TIM4->ARR = 249; //auto reload value
  TIM4->EGR = 0x01; //generate update event -> reload counter
  cbi(TIM4->SR1, 0); //clear interrupt flag
  TIM4->IER |= (1<<0); //enable interrupt update
  TIM4->CR1 |= (1<<0); //enable timer4
  __enable_interrupt(); //enable global interrupt
  while(1){
    delay(500);
    sbi(GPIOE->ODR, 7);
    delay(500);
    cbi(GPIOE->ODR, 7);
  }
  return 0;
}

void delay(unsigned long int n) {
  timeCount=0;
  while(timeCount != n) {};
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler, 25) {
  timeCount++;
  cbi(TIM4->SR1, 0); //clear update interrupt flag
}