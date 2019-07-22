/*
    FreeRTOS V8.0.1 - Copyright (C) 2014 Real Time Engineers Ltd. 
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the AVR/IAR port.
 *----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#define portFLAGS_INT_ENABLED					( ( StackType_t ) 0x00 )

/* Hardware constants for timer 1. */
#define portCLEAR_COUNTER_ON_MATCH				( ( uint8_t ) 0x08 )
#define portPRESCALE_64							( ( uint8_t ) 0x03 )
#define portCLOCK_PRESCALER						( ( uint32_t ) 2 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE	( ( uint8_t ) 0x10 )

/* The number of bytes used on the hardware stack by the task start address. */
#define portBYTES_USED_BY_RETURN_ADDRESS		( 2 )
/*-----------------------------------------------------------*/

/* Stores the critical section nesting.  This must not be initialised to 0.
It will be initialised when a task starts. */
#define portNO_CRITICAL_NESTING					( ( UBaseType_t ) 0 )
UBaseType_t uxCriticalNesting = 0x50;


/*
 * Perform hardware setup to enable ticks from timer 1, compare match A.
 */
static void prvSetupTimerInterrupt( void );

/*
 * The IAR compiler does not have full support for inline assembler, so
 * these are defined in the portmacro assembler file.
 */
extern void vPortYieldFromTick( void );
extern void vPortStart( void );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
uint32_t usAddress;

    /* Place a few bytes of known values on the bottom of the stack.
	This is just useful for debugging. */

//	*pxTopOfStack = ( StackType_t ) 0x11;
//	pxTopOfStack--;
//	*pxTopOfStack = ( StackType_t ) 0x22;
//	pxTopOfStack--;
//	*pxTopOfStack = ( StackType_t ) 0x33;
//	pxTopOfStack--;
    
	*pxTopOfStack = ( StackType_t ) 'r';
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 't';
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 'S';
	pxTopOfStack--;

	/* Simulate how the stack would look after a call to vPortYield(). */

	/* Place the start	address of the task on the stack. */
	usAddress = ( uint32_t ) pxCode;
	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint32_t ) 0x000000ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint32_t ) 0x000000ff );
	pxTopOfStack--;
    
	usAddress >>= 8;
	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint32_t ) 0x000000ff );
	pxTopOfStack--;


	/* Next simulate the stack as if after a call to portSAVE_CONTEXT().
	portSAVE_CONTEXT places the flags on the stack immediately after r0
	to ensure the interrupts get disabled as soon as possible, and so ensuring
	the stack use is minimal should a context switch interrupt occur. */
    
    /* Y Register */
	*pxTopOfStack = ( StackType_t ) 0x11;	/* Y Register LSB */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x11;	/* Y Register MSB */
	pxTopOfStack--;
    
	/* Place the parameter on the stack in the expected location. */
    /* X  - Parameters are passed through registers. X is the first one used.
            So 'pvParameters' passed over X*/
	usAddress = ( uint16_t ) pvParameters;
	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint16_t ) 0x00ff );
	pxTopOfStack--;
	usAddress >>= 8;
	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint16_t ) 0x00ff );
	pxTopOfStack--;    
    
    /* A */
	*pxTopOfStack = ( StackType_t ) 0xaa;	/* A Register */
	pxTopOfStack--;
    
    /* CC Register
     * VIMP - Simulate as if interrupts are enabled 
     *        I0 and I1 to be set to 1*/
	*pxTopOfStack = ( StackType_t ) portFLAGS_INT_ENABLED; /* CC Register */
	pxTopOfStack--;
    
#if configUSE_PREEMPTION == 1    
//__task void SIG_OUTPUT_COMPARE1A( void );
//
//	/* Place the start	address of the task on the stack. */
//	usAddress = ( uint32_t ) 0x00969B;
//	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint32_t ) 0x000000ff );
//	pxTopOfStack--;
//
//	usAddress >>= 8;
//	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint32_t ) 0x000000ff );
//	pxTopOfStack--;
//    
//	usAddress >>= 8;
//	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint32_t ) 0x000000ff );
//	pxTopOfStack--;

#endif


	/* Now the remaining registers. */
	*pxTopOfStack = ( StackType_t ) 0x01;	/* b8 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x02;	/* b9 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x03;	/* b10 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x04;	/* b11 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x05;	/* b12 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x06;	/* b13 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x07;	/* b14 */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) 0x08;	/* b15 */
	pxTopOfStack--;

//	/* Place the parameter on the stack in the expected location. */
//	usAddress = ( uint16_t ) pvParameters;
//	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint16_t ) 0x00ff );
//	pxTopOfStack--;
//
//	usAddress >>= 8;
//	*pxTopOfStack = ( StackType_t ) ( usAddress & ( uint16_t ) 0x00ff );
//	pxTopOfStack--;

	pxTopOfStack--;
	*pxTopOfStack = portNO_CRITICAL_NESTING;	/* Critical nesting is zero when the task starts. */

	/*lint +e950 +e611 +e923 */

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
	/* Setup the hardware to generate the tick. */
	prvSetupTimerInterrupt();

	/* Restore the context of the first task that is going to run.
	Normally we would just call portRESTORE_CONTEXT() here, but as the IAR
	compiler does not fully support inline assembler we have to make a call.*/
	vPortStart();

	/* Should not get here! */
	return pdTRUE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* It is unlikely that the AVR port will get stopped.  If required simply
	disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
static void prvSetupTimerInterrupt( void )
{
uint32_t ulTickTime;

	/* Using 16bit timer 1 to generate the tick.  Correct clock configuration
    must be selected for the configCPU_CLOCK_HZ clock. */
    ulTickTime = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

    ulTickTime /= portCLOCK_PRESCALER;
    
    /* Time Base configuration */
    TIM1_TimeBaseInit(portCLOCK_PRESCALER, TIM1_COUNTERMODE_UP, ulTickTime, 0u);
    /* Prescaler configuration - 8MHz clock source Devided by 2 by sending prescalar 1u*/
    TIM1_PrescalerConfig(1u, TIM1_PSCRELOADMODE_IMMEDIATE);
    /* Output compare register value */
    TIM1_ARRPreloadConfig(ENABLE);
    /* TIM1 enable counter */
    TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);    
    
    /* Start the timer */
    TIM1_ARRPreloadConfig(ENABLE);
    TIM1_Cmd(ENABLE);
    TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
}
/*-----------------------------------------------------------*/
#if 0
#if configUSE_PREEMPTION == 1

	/*
	 * Tick ISR for preemptive scheduler.  We can use a __task attribute as
	 * the context is saved at the start of vPortYieldFromTick().  The tick
	 * count is incremented after the context is saved.
	 */
	__task void SIG_OUTPUT_COMPARE1A( void )
	{
        //if( SET == TIM1_GetITStatus(TIM1_IT_UPDATE ) )
        {
            /* Cleat Interrupt Pending bit */
            TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
            
            vPortYieldFromTick();
        }
		asm( "iret" );
	}

#else

	/*
	 * Tick ISR for the cooperative scheduler.  All this does is increment the
	 * tick count.  We don't need to switch context, this can only be done by
	 * manual calls to taskYIELD();
	 *
	 * THE INTERRUPT VECTOR IS POPULATED IN portmacro.s90.  DO NOT INSTALL
	 * IT HERE USING THE USUAL PRAGMA.
	 */
	__interrupt void SIG_OUTPUT_COMPARE1A( void )
	{
          /* Cleat Interrupt Pending bit */
        TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
        
		xTaskIncrementTick();
	}
#endif
#endif
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
	portDISABLE_INTERRUPTS();
	uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
	uxCriticalNesting--;
	if( uxCriticalNesting == portNO_CRITICAL_NESTING )
	{
		portENABLE_INTERRUPTS();
	}
}


