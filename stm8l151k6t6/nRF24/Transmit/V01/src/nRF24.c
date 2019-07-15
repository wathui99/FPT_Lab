/*
* clock must enable
* gpio must config for spi and CSS + CE
*/

#include "nRF24.h"

uint8_t nRF_payloadLength=0;

void nRF_Delay(uint32_t value) {
  for (uint32_t i=0; i<value; i++) {
    for (uint32_t j=0; j<nRF_Delay_Time; j++) {};
  }
}
/* set static payload for send or receive */
void nRF_Set_Payload_Leng(uint8_t value) {
  nRF_payloadLength=value;
}
/* get status register */
uint8_t nRF_Get_Status_Reg() {
  uint8_t ret=0;
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  if (nRF_Delay_Mask) {
    nRF_Delay(1);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  ret = SPI_Send_Sync_One(0xFF);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
/* Write just one byte into one register */
void nRF_Write_One_Reg(uint8_t reg, uint8_t value) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  if (nRF_Delay_Mask) {
    nRF_Delay(1);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_REGISTER | (REGISTER_MASK & reg));
  SPI_Write_One_Byte(value);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
}
/* Read just one byte from one register */
uint8_t nRF_Read_One_Reg(uint8_t reg) {
  uint8_t ret=0;
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  if (nRF_Delay_Mask) {
    nRF_Delay(1);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte((reg & REGISTER_MASK) | R_REGISTER);
  ret=SPI_Send_Sync_One(NOP);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
/* Write multi bytes into registers*/
void nRF_Write_Multi_Regs(uint8_t reg, uint8_t *value, uint8_t len) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  if (nRF_Delay_Mask) {
    nRF_Delay(1);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_REGISTER | (REGISTER_MASK & reg));
  for (int8_t i=0; i<len; i++) {
    SPI_Write_One_Byte(value[i]);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
}
/*Read multi bytes from registers*/
uint8_t *nRF_Read_Multi_Regs(uint8_t reg, uint8_t *ret, uint8_t len) {
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  if (nRF_Delay_Mask) {
    nRF_Delay(1);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(R_REGISTER | (REGISTER_MASK & reg));
  for (int8_t i=0; i<len; i++) {
    ret[i]=SPI_Send_Sync_One(NOP);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  return ret;
}
/*
* nRF_MaskInterrupt_TypeDef: Interrupt
* nRF_CRC_TypeDef: CRC check
* nRF_Mode_TypeDef: Mode TX|RX
* nRF_AA_TypeDef: Auto ack
* nRF_EN_Pipe_TypeDef: Enable RX pipe
* nRF_Add_Width_TypeDef: Address width
* uint8_t: Delay between re-tries (max 15)
* uint8_t: Number of re-tries (max 15)
* uint8_t: RF channel (please refer datasheet)
* nRF_DataRate_TypeDef: Data rate transmit
* nRF_OutPower_Tx_TypeDef: Output power transmit
* uint8_t*: RX address P0
* uint8_t*: RX address P1
* uint8_t: RX address P2
* uint8_t: RX address P3
* uint8_t: RX address P4
* uint8_t: RX address P5
* uint8_t*: TX address
* uint8_t: Number of byte receive in P0
* uint8_t: Number of byte receive in P1
* uint8_t: Number of byte receive in P2
* uint8_t: Number of byte receive in P3
* uint8_t: Number of byte receive in P4
* uint8_t: Number of byte receive in P5
*/
void nRF_Config(nRF_MaskInterrupt_TypeDef MaskInterrupt, nRF_Mode_TypeDef Mode, \
                nRF_AA_TypeDef AA, nRF_EN_Pipe_TypeDef EN_Pipe, nRF_Add_Width_TypeDef Add_Width, \
                uint8_t delay_reTrans, uint8_t num_reTrans, uint8_t RF_channel, \
                nRF_DataRate_TypeDef DataRate, nRF_OutPower_Tx_TypeDef OutPower, 
                uint8_t *RX_Add_P0, uint8_t *RX_Add_P1, \
                uint8_t RX_Add_P2, uint8_t RX_Add_P3, uint8_t RX_Add_P4, uint8_t RX_Add_P5, \
                uint8_t *TX_Add, uint8_t num_Byte_P0, uint8_t num_Byte_P1, uint8_t num_Byte_P2, \
                uint8_t num_Byte_P3, uint8_t num_Byte_P4, uint8_t num_Byte_P5) {
  /*write config reg (interrupt, CRC, Mode TX|RX*/
  nRF_Write_One_Reg(CONFIG, MaskInterrupt | CONFIG_DEFAULT | Mode);
  /* auto ack pipe */
  nRF_Write_One_Reg(EN_AA, AA);
  /* enable rx pipe */
  nRF_Write_One_Reg(EN_RXADDR, EN_Pipe);
  /* address width -> recommended: 5bytes */
  nRF_Write_One_Reg(SETUP_AW, Add_Width);
  /* delay retries + try times */
  nRF_Write_One_Reg(SETUP_RETR, (delay_reTrans<<4) | num_reTrans);
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
* else return 1
*/
uint8_t nRF_Is_Sending(void) {
  uint8_t status = nRF_Get_Status_Reg();
  if((status & ((1<<TX_DS) | (1<<MAX_RT)))) {
    return 0;
  }
  return 1;
}
/*
* clear bit RX_PRIM
* set bit POWER
*/
void nRF_Powerup_TX(void) {
  /* CRC enable, 1 byte scheme */
  nRF_Write_One_Reg(CONFIG,(CONFIG_DEFAULT)|((1<<PWR_UP)|(0<<PRIM_RX)));
}
/*
* set bit RX_PRIM
* set bit POWER
*/
void nRF_Powerup_RX(void) {
  /* CRC enable, 1 byte scheme */
  nRF_Write_One_Reg(CONFIG,(CONFIG_DEFAULT)|((1<<PWR_UP)|(1<<PRIM_RX)));
}
/*
* clear bit POWER
*/
void nRF_Powerdown(void) {
  /* CRC enable, 1 byte scheme */
  nRF_Write_One_Reg(CONFIG,(CONFIG_DEFAULT)|(1<<PRIM_RX));
}
/*
* nRF send payload
* <! CE still high after this function
*/
void nRF_Send(uint8_t *payload, uint8_t len, uint8_t clearFIFO) {
  GPIO_Write_Bit(CE_GPIO, CE_PIN, OFF);
  nRF_Write_One_Reg(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT)); //Write 1 to clear all flag
  /* CRC enable, 1 byte scheme, power-up, tx */
  nRF_Powerup_TX();
  /* flush TX FIFO */
  if(clearFIFO) {
    GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
    SPI_Write_One_Byte(FLUSH_TX);
    GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  }
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, OFF);
  SPI_Write_One_Byte(W_TX_PAYLOAD);
  SPI_Write_Multi_Bytes(payload,len,SPI_FirstByte_MSB);
  GPIO_Write_Bit(CSS_GPIO, CSS_PIN, ON);
  GPIO_Write_Bit(CE_GPIO, CE_PIN, ON);
}
/*
* clear fifo tx
* send data
* wait sending
* set ce low
* powerdown
*/
void User_nRF_Send(uint8_t *payload, uint8_t len) {
  nRF_Send(payload, len, 1);
  while(nRF_Is_Sending());
  GPIO_Write_Bit(CE_GPIO, CE_PIN, OFF);
  nRF_Write_One_Reg(CONFIG,(CONFIG_DEFAULT)|(0<<PWR_UP));
}



