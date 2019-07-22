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

; Get definitions for virtual registers used by the compiler
//#include "vregs.inc"

; Declare all extern symbols here - including any ISRs that are referenced in
; the vector table.

; ISR functions
; -------------
EXTERN SIG_OUTPUT_COMPARE1A
EXTERN SIG_UART_RECV
EXTERN SIG_UART_DATA



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
    EXTERN   __iar_program_start

__intvec:
    DC8     0x82
    DC24    __iar_program_start          ; RESET    0x8000
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
    DC24    SIG_OUTPUT_COMPARE1A        ;8034
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


; Just a filler for unused interrupt vectors.
vNoISR:
	iret


	END

