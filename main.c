#include <stdint.h>
#include "intrinsics.h"
#include "timer1.h"
#include <timer1.h>

#define PortAb   ((GPIObit*)0x5000)    
#define PortBb   ((GPIObit*)0x5005)   
#define PortCb   ((GPIObit*)0x500a)   
#define PortDb   ((GPIObit*)0x500f)   
#define PortEb   ((GPIObit*)0x5014)  
#define PortFb   ((GPIObit*)0x5019) 

typedef struct ODR
{
  uint8_t       ODR0 :1;
  uint8_t       ODR1 :1;
  uint8_t       ODR2 :1;
  uint8_t       ODR3 :1;
  uint8_t       ODR4 :1;
  uint8_t       ODR5 :1;
  uint8_t       ODR6 :1;
  uint8_t       ODR7 :1;
}ODRreg;
 
typedef struct IDR
{
  uint8_t       IDR0 :1;
  uint8_t       IDR1 :1;
  uint8_t       IDR2 :1;
  uint8_t       IDR3 :1;
  uint8_t       IDR4 :1;
  uint8_t       IDR5 :1;
  uint8_t       IDR6 :1;
  uint8_t       IDR7 :1;
}IDRreg;

typedef struct DDR
{
  uint8_t       DDR0 :1;
  uint8_t       DDR1 :1;
  uint8_t       DDR2 :1;
  uint8_t       DDR3 :1;
  uint8_t       DDR4 :1;
  uint8_t       DDR5 :1;
  uint8_t       DDR6 :1;
  uint8_t       DDR7 :1;
}DDRreg;

typedef struct CR1
{
  uint8_t       CR10 :1;
  uint8_t       CR11 :1;
  uint8_t       CR12 :1;
  uint8_t       CR13 :1;
  uint8_t       CR14 :1;
  uint8_t       CR15 :1;
  uint8_t       CR16 :1;
  uint8_t       CR17 :1;
}CR1reg;

typedef struct CR2
{
  uint8_t       CR20 :1;
  uint8_t       CR21 :1;
  uint8_t       CR22 :1;
  uint8_t       CR23 :1;
  uint8_t       CR24 :1;
  uint8_t       CR25 :1;
  uint8_t       CR26 :1;
  uint8_t       CR27 :1;
}CR2reg;

//Define with bitfeild stype    
typedef struct GPIORegbit
{
  ODRreg       ODR;
  IDRreg       IDR;
  DDRreg       DDR;
  CR1reg       CR1;
  CR2reg       CR2;
} GPIObit;


typedef struct Clock
{
  uint8_t       CLK_DIVR;
  uint8_t       CLK_CRTCR;
  uint8_t       CLK_ICKR;
  uint8_t       CLK_PCKENR1;
  uint8_t       CLK_PCKENR2;   
  uint8_t       CLK_CCOR;
  uint8_t       CLK_ECKR;
  uint8_t       CLK_SCSR;
  uint8_t       CLK_SWR;
  uint8_t       CLK_SWCR;   
  uint8_t       CLK_CSSR;
  uint8_t       CLK_CBEEPR;
  uint8_t       CLK_HSICALR;
  uint8_t       CLK_HSITRIMR;
  uint8_t       CLK_HSIUNLCKR;
  uint8_t       CLK_REGCSR; 
}ClodkReg;

#define Clock   ((ClodkReg*)0x50C0) 


int main( void )
{
  Clock->CLK_DIVR = 0x00;
  Clock->CLK_PCKENR2 = 0x02;
  
  PortCb->DDR.DDR7=1;\
  PortCb->CR1.CR17=1;\
  Quantumn_time_RoundRobin_10ms();
  
  asm("rim\n");
  
  return 0;
}
_Pragma( "vector = 25" ) __interrupt void
tim1_int_handler( void )
{
  PortCb->ODR.ODR7^=1; //for debug
  TIM1->TIM1_SR1 = ~0x01;
}

