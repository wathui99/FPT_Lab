#include"GPIO.h"
uint8_t temp=0x00;
/*-------------------------------------------------------------*/
/*
In_Fl_No_IT       // input, floating point, non-external Interrupt
In_Fl_IT          // input, floating point, external Interrupt
In_PU_No_IT       // input, pull up, non-external Interrupt
In_PU_IT          // input, Pull up, external Interrupt
Out_OD_Low_Fast   // Output, open drain, low level, 10Mhz
Out_PP_Low_Fast   // Output, push-pulse, low level, 10Mhz
Out_OD_Low_Slow   // Output, open drain, low level, 2Mhz
Out_PP_Low_Slow   // Output, push-pulse, low level, 2Mhz
Out_OD_High_Fast  // Output, open drain, high level, 10Mhz
Out_PP_High_Fast  // Output, push-pulse, high level, 10Mhz
Out_OD_High_Slow  // Output, open drain, high level, 2Mhz
Out_PP_High_Slow  // Output, push-pulse, high level, 2Mhz
*/
//GPIO_Mode
/*---------------------------------------------------------------*/

/*
 Port_A 
 Port_B 
 Port_C 
 Port_D 
 Port_E 
 Port_F 
*/// GPIO_Type
/*---------------------------------------------------------------*/
bool gpio_init(GPIO_Type* Port_X, uint8_t GPIO_Pin, GPIO_Mode mode ){
	
	/*----------------------------*/
	/* input/output mode selection*/
	/*----------------------------*/
	if((uint8_t)(mode)&0x80){            // output
		Port_X->DDR |=GPIO_Pin;
		temp=Port_X->DDR;
		#if temp!=GPIO_Pin
			#error "DDR config for output is wrong!"
		#endif
		//if(Port_X->ODR & GPIO_Pin !=0)
		if((uint8_t)(mode) &0x10){        // high level
			Port_X->ODR |=GPIO_Pin;
			temp= Port_X->ODR;
			#if temp!=GPIO_Pin
				#error "ODR config for high level is wrong!"
			#endif
		}
		else{                       // low level
			Port_X->ODR &=~GPIO_Pin;
			temp= Port_X->ODR;
			#if temp!=GPIO_Pin
				#error "ODR config for low level is wrong!"
			#endif
		}
	}
	else{ 						  // input
		Port_X->DDR &=~GPIO_Pin;
		temp=Port_X->DDR;
		#if temp!=GPIO_Pin
			#error "DDR config for input is wrong!"
		#endif
	}
	/*------------------------------------------------------------------------*/
	/*  Pull-Up/Float (Input) or Push-Pull/Open-Drain (Output) modes selection*/
	/*------------------------------------------------------------------------*/
	if((uint8_t)(mode)&0x40){            /* Pull-Up or Push-Pull */
		Port_X->CR1 |=GPIO_Pin;
		temp=Port_X->CR1;
		#if temp!=GPIO_Pin
			#error "CR1 config for Pull-Up or Push-Pull is wrong"
		#endif
	}
	else{                          /* Float or Open-Drain */
		Port_X->CR1 &=~GPIO_Pin;
		temp=Port_X->CR1;
		#if temp!=GPIO_Pin
			#error "CR1 config for  Float or Open-Drain is wrong"
		#endif
	}
	/*-----------------------------------------------------*/
	/* Interrupt (Input) or Slope (Output) modes selection */
	/*-----------------------------------------------------*/
	if((uint8_t)(mode)&0x20){            /* enable Interrupt or output 10Mhz */
		Port_X->CR2 |=GPIO_Pin;
		temp=Port_X->CR2;
		#if temp!=GPIO_Pin
			#error "CR2 config for enable Interrupt or output 10Mhz is wrong"
		#endif 
	}
	else {                         /* disable Interrupt or ouput 2Mhz */
		Port_X->CR2 &=~GPIO_Pin;
		temp=Port_X->CR2;
		#if temp!=GPIO_Pin
			#error "CR2 config for disable Interrupt or ouput 2Mhz is wrong"
		#endif
	}
	return TRUE;
}
bool gpio_deinit(GPIO_Type* Port_X){
	Port_X->DDR=0x00;
	temp=Port_X->DDR;
	#if temp!=0x00
		#error "can't reset DDR"
	#endif
	Port_X->ODR=0x00;
	temp=Port_X->ODR;
	#if temp!=0x00
		#error "can't reset ODR"
	#endif
	Port_X->CR1=0x00;
	temp=Port_X->CR1;
	#if temp!=0x00
		#error "can't reset CR1"
	#endif
	Port_X->CR2=0x00;
	temp=Port_X->CR2;
	#if temp!=0x00
		#error "can't reset CR2"
	#endif
	return TRUE;
}
//select pins and set or reset pins
void GPIO_Write(GPIO_Type* GPIO_X, uint8_t Value){
	GPIO_X->ODR = Value;
	temp= GPIO_X->ODR;
	#if temp!=Value
		#error "input value is wrong!"
	#endif
}

bool GPIO_read (GPIO_Type* GPIO_X,uint8_t GPIO_Pin){
	if(GPIO_X->IDR & GPIO_Pin) return TRUE;
	return FALSE;
}