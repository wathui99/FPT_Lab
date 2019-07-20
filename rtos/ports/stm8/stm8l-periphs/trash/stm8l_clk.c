#ifndef _STM8L152C6_CLK_H_
#define _STM8L152C6_CLK_H_
#include <stdint.h>
#include "stm8l_clk.h"
/*Clock STM8L152C6*/
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {
  CLK_SYSCLKDiv_1   = (uint8_t)0x00, /*!< System Clock Divider: 1 */
  CLK_SYSCLKDiv_2   = (uint8_t)0x01, /*!< System Clock Divider: 2 */
  CLK_SYSCLKDiv_4   = (uint8_t)0x02, /*!< System Clock Divider: 4 */
  CLK_SYSCLKDiv_8   = (uint8_t)0x03, /*!< System Clock Divider: 8 */
  CLK_SYSCLKDiv_16  = (uint8_t)0x04, /*!< System Clock Divider: 16 */
  CLK_SYSCLKDiv_32  = (uint8_t)0x05, /*!< System Clock Divider: 32 */
  CLK_SYSCLKDiv_64  = (uint8_t)0x06, /*!< System Clock Divider: 64 */
  CLK_SYSCLKDiv_128 = (uint8_t)0x07  /*!< System Clock Divider: 128 */
} CLK_SYSCLKDiv_TypeDef;

typedef enum {
  CLK_RTCCLKDiv_1  = (uint8_t)0x00, /*!< Clock RTC Div 1 */
  CLK_RTCCLKDiv_2  = (uint8_t)0x20, /*!< Clock RTC Div 2  */
  CLK_RTCCLKDiv_4  = (uint8_t)0x40, /*!< Clock RTC Div 4 */
  CLK_RTCCLKDiv_8  = (uint8_t)0x60, /*!< Clock RTC Div 8 */
  CLK_RTCCLKDiv_16 = (uint8_t)0x80, /*!< Clock RTC Div 16 */
  CLK_RTCCLKDiv_32 = (uint8_t)0xA0, /*!< Clock RTC  Div 32 */
  CLK_RTCCLKDiv_64 = (uint8_t)0xC0  /*!< Clock RTC  Div 64 */
} CLK_RTCCLKDiv_TypeDef;

typedef enum {
  CLK_RTCCLKSource_Off = (uint8_t)0x00, /*!< Clock RTC Off */
  CLK_RTCCLKSource_HSI = (uint8_t)0x02, /*!< Clock RTC : HSI */
  CLK_RTCCLKSource_LSI = (uint8_t)0x04, /*!< Clock RTC : LSI */
  CLK_RTCCLKSource_HSE = (uint8_t)0x08, /*!< Clock RTC : HSE */
  CLK_RTCCLKSource_LSE = (uint8_t)0x10  /*!< Clock RTC : LSE */
} CLK_RTCCLKSource_TypeDef;

typedef enum {
  CLK_Peripheral_TIM2    = (uint8_t)0x00, /*!< Peripheral Clock Enable 1, TIM2 */
  CLK_Peripheral_TIM3    = (uint8_t)0x01, /*!< Peripheral Clock Enable 1, TIM3 */
  CLK_Peripheral_TIM4    = (uint8_t)0x02, /*!< Peripheral Clock Enable 1, TIM4 */
  CLK_Peripheral_I2C1    = (uint8_t)0x03, /*!< Peripheral Clock Enable 1, I2C1 */
  CLK_Peripheral_SPI1    = (uint8_t)0x04, /*!< Peripheral Clock Enable 1, SPI1 */
  CLK_Peripheral_USART1  = (uint8_t)0x05, /*!< Peripheral Clock Enable 1, USART1 */
  CLK_Peripheral_BEEP    = (uint8_t)0x06, /*!< Peripheral Clock Enable 1, BEEP */
  CLK_Peripheral_DAC     = (uint8_t)0x07, /*!< Peripheral Clock Enable 1, DAC */
  CLK_Peripheral_ADC1    = (uint8_t)0x10, /*!< Peripheral Clock Enable 2, ADC1 */
  CLK_Peripheral_TIM1    = (uint8_t)0x11, /*!< Peripheral Clock Enable 2, TIM1 */
  CLK_Peripheral_RTC     = (uint8_t)0x12, /*!< Peripheral Clock Enable 2, RTC */
  CLK_Peripheral_LCD     = (uint8_t)0x13, /*!< Peripheral Clock Enable 2, LCD */
  CLK_Peripheral_DMA1    = (uint8_t)0x14, /*!< Peripheral Clock Enable 2, DMA1 */
  CLK_Peripheral_COMP    = (uint8_t)0x15, /*!< Peripheral Clock Enable 2, COMP1 and COMP2 */
  CLK_Peripheral_BOOTROM = (uint8_t)0x17,/*!< Peripheral Clock Enable 2, Boot ROM */
  CLK_Peripheral_AES     = (uint8_t)0x20, /*!< Peripheral Clock Enable 3, AES */
  CLK_Peripheral_TIM5    = (uint8_t)0x21, /*!< Peripheral Clock Enable 3, TIM5 */
  CLK_Peripheral_SPI2    = (uint8_t)0x22, /*!< Peripheral Clock Enable 3, SPI2 */
  CLK_Peripheral_USART2  = (uint8_t)0x23, /*!< Peripheral Clock Enable 3, USART2 */
  CLK_Peripheral_USART3  = (uint8_t)0x24,  /*!< Peripheral Clock Enable 3, USART3 */
  CLK_Peripheral_CSSLSE  = (uint8_t)0x25   /*!< Peripheral Clock Enable 3, CSS on LSE */
} CLK_Peripheral_TypeDef;

typedef enum {
  CLK_SYSCLKSource_HSI = (uint8_t)0x01, /*!< System Clock Source HSI */
  CLK_SYSCLKSource_LSI = (uint8_t)0x02, /*!< System Clock Source LSI */
  CLK_SYSCLKSource_HSE = (uint8_t)0x04, /*!< System Clock Source HSE */
  CLK_SYSCLKSource_LSE = (uint8_t)0x08  /*!< System Clock Source LSE */
} CLK_SYSCLKSource_TypeDef;

typedef struct TypeClock {
  uint8_t CKDIVR;        /*!< Clock Master Divider Register */
  uint8_t CRTCR;         /*!< RTC Clock selection Register */
  uint8_t ICKCR;         /*!< Internal Clocks Control Register */
  uint8_t PCKENR1;       /*!< Peripheral Clock Gating Register 1 */
  uint8_t PCKENR2;       /*!< Peripheral Clock Gating Register 2 */
  uint8_t CCOR;          /*!< Configurable Clock Output Register */
  uint8_t ECKCR;         /*!< External Clocks Control Register */
  uint8_t SCSR;          /*!< System clock status Register */
  uint8_t SWR;           /*!< System clock Switch Register */
  uint8_t SWCR;          /*!< Switch Control Register */
  uint8_t CSSR;          /*!< Clock Security Sytem Register */
  uint8_t CBEEPR;        /*!< Clock BEEP Register */
  uint8_t HSICALR;       /*!< HSI Calibration Register */
  uint8_t HSITRIMR;      /*!< HSI clock Calibration Trimmer Register */
  uint8_t HSIUNLCKR;     /*!< HSI Unlock  Register */
  uint8_t REGCSR;        /*!< Main regulator control status register */
  uint8_t PCKENR3;       /*!< Peripheral Clock Gating Register 3 */
} Clock_Type;

#define CLK ((Clock_Type *) 0x50C0)

#endif