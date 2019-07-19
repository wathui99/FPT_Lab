#ifndef _STM8L152C6_CLK_H_
#define _STM8L152C6_CLK_H_
#include <stdint.h>
/*Clock STM8L152C6*/
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef struct TypeInternalClock{
  uint8_t HSION : 1;
  uint8_t HSIRDY : 1;
  uint8_t LSION : 1;
  uint8_t LSIRDY : 1;
  uint8_t SAHALT : 1;
  uint8_t FHWU : 1;
  uint8_t BEEPAHALT : 1;
  uint8_t Reserved : 1;
} InternalClock_Type;

typedef struct TypeExternalClock{
  uint8_t HSEON : 1;
  uint8_t HSERDY : 1;
  uint8_t LSEON : 1;
  uint8_t LSERDY : 1;
  uint8_t HSEBYP : 1;
  uint8_t LSEBYP : 1;
  uint8_t Reserved1 : 1;
  uint8_t Reserved2 : 1;
} ExternalClock_Type;

typedef struct TypeSwitchControl{
  uint8_t SWBSY : 1;
  uint8_t SWEN : 1;
  uint8_t SWIEN : 1;
  uint8_t SWIF : 1;
  uint8_t Reserved : 4;
} SwitchControl_Type;

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

typedef struct TypeRTC{
  uint8_t RTCSWBSY : 1;
  uint8_t RTCSEL : 4;
  uint8_t RTCDIV : 3;
} RTC_Type;

typedef struct TypeStatus{
  uint8_t REGREADY : 1;
  uint8_t REGOFF : 1;
  uint8_t HSIPD : 1;
  uint8_t LSIPD : 1;
  uint8_t HSEPD : 1;
  uint8_t LSEPD : 1;
  uint8_t EEBUSY : 1;
  uint8_t EEREADY : 1;
} Status_Type;


typedef struct CLK_CCOR{
  uint8_t CCOSWBSY : 1;
  uint8_t CCOSEL : 4;
  uint8_t CCODIV : 3;
} CLK_CCOR_Type;

typedef struct CLK_CSSR{
  uint8_t CSSEN : 1;
  uint8_t AUX : 1;
  uint8_t CSSDIE : 1;
  uint8_t CSSD : 1;
  uint8_t CSSDGON : 1;
  uint8_t Reserved : 3;
} CLK_CSSR_Type;

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

typedef struct TypeClock {
    uint8_t CLK_DIVR;
    uint8_t CLK_CRTCR;
    InternalClock_Type CLK_ICKR;
    uint8_t CLK_PCKENR1;
    uint8_t CLK_PCKENR2;
    CLK_CCOR_Type CLK_CCOR;
    ExternalClock_Type CLK_ECKR;
    uint8_t CLK_SCSR;
    uint8_t CLK_SWR;
    SwitchControl_Type CLK_SWCR;
    uint8_t CLK_CSSR;
    uint8_t CLK_CBEEPR;
    uint8_t CLK_HSICALR;
    uint8_t CLK_HSITRIMR;
    uint8_t CLK_HSIUNLCKR;
    Status_Type CLK_REGCSR;
} Clock_Type;

typedef enum {
  CLK_SYSCLKSource_HSI = (uint8_t)0x01, /*!< System Clock Source HSI */
  CLK_SYSCLKSource_LSI = (uint8_t)0x02, /*!< System Clock Source LSI */
  CLK_SYSCLKSource_HSE = (uint8_t)0x04, /*!< System Clock Source HSE */
  CLK_SYSCLKSource_LSE = (uint8_t)0x08  /*!< System Clock Source LSE */
} CLK_SYSCLKSource_TypeDef;

void CLK_HSICmd(FunctionalState NewState);
void CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_TypeDef CLK_SYSCLKSource);
void CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv);
void CLK_SYSCLKSourceSwitchCmd(FunctionalState NewState);
CLK_SYSCLKSource_TypeDef CLK_GetSYSCLKSource(void);
uint32_t CLK_GetClockFreq(void);
void CLK_RTCClockConfig(CLK_RTCCLKSource_TypeDef CLK_RTCCLKSource, CLK_RTCCLKDiv_TypeDef CLK_RTCCLKDiv);
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState);

#define CFG_GCR (*(uint8_t*)0x007F60)

#define CLK ((Clock_Type*)0x0050C0)

#endif // _KHA_CLOCK_H_