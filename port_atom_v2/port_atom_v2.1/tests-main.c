#include <stdio.h>
#include "atom.h"
#include "atomport-private.h"
#include "atomport-tests.h"
#include "atomtimer.h"
#include "uart.h"
#include "gpio.h"
#include "clk.h"


/* Constants */
#define IDLE_STACK_SIZE_BYTES       128
#define TEST_THREAD_STACK_SIZE      192
#define TEST_THREAD_PRIO            16

/* Number of test threads */
#define NUM_TEST_THREADS      2

/* Test OS objects */
static ATOM_TCB tcb[NUM_TEST_THREADS];
static uint8_t test_thread_stack[NUM_TEST_THREADS][TEST_THREAD_STACK_SIZE];

/* Idle thread's stack area (large so place outside of the small page0 area on STM8) */
static uint8_t idle_thread_stack[IDLE_STACK_SIZE_BYTES];

/* Forward declarations */
static void test1_thread_func (uint32_t param);
static void test2_thread_func (uint32_t param);

NO_REG_SAVE void main ( void )
{
    int8_t status;
    
    /* Initialise the OS before creating our threads */
    status = atomOSInit(&idle_thread_stack[0], IDLE_STACK_SIZE_BYTES, TRUE);
    if (status == ATOM_OK)
    {
        /* Init clk with sysclk=16Mhz */
        Clk_Init();
        
        /* Enable the system tick timer*/
        archInitSystemTickTimer();
        
        /* Initilize Periphs */
        GPIO_Init();
        uart_init(); //baudrate = 9600
        
        /* status create os, thread*/
        status = 0;
        
        /* Create an application thread */
        /* Create thread 1 */
        if(atomThreadCreate(&tcb[0], TEST_THREAD_PRIO, test1_thread_func, 0,
           &test_thread_stack[0][0],
           TEST_THREAD_STACK_SIZE, TRUE) != ATOM_OK) {
          /* if error create thread 1 */
          printf("Error creating thread 1\n");
          status--;
        } else {
          printf("thread 1 created\n");
        }
        /* Create thread 2 */
        if (atomThreadCreate(&tcb[1], TEST_THREAD_PRIO, test2_thread_func, 0,
            &test_thread_stack[1][0],
            TEST_THREAD_STACK_SIZE, TRUE) != ATOM_OK) {
          /* if error create thread 2 */
          printf("Error creating thread 2\n");
          status--;
        } else { 
          printf("thread 2 created\n");
        }
        /* if there's no error occur -> start OS */
        if (status == 0)
        {
            atomOSStart();
        }
    }

    /* There was an error starting the OS if we reach here */
    while (1)
    {
    }
}

static void test1_thread_func (uint32_t param)
{
    /* Compiler warnings */
    param = param;
    /* Wait forever */
    while (1)
    {
      printf("thread 1: Togle led\n");
      Togle_Led_Green();
      atomTimerDelay (SYSTEM_TICKS_PER_SEC);
    }
}

static void test2_thread_func (uint32_t param)
{
    /* Compiler warnings */
    param = param;
    /* Wait forever */
    while (1)
    {
      if(Check_User_Btn()) {
        printf("thread 2: BTN press\n");
        Togle_Led_Blue();
        while(Check_User_Btn());
      }
    }
}

