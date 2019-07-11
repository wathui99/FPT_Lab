#include "itc.h"

void Itc_Init(void) {
  /* priority exti
  * I[1:0] = 01 ==> level 1
  */
  cbi(ITC->ISPR3, 1);
  sbi(ITC->ISPR3, 0);
}