;/*
;    FreeRTOS V8.0.1 - Copyright (C) 2014 Real Time Engineers Ltd.
;    All rights reserved
;
;
;    ***************************************************************************
;     *                                                                       *
;     *    FreeRTOS tutorial books are available in pdf and paperback.        *
;     *    Complete, revised, and edited pdf reference manuals are also       *
;     *    available.                                                         *
;     *                                                                       *
;     *    Purchasing FreeRTOS documentation will not only help you, by       *
;     *    ensuring you get running as quickly as possible and with an        *
;     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
;     *    the FreeRTOS project to continue with its mission of providing     *
;     *    professional grade, cross platform, de facto standard solutions    *
;     *    for microcontrollers - completely free of charge!                  *
;     *                                                                       *
;     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
;     *                                                                       *
;     *    Thank you for using FreeRTOS, and thank you for your support!      *
;     *                                                                       *
;    ***************************************************************************
;
;
;    This file is part of the FreeRTOS distribution.
;
;    FreeRTOS is free software; you can redistribute it and/or modify it under
;    the terms of the GNU General Public License (version 2) as published by the
;    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
;    >>>NOTE<<< The modification to the GPL is included to allow you to
;    distribute a combined work that includes FreeRTOS without being obliged to
;    provide the source code for proprietary components outside of the FreeRTOS
;    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
;    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
;    more details. You should have received a copy of the GNU General Public
;    License and the FreeRTOS license exception along with FreeRTOS; if not it
;    can be viewed here: http://www.freertos.org/a00114.html and also obtained
;    by writing to Richard Barry, contact details for whom are available on the
;    FreeRTOS WEB site.
;
;    1 tab == 4 spaces!
;
;    http://www.FreeRTOS.org - Documentation, latest information, license and
;    contact details.
;
;    http://www.SafeRTOS.com - A version that is certified for use in safety
;    critical systems.
;
;    http://www.OpenRTOS.com - Commercial support, development, porting,
;    licensing and training services.
;*/

//#include "stm8s.h"
; Get definitions for virtual registers used by the compiler
#include "vregs.inc"
//#include "FreeRTOSConfig.h"

; Declare all extern symbols here - including any ISRs that are referenced in
; the vector table.

; ISR functions
; -------------
EXTERN SIG_OUTPUT_COMPARE1A
EXTERN SIG_UART_RECV
EXTERN SIG_UART_DATA


; Functions used by scheduler
; ---------------------------
EXTERN vTaskSwitchContext
EXTERN pxCurrentTCB
EXTERN xTaskIncrementTick
EXTERN uxCriticalNesting

; Functions implemented in this file
; ----------------------------------
PUBLIC vPortYield
PUBLIC vPortYieldFromTick
PUBLIC vPortStart


; Interrupt vector table.
; -----------------------
;
; For simplicity the RTOS tick interrupt routine uses the __task keyword.
; As the IAR compiler does not permit a function to be declared using both
; __task and __interrupt, the use of __task necessitates that the interrupt
; vector table be setup manually.
;
; To write an ISR, implement the ISR function using the __interrupt keyword
; but do not install the interrupt using the "#pragma vector=ABC" method.
; Instead manually place the name of the ISR in the vector table using an
; ORG and jmp instruction as demonstrated below.
; You will also have to add an EXTERN statement at the top of the file.

    SECTION `.intvec`:CONST
    PUBLIC  __intvec
    EXTERN  __iar_program_start

__intvec:
    DC8     0x82
    DC24    __iar_program_start   ; RESET    0x8000
    DC8     0x82
    DC24    vNoISR                ;0x8004
    DC8     0x82
    DC24    vNoISR                ;0x8008
    DC8     0x82
    DC24    vNoISR                ;0x800C
    DC8     0x82
    DC24    vNoISR                ;8010
    DC8     0x82
    DC24    vNoISR                ;8014
    DC8     0x82
    DC24    vNoISR                ;8018
    DC8     0x82
    DC24    vNoISR                ;801C
    DC8     0x82
    DC24    vNoISR                ;8020
    DC8     0x82
    DC24    vNoISR                ;8024
    DC8     0x82
    DC24    vNoISR               ;8028
    DC8     0x82
    DC24    vNoISR               ;802C
    DC8     0x82
    DC24    vNoISR               ;8030
    DC8     0x82
    DC24    vPortYieldFromTick   ;8034
    DC8     0x82
    DC24    vNoISR               ;8038
    DC8     0x82
    DC24    vNoISR               ;803C
    DC8     0x82
    DC24    vNoISR               ;8040
    DC8     0x82
    DC24    vNoISR               ;8044
    DC8     0x82
    DC24    vNoISR               ;8048
    DC8     0x82
    DC24    SIG_UART_DATA               ;804C
    DC8     0x82
    DC24    SIG_UART_RECV               ;8050
    DC8     0x82
    DC24    vNoISR               ;8054
    DC8     0x82
    DC24    vNoISR               ;8058
    DC8     0x82
    DC24    vNoISR               ;805C
    DC8     0x82
    DC24    vNoISR               ;8060
    DC8     0x82
    DC24    vNoISR               ;8064
    DC8     0x82
    DC24    vNoISR               ;8068
    DC8     0x82
    DC24    vNoISR               ;806C
    DC8     0x82
    DC24    vNoISR               ;8070
    DC8     0x82
    DC24    vNoISR               ;8074
    DC8     0x82
    DC24    vNoISR               ;8078
    DC8     0x82
    DC24    vNoISR               ;807C



; Saving and Restoring a Task Context and Task Switching
; ------------------------------------------------------
;
; The IAR compiler does not fully support inline assembler, so saving and
; restoring a task context has to be written in an asm file.
;
; Implemented both vPortYield() and vPortYieldFromTick() in this assembly file.  
; STM8 architecure has only 3 general purpose registers, X, Y and A. Upon 
; interrupt return address [24bit], Code Codition Register [cc] and x,y and a 
; registers are pushed on to the stack acuomatically by the controller
;  
; In addition to the physical registers in STM8 (A, X, Y, CC, and SP), the 
; compiler also uses virtual registers. A virtual register is a static memory 
; location in the fastest memory used for storing variables and temporary values.
; The runtime library defines 16 one-byte (8-bit) virtual registers called
; ?b0, ?b1, …, ?b15. They are placed in the .vregs section, which is / must be 
; allocated in RAM in the first 256 bytes of memory.
; For convenience portSAVE_CONTEXT and portRESTORE_CONTEXT are implemented as macros.

portSAVE_CONTEXT MACRO
    push ?b8            ; Now store the rest of the registers.  Dont store the ...
    push ?b9            ; ... the stack pointer register here
    push ?b10           ; stack pointer and will get saved into the TCB.
    push ?b11           ; Note: These are not the actual registers of STM8 core
    push ?b12           ;       These are vertual registers used by IAR compiler
    push ?b13
    push ?b14
    push ?b15
	
	ld a, uxCriticalNesting ; Store the critical nesting counter. You may have to use ldf
	push a					

    ldw x, pxCurrentTCB         ; Finally save the stack pointer register
    ldw y, sp                   ; into the TCB.
    ldw (x), y 

	ENDM

;-------------------------------------------------------------------------------
portRESTORE_CONTEXT MACRO
    ldw x, pxCurrentTCB         ; Restore the software stack pointer from ...
    ldw x, (x)                  ; the TCB into the stack pointer register
    ldw sp, x
	
	pop a	
	ld uxCriticalNesting, a     ; Store the critical nesting counter. 
    
    pop ?b15
    pop ?b14
    pop ?b13
    pop ?b12
    pop ?b11
    pop ?b10
    pop ?b9
    pop ?b8
	iret 		                ; ... scheduler decided should run.
	ENDM


; vPortYield() and vPortYieldFromTick()
; -------------------------------------
;
; Manual and preemptive context switch functions respectively.
; The IAR compiler does not fully support inline assembler,
; so these are implemented here rather than the more usually
; place of within port.c.
;-------------------------------------------------------------------------------
vPortYield:

    pushw y
    pushw x
    push a
    push cc
    
    sim                         ;Disable interrupts
    
    portSAVE_CONTEXT			; Save the context of the current task.
	callf vTaskSwitchContext		; Call the scheduler.
	portRESTORE_CONTEXT			; Restore the context of whichever task the ...

;----------------------
vPortYieldFromTick:

    LD        A, S:0x01         ; Clear the Timer 1 IT pending Bit
    CPL       A                 ; TIM1->SR1 = (uint8_t)(~(uint8_t)TIM1_IT);
    LD        L:0x5255, A
    
    portSAVE_CONTEXT			; Save the context of the current task.
    
	callf xTaskIncrementTick	; Call the timer tick function.
	tnz a
	jreq SkipTaskSwitch
	callf vTaskSwitchContext	; Call the scheduler.
SkipTaskSwitch:
	portRESTORE_CONTEXT			; Restore the context of whichever task the ...
    
;-------------------------------------------------------------------------------
; vPortStart()
; ------------
;
; Again due to the lack of inline assembler, this is required
; to get access to the portRESTORE_CONTEXT macro.
vPortStart:
	portRESTORE_CONTEXT

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Just a filler for unused interrupt vectors.
vNoISR:
	iret
;-------------------------------------------------------------------------------
END
