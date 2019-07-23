/**
  ******************************************************************************
  * @author  LeHoangPhuc
  * @date    June-2019
  * @course  FGA-UIT training course
  ******************************************************************************
  * @attention
  * I wrote this libary to use in course only.
  * Any problem, please contact me at:
  *        https://github.com/hoangphuc-fn
  ******************************************************************************
  */ 

#ifndef _stm8l_lcd_h_
#define _stm8l_lcd_h_

#include <stdint.h>
#include <stdarg.h>

typedef struct LCD_struct{
  volatile unsigned char CR1;      /*!< LCD control register 1 */
  volatile unsigned char CR2;      /*!< LCD control register 2 */
  volatile unsigned char CR3;      /*!< LCD control register 3 */
  volatile unsigned char FRQ;      /*!< LCD frequency register */
  volatile unsigned char PM[6];    /*!< LCD portmask registers*/
  volatile unsigned char RESERVED1[2];  /*!< Reserved */
  volatile unsigned char RAM[22];  /*!< LCD RAM registers*/
  volatile unsigned char RESERVED2[13]; /*!< Reserved */
  volatile unsigned char CR4;      /*!< LCD control register 4 */
}LCD_TypeDef;

#define LCD                             ((LCD_TypeDef *) 0x5400)

/******************************************************************************/
/*                          Define group LCD_Prescaler            	      */
/******************************************************************************/
typedef enum {
  LCD_Prescaler_1     = (uint8_t)0x00, /*!< CLKprescaler = ClKinput       */
  LCD_Prescaler_2     = (uint8_t)0x10, /*!< CLKprescaler = ClKinput/2     */
  LCD_Prescaler_4     = (uint8_t)0x20, /*!< CLKprescaler = ClKinput/4     */
  LCD_Prescaler_8     = (uint8_t)0x30, /*!< CLKprescaler = ClKinput/8     */
  LCD_Prescaler_16    = (uint8_t)0x40, /*!< CLKprescaler = ClKinput/16    */
  LCD_Prescaler_32    = (uint8_t)0x50, /*!< CLKprescaler = ClKinput/32    */
  LCD_Prescaler_64    = (uint8_t)0x60, /*!< CLKprescaler = ClKinput/64    */
  LCD_Prescaler_128   = (uint8_t)0x70, /*!< CLKprescaler = ClKinput/128   */
  LCD_Prescaler_256   = (uint8_t)0x80, /*!< CLKprescaler = ClKinput/256   */
  LCD_Prescaler_512   = (uint8_t)0x90, /*!< CLKprescaler = ClKinput/512   */
  LCD_Prescaler_1024  = (uint8_t)0xA0, /*!< CLKprescaler = ClKinput/1024  */
  LCD_Prescaler_2048  = (uint8_t)0xB0, /*!< CLKprescaler = ClKinput/2048  */
  LCD_Prescaler_4096  = (uint8_t)0xC0, /*!< CLKprescaler = ClKinput/4096  */
  LCD_Prescaler_8192  = (uint8_t)0xD0, /*!< CLKprescaler = ClKinput/8192  */
  LCD_Prescaler_16384 = (uint8_t)0xE0, /*!< CLKprescaler = ClKinput/16384 */
  LCD_Prescaler_32768 = (uint8_t)0xF0  /*!< CLKprescaler = ClKinput/32768 */
} LCD_Prescaler_TypeDef;

/******************************************************************************/
/*                          Define group LCD_Divider            	      */
/******************************************************************************/
typedef enum {
  LCD_Divider_16 = (uint8_t)0x00, /*!< LCD frequency = CLKprescaler/16 */
  LCD_Divider_17 = (uint8_t)0x01, /*!< LCD frequency = CLKprescaler/17 */
  LCD_Divider_18 = (uint8_t)0x02, /*!< LCD frequency = CLKprescaler/18 */
  LCD_Divider_19 = (uint8_t)0x03, /*!< LCD frequency = CLKprescaler/19 */
  LCD_Divider_20 = (uint8_t)0x04, /*!< LCD frequency = CLKprescaler/20 */
  LCD_Divider_21 = (uint8_t)0x05, /*!< LCD frequency = CLKprescaler/21 */
  LCD_Divider_22 = (uint8_t)0x06, /*!< LCD frequency = CLKprescaler/22 */
  LCD_Divider_23 = (uint8_t)0x07, /*!< LCD frequency = CLKprescaler/23 */
  LCD_Divider_24 = (uint8_t)0x08, /*!< LCD frequency = CLKprescaler/24 */
  LCD_Divider_25 = (uint8_t)0x09, /*!< LCD frequency = CLKprescaler/25 */
  LCD_Divider_26 = (uint8_t)0x0A, /*!< LCD frequency = CLKprescaler/26 */
  LCD_Divider_27 = (uint8_t)0x0B, /*!< LCD frequency = CLKprescaler/27 */
  LCD_Divider_28 = (uint8_t)0x0C, /*!< LCD frequency = CLKprescaler/28 */
  LCD_Divider_29 = (uint8_t)0x0D, /*!< LCD frequency = CLKprescaler/29 */
  LCD_Divider_30 = (uint8_t)0x0E, /*!< LCD frequency = CLKprescaler/30 */
  LCD_Divider_31 = (uint8_t)0x0F  /*!< LCD frequency = CLKprescaler/31 */
} LCD_Divider_TypeDef;

/******************************************************************************/
/*                          Define group LCD_Contrast            	      */
/******************************************************************************/
typedef enum {
  LCD_Contrast_Level_0 = (uint8_t)0x00, /*!< Medium Density / High Density Maximum Voltage = 2.60V / 2.60V */
  LCD_Contrast_Level_1 = (uint8_t)0x02, /*!< Medium Density / High Density Maximum Voltage = 2.70V / 2.73V */
  LCD_Contrast_Level_2 = (uint8_t)0x04, /*!< Medium Density / High Density Maximum Voltage = 2.80V / 2.86V */
  LCD_Contrast_Level_3 = (uint8_t)0x06, /*!< Medium Density / High Density Maximum Voltage = 2.90V / 2.99V */
  LCD_Contrast_Level_4 = (uint8_t)0x08, /*!< Medium Density / High Density Maximum Voltage = 3.00V / 3.12V */
  LCD_Contrast_Level_5 = (uint8_t)0x0A, /*!< Medium Density / High Density Maximum Voltage = 3.10V / 3.25V */
  LCD_Contrast_Level_6 = (uint8_t)0x0C, /*!< Medium Density / High Density Maximum Voltage = 3.20V / 3.38V */
  LCD_Contrast_Level_7 = (uint8_t)0x0E  /*!< Medium Density / High Density Maximum Voltage = 3.30V / 3.51V */
} LCD_Contrast_TypeDef;

/******************************************************************************/
/*                          Define group LCD_Pulse	            	      */
/******************************************************************************/
typedef enum {
  LCD_PulseOnDuration_0 = (uint8_t)0x00, /*!< Pulse on duration = 0/CLKprescaler  */
  LCD_PulseOnDuration_1 = (uint8_t)0x20, /*!< Pulse on duration = 1/CLKprescaler  */
  LCD_PulseOnDuration_2 = (uint8_t)0x40, /*!< Pulse on duration = 2/CLKprescaler  */
  LCD_PulseOnDuration_3 = (uint8_t)0x60, /*!< Pulse on duration = 3/CLKprescaler  */
  LCD_PulseOnDuration_4 = (uint8_t)0x80, /*!< Pulse on duration = 4/CLKprescaler  */
  LCD_PulseOnDuration_5 = (uint8_t)0xA0, /*!< Pulse on duration = 5/CLKprescaler  */
  LCD_PulseOnDuration_6 = (uint8_t)0xC0, /*!< Pulse on duration = 6/CLKprescaler  */
  LCD_PulseOnDuration_7 = (uint8_t)0xE0  /*!< Pulse on duration = 7/CLKprescaler  */
} LCD_PulseOnDuration_TypeDef;

/******************************************************************************/
/*                          Define group LCD_DeadTime	            	      */
/******************************************************************************/
typedef enum {
  LCD_DeadTime_0 = (uint8_t)0x00, /*!< No dead Time  */
  LCD_DeadTime_1 = (uint8_t)0x01, /*!< One Phase between different couple of Frame   */
  LCD_DeadTime_2 = (uint8_t)0x02, /*!< Two Phase between different couple of Frame   */
  LCD_DeadTime_3 = (uint8_t)0x03, /*!< Tree Phase between different couple of Frame  */
  LCD_DeadTime_4 = (uint8_t)0x04, /*!< Four Phase between different couple of Frame  */
  LCD_DeadTime_5 = (uint8_t)0x05, /*!< Five Phase between different couple of Frame  */
  LCD_DeadTime_6 = (uint8_t)0x06, /*!< Six Phase between different couple of Frame   */
  LCD_DeadTime_7 = (uint8_t)0x07  /*!< Seven Phase between different couple of Frame */
} LCD_DeadTime_TypeDef;

/******************************************************************************/
/*                          Define group LCD_Duty	            	      */
/******************************************************************************/
typedef enum {
  LCD_Duty_Static = (uint8_t)0x00, /*!< Static duty */
  LCD_Duty_1_2    = (uint8_t)0x02, /*!< 1/2 duty    */
  LCD_Duty_1_3    = (uint8_t)0x04, /*!< 1/3 duty    */
  LCD_Duty_1_4    = (uint8_t)0x06, /*!< 1/4 duty    */
  LCD_Duty_1_8    = (uint8_t)0x20  /*!< 1/8 duty    */
} LCD_Duty_TypeDef;

/******************************************************************************/
/*                          Define for User				      */
/******************************************************************************/
/*!< Array of character */

static uint16_t char_list[38] = {
/*0-0     1      2      3      4      5      6      7      8      9     */
0x00D7,0x0006,0x007D,0x006F,0x00AE,0x00EB,0x00FB,0x0046,0x00FF,0x00EF, 
/*A-10    B      C      D      E      F      G      H      I      J     */
0x00FE,0x4467,0x00D1,0x4447,0x00F9,0x00F8,0x00F3,0x00BE,0x4400,0x0017,
/*K-20    L      M      N      O      P      Q      R      S      T     */
0x1198,0x0091,0x9096,0x8196,0x00D7,0x00FC,0x01D7,0x01FC,0x00EB,0x4440,
/*U-30    V      W      X      Y      Z    SPACE     -                  */
0x0097,0x3090,0x2196,0xB100,0x9400,0x3041,0x0000, 0x0028};
/*!< buffer to process */
static uint8_t buffer_lcd[2];
/*!< pointer of lcd  -  max value is 6 (LCD has 6 columns) */
static uint8_t lcd_pointer = 1;

/*!< Config & Init LCD vs RTC */
void config_LCDvsRTC();
/*!< Delete all character on LCD */
void lcd_clear();
/*!< Display character following the defined array */
void lcd_print(int16_t character, uint8_t pos);
/*!< Display a character (ASCII) at pos-position on LCD */
void lcd_print_char(char c, uint8_t pos);
/*!< Display a string at pos-position on LCD */
void lcd_print_string(char* str, uint8_t pos);
/*!< Display a character at next-position (lcd_pointer) on LCD */
void lcd_print_char_auto(char c);
/*!< Display a string at next-position (lcd_pointer) on LCD */
void lcd_print_string_auto(char* str);
/*!< Convert integer number into octal, hex, etc... */
char* convert(unsigned int, int); 
/*!< Reset status of LCD */
void LCD_reset();
/*!< LCD printf function same as printf function in "stdio.h" file */
/*!< Only support for %c %d %s %x %o */
void LCD_printf(char *,...); 

#endif /*_stm8l_lcd_h_*/