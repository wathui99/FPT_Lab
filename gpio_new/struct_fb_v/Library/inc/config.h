#ifndef __CONFIG_H
#define __CONFIG_H

#define STRINGVECTOR(x) #x
#define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
#define INTERRUPT_HANDLER( a, b )  \
_Pragma( VECTOR_ID( (b)+2 ) )        \
__interrupt void (a)( void )
#define INTERRUPT __interrupt

INTERRUPT void TIM4_UPD_OVF_TRG_IRQHandler(void); /* TIM4 UPDATE,OF,TRIG */

#endif /* __CONFIG_H */