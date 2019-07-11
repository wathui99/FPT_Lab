#include "spi.h"

void SPI_Init(SPI_FirstBit_TypeDef SPI_FirstBit,
              SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler,
              SPI_Mode_TypeDef SPI_Mode, SPI_CPOL_TypeDef SPI_CPOL,
              SPI_CPHA_TypeDef SPI_CPHA, SPI_DirectionMode_TypeDef SPI_Data_Direction,
              SPI_NSS_TypeDef SPI_Slave_Management, uint8_t CRCPolynomial)
{
  /* Frame Format, BaudRate, Clock Polarity and Phase configuration */
  SPI->CR1 = (uint8_t)((uint8_t)((uint8_t)SPI_FirstBit |
                                  (uint8_t)SPI_BaudRatePrescaler) |
                        (uint8_t)((uint8_t)SPI_CPOL |
                                  SPI_CPHA));

  /* Data direction configuration: BDM, BDOE and RXONLY bits */
  SPI->CR2 = (uint8_t)((uint8_t)(SPI_Data_Direction) | (uint8_t)(SPI_Slave_Management));

  if (SPI_Mode == SPI_Mode_Master)
  {
    SPI->CR2 |= (uint8_t)(1<<0);
  }
  else
  {
    SPI->CR2 &= (uint8_t)~(1<<0);
  }

  /* Master/Slave mode configuration */
  SPI->CR1 |= (uint8_t)(SPI_Mode);

  /* CRC configuration */
  SPI->CRCPR = (uint8_t)CRCPolynomial;
}

void SPI_Cmd(uint8_t NewState)
{
  if (NewState != DISABLE)
  {
    SPI->CR1 |= (1<<6); /* Enable the SPI peripheral*/
  }
  else
  {
    SPI->CR1 &= (uint8_t)(~(1<<6)); /* Disable the SPI peripheral*/
  }
}

void SPI_Write_One_Byte(uint8_t value) {
  SPI->DR = value;
  while(!bit_is_set(SPI->SR, 1)) {} //wait trans completed
}

void SPI_Write_Multi_Bytes(uint8_t *value, uint8_t len, SPI_FirstByte_TypeDef FB) {
  if (FB == SPI_FirstByte_MSB) {
    for (int8_t i=0; i<len; i++) {
      SPI->DR = value[i];
      while(!bit_is_set(SPI->SR, 1)) {} //wait trans completed
    }
  } else {
    for (int8_t i=len-1; i>=0; i--) {
      SPI->DR = value[i];
      while(!bit_is_set(SPI->SR, 1)) {} //wait trans completed
    }
  }
}

uint8_t SPI_Get_DR(void) {
  return SPI->DR;
}

uint8_t SPI_Send_Sync_One(uint8_t value) {
  SPI_Write_One_Byte(value);
  while(!bit_is_set(SPI->SR, 0)) {} //wait receive done
  return SPI_Get_DR();
}

uint8_t *SPI_Send_Sync_Multi(uint8_t *value, uint8_t *ret, uint8_t len, SPI_FirstByte_TypeDef FB) {
  if (FB == SPI_FirstByte_MSB) {
    for (int8_t i=0; i<len; i++) {
      SPI_Write_One_Byte(value[i]);
      while(!bit_is_set(SPI->SR, 0)) {} //wait receive done
      ret[i] = SPI_Get_DR();
    }
  } else {
    for (int8_t i=len-1; i>=0; i--) {
      SPI_Write_One_Byte(value[i]);
      while(!bit_is_set(SPI->SR, 0)) {} //wait receive done
      ret[i] = SPI_Get_DR();
    }
  }
  return ret;
}