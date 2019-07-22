#ifndef __main_h__
#define __main_h__

#include <stdio.h>
#include "atom.h"
#include "atomsem.h"
#include "atomport-private.h"
#include "atomport-tests.h"
#include "atomtests.h"
#include "atomtimer.h"

#include "stm8l.h"
#include "stm8l_gpio.h"
#include "stm8l152c6_clock.h"
#include "stm8l_timer1.h"
#include "stm8l_lcd.h"
#include <intrinsics.h>

/******************************************************************************/
/*                          Macro to Control Bit              	              */
/******************************************************************************/
#define sbi(sfr,bit)   (sfr |=(1<<bit))		/*!< Set bits value to 1 */
#define cbi(sfr,bit)   (sfr &=~(1<<bit))	/*!< Clear bits value to 0 */
#define tbi(sfr,bit)   (sfr ^=(1<<bit))		/*!< Toggle bits value */
#define gbi(sfr,bit)   (sfr &(1<<bit))		/*!< Get bits value */

#endif /*__main_h_*/