#include "lcd.h"

void LCD_Init(void) {
  /*
  *LCD onboard has 4 commons => duty = 1/4
  *LCDclk = 16.384 kHz
  *PS[3:0]=2, DIV[3:0]=0, Ratio = 64, fLCD = 256, f_frame=64 Hz, BLINKF[2:0]: /256, f_BLINK = 1 Hz
  */
  LCD->FRQ = (uint8_t)0x20; //ps and div
  LCD->CR1 = (uint8_t)0x2E; //no blink, blink fre=258 | duty=1/4, bias=1/3
  /* */
  LCD->PM[0] = 0xFF; 
  LCD->PM[1] = 0xFF; 
  LCD->PM[2] = 0xFF; 
  LCD->PM[3] = 0xFF; 
  LCD->PM[4] = 0xFF; 
  LCD->PM[5] = 0xFF; 
  /* Pulse on duration = 3 CLK_PS pulses, HD enable, VLCD7 = 3.3V, internal source */
  LCD->CR2 = 0x0E;
  /* adj contrast:
  * medium contrast => dead time = 3-phase
  * no interrupt
  */
  LCD->CR3 &= 0xF8;
  LCD->CR3 |= 0x03; //dead time
  sbi(LCD->CR3, 6); //enable lcd
}

/*
! Need to do before writing to LCD ram
*/
void Start_Write_Ram(void) {
  sbi(LCD->CR3, 3); //clear SOF flag
  while(!bit_is_set(LCD->CR3, 4)); //wait SOF active
}

/* Clear 2 digits LCD */
void LCD_Clear_Digits() {
  Start_Write_Ram();
  LCD->RAM[0]=0x00;
  LCD->RAM[2]=0x00;
  LCD->RAM[3]=0x00;
  LCD->RAM[6]=0x00;
}

/* print each digits in each colum */
void LCD_Print_Digits(uint8_t col, uint8_t value) {
  if(value>9 || col>1) return;
  Start_Write_Ram();
  if(col==1) {
    switch(value) {
      case 0:
        LCD_Sb(0,2);
        LCD_Sb(6,1);
        LCD_Sb(6,0);
        LCD_Sb(2,4);
        LCD_Sb(3,7);
        LCD_Sb(3,6);
        break;
      case 1:
        LCD_Sb(2,4);
        LCD_Sb(3,7);
        break;
      case 2:
        LCD_Sb(6,0);
        LCD_Sb(2,4);
        LCD_Sb(2,5);
        LCD_Sb(0,3);
        LCD_Sb(0,2);
        LCD_Sb(3,6);
        break;
      case 3:
        LCD_Sb(6,0);
        LCD_Sb(2,4);
        LCD_Sb(2,5);
        LCD_Sb(0,3);
        LCD_Sb(3,7);
        LCD_Sb(3,6);
        break;
      case 4:
        LCD_Sb(6,1);
        LCD_Sb(2,5);
        LCD_Sb(0,3);
        LCD_Sb(2,4);
        LCD_Sb(3,7);
        break;
      case 5:
        LCD_Sb(6,0);
        LCD_Sb(6,1);
        LCD_Sb(2,5);
        LCD_Sb(0,3);
        LCD_Sb(3,7);
        LCD_Sb(3,6);
        break;
      case 6:
        LCD_Sb(6,0);
        LCD_Sb(6,1);
        LCD_Sb(0,2);
        LCD_Sb(3,6);
        LCD_Sb(3,7);
        LCD_Sb(0,3);
        LCD_Sb(2,5);
        break;
      case 7:
        LCD_Sb(6,0);
        LCD_Sb(2,4);
        LCD_Sb(3,7);
        break;
      case 8:
        LCD_Sb(0,2);
        LCD_Sb(6,1);
        LCD_Sb(6,0);
        LCD_Sb(2,4);
        LCD_Sb(3,7);
        LCD_Sb(3,6);
        LCD_Sb(2,5);
        LCD_Sb(0,3);
        break;
      case 9:
        LCD_Sb(6,1);
        LCD_Sb(6,0);
        LCD_Sb(2,4);
        LCD_Sb(3,7);
        LCD_Sb(3,6);
        LCD_Sb(2,5);
        LCD_Sb(0,3);
        break;
    }
  }
  if (col==0) {
    switch(value) {
      case 0:
        LCD_Sb(0,0);
        LCD_Sb(6,3);
        LCD_Sb(6,2);
        LCD_Sb(2,6);
        LCD_Sb(3,5);
        LCD_Sb(3,4);
        break;
      case 1:
        LCD_Sb(2,6);
        LCD_Sb(3,5);
        break;
      case 2:
        LCD_Sb(6,2);
        LCD_Sb(2,6);
        LCD_Sb(2,7);
        LCD_Sb(0,1);
        LCD_Sb(0,0);
        LCD_Sb(3,4);
        break;
      case 3:
        LCD_Sb(6,2);
        LCD_Sb(2,6);
        LCD_Sb(2,7);
        LCD_Sb(0,1);
        LCD_Sb(3,5);
        LCD_Sb(3,4);
        break;
      case 4:
        LCD_Sb(6,3);
        LCD_Sb(2,7);
        LCD_Sb(0,1);
        LCD_Sb(2,6);
        LCD_Sb(3,5);
        break;
      case 5:
        LCD_Sb(6,2);
        LCD_Sb(6,3);
        LCD_Sb(2,7);
        LCD_Sb(0,1);
        LCD_Sb(3,5);
        LCD_Sb(3,4);
        break;
      case 6:
        LCD_Sb(6,2);
        LCD_Sb(6,3);
        LCD_Sb(0,0);
        LCD_Sb(3,4);
        LCD_Sb(3,5);
        LCD_Sb(0,1);
        LCD_Sb(2,7);
        break;
      case 7:
        LCD_Sb(6,2);
        LCD_Sb(2,6);
        LCD_Sb(3,5);
        break;
      case 8:
        LCD_Sb(0,0);
        LCD_Sb(6,3);
        LCD_Sb(6,2);
        LCD_Sb(2,6);
        LCD_Sb(3,5);
        LCD_Sb(3,4);
        LCD_Sb(2,7);
        LCD_Sb(0,1);
        break;
      case 9:
        LCD_Sb(6,3);
        LCD_Sb(6,2);
        LCD_Sb(2,6);
        LCD_Sb(3,5);
        LCD_Sb(3,4);
        LCD_Sb(2,7);
        LCD_Sb(0,1);
        break;
    }
  }
}