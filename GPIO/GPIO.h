#ifndef GPIO
#define GPIO
#include <stdio.h>
#include <stdlib.h>
typedef enum {FALSE=0,TRUE=1}bool;
#define uint8_t unsigned char 

//#define     __I     volatile const   /*!< defines 'read only' permissions     */
//#define     __O     volatile         /*!< defines 'write only' permissions    */
//#define     __IO    volatile         /*!< defines 'read / write' permissions  */


typedef struct{
  uint8_t ODR;
  uint8_t IDR;
  uint8_t DDR;
  uint8_t CR1;
  uint8_t CR2;
}GPIO_Type;

// GPIO mode
typedef enum{
	In_Fl_No_IT      = (uint8_t)0x00, // input, floating point, non-external Interrupt
	In_Fl_IT         = (uint8_t)0x20, // input, floating point, external Interrupt
	In_PU_No_IT      = (uint8_t)0x40, // input, pull up, non-external Interrupt
	In_PU_IT         = (uint8_t)0x60, // input, Pull up, external Interrupt
	Out_OD_Low_Fast  = (uint8_t)0xA0, // Output, open drain, low level, 10Mhz
	Out_PP_Low_Fast  = (uint8_t)0xE0, // Output, push-pulse, low level, 10Mhz
	Out_OD_Low_Slow  = (uint8_t)0x80, // Output, open drain, low level, 2Mhz
	Out_PP_Low_Slow  = (uint8_t)0xC0, // Output, open drain, low level, 2Mhz
	Out_OD_High_Fast = (uint8_t)0xB0, // Output, open drain, high level, 10Mhz
	Out_PP_High_Fast = (uint8_t)0xF0, //Output, push-pulse, high level, 10Mhz
	Out_OD_High_Slow = (uint8_t)0x90, //  Output, open drain, high level, 2Mhz
	Out_PP_High_Slow = (uint8_t)0xD0 // ouput, push-pulse, high level, 2Mhz
}GPIO_Mode;


// define PortX address
#define Port_A (( GPIO_Type *)0x5000)
#define Port_B (( GPIO_Type *)0x5005)
#define Port_C (( GPIO_Type *)0x500A)
#define Port_D (( GPIO_Type *)0x500F)
#define Port_E (( GPIO_Type *)0x5014)
#define Port_F (( GPIO_Type *)0x5019)

bool gpio_init(GPIO_Type* Port_X, uint8_t GPIO_Pin, GPIO_Mode mode );
bool gpio_deinit(GPIO_Type* Port_X);
void GPIO_Write(GPIO_Type* GPIO_X, uint8_t select_pins);
bool GPIO_read (GPIO_Type* GPIO_X,uint8_t GPIO_Pin);

#endif
