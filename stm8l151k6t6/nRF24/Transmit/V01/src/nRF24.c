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
  uint8_t ret=0;
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte((reg & REGISTER_MASK) | R_REGISTER);
  ret=SPI_Send_Sync_One(NOP);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
/* Write multi bytes into registers*/
void nRF_Write_Multi_Regs(uint8_t reg, uint8_t *value, uint8_t len) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_REGISTER | (REGISTER_MASK & reg));
  for (int8_t i=0; i<len; i++) {
    SPI_Write_One_Byte(value[i]);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
}
/*Read multi bytes from registers*/
uint8_t *nRF_Read_Multi_Regs(uint8_t reg, uint8_t *ret, uint8_t len) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(R_REGISTER | (REGISTER_MASK & reg));
  for (int8_t i=0; i<len; i++) {
    ret[i]=SPI_Send_Sync_One(NOP);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}

void nRF_Config(nRF_MaskInterrupt_TypeDef MaskInterrupt, nRF_CRC_TypeDef CRC, nRF_Mode_TypeDef Mode, \
                nRF_AA_TypeDef AA, nRF_EN_Pipe_TypeDef EN_Pipe, nRF_Add_Width_TypeDef Add_Width, \
                uint8_t delay_reTrans, uint8_t num_reTrans, uint8_t RF_channel, \
                nRF_DataRate_TypeDef DataRate, nRF_OutPower_Tx_TypeDef OutPower, 
                uint8_t *RX_Add_P0, uint8_t *RX_Add_P1, \
                uint8_t RX_Add_P2, uint8_t RX_Add_P3, uint8_t RX_Add_P4, uint8_t RX_Add_P5, \
                uint8_t *TX_Add, uint8_t num_Byte_P0, uint8_t num_Byte_P1, uint8_t num_Byte_P2, \
                uint8_t num_Byte_P3, uint8_t num_Byte_P4, uint8_t num_Byte_P5) {
  /*write config reg (interrupt, CRC, Mode TX|RX*/
  nRF_Write_One_Reg(CONFIG, MaskInterrupt | CRC | Mode);
  /* auto ack pipe */
  nRF_Write_One_Reg(EN_AA, AA);
  /* enable rx pipe */
  nRF_Write_One_Reg(EN_RXADDR, EN_Pipe);
  /* address width -> recommended: 5bytes */
  nRF_Write_One_Reg(SETUP_AW, Add_Width);
  /* delay retries + try times */
  nRF_Write_One_Reg(SETUP_RETR, delay_reTrans | num_reTrans);
  /* channel */
  nRF_Write_One_Reg(RF_CH, RF_channel);
  /* data rate, output signal */
  nRF_Write_One_Reg(RF_SETUP, 0x01 | DataRate | OutPower); //0x01 keep LNA
  /* RX and TX address
  * <! If AACK enable TX and RX_P0 must have same address
  */
  /* Receive address P0, P1+P2+P3+P4+P5 share same 4MSByte address */
  nRF_Write_Multi_Regs(RX_ADDR_P0, RX_Add_P0, 5);
  nRF_Write_Multi_Regs(RX_ADDR_P1, RX_Add_P1, 5);
  nRF_Write_One_Reg(RX_ADDR_P2, RX_Add_P2);
  nRF_Write_One_Reg(RX_ADDR_P3, RX_Add_P3);
  nRF_Write_One_Reg(RX_ADDR_P4, RX_Add_P4);
  nRF_Write_One_Reg(RX_ADDR_P5, RX_Add_P5);
  /* Transmit address */
  nRF_Write_Multi_Regs(TX_ADDR, TX_Add, 5);
  /* Number of byte receive in each pipe*/
  nRF_Write_One_Reg(RX_PW_P0, num_Byte_P0);
  nRF_Write_One_Reg(RX_PW_P1, num_Byte_P1);
  nRF_Write_One_Reg(RX_PW_P2, num_Byte_P2);
  nRF_Write_One_Reg(RX_PW_P3, num_Byte_P3);
  nRF_Write_One_Reg(RX_PW_P4, num_Byte_P4);
  nRF_Write_One_Reg(RX_PW_P5, num_Byte_P5);
}
/*
* return 0 if not receive ACK and fail n re-tries
*/
uint8_t nRF_Is_Sending(void);





