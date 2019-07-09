#include <stdint.h>
#include <intrinsics.h>
#include "clk.h"
#include "tim1.h"
#include "lcd.h"

uint16_t LCDVal = 0;

char* itoa(int i, char b[]);
void Delay_TIM1(unsigned long int value);
void Print_Digits(uint16_t value);

void main (void) {
  Clk_Init();
  Tim1_Init();
  LCD_Init();
  Lcd_Clear();
  __enable_interrupt(); //enable global interrupt
  while(1) {
    
  }
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

void Delay_TIM1(unsigned long int value) {
  timeCount_TIM1=0;
  while(timeCount_TIM1<value) {}
}

void Print_Digits(uint16_t value) {
  char stringVal[10];
  Lcd_Clear();
  itoa(value, stringVal);
  Lcd_Print_String(stringVal, 1);
}

#pragma vector = 25 //23+2
__interrupt void TIM1_Update (void) {
  timeCount_TIM1++;
  LCDVal++;
  if(LCDVal>9999) LCDVal = 0;
  Print_Digits(LCDVal);
  cbi(TIM1->SR1, 0); //clear UIF flag
}

