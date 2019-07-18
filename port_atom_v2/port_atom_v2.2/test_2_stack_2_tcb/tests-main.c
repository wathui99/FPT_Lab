/*
*/

#include <stdio.h>
#include <stdlib.h>
#include "atom.h"
#include "atomport-private.h"
#include "atomport-tests.h"
#include "atomtimer.h"
#include "atomsem.h"
#include "uart.h"
#include "gpio.h"
#include "clk.h"

/* Constants */
#define IDLE_STACK_SIZE_BYTES       128
#define TEST_THREAD_STACK_SIZE      192
#define BUTTON_THREAD_PRIO          16
#define LED_THREAD_PRIO             16

/* Number of test threads */
#define NUM_TEST_THREADS      2

/* Test OS objects */
static ATOM_TCB tcb[NUM_TEST_THREADS];
static uint8_t led_thread_stack[TEST_THREAD_STACK_SIZE];
static uint8_t button_thread_stack[TEST_THREAD_STACK_SIZE];

/* process mode */
ATOM_SEM sem_editMode;
uint8_t mode=1; //mode 1s flash led (default)

/* Idle thread's stack area (large so place outside of the small page0 area on STM8) */
static uint8_t idle_thread_stack[IDLE_STACK_SIZE_BYTES];

/* Forward declarations */
static void Led_Stask (uint32_t param);
static void Button_Stask (uint32_t param);

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
        
        /* creat semaphore for read and write mode */
        atomSemCreate(&sem_editMode, 1);
        
        /* Create an application thread */
        /* Create thread 1 */
        if(atomThreadCreate(&tcb[0], BUTTON_THREAD_PRIO, Button_Stask, 0,
           &button_thread_stack[0],
           TEST_THREAD_STACK_SIZE, TRUE) != ATOM_OK) {
          /* if error create thread 1 */
          printf("Error creating thread 1\n");
          status--;
        } else {
          printf("thread 1 created\n");
        }
        /* Create thread 2 */
        if (atomThreadCreate(&tcb[1], LED_THREAD_PRIO, Led_Stask, 0,
            &led_thread_stack[0],
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

static void Led_Stask (uint32_t param)
{
    /* Compiler warnings */
    param = param;
    
    uint16_t tickDelay=mode*SYSTEM_TICKS_PER_SEC;
    
    /* Wait forever */
    while (1)
    {
      Togle_Led_Green();
      atomSemGet(&sem_editMode,0);
      tickDelay=mode*SYSTEM_TICKS_PER_SEC;
      printf("\nthread 1: Togle led, time delay: %d", tickDelay);
      atomSemPut(&sem_editMode);
      atomTimerDelay (tickDelay);
    }
}

static void Button_Stask (uint32_t param)
{
    /* Compiler warnings */
    param = param;
    /* Wait forever */
    while (1)
    {
      if(Check_User_Btn()) {
        atomSemGet(&sem_editMode,0);
        mode = (mode % 4) + 1;
        atomSemPut(&sem_editMode);
        printf("\nthread 2: BTN press, change mode to: %d", mode);
        Togle_Led_Blue();
        while(Check_User_Btn());
      }
    }
}

