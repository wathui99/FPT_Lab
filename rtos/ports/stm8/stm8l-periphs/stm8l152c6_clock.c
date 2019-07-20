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
void InitClock_LCD(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);
};