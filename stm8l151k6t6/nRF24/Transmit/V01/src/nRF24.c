/*
* clock must enable
* gpio must config for spi and CSS + CE
*/

#include "nRF24.h"

uint8_t nRF_payloadLength=0;

void nRF_Set_Payload_Leng(uint8_t value) {
  nRF_payloadLength=value;
}

uint8_t nRF_Get_Status_Reg() {
  uint8_t ret=0;
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  ret = SPI_Send_Sync_One(0xFF);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
void nRF_Write_One_Reg(uint8_t reg, uint8_t value) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_REGISTER | (REGISTER_MASK & reg));
  SPI_Write_One_Byte(value);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
}
uint8_t nRF_Read_One_Reg(uint8_t reg) {
  return SPI_Send_Sync_One(R_REGISTER | (reg & REGISTER_MASK));
}
