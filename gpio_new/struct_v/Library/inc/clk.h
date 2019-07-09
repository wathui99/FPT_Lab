#ifndef __CONFIG_H
#define __CONFIG_H

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