#include "stm8l_lcd.h"

/*!< Config & Init LCD vs RTC */
void config_LCDvsRTC(){
  /*!< Enable RTC clock */
  //CLK->PCKENR2 |= (1<<2);
  /*!< Enable LCD clock */
  //CLK->PCKENR2 |= (1<<3);  
  //CLK->CRTCR = (uint8_t)((uint8_t)0x04 | (uint8_t)0x00);
  /*!< LCD_Prescale_1 LCD_Divide_31 */
  LCD->FRQ |= LCD_Prescaler_1;
  LCD->FRQ |= LCD_Divider_16;
  /*!< 1/3-bias 1/4-duty ---------------- */
  LCD->CR1 |= LCD_Duty_1_4;
  /*!< Internal Source */
  LCD->CR2 |= (0<<0);
  /* Mask register - use 0 to 23 segments. */
  LCD->PM[0] = 0xFF;
  LCD->PM[1] = 0xFF;    // 7F if using SPI => only 1,2,3 position
  LCD->PM[2] = 0xFF;    // FC if using SPI => only 1,2,3 position
  /* Set contrast */
  LCD->CR2 |= LCD_Contrast_Level_4;
  /*!< No dead Time  */
  LCD->CR3 |= LCD_DeadTime_0;
  LCD->CR2 |= LCD_PulseOnDuration_1;
  /*!< Enable LCD */
  LCD->CR3 |= 0x40;
}

/*!< Delete all character on LCD */
void lcd_clear(){
  for(int i =0; i<14; i++){
    LCD->RAM[i] = 0x00;
  }
}

/*!< Display character following the defined array */
void lcd_print(int16_t character, uint8_t pos){
  /*!< Space character */
  if(character<0)     character = 36;
  buffer_lcd[1] = (uint8_t)(char_list[character]>>8);
  buffer_lcd[0] = char_list[character];
  /*!< Print the character at each position*/
  if(pos == 6){
      LCD->RAM[12] &=0xFC;
      LCD->RAM[12] |=  (buffer_lcd[1]>>6) & 0x03;   // 6H 6J

      LCD->RAM[8] &=0xCF;
      LCD->RAM[8] |=  (buffer_lcd[1]) & 0x30;      // 6Q 6K

      LCD->RAM[8] &=0xF3;
      LCD->RAM[8] |=  (buffer_lcd[1]) & 0x0C;      // 6COL 6P

      LCD->RAM[11] &=0x3F;
      LCD->RAM[11] |=  (buffer_lcd[1]<<6) & 0xC0;   // 6DP 6N

      LCD->RAM[5] &=0xFC;
      LCD->RAM[5] |=  (buffer_lcd[0]>>6) & 0x03;   // 6A 6F
      
      LCD->RAM[1] &=0xF3;
      LCD->RAM[1] |=  (buffer_lcd[0]>>2) & 0x0C;   // 6M 6E
      
      LCD->RAM[1] &=0xCF;
      LCD->RAM[1] |=  (buffer_lcd[0]<<2) & 0x30;   // 6G 6B
      
      LCD->RAM[4] &=0x3F;
      LCD->RAM[4] |=  (buffer_lcd[0]<<6) & 0xC0;   // 6C 6D
  }
  else if(pos == 5){
      LCD->RAM[12] &=0xF3;
      LCD->RAM[12] |=  (buffer_lcd[1]>>4) & 0x0C;   // 5H 5J

      LCD->RAM[8] &=0x3F;
      LCD->RAM[8] |=  (buffer_lcd[1]<<2) & 0xC0;    // 5Q 5K

      LCD->RAM[8] &=0xFC;
      LCD->RAM[8] |=  (buffer_lcd[1]>>2) & 0x03;      // 5COL 5P

      LCD->RAM[11] &=0xCF;
      LCD->RAM[11] |=  (buffer_lcd[1]<<4) & 0x30;   // 5DP 5N

      LCD->RAM[5] &=0xF3;
      LCD->RAM[5] |=  (buffer_lcd[0]>>4) & 0x0C;      // 5A 5F
      
      LCD->RAM[1] &=0xFC;
      LCD->RAM[1] |=  (buffer_lcd[0]>>4) & 0x03;      // 5M 5E
      
      LCD->RAM[1] &=0x3F;
      LCD->RAM[1] |=  (buffer_lcd[0]<<4) & 0xC0;   // 5G 5B
      
      LCD->RAM[4] &=0xCF;
      LCD->RAM[4] |=  (buffer_lcd[0]<<4) & 0x30;   // 6C 6D
  }
  else if(pos == 4){
      LCD->RAM[12] &=0xCF;
      LCD->RAM[12] |=  (buffer_lcd[1]>>2) & 0x30;   // 4H 4J

      LCD->RAM[9] &=0xFC;
      LCD->RAM[9] |=  (buffer_lcd[1]>>4) & 0x03;    // 4Q 4K

      LCD->RAM[7] &=0x3F;
      LCD->RAM[7] |=  (buffer_lcd[1]<<4) & 0xC0;      // 4COL 4P

      LCD->RAM[11] &=0xF3;
      LCD->RAM[11] |=  (buffer_lcd[1]<<2) & 0x0C;   // 4DP 4N

      LCD->RAM[5] &=0xCF;
      LCD->RAM[5] |=  (buffer_lcd[0]>>2) & 0x30;   // 4A 4F
      
      LCD->RAM[0] &=0x3F;
      LCD->RAM[0] |=  (buffer_lcd[0]<<2) & 0xC0;   // 4M 4E
      
      LCD->RAM[2] &=0xFC;
      LCD->RAM[2] |=  (buffer_lcd[0]>>2) & 0x03;   // 4G 4B
      
      LCD->RAM[4] &=0xF3;
      LCD->RAM[4] |=  (buffer_lcd[0]<<2) & 0x0C;   // 4C 4D
  }
  else if(pos == 3){
      LCD->RAM[12] &=0x3F;
      LCD->RAM[12] |=  (buffer_lcd[1]) & 0xC0;   // 3H 3J

      LCD->RAM[9] &=0xF3;
      LCD->RAM[9] |=  (buffer_lcd[1]>>2) & 0x0C;    // 3Q 3K

      LCD->RAM[7] &=0xCF;
      LCD->RAM[7] |=  (buffer_lcd[1]<<2) & 0x30;      // 3COL 3P

      LCD->RAM[11] &=0xFC;
      LCD->RAM[11] |=  (buffer_lcd[1]) & 0x03;   // 3DP 3N

      LCD->RAM[5] &=0x3F;
      LCD->RAM[5] |=  (buffer_lcd[0]) & 0xC0;   // 3A 3F
      
      LCD->RAM[0] &=0xCF;
      LCD->RAM[0] |=  (buffer_lcd[0]) & 0x30;   // 3M 3E
      
      LCD->RAM[2] &=0xF3;
      LCD->RAM[2] |=  (buffer_lcd[0]) & 0x0C;      // 3G 3B
      
      LCD->RAM[4] &=0xFC;
      LCD->RAM[4] |=  (buffer_lcd[0]) & 0x03;      // 3C 3D
  }
  else if(pos == 2){
      LCD->RAM[13] &=0xFC;
      LCD->RAM[13] |=  (buffer_lcd[1]>>6) & 0x03;   // 2H 2J

      LCD->RAM[9] &=0xCF;
      LCD->RAM[9] |=  (buffer_lcd[1]) & 0x30;    // 2Q 2K

      LCD->RAM[7] &=0xF3;
      LCD->RAM[7] |=  (buffer_lcd[1]) & 0x0C;      // 2COL 2P

      LCD->RAM[10] &=0x3F;
      LCD->RAM[10] |=  (buffer_lcd[1]<<6) & 0xC0;   // 2DP 2N

      LCD->RAM[6] &=0xFC;
      LCD->RAM[6] |=  (buffer_lcd[0]>>6) & 0x03;   // 2A 2F
      
      LCD->RAM[0] &=0xF3;
      LCD->RAM[0] |=  (buffer_lcd[0]>>2) & 0x0C;   // 2M 2E
      
      LCD->RAM[2] &=0xCF;
      LCD->RAM[2] |=  (buffer_lcd[0]<<2) & 0x30;   // 2G 2B
      
      LCD->RAM[3] &=0x3F;
      LCD->RAM[3] |=  (buffer_lcd[0]<<6) & 0xC0;   // 2C 2D
  }
  else if(pos == 1){
      LCD->RAM[13] &=0xF3;
      LCD->RAM[13] |=  (buffer_lcd[1]>>4) & 0x0C;   // 1H 1J

      LCD->RAM[9] &=0x3F;
      LCD->RAM[9] |=  (buffer_lcd[1]<<2) & 0xC0;    // 1Q 1K

      LCD->RAM[7] &=0xFC;
      LCD->RAM[7] |=  (buffer_lcd[1]>>2) & 0x03;      // 1COL 1P

      LCD->RAM[10] &=0xCF;
      LCD->RAM[10] |=  (buffer_lcd[1]<<4) & 0x30;   // 1DP 1N

      LCD->RAM[6] &=0xF3;
      LCD->RAM[6] |=  (buffer_lcd[0]>>4) & 0x0C;      // 1A 1F
      
      LCD->RAM[0] &=0xFC;
      LCD->RAM[0] |=  (buffer_lcd[0]>>4) & 0x03;      // 1M 1E
      
      LCD->RAM[2] &=0x3F;
      LCD->RAM[2] |=  (buffer_lcd[0]<<4) & 0xC0;   // 1G 1B
      
      LCD->RAM[3] &=0xCF;
      LCD->RAM[3] |=  (buffer_lcd[0]<<4) & 0x30;   // 1C 1D
  }
}

/*!< Display a character (ASCII) at pos-position on LCD */
void lcd_print_char(char c, uint8_t pos){
  /*!< if character is  lowercase -> convert to uppercase */
  if(c >= 97 && c <= 122){
    lcd_print(c-55-32,pos);
  }
  /*!< if character is  a number */
  else if(c >= 48 && c <= 57){
    lcd_print(c-48,pos);
  }  
  /*!< if character is '-' character */
  else if(c == 45){
    lcd_print(37,pos);
  }
  /*!< if character is  a uppercase */
  else {
    lcd_print(c-55,pos);
  }
}

/*!< Display a string at pos-position on LCD */
void lcd_print_string(char* str, uint8_t pos){
  while(*str){
   lcd_print_char(*str,pos);
   str++;
   pos++;
  }
}

/*!< Display a character at next-position (lcd_pointer) on LCD */
void lcd_print_char_auto(char c){
  /*!< if character is  lowercase -> convert to uppercase */
  if(c >= 97 && c <= 122){
    lcd_print(c-55-32,lcd_pointer++);
  }
  /*!< if character is  a number */
  else if(c >= 48 && c <= 57){
    lcd_print(c-48,lcd_pointer++);
  }
  /*!< if character is '-' character */
  else if(c == 45){
    lcd_print(37,lcd_pointer++);
  }
  /*!< if character is  a uppercase */
  else {
    lcd_print(c-55,lcd_pointer++);
  }
  if(lcd_pointer > 6){
    lcd_pointer = 1;
  }
}

/*!< Display a string at next-position (lcd_pointer) on LCD */
void lcd_print_string_auto(char* str){
  while(*str){
   lcd_print_char_auto(*str);
   str++;
  }
}

/*!< Convert integer number into octal, hex, etc... */
char *convert(unsigned int num, int base) { 
  static char Representation[]= "0123456789ABCDEF";
  static char buffer[50]; 
  char *ptr; 
  ptr = &buffer[49]; 
  *ptr = '\0'; 	
  do { 
    *--ptr = Representation[num%base]; 
    num /= base; 
  }while(num != 0); 	
  return(ptr); 
}

/*!< Reset status of LCD */
void LCD_reset(){
  /*!< Clear LCD's buffer */
  lcd_clear();
  /*!< Reset LCD pointer */
  lcd_pointer = 1;
}

/*!< LCD printf function same as printf function in "stdio.h" file */
/*!< Only support for %c %d %s %x %o */
void LCD_printf(char* format,...){ 
  char *traverse; 
  int16_t i; 
  char *s; 
	
  //Module 1: Initializing LCD_printf's arguments 
  va_list arg; 
  va_start(arg, format); 
  for(traverse = format; *traverse != '\0'; traverse++){ 
    while( *traverse != '%' && *traverse != '\0' ) { 
      lcd_print_char_auto(*traverse);
      traverse++; 
    } 
    if( *traverse == '\0'){
      break;
    }
    traverse++; 
                  
    //Module 2: Fetching and executing arguments
    switch(*traverse) { 
      case 'c' :
        i = va_arg(arg,int);		//Fetch char argument
        lcd_print_char_auto(i);
        break; 
                                                  
      case 'd' : 
        i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
        if(i<0) { 
          i = -i;
          lcd_print_char_auto('-'); 
        } 
        lcd_print_string_auto(convert(i,10));
        break; 
                                                  
      case 'o': 
        i = va_arg(arg,unsigned int); //Fetch Octal representation
        lcd_print_string_auto(convert(i,8));
        break; 
                                                  
      case 's': 
        s = va_arg(arg,char *); 		//Fetch string
        lcd_print_string_auto(s); 
        break; 
                                                  
      case 'x': 
        i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
        lcd_print_string_auto(convert(i,16));
        break; 
     }	
  } 
	
  //Module 3: Closing argument list to necessary clean-up
  va_end(arg); 
} 

