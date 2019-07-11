#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>
#include "mymacro.h"

typedef enum {
  SPI_Direction_2Lines_FullDuplex = (uint8_t)0x00, /*!< 2-line uni-directional data mode enable */
  SPI_Direction_2Lines_RxOnly     = (uint8_t)0x04, /*!< Receiver only in 2 line uni-directional data mode */
  SPI_Direction_1Line_Rx          = (uint8_t)0x80, /*!< Receiver only in 1 line bi-directional data mode */
  SPI_Direction_1Line_Tx          = (uint8_t)0xC0  /*!< Transmit only in 1 line bi-directional data mode */
} SPI_DirectionMode_TypeDef;
 
typedef enum
{
  SPI_NSS_Soft  = (uint8_t)0x02, /*!< Software slave management disabled */
  SPI_NSS_Hard  = (uint8_t)0x00  /*!< Software slave management enabled */
} SPI_NSS_TypeDef;

typedef enum 
{
  SPI_Direction_Rx = (uint8_t)0x00, /*!< Select Rx receive direction in bi-directional mode */
  SPI_Direction_Tx = (uint8_t)0x01  /*!< Select Tx transmission direction in bi-directional mode */
} SPI_Direction_TypeDef;

typedef enum
{
  SPI_Mode_Master = (uint8_t)0x04, /*!< SPI Master configuration */
  SPI_Mode_Slave  = (uint8_t)0x00  /*!< SPI Slave configuration */
} SPI_Mode_TypeDef;

typedef enum {
  SPI_BaudRatePrescaler_2   = (uint8_t)0x00, /*!< SPI frequency = frequency(CPU)/2 */
  SPI_BaudRatePrescaler_4   = (uint8_t)0x08, /*!< SPI frequency = frequency(CPU)/4 */
  SPI_BaudRatePrescaler_8   = (uint8_t)0x10, /*!< SPI frequency = frequency(CPU)/8 */
  SPI_BaudRatePrescaler_16  = (uint8_t)0x18, /*!< SPI frequency = frequency(CPU)/16 */
  SPI_BaudRatePrescaler_32  = (uint8_t)0x20, /*!< SPI frequency = frequency(CPU)/32 */
  SPI_BaudRatePrescaler_64  = (uint8_t)0x28, /*!< SPI frequency = frequency(CPU)/64 */
  SPI_BaudRatePrescaler_128 = (uint8_t)0x30, /*!< SPI frequency = frequency(CPU)/128 */
  SPI_BaudRatePrescaler_256 = (uint8_t)0x38  /*!< SPI frequency = frequency(CPU)/256 */
} SPI_BaudRatePrescaler_TypeDef;

typedef enum 
{
  SPI_CPOL_Low  = (uint8_t)0x00, /*!< Clock to 0 when idle */
  SPI_CPOL_High = (uint8_t)0x02  /*!< Clock to 1 when idle */
} SPI_CPOL_TypeDef;

typedef enum 
{
  SPI_CPHA_1Edge = (uint8_t)0x00, /*!< The first clock transition is the first data capture edge */
  SPI_CPHA_2Edge = (uint8_t)0x01  /*!< The second clock transition is the first data capture edge */
} SPI_CPHA_TypeDef;

typedef enum 
{
  SPI_FirstBit_MSB = (uint8_t)0x00, /*!< MSB bit will be transmitted first */
  SPI_FirstBit_LSB = (uint8_t)0x80  /*!< LSB bit will be transmitted first */
} SPI_FirstBit_TypeDef;

typedef enum {
  SPI_DMAReq_RX = (uint8_t)0x01,    /*!< SPI DMA Rx transfer requests */
  SPI_DMAReq_TX = (uint8_t)0x02     /*!< SPI DMA Tx transfer requests */
} SPI_DMAReq_TypeDef;

typedef enum {
  SPI_CRC_RX = (uint8_t)0x00, /*!< Select Tx CRC register */
  SPI_CRC_TX = (uint8_t)0x01  /*!< Select Rx CRC register */
} SPI_CRC_TypeDef;

typedef enum {
  SPI_FLAG_BSY    = (uint8_t)0x80, /*!< Busy flag */
  SPI_FLAG_OVR    = (uint8_t)0x40, /*!< Overrun flag */
  SPI_FLAG_MODF   = (uint8_t)0x20, /*!< Mode fault */
  SPI_FLAG_CRCERR = (uint8_t)0x10, /*!< CRC error flag */
  SPI_FLAG_WKUP   = (uint8_t)0x08, /*!< Wake-up flag */
  SPI_FLAG_TXE    = (uint8_t)0x02, /*!< Transmit buffer empty */
  SPI_FLAG_RXNE   = (uint8_t)0x01  /*!< Receive buffer empty */
} SPI_FLAG_TypeDef;

typedef enum
{
  SPI_IT_WKUP   = (uint8_t)0x34, /*!< Wake-up interrupt*/
  SPI_IT_OVR    = (uint8_t)0x65,  /*!< Overrun interrupt*/
  SPI_IT_MODF   = (uint8_t)0x55, /*!< Mode fault interrupt*/
  SPI_IT_CRCERR = (uint8_t)0x45, /*!< CRC error interrupt*/
  SPI_IT_TXE    = (uint8_t)0x17, /*!< Transmit buffer empty interrupt*/
  SPI_IT_RXNE   = (uint8_t)0x06, /*!< Receive buffer not empty interrupt*/
  SPI_IT_ERR    = (uint8_t)0x05  /*!< Error interrupt*/
} SPI_IT_TypeDef;

typedef enum
{
  SPI_FirstByte_MSB,
  SPI_FirstByte_LSB
} SPI_FirstByte_TypeDef;

typedef struct SPI_struct
{
  volatile uint8_t CR1;    /*!< SPI control register 1 */
  volatile uint8_t CR2;    /*!< SPI control register 2 */
  volatile uint8_t CR3;    /*!< SPI DMA and interrupt control register */
  volatile uint8_t SR;     /*!< SPI status register */
  volatile uint8_t DR;     /*!< SPI data I/O register */
  volatile uint8_t CRCPR;  /*!< SPI CRC polynomial register */
  volatile uint8_t RXCRCR; /*!< SPI Rx CRC register */
  volatile uint8_t TXCRCR; /*!< SPI Tx CRC register */
}
SPI_TypeDef;

#define SPI_BASE                   (uint16_t)0x5200
#define SPI                        ((SPI_TypeDef *) SPI_BASE)

void SPI_Init(SPI_FirstBit_TypeDef SPI_FirstBit,
              SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler,
              SPI_Mode_TypeDef SPI_Mode, SPI_CPOL_TypeDef SPI_CPOL,
              SPI_CPHA_TypeDef SPI_CPHA, SPI_DirectionMode_TypeDef SPI_Data_Direction,
              SPI_NSS_TypeDef SPI_Slave_Management, uint8_t CRCPolynomial);
void SPI_Cmd(uint8_t NewState);
void SPI_Write_One_Byte(uint8_t value);
void SPI_Write_Multi_Bytes(uint8_t *value, uint8_t len, SPI_FirstByte_TypeDef FB);
uint8_t SPI_Get_DR(void);
uint8_t SPI_Send_Sync_One(uint8_t value);
uint8_t *SPI_Send_Sync_Multi(uint8_t *value, uint8_t *ret, uint8_t len, SPI_FirstByte_TypeDef FB);

#endif /* __SPI_H */