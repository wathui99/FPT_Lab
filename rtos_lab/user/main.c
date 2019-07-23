#include "main.h"

volatile uint32_t cnt = 0;

#define DEBUG

#ifndef DEBUG
  #define printf(s)
#endif

#define IDLE_STACK_SIZE_BYTES       128
#define MAIN_STACK_SIZE_BYTES       384

/* Local data */
uint8_t delay_time = 1;

/* Semaphore 
* semLCD: control LCD display thread
* semStatusLed: control read/write delay_time variable
*/
ATOM_SEM semLCD;
ATOM_SEM semDelayTime;

/* Application threads' TCBs */
static ATOM_TCB led_thread_tcb;
static ATOM_TCB button_thread_tcb;
static ATOM_TCB display_thread_tcb;

/* LED thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t led_thread_stack[MAIN_STACK_SIZE_BYTES];
/* BUTTON thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t button_thread_stack[MAIN_STACK_SIZE_BYTES];
/* BUTTON thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t display_thread_stack[MAIN_STACK_SIZE_BYTES];

/* Idle thread's stack area (large so place outside of the small page0 area on STM8) */
NEAR static uint8_t idle_thread_stack[IDLE_STACK_SIZE_BYTES];

/* Forward declarations */
static void led_thread (uint32_t param);
static void button_thread (uint32_t param);
static void display_thread (uint32_t param);

NO_REG_SAVE void main ( void ){

  InitClock_Source(CLK_SYSCLKSource_HSI, CLK_SYSCLKDiv_1); 
  
  switch(CLK_GetSYSCLKSource())
  {
  case CLK_SYSCLKSource_HSI:
    printf ("CLK_SYSCLKSource_HSI\n");
  break;
  case CLK_SYSCLKSource_HSE:
    printf ("CLK_SYSCLKSource_HSE\n");
  break;
  case CLK_SYSCLKSource_LSI:
    printf ("CLK_SYSCLKSource_LSI\n");
  break;
  case CLK_SYSCLKSource_LSE:
    printf ("CLK_SYSCLKSource_LSE\n");
  break;
  };
  
  InitClock_Timer();
    int8_t status_led;
    int8_t status_button;
    int8_t status_display;
    /**
     * Note: to protect OS structures and data during initialisation,
     * interrupts must remain disabled until the first thread
     * has been restored. They are reenabled at the very end of
     * the first thread restore, at which point it is safe for a
     * reschedule to take place.
     */
    /* Initialise the OS before creating our threads */
    status_led = atomOSInit(&idle_thread_stack[0], IDLE_STACK_SIZE_BYTES, TRUE);
    
    if (status_led == ATOM_OK)
    {
        /* Enable the system tick timer */
        archInitSystemTickTimer();
        /* Create an application thread */
        status_led = atomThreadCreate(&led_thread_tcb,
                     TEST_THREAD_PRIO, led_thread, 0,
                     &led_thread_stack[0],
                     MAIN_STACK_SIZE_BYTES,
                     TRUE);
        status_button = atomThreadCreate(&button_thread_tcb,
                     TEST_THREAD_PRIO, button_thread, 0,
                     &button_thread_stack[0],
                     MAIN_STACK_SIZE_BYTES,
                     TRUE);
        status_display = atomThreadCreate(&display_thread_tcb,
                     TEST_THREAD_PRIO, display_thread, 0,
                     &display_thread_stack[0],
                     MAIN_STACK_SIZE_BYTES,
                     TRUE);
        /* 3 thread create successful */
        if (status_button == ATOM_OK && status_led == ATOM_OK && status_display == ATOM_OK)
        {
          /* 2 semaphore create successful */
          if(atomSemCreate(&semLCD, 1) == ATOM_OK && atomSemCreate(&semDelayTime, 1) == ATOM_OK) {
            atomOSStart();
          }
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
    /*local delay variable*/
    uint16_t local_delay_time = delay_time*SYSTEM_TICKS_PER_SEC;
    while (1)
    {
      Port_E->ODR ^= 0x80;
      atomSemGet(&semDelayTime, 0); //request right, no time out
      local_delay_time = delay_time*SYSTEM_TICKS_PER_SEC; //update new value
      atomSemPut(&semDelayTime); //increase semaphore delay time
      atomTimerDelay (local_delay_time);
    }
}

static void button_thread (uint32_t param){
    /* Compiler warnings */
    param = param;
    /* Init PC7 as output pin */
    gpio_init(Port_C, 0x80, Out_PP_High_Fast );
    /* Init PC1 as input pin without interrupt */
    gpio_init(Port_C, 0x02, In_Fl_No_IT );
    /* Put a message out on the UART or terminal */
    printf ("button_thread has been created\n");
    while (1){
      if(!GPIO_read(Port_C,0x02)){
         atomSemGet(&semDelayTime, 0); //request right, no time out
         delay_time = (delay_time%3) + 1;
         atomSemPut(&semDelayTime); //increase semaphore delay time
         atomSemPut(&semLCD); //increase semaphore control LCD
         Port_C->ODR ^= 0x80;
         while(!GPIO_read(Port_C,0x02));
      }
    }
}

static void display_thread (uint32_t param){
    /* Compiler warnings */
    param = param;
    /* Enable LCD & RTC clock */
    InitClock_LCD_RTC();
    /* Init LCD */
    config_LCDvsRTC();
    /* Put a message out on the UART or terminal */
    printf ("display_thread has been created\n");
    LCD_printf("time %d",delay_time);    
    while (1){
       atomSemGet(&semLCD, 0); //request right to print lcd, no time out
       printf ("D\n");
       LCD_printf("time %d",delay_time);
    }
}
