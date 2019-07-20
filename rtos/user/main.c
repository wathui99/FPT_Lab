#include "main.h"

volatile uint32_t cnt = 0;

#define IDLE_STACK_SIZE_BYTES       128
#define MAIN_STACK_SIZE_BYTES       384

/* Local data */

/* Application threads' TCBs */
static ATOM_TCB led_thread_tcb;
static ATOM_TCB button_thread_tcb;

/* LED thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t led_thread_stack[MAIN_STACK_SIZE_BYTES];
/* BUTTON thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t button_thread_stack[MAIN_STACK_SIZE_BYTES];

/* Idle thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t idle_thread_stack[IDLE_STACK_SIZE_BYTES];

uint8_t delay_time = 1;
/* Forward declarations */
static void led_thread (uint32_t param);
static void button_thread (uint32_t param);

NO_REG_SAVE void main ( void ){

  InitClock_Source(CLK_SYSCLKSource_HSI, CLK_SYSCLKDiv_1);
  InitClock_Timer();
    int8_t status;
    int8_t st;
    /**
     * Note: to protect OS structures and data during initialisation,
     * interrupts must remain disabled until the first thread
     * has been restored. They are reenabled at the very end of
     * the first thread restore, at which point it is safe for a
     * reschedule to take place.
     */
    /* Initialise the OS before creating our threads */
    status = atomOSInit(&idle_thread_stack[0], IDLE_STACK_SIZE_BYTES, TRUE);
    
    if (status == ATOM_OK)
    {
        /* Enable the system tick timer */
        archInitSystemTickTimer();
        /* Create an application thread */
        status = atomThreadCreate(&led_thread_tcb,
                     TEST_THREAD_PRIO, led_thread, 0,
                     &led_thread_stack[0],
                     MAIN_STACK_SIZE_BYTES,
                     TRUE);
        st = atomThreadCreate(&button_thread_tcb,
                     TEST_THREAD_PRIO, button_thread, 0,
                     &button_thread_stack[0],
                     MAIN_STACK_SIZE_BYTES,
                     TRUE);
        
        if (st == ATOM_OK && status == ATOM_OK)
        {
            atomOSStart();
        }
    }
    /* There was an error starting the OS if we reach here */
    while (1){
       printf ("If this is printed, the OS initialization has failed\n");
    }

}

static void led_thread (uint32_t param){
    /* Compiler warnings */
    param = param;
    /* Init PE7 as output pin */
    gpio_init(Port_E, 0x80, Out_PP_Low_Fast );    
    /* Put a message out on the UART or terminal */
    printf ("led_thread has been created\n");
    while (1)
    {
      Port_E->ODR ^= 0x80;
      atomTimerDelay (SYSTEM_TICKS_PER_SEC*delay_time);
    }
}

static void button_thread (uint32_t param){
    /* Compiler warnings */
    param = param;
    /* Init PC7 as output pin */
    gpio_init(Port_C, 0x80, Out_PP_High_Fast );
    /* Init PC1 as input pin without interrupt */
    gpio_init(Port_C, 0x01, In_Fl_No_IT );
    /* Put a message out on the UART or terminal */
    printf ("button_thread has been created\n");
    while (1){
      if(!GPIO_read(Port_C,0x02)){
         delay_time++;
         if(delay_time>3) delay_time = 1;
         atomTimerDelay (SYSTEM_TICKS_PER_SEC);
      }
      else{
         Port_C->ODR ^= 0x80;
         atomTimerDelay (SYSTEM_TICKS_PER_SEC/10);
      }
    }
}