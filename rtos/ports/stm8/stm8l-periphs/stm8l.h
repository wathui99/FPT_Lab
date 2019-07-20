/**
  ******************************************************************************
  * @file stm8s.h
  * @brief This file contains all HW registers definitions and memory mapping.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.1.1
  * @date 06/05/2009
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_H
#define __STM8S_H

/******************************************************************************/
/*                   Library configuration section                            */
/******************************************************************************/
/* Check the used compiler */
#if defined(__CSMC__)
 #undef _RAISONANCE_
 #undef _IAR_SYSTEMS_
 #undef _SDCC_
 #define _COSMIC_
#elif defined(__RCST7__)
 #undef _COSMIC_
 #undef _IAR_SYSTEMS_
 #undef _SDCC_
 #define _RAISONANCE_
#elif defined(__IAR_SYSTEMS_ICC__)
 #undef _COSMIC_
 #undef _RAISONANCE_
 #undef _SDCC_
 #define _IAR_SYSTEMS_
#elif defined(__SDCC_stm8)
 #undef _COSMIC_
 #undef _RAISONANCE_
 #undef _IAR_SYSTEMS_
 #define _SDCC_
#else
 #error "Unsupported Compiler!"          /* Compiler defines not found */
#endif

/* Uncomment the line below according to the target STM8S device used in your
   application. 
   Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor. */
#if !defined (STM8S208) && !defined (STM8S207) && !defined (STM8S105) && !defined (STM8S103) && !defined (STM8S903)
// # error "STM8S device not specified"
 /* #define STM8S208 */
 /* #define STM8S207 */
 /* #define STM8S105 */  
 /* #define STM8S103 */
 /* #define STM8S903 */
#endif


#if !defined  USE_STDPERIPH_DRIVER
/* Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will be
   based on direct access to peripherals registers */
  #define USE_STDPERIPH_DRIVER
#endif

/* For FLASH routines, select whether pointer will be declared as near (2 bytes, handle
   code smaller than 64KB) or far (3 bytes, handle code larger than 64K) */
/*#define PointerAttr_Near 1  */  /*!< Used with memory Models for code smaller than 64K */ 
#define PointerAttr_Far 2 /*!< Used with memory Models for code larger than 64K */ 

#ifdef _COSMIC_
 #define FAR  @far
 #define NEAR @near
 #define TINY @tiny
 #define __CONST  const
#endif

#ifdef _RAISONANCE_
 #define FAR  far
 #define NEAR data
 #define TINY page0
 #define __CONST  code
#endif

#ifdef _IAR_SYSTEMS_
 #define FAR  __far
 #define NEAR __near
 #define TINY __tiny
 #define __CONST  const
#endif

#ifdef _SDCC_
 #define NEAR
 #define __CONST  const
#endif

#ifdef PointerAttr_Far
 #define PointerAttr FAR 
#else /* PointerAttr_Near */
 #define PointerAttr NEAR
#endif /* PointerAttr_Far */


/* Uncomment the line below to use the cosmic section */
#if defined(_COSMIC_)
/* #define USE_COSMIC_SECTIONS  (1)*/
#endif

/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8l_type.h"

/* Exported types and constants-----------------------------------------------*/
/** @addtogroup MAP_FILE_Exported_Types_and_Constants
  * @{
  */



/**
  * @brief Configuration Registers (CFG)
  */

typedef struct CFG_struct
{
  vu8 GCR; /*!< Global Configuration register */
}
CFG_TypeDef;

/** @addtogroup CFG_Registers_Reset_Value
  * @{
  */

#define CFG_GCR_RESET_VALUE ((u8)0x00)

/**
  * @}
  */

/** @addtogroup CFG_Registers_Bits_Definition
  * @{
  */

#define CFG_GCR_SWD ((u8)0x01) /*!< Swim disable bit mask */
#define CFG_GCR_AL  ((u8)0x02) /*!< Activation Level bit mask */

/**
  * @}
  */

/**
  * @}
  */

/******************************************************************************/
/*                          Peripherals Base Address                          */
/******************************************************************************/

/** @addtogroup MAP_FILE_Base_Addresses
  * @{
  */
#define OPT_BaseAddress         0x4800
#define GPIOA_BaseAddress       0x5000
#define GPIOB_BaseAddress       0x5005
#define GPIOC_BaseAddress       0x500A
#define GPIOD_BaseAddress       0x500F
#define GPIOE_BaseAddress       0x5014
#define GPIOF_BaseAddress       0x5019
#define GPIOG_BaseAddress       0x501E
#define GPIOH_BaseAddress       0x5023
#define GPIOI_BaseAddress       0x5028

#define FLASH_BaseAddress       0x505A

#define EXTI_BaseAddress        0x50A0
#define RST_BaseAddress         0x50B3
#define CLK_BaseAddress         0x50C0
#define WWDG_BaseAddress        0x50D1
#define IWDG_BaseAddress        0x50E0
#define AWU_BaseAddress         0x50F0
#define BEEP_BaseAddress        0x50F3
#define SPI_BaseAddress         0x5200
#define I2C_BaseAddress         0x5210
#define UART1_BaseAddress       0x5230
#define UART2_BaseAddress       0x5240
#define UART3_BaseAddress       0x5240
#define TIM1_BaseAddress        0x5250
#define TIM2_BaseAddress        0x5300
#define TIM3_BaseAddress        0x5320
#define TIM4_BaseAddress        0x5340
#define TIM5_BaseAddress        0x5300
#define TIM6_BaseAddress        0x5340

#define ADC1_BaseAddress        0x53E0
#define ADC2_BaseAddress        0x5400
#define CAN_BaseAddress         0x5420

#define CFG_BaseAddress         0x7F60
#define ITC_BaseAddress         0x7F70
#define SWIM_BaseAddress        0x7F80
#define DM_BaseAddress          0x7F90

/**
  * @}
  */

/******************************************************************************/
/*                          Peripherals declarations                          */
/******************************************************************************/

#if defined(STM8S105) || defined(STM8S103) || defined(STM8S903)
 #define ADC1 ((ADC1_TypeDef *) ADC1_BaseAddress)
#endif /* (STM8S105) ||(STM8S103) || (STM8S903) */

#if defined(STM8S208) || defined(STM8S207)
#define ADC2 ((ADC2_TypeDef *) ADC2_BaseAddress)
#endif /* (STM8S208) ||(STM8S207)  */


#if defined(STM8S207) || defined(STM8S208) || defined(STM8S105)
 #define GPIOG ((GPIO_TypeDef *) GPIOG_BaseAddress)
#endif /* (STM8S208) ||(STM8S207)  || (STM8S105) */

#if defined(STM8S207) || defined(STM8S208)
 #define GPIOH ((GPIO_TypeDef *) GPIOH_BaseAddress)
 #define GPIOI ((GPIO_TypeDef *) GPIOI_BaseAddress)
#endif /* (STM8S208) ||(STM8S207) */

#define RST ((RST_TypeDef *) RST_BaseAddress)

#define WWDG ((WWDG_TypeDef *) WWDG_BaseAddress)
#define IWDG ((IWDG_TypeDef *) IWDG_BaseAddress)

#define SPI ((SPI_TypeDef *) SPI_BaseAddress)
#define I2C ((I2C_TypeDef *) I2C_BaseAddress)

#if defined(STM8S208) ||defined(STM8S207) ||defined(STM8S103) ||defined(STM8S903)
 #define UART1 ((UART1_TypeDef *) UART1_BaseAddress)
#endif /* (STM8S208) ||(STM8S207)  || (STM8S103) || (STM8S903)  */

#ifdef STM8S105
 #define UART2 ((UART2_TypeDef *) UART2_BaseAddress)
#endif /* STM8S105 */

#if defined(STM8S208) ||defined(STM8S207)
 #define UART3 ((UART3_TypeDef *) UART3_BaseAddress)
#endif /* (STM8S208) ||(STM8S207) */


#if defined(STM8S208) ||defined(STM8S207) ||defined(STM8S103) ||defined(STM8S105)
 #define TIM2 ((TIM2_TypeDef *) TIM2_BaseAddress)
#endif /* (STM8S208) ||(STM8S207)  || (STM8S103) || (STM8S105)  */

#if defined(STM8S208) ||defined(STM8S207) ||defined(STM8S105)
 #define TIM3 ((TIM3_TypeDef *) TIM3_BaseAddress)
#endif /* (STM8S208) ||(STM8S207)  || (STM8S105) */

#if defined(STM8S208) ||defined(STM8S207) ||defined(STM8S103) ||defined(STM8S105)
 #define TIM4 ((TIM4_TypeDef *) TIM4_BaseAddress)
#endif /* (STM8S208) ||(STM8S207)  || (STM8S103) || (STM8S105)  */

#ifdef STM8S903
 #define TIM5 ((TIM5_TypeDef *) TIM5_BaseAddress)
 #define TIM6 ((TIM6_TypeDef *) TIM6_BaseAddress)
#endif /* STM8S903 */ 

#define ITC ((ITC_TypeDef *) ITC_BaseAddress)

#define CFG ((CFG_TypeDef *) CFG_BaseAddress)

#define SWIM ((SWIM_TypeDef *) SWIM_BaseAddress)

#define DM ((DM_TypeDef *) DM_BaseAddress)


#ifdef USE_STDPERIPH_DRIVER
 #include "stm8s_conf.h"
#endif

/* Exported macro --------------------------------------------------------------*/

/*============================== Interrupts ====================================*/
#ifdef _RAISONANCE_
 #include <intrist7.h>
 #define enableInterrupts()  _rim_()  /* enable interrupts */
 #define disableInterrupts() _sim_()  /* disable interrupts */
 #define rim()               _rim_()  /* enable interrupts */
 #define sim()               _sim_()  /* disable interrupts */
 #define nop()               _nop_()  /* No Operation */
 #define trap()              _trap_() /* Trap (soft IT) */
 #define wfi()               _wfi_()  /* Wait For Interrupt */
 #define halt()              _halt_() /* Halt */
#endif

#ifdef _COSMIC_
 #define enableInterrupts() {_asm("rim\n");} /* enable interrupts */
 #define disableInterrupts() {_asm("sim\n");} /* disable interrupts */
 #define rim() {_asm("rim\n");} /* enable interrupts */
 #define sim() {_asm("sim\n");} /* disable interrupts */
 #define nop() {_asm("nop\n");} /* No Operation */
 #define trap() {_asm("trap\n");} /* Trap (soft IT) */
 #define wfi() {_asm("wfi\n");} /* Wait For Interrupt */
 #define halt() {_asm("halt\n");} /* Halt */
#endif

#ifdef _IAR_SYSTEMS_
 #include <intrinsics.h>
 #define enableInterrupts()  __enable_interrupt()   /* enable interrupts */
 #define disableInterrupts() __disable_interrupt()  /* disable interrupts */
 #define rim()               __enable_interrupt()   /* enable interrupts */
 #define sim()               __disable_interrupt()  /* disable interrupts */
 #define nop()               __no_operation()       /* No Operation */
 #define trap()              __trap_()              /* Trap (soft IT) */
 #define wfi()               __wait_for_interrupt() /* Wait For Interrupt */
 #define halt()              __halt_()              /* Halt */
#endif

/*============================== Handling bits ====================================*/
/*-----------------------------------------------------------------------------
Method : I
Description : Handle the bit from the character variables.
Comments :    The different parameters of commands are
              - VAR : Name of the character variable where the bit is located.
              - Place : Bit position in the variable (7 6 5 4 3 2 1 0)
              - Value : Can be 0 (reset bit) or not 0 (set bit)
              The "MskBit" command allows to select some bits in a source
              variables and copy it in a destination var (return the value).
              The "ValBit" command returns the value of a bit in a char
              variable: the bit is reseted if it returns 0 else the bit is set.
              This method generates not an optimised code yet.
-----------------------------------------------------------------------------*/
#define SetBit(VAR,Place)         ( (VAR) |= (u8)((u8)1<<(u8)(Place)) )
#define ClrBit(VAR,Place)         ( (VAR) &= (u8)((u8)((u8)1<<(u8)(Place))^(u8)255) )

#define ChgBit(VAR,Place)         ( (VAR) ^= (u8)((u8)1<<(u8)(Place)) )
#define AffBit(VAR,Place,Value)   ((Value) ? \
                                   ((VAR) |= ((u8)1<<(Place))) : \
                                   ((VAR) &= (((u8)1<<(Place))^(u8)255)))
#define MskBit(Dest,Msk,Src)      ( (Dest) = ((Msk) & (Src)) | ((~(Msk)) & (Dest)) )

#define ValBit(VAR,Place)         ((u8)(VAR) & (u8)((u8)1<<(u8)(Place)))

#define BYTE_0(n)                 ((u8)((n) & (u8)0xFF))        /*!< Returns the low byte of the 32-bit value */
#define BYTE_1(n)                 ((u8)(BYTE_0((n) >> (u8)8)))  /*!< Returns the second byte of the 32-bit value */
#define BYTE_2(n)                 ((u8)(BYTE_0((n) >> (u8)16))) /*!< Returns the third byte of the 32-bit value */
#define BYTE_3(n)                 ((u8)(BYTE_0((n) >> (u8)24))) /*!< Returns the high byte of the 32-bit value */

/*============================== Assert Macros ====================================*/
#define IS_STATE_VALUE_OK(SensitivityValue) \
  (((SensitivityValue) == ENABLE) || \
   ((SensitivityValue) == DISABLE))

/*-----------------------------------------------------------------------------
Method : II
Description : Handle directly the bit.
Comments :    The idea is to handle directly with the bit name. For that, it is
              necessary to have RAM area descriptions (example: HW register...)
              and the following command line for each area.
              This method generates the most optimized code.
-----------------------------------------------------------------------------*/

#define AREA 0x00     /* The area of bits begins at address 0x10. */

#define BitClr(BIT)  ( *((unsigned char *) (AREA+(BIT)/8)) &= (~(1<<(7-(BIT)%8))) )
#define BitSet(BIT)  ( *((unsigned char *) (AREA+(BIT)/8)) |= (1<<(7-(BIT)%8)) )
#define BitVal(BIT)  ( *((unsigned char *) (AREA+(BIT)/8)) & (1<<(7-(BIT)%8)) )

/* Exported functions ------------------------------------------------------- */

#endif /* __STM8S_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
