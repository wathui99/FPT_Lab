#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdint.h>
#include "mymacro.h"

#define  CLK_SYSCLKSource_HSI  (uint8_t)0x01  /*!< System Clock Source HSI */
#define  CLK_SYSCLKSource_LSI  (uint8_t)0x02  /*!< System Clock Source LSI */
#define  CLK_SYSCLKSource_HSE  (uint8_t)0x04  /*!< System Clock Source HSE */
#define  CLK_SYSCLKSource_LSE  (uint8_t)0x08  /*!< System Clock Source LSE */

#define  CLK_SYSCLKDiv_1    (uint8_t)0x00 /*!< System Clock Divider: 1 */
#define  CLK_SYSCLKDiv_2    (uint8_t)0x01 /*!< System Clock Divider: 2 */
#define  CLK_SYSCLKDiv_4    (uint8_t)0x02 /*!< System Clock Divider: 4 */
#define  CLK_SYSCLKDiv_8    (uint8_t)0x03 /*!< System Clock Divider: 8 */
#define  CLK_SYSCLKDiv_16   (uint8_t)0x04 /*!< System Clock Divider: 16 */
#define  CLK_SYSCLKDiv_32   (uint8_t)0x05 /*!< System Clock Divider: 32 */
#define  CLK_SYSCLKDiv_64   (uint8_t)0x06 /*!< System Clock Divider: 64 */
#define  CLK_SYSCLKDiv_128  (uint8_t)0x07  /*!< System Clock Divider: 128 */

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

void Clk_Init (void);

#endif /* __CONFIG_H */