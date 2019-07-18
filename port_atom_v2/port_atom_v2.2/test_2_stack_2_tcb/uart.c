#include <stdio.h>
#include "mymacro.h"
#include "atom.h"
#include "atommutex.h"
#include "usart.h"
#include <yfuns.h>


/*
 * Semaphore for single-threaded access to UART device
 */
static ATOM_MUTEX uart_mutex;


/*
 * Initialize the UART to requested baudrate, tx/rx, 8N1.
 */
int uart_init(void)
{
  int status;
  
  /* 1 start bit, 8 data bits */
  cbi(USART1->CR1, 4);
  /* 1 stop bit */
  USART1->CR3 = 0x00;
  /* 
  * baud rate, see config in page 533 reference manual 
  * Fsysclk = 16MHz
  */
  USART1->BRR2 = 0x03;
  USART1->BRR1 = 0x68;
  /*
  * enable transmitter
  * enable receiver
  */
  sbi(USART1->CR2, 2);
  sbi(USART1->CR2, 3);

  /* Create a mutex for single-threaded putchar() access */
  if (atomMutexCreate (&uart_mutex) != ATOM_OK)
  {
    status = -1;
  }
  else
  {
    status = 0;
  }

  /* Finished */
  return (status);
}

char uart_putchar (char c)
{
    /* Block on private access to the UART */
    if (atomMutexGet(&uart_mutex, 0) == ATOM_OK)
    {
        /* Convert \n to \r\n */
        if (c == '\n')
            putchar('\r');

        while(!bit_is_set(USART1->SR, 7)) {} //wait until SDR empty -> able write to USART_DR without overwrite old data
        USART1->DR = c;
      
        while(!bit_is_set(USART1->SR, 6)) {}

        /* Return mutex access */
        atomMutexPut(&uart_mutex);
    }

    return (c);
}

_STD_BEGIN

#pragma module_name = "?__write"

/*
 * If the __write implementation uses internal buffering, uncomment
 * the following line to ensure that we are called with "buffer" as 0
 * (i.e. flush) when the application terminates.
 */

size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  /* Remove the #if #endif pair to enable the implementation */
#if 1    

  size_t nChars = 0;

  if (buffer == 0)
  {
    /*
     * This means that we should flush internal buffers.  Since we
     * don't we just return.  (Remember, "handle" == -1 means that all
     * handles should be flushed.)
     */
    return 0;
  }

  /* This template only writes to "standard out" and "standard err",
   * for all other file handles it returns failure. */
  if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR)
  {
    return _LLIO_ERROR;
  }

  for (/* Empty */; size != 0; --size)
  {
    uart_putchar(*buffer++);
    ++nChars;
  }

  return nChars;

#else

  /* Always return error code when implementation is disabled. */
  return _LLIO_ERROR;

#endif

}

_STD_END