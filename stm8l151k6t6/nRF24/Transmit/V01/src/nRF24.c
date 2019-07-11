/*
* clock must enable
* gpio must config for spi and CSS + CE
*/

#include "nRF24.h"

uint8_t nRF_payloadLength=0;

/* set static payload for send or receive */
void nRF_Set_Payload_Leng(uint8_t value) {
  nRF_payloadLength=value;
}
/* get status register */
uint8_t nRF_Get_Status_Reg() {
  uint8_t ret=0;
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  ret = SPI_Send_Sync_One(0xFF);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
/* Write just one byte into one register */
void nRF_Write_One_Reg(uint8_t reg, uint8_t value) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_REGISTER | (REGISTER_MASK & reg));
  SPI_Write_One_Byte(value);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
}
/* Read just one byte from one register */
uint8_t nRF_Read_One_Reg(uint8_t reg) {
  return SPI_Send_Sync_One(R_REGISTER | (reg & REGISTER_MASK));
}
/* Write multi bytes into registers (base_address = reg) */
void nRF_Write_Multi_Regs(uint8_t reg, uint8_t *value, uint8_t len) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_REGISTER | (REGISTER_MASK & reg));
  for (int8_t i=0; i<len; i++) {
    SPI_Write_One_Byte(value[i]);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
}
/* Read multi bytes from registers (base_address = reg) */
uint8_t *nRF_Read_Multi_Regs(uint8_t reg, uint8_t *ret, uint8_t len) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(R_REGISTER | (REGISTER_MASK & reg));
  for (int8_t i=0; i<len; i++) {
    ret[i]=SPI_Send_Sync_One(NOP);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
