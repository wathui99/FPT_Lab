#include "stm8l152c6_clock.h"

//16Mhz
void InitClock_Source(CLK_SYSCLKSource_TypeDef CLK_SYSCLKSource, CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
    //CLK_DeInit();
    CLK_HSICmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource, CLK_SYSCLKDiv);
};

//SystemClock
void InitClock_Timer(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
};

//SystemClock
void InitClock_RTC(void)
{
    CLK_RTCClockConfig(CLK_RTCCLKSource_HSI, CLK_RTCCLKDiv_64);
};

//SystemClock
void InitClock_LCD_RTC(void)
{
    /*Enable rtc clock */
    CLK->CLK_PCKENR2 |= (1<<2);
    CLK->CLK_CRTCR = (uint8_t)((uint8_t)0x04 | (uint8_t)0x00);
    /*Enable lcd clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);
};