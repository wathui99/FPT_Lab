#include "stm8l152c6_clk.h"

void CLK_HSICmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Set HSION bit */
    CLK->CLK_ICKR.HSION = 1;
  }
  else
  {
    /* Reset HSION bit */
    CLK->CLK_ICKR.HSION = 0;
  }
};
void CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_TypeDef CLK_SYSCLKSource, CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
  CLK->CLK_SWR = (uint8_t)CLK_SYSCLKSource;
  CLK->CLK_DIVR = CLK_SYSCLKDiv;
};
void CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
  CLK->CLK_DIVR = (uint8_t)(CLK_SYSCLKDiv);
};
void CLK_SYSCLKSourceSwitchCmd(FunctionalState NewState);
CLK_SYSCLKSource_TypeDef CLK_GetSYSCLKSource(void);
uint32_t CLK_GetClockFreq(void);
void CLK_RTCClockConfig(CLK_RTCCLKSource_TypeDef CLK_RTCCLKSource, CLK_RTCCLKDiv_TypeDef CLK_RTCCLKDiv)
{
  CLK->CLK_CRTCR = (uint8_t)((uint8_t)CLK_RTCCLKSource | (uint8_t)CLK_RTCCLKDiv);
};
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
{
  uint8_t reg = 0;

  /* get flag register */
  reg = (uint8_t)((uint8_t)CLK_Peripheral & (uint8_t)0xF0);

  if ( reg == 0x00)
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->CLK_PCKENR1 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->CLK_PCKENR1 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
  else if (reg == 0x10)
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->CLK_PCKENR2 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->CLK_PCKENR2 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      //CLK->CLK_PCKENR3 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      //CLK->CLK_PCKENR3 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
};