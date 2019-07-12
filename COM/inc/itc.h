#ifndef __ITC_H
#define __ITC_H

#include <stdint.h>
#include "mymacro.h"

typedef struct ITC_struct
{
  volatile uint8_t ISPR1; /*!<  Interrupt Software Priority register 1 */
  volatile uint8_t ISPR2; /*!<  Interrupt Software Priority register 2 */
  volatile uint8_t ISPR3; /*!<  Interrupt Software Priority register 3 */
  volatile uint8_t ISPR4; /*!<  Interrupt Software Priority register 4 */
  volatile uint8_t ISPR5; /*!<  Interrupt Software Priority register 5 */
  volatile uint8_t ISPR6; /*!<  Interrupt Software Priority register 6 */
  volatile uint8_t ISPR7; /*!<  Interrupt Software Priority register 7 */
  volatile uint8_t ISPR8; /*!<  Interrupt Software Priority register 8 */
}
ITC_TypeDef;

#define ITC_BASE                    (uint16_t)0x7F70
#define ITC                         ((ITC_TypeDef *) ITC_BASE)

void Itc_Init(void);

#endif /* __ITC_H */