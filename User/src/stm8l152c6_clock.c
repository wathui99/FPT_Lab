#include "stm8l152c6_clock.h"

//16Mhz
void InitClock_Source(void)
{
    //CLK_DeInit();
    CLK_HSICmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
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