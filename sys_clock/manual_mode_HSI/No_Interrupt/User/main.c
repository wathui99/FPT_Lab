#include "clk.h"
#include "gpio.h"
#include <stdint.h>

void delay(unsigned long int n) {
  while(n-- != 0);
}

int main (void) {
  Clk_Init();
  GPIO_Init();
  while(1) {
    delay(500);
    Togle_Led_Green();
  }
}