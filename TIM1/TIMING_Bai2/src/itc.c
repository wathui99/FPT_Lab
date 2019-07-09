#include "itc.h"

void Itc_Init(void) {
  /* priority exti
  * I[1:0] = 01 ==> level 1
  */
  //vector 9
  cbi(ITC->ISPR3, 3);
  sbi(ITC->ISPR3, 2);
  //vector 8
  cbi(ITC->ISPR3, 1);
  sbi(ITC->ISPR3, 0);
}