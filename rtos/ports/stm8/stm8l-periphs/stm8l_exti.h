#ifndef _stm8l_exti_h_
#define _stm8l_exti_h_
#include <stdint.h>

/******************************************************************************/
/*                          EXTI registers structures            	      */
/******************************************************************************/
typedef struct EXTI_struct
{
  volatile unsigned char CR1;           /*!<  The four LSB EXTI  pin sensitivity */
  volatile unsigned char CR2;           /*!<  The four MSB EXTI  pin sensitivity */
  volatile unsigned char CR3;           /*!<  EXTI port B & port D sensitivity */
  volatile unsigned char SR1;           /*!<  Pins Status flag register 1 */
  volatile unsigned char SR2;           /*!<  Ports Status flage register 2 */
  volatile unsigned char CONF1;         /*!<  Port interrupt selector */
  volatile unsigned char RESERVED[4];  	/*!<  reserved area */
  volatile unsigned char CR4;           /*!<  EXTI port G & port H sensitivity */
  volatile unsigned char CONF2;         /*!<  Port interrupt selector */
}
EXTI_TypeDef;
#define EXTI                        ((EXTI_TypeDef *) 0x50A0)

#endif /* _stm8l_exti_h_ */