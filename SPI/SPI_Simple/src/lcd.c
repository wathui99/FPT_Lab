#include "lcd.h"

/*!< Array of character */
uint16_t char_list[37] = {
/*0-0     1      2      3      4      5      6      7      8      9     */
0x00D7,0x0006,0x007D,0x006F,0x00AE,0x00EB,0x00FB,0x0046,0x00FF,0x00EF, 
/*A-10    B      C      D      E      F      G      H      I      J     */
0x00FE,0x00BB,0x00D1,0x003F,0x00F9,0x00F8,0x00F3,0x00BE,0x4441,0x0017,
/*K-20    L      M      N      O      P      Q      R      S      T     */
0x1198,0x0091,0x9096,0x8196,0x00D7,0x00FC,0x00EE,0x01FC,0x00EB,0x4440,
/*U-30    V      W      X      Y      Z    SPACE                        */
0x0097,0x9096,0x2196,0xB100,0x9400,0x3041,0x0000};
uint8_t buffer[2]={0x00,0x00};

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
  LCD->PM[1] = 0x7F; 
  LCD->PM[2] = 0xFC;
  /* Pulse on duration = 3 CLK_PS pulses, HD enable, VLCD7 = 3.3V, internal source */
  LCD->CR2 = 0x0E;
  /* adj contrast:
  * max contrast => dead time = 0-phase
  * no interrupt
  */
  LCD->CR3 &= 0xF8;
  LCD->CR3 |= 0x00; //dead time
  sbi(LCD->CR3, 6); //enable lcd
}

/*
! Need to do before writing to LCD ram
*/
void Start_Write_Ram(void) {
  sbi(LCD->CR3, 3); //clear SOF flag
  while(!bit_is_set(LCD->CR3, 4)); //wait SOF active
}

void Lcd_Clear_Col(uint8_t pos) {
  Start_Write_Ram();
  switch(pos) {
  case 1:
    LCD->RAM[13] &=0xF3;
    LCD->RAM[9] &=0x3F;
    LCD->RAM[7] &=0xFC;
    LCD->RAM[10] &=0xCF;
    LCD->RAM[6] &=0xF3;
    LCD->RAM[0] &=0xFC;
    LCD->RAM[2] &=0x3F;
    LCD->RAM[3] &=0xCF;
    break;
  case 2:
    LCD->RAM[13] &=0xFC;
    LCD->RAM[9] &=0xCF;
    LCD->RAM[7] &=0xF3;
    LCD->RAM[10] &=0x3F;
    LCD->RAM[6] &=0xFC;
    LCD->RAM[0] &=0xF3;
    LCD->RAM[2] &=0xCF;
    LCD->RAM[3] &=0x3F;
    break;
  case 3:
    LCD->RAM[12] &=0x3F;
    LCD->RAM[9] &=0xF3;
    LCD->RAM[7] &=0xCF;
    LCD->RAM[11] &=0xFC;
    LCD->RAM[5] &=0x3F;
    LCD->RAM[0] &=0xCF;
    LCD->RAM[2] &=0xF3;
    LCD->RAM[4] &=0xFC;
    break;
  case 4:
    LCD->RAM[12] &=0xCF;
    LCD->RAM[9] &=0xFC;
    LCD->RAM[7] &=0x3F;
    LCD->RAM[11] &=0xF3;
    LCD->RAM[5] &=0xCF;
    LCD->RAM[0] &=0x3F;
    LCD->RAM[2] &=0xFC;
    LCD->RAM[4] &=0xF3;
    break;
  case 5:
    LCD->RAM[12] &=0xF3;
    LCD->RAM[8] &=0x3F;
    LCD->RAM[8] &=0xFC;
    LCD->RAM[11] &=0xCF;
    LCD->RAM[5] &=0xF3;
    LCD->RAM[1] &=0xFC;
    LCD->RAM[1] &=0x3F;
    LCD->RAM[4] &=0xCF;
    break;
  case 6:
    LCD->RAM[12] &=0xFC;
    LCD->RAM[8] &=0xCF;
    LCD->RAM[8] &=0xF3;
    LCD->RAM[11] &=0x3F;
    LCD->RAM[5] &=0xFC;
    LCD->RAM[1] &=0xF3;
    LCD->RAM[1] &=0xCF;
    LCD->RAM[4] &=0x3F;
    break;
  }
}

/*!< Delete all character on LCD */
void Lcd_Clear_All(){
  Start_Write_Ram();
  for(int i =0; i<14; i++){
    LCD->RAM[i] = 0x00;
  }
}
/*!< Display a character at pos-position on LCD */
void Lcd_Print_Char(char charPrint, uint8_t pos){
  if(!isalpha(charPrint) && !isalnum(charPrint) && charPrint!=' ') {
    return;
  }
  if(isalpha(charPrint)) {
    charPrint=toupper(charPrint);
  }
  int16_t character = charPrint-55;
  Start_Write_Ram();
  /*!< Space character */
  if(character<0)     character = 36;
  buffer[1] = (uint8_t)(char_list[character]>>8);
  buffer[0] = char_list[character];
  /*!< Print the character at each position*/
  if(pos == 6){
      LCD->RAM[12] &=0xFC;
      LCD->RAM[12] |=  (buffer[1]>>6) & 0x03;   // 6H 6J

      LCD->RAM[8] &=0xCF;
      LCD->RAM[8] |=  (buffer[1]) & 0x30;      // 6Q 6K

      LCD->RAM[8] &=0xF3;
      LCD->RAM[8] |=  (buffer[1]) & 0x0C;      // 6COL 6P

      LCD->RAM[11] &=0x3F;
      LCD->RAM[11] |=  (buffer[1]<<6) & 0xC0;   // 6DP 6N

      LCD->RAM[5] &=0xFC;
      LCD->RAM[5] |=  (buffer[0]>>6) & 0x03;   // 6A 6F
      
      LCD->RAM[1] &=0xF3;
      LCD->RAM[1] |=  (buffer[0]>>2) & 0x0C;   // 6M 6E
      
      LCD->RAM[1] &=0xCF;
      LCD->RAM[1] |=  (buffer[0]<<2) & 0x30;   // 6G 6B
      
      LCD->RAM[4] &=0x3F;
      LCD->RAM[4] |=  (buffer[0]<<6) & 0xC0;   // 6C 6D
  }
  else if(pos == 5){
      LCD->RAM[12] &=0xF3;
      LCD->RAM[12] |=  (buffer[1]>>4) & 0x0C;   // 5H 5J

      LCD->RAM[8] &=0x3F;
      LCD->RAM[8] |=  (buffer[1]<<2) & 0xC0;    // 5Q 5K

      LCD->RAM[8] &=0xFC;
      LCD->RAM[8] |=  (buffer[1]>>2) & 0x03;      // 5COL 5P

      LCD->RAM[11] &=0xCF;
      LCD->RAM[11] |=  (buffer[1]<<4) & 0x30;   // 5DP 5N

      LCD->RAM[5] &=0xF3;
      LCD->RAM[5] |=  (buffer[0]>>4) & 0x0C;      // 5A 5F
      
      LCD->RAM[1] &=0xFC;
      LCD->RAM[1] |=  (buffer[0]>>4) & 0x03;      // 5M 5E
      
      LCD->RAM[1] &=0x3F;
      LCD->RAM[1] |=  (buffer[0]<<4) & 0xC0;   // 5G 5B
      
      LCD->RAM[4] &=0xCF;
      LCD->RAM[4] |=  (buffer[0]<<4) & 0x30;   // 6C 6D
  }
  else if(pos == 4){
      LCD->RAM[12] &=0xCF;
      LCD->RAM[12] |=  (buffer[1]>>2) & 0x30;   // 4H 4J

      LCD->RAM[9] &=0xFC;
      LCD->RAM[9] |=  (buffer[1]>>4) & 0x03;    // 4Q 4K

      LCD->RAM[7] &=0x3F;
      LCD->RAM[7] |=  (buffer[1]<<4) & 0xC0;      // 4COL 4P

      LCD->RAM[11] &=0xF3;
      LCD->RAM[11] |=  (buffer[1]<<2) & 0x0C;   // 4DP 4N

      LCD->RAM[5] &=0xCF;
      LCD->RAM[5] |=  (buffer[0]>>2) & 0x30;   // 4A 4F
      
      LCD->RAM[0] &=0x3F;
      LCD->RAM[0] |=  (buffer[0]<<2) & 0xC0;   // 4M 4E
      
      LCD->RAM[2] &=0xFC;
      LCD->RAM[2] |=  (buffer[0]>>2) & 0x03;   // 4G 4B
      
      LCD->RAM[4] &=0xF3;
      LCD->RAM[4] |=  (buffer[0]<<2) & 0x0C;   // 4C 4D
  }
  else if(pos == 3){
      LCD->RAM[12] &=0x3F;
      LCD->RAM[12] |=  (buffer[1]) & 0xC0;   // 3H 3J

      LCD->RAM[9] &=0xF3;
      LCD->RAM[9] |=  (buffer[1]>>2) & 0x0C;    // 3Q 3K

      LCD->RAM[7] &=0xCF;
      LCD->RAM[7] |=  (buffer[1]<<2) & 0x30;      // 3COL 3P

      LCD->RAM[11] &=0xFC;
      LCD->RAM[11] |=  (buffer[1]) & 0x03;   // 3DP 3N

      LCD->RAM[5] &=0x3F;
      LCD->RAM[5] |=  (buffer[0]) & 0xC0;   // 3A 3F
      
      LCD->RAM[0] &=0xCF;
      LCD->RAM[0] |=  (buffer[0]) & 0x30;   // 3M 3E
      
      LCD->RAM[2] &=0xF3;
      LCD->RAM[2] |=  (buffer[0]) & 0x0C;      // 3G 3B
      
      LCD->RAM[4] &=0xFC;
      LCD->RAM[4] |=  (buffer[0]) & 0x03;      // 3C 3D
  }
  else if(pos == 2){
      LCD->RAM[13] &=0xFC;
      LCD->RAM[13] |=  (buffer[1]>>6) & 0x03;   // 2H 2J

      LCD->RAM[9] &=0xCF;
      LCD->RAM[9] |=  (buffer[1]) & 0x30;    // 2Q 2K

      LCD->RAM[7] &=0xF3;
      LCD->RAM[7] |=  (buffer[1]) & 0x0C;      // 2COL 2P

      LCD->RAM[10] &=0x3F;
      LCD->RAM[10] |=  (buffer[1]<<6) & 0xC0;   // 2DP 2N

      LCD->RAM[6] &=0xFC;
      LCD->RAM[6] |=  (buffer[0]>>6) & 0x03;   // 2A 2F
      
      LCD->RAM[0] &=0xF3;
      LCD->RAM[0] |=  (buffer[0]>>2) & 0x0C;   // 2M 2E
      
      LCD->RAM[2] &=0xCF;
      LCD->RAM[2] |=  (buffer[0]<<2) & 0x30;   // 2G 2B
      
      LCD->RAM[3] &=0x3F;
      LCD->RAM[3] |=  (buffer[0]<<6) & 0xC0;   // 2C 2D
  }
  else if(pos == 1){
      LCD->RAM[13] &=0xF3;
      LCD->RAM[13] |=  (buffer[1]>>4) & 0x0C;   // 1H 1J

      LCD->RAM[9] &=0x3F;
      LCD->RAM[9] |=  (buffer[1]<<2) & 0xC0;    // 1Q 1K

      LCD->RAM[7] &=0xFC;
      LCD->RAM[7] |=  (buffer[1]>>2) & 0x03;      // 1COL 1P

      LCD->RAM[10] &=0xCF;
      LCD->RAM[10] |=  (buffer[1]<<4) & 0x30;   // 1DP 1N

      LCD->RAM[6] &=0xF3;
      LCD->RAM[6] |=  (buffer[0]>>4) & 0x0C;      // 1A 1F
      
      LCD->RAM[0] &=0xFC;
      LCD->RAM[0] |=  (buffer[0]>>4) & 0x03;      // 1M 1E
      
      LCD->RAM[2] &=0x3F;
      LCD->RAM[2] |=  (buffer[0]<<4) & 0xC0;   // 1G 1B
      
      LCD->RAM[3] &=0xCF;
      LCD->RAM[3] |=  (buffer[0]<<4) & 0x30;   // 1C 1D
  }
}

/*!< Display a string at pos-position on LCD */
void Lcd_Print_String(char* str, uint8_t pos){
  while(*str){
    Lcd_Print_Char(*str,pos);
    str++;
    pos++;
  }
}