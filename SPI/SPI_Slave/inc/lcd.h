#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>
#include "mymacro.h"
#include <ctype.h> //xu ly ki tu

typedef struct LCD_struct
{
  volatile uint8_t CR1;      /*!< LCD control register 1 */
  volatile uint8_t CR2;      /*!< LCD control register 2 */
  volatile uint8_t CR3;      /*!< LCD control register 3 */
  volatile uint8_t FRQ;      /*!< LCD frequency register */
  volatile uint8_t PM[6];    /*!< LCD portmask registers*/
  uint8_t RESERVED1[2];  /*!< Reserved */
  volatile uint8_t RAM[22];  /*!< LCD RAM registers*/
  uint8_t RESERVED2[13]; /*!< Reserved */
  volatile uint8_t CR4;      /*!< LCD control register 4 */
}
LCD_TypeDef;

#define LCD_BASE                    (uint16_t)0x5400
#define LCD                         ((LCD_TypeDef *) LCD_BASE)

void LCD_Init(void);
void Start_Write_Ram(void);
void Lcd_Clear_Col(uint8_t pos);
void Lcd_Clear_All(void);
void Lcd_Print_Char(char charPrint, uint8_t pos);
void Lcd_Print_String(char* str, uint8_t pos);

#endif /* __LCD_H */