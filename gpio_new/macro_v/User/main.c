#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim4.h"
#include "mymacro.h"

/**************************Define struct gpio********************************/

#define PE_ODR (*(uint8_t *)((uint16_t)0x5014))
#define PE_IDR (*(uint8_t *)((uint16_t)0x5015))
#define PE_DDR (*(uint8_t *)((uint16_t)0x5016))
#define PE_CR1 (*(uint8_t *)((uint16_t)0x5017))
#define PE_CR2 (*(uint8_t *)((uint16_t)0x5018))

/**************************Define macro********************************/

#define ON (uint8_t)1
#define OFF (uint8_t)0

#define Turn_Led_Green(state) ((state) == (ON) ? (PE_ODR|=(1<<7)) : (PE_ODR&=~(1<<7)))

/**************************Declare function********************************/

void Config_GPIO (void);
void delay(unsigned long int n);

/****************************main function********************************/

int main (void) {
  Config_GPIO();
  Clk_Init();
  Tim4_Init();
  __enable_interrupt(); //enable global interrupt
  while(1) {
    delay(1000);
    Turn_Led_Green(OFF);
    delay(1000);
    Turn_Led_Green(ON);
  }
}

/**************************Define function********************************/

void Config_GPIO (void) {
  /* led green */
  sbi(PE_DDR, 7); //output mode
  sbi(PE_CR1, 7); //push-pull(1), open-drain(0)
  sbi(PE_CR2, 7); //high speed output(10Mhz)(1), low speed(0)(2Mhz)
  cbi(PE_ODR, 7); //reset state
}

void delay(unsigned long int n) {
  timeCount = 0;
  while (timeCount != n) {};
}
