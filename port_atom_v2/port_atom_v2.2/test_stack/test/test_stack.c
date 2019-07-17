#include "atom.h"
#include "test_stack.h"
#include "gpio.h"
#include <stdio.h>

/* Number of test threads */
#define NUM_TEST_THREADS      2


/* Test OS objects */
ATOM_SEM sem_test;
static ATOM_TCB tcb[NUM_TEST_THREADS];
static uint8_t test_thread_stack[NUM_TEST_THREADS][TEST_THREAD_STACK_SIZE];


/* Forward declarations */
static void test1_thread_func (uint32_t param);
static void test2_thread_func (uint32_t param);

void test_start (void)
{
  if(atomSemCreate(&sem_test, 0) == ATOM_OK) {
      if(atomThreadCreate(&tcb[0], TEST_THREAD_PRIO, test1_thread_func, 0,
         test_thread_stack[0],
         TEST_THREAD_STACK_SIZE, TRUE) != ATOM_OK) {
        printf("Error creating thread 1\n");
      } else {
        printf("thread 1 created\n");
      }
      if (atomThreadCreate(&tcb[1], TEST_THREAD_PRIO, test2_thread_func, 0,
          test_thread_stack[1],
          TEST_THREAD_STACK_SIZE, TRUE) != ATOM_OK) {
        printf("Error creating thread 2\n");
      } else { 
        printf("thread 2 created\n");
      }
  }
}

static void test1_thread_func (uint32_t param)
{
    /* Compiler warnings */
    param = param;
    /* create an variable in the same stack */
    uint8_t value_test_1 = 1;
    /* Wait forever */
    while (1)
    {
      printf("this is thread 1 value after wait thread 2 is: %d\n", value_test_1);
      atomTimerDelay (SYSTEM_TICKS_PER_SEC);
    }
}

static void test2_thread_func (uint32_t param)
{
    /* Compiler warnings */
    param = param;
    /* create an variable in the same stack */
    uint8_t value_test_2 = 2;
    printf("this is thread 2 value is: %d", value_test_2);
    /* Wait forever */
    while (1)
    {
      atomTimerDelay (SYSTEM_TICKS_PER_SEC);
    }
}
