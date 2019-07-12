#ifndef __USART_H
#define __USART_H

#include <stdint.h>
#include "mymacro.h"
#include "tim4.h"

#define RECEIVE_FAIL 0

typedef struct USART_struct
{
  volatile uint8_t SR;   /*!<  USART status register  */
  volatile uint8_t DR;   /*!<  USART data register     */
  volatile uint8_t BRR1; /*!<  USART baud rate register   */
  volatile uint8_t BRR2; /*!<  USART DIV mantissa[11:8] SCIDIV fraction */
  volatile uint8_t CR1;  /*!<  USART control register 1     */
  volatile uint8_t CR2;  /*!<  USART control register 2     */
  volatile uint8_t CR3;  /*!<  USART control register 3      */
  volatile uint8_t CR4;  /*!< USART control register 4      */
  volatile uint8_t CR5;  /*!<  USART control register 5       */
  volatile uint8_t GTR;  /*!<  USART guard time register     */
  volatile uint8_t PSCR; /*!<  USART prescaler register     */
}
USART_TypeDef;

#define USART1_BASE                 (uint16_t)0x5230
#define USART1                      ((USART_TypeDef *) USART1_BASE)

extern char Buff_Receive_USART[200];

void USART1_Init(void);
void USART1_Send_Char(char value);
void USART1_Send_String(char *Str, uint8_t leng);
uint8_t USART1_Receive_Char(char *ch);
void USART1_Receive_String(char charDelim, uint8_t leng);
void USART1_Receive_String_TimeOut(char charDelim, uint8_t leng, unsigned long int timeOut);
void USART1_Receive_String_TimeOutReset(char charDelim, uint8_t leng, unsigned long int timeOut);

#endif /* __USART_H */