#ifndef __nRF24_H
#define __nRF24_H

#include <stdint.h>
#include "mymacro.h"
#include "nRF24_PinMap.h"
#include "spi.h"
#include "gpio.h"

#define nRF_Delay_Time 100
/*
* 1 enable delay
* 0 no delay
*/
#define nRF_Delay_Mask 1
#define CONFIG_DEFAULT 0x08


typedef enum {
  nRF_MaskInterrupt_Disable = (uint8_t)0x00,
  nRF_MaskInterrupt_MaxTries = (uint8_t)0x10,
  nRF_MaskInterrupt_TX = (uint8_t)0x20,
  nRF_MaskInterrupt_RX = (uint8_t)0x40
} nRF_MaskInterrupt_TypeDef;
typedef enum {
  nRF_Mode_TX    = (uint8_t)0x00,
  nRF_Mode_RX    = (uint8_t)0x01
} nRF_Mode_TypeDef;
typedef enum {
  nRF_CRC_Disable = (uint8_t)0x00,
  nRF_CRC_1Byte    = (uint8_t)0x08,
  nRF_CRC_2Bytes    = (uint8_t)0x0C
} nRF_CRC_TypeDef;
typedef enum {
  nRF_AA_Disable = (uint8_t)0x00,
  nRF_AA_Pipe_0 = (uint8_t)0x01,
  nRF_AA_Pipe_1 = (uint8_t)0x02,
  nRF_AA_Pipe_2 = (uint8_t)0x04,
  nRF_AA_Pipe_3 = (uint8_t)0x08,
  nRF_AA_Pipe_4 = (uint8_t)0x10,
  nRF_AA_Pipe_5 = (uint8_t)0x20
} nRF_AA_TypeDef;
typedef enum {
  nRF_Pipe_Disable = (uint8_t)0x00,
  nRF_EN_Pipe_0 = (uint8_t)0x01,
  nRF_EN_Pipe_1 = (uint8_t)0x02,
  nRF_EN_Pipe_2 = (uint8_t)0x04,
  nRF_EN_Pipe_3 = (uint8_t)0x08,
  nRF_EN_Pipe_4 = (uint8_t)0x10,
  nRF_EN_Pipe_5 = (uint8_t)0x20
} nRF_EN_Pipe_TypeDef;

typedef enum {
  nRF_Add_Width_3Bytes = (uint8_t)0x01,
  nRF_Add_Width_4Bytes = (uint8_t)0x02,
  nRF_Add_Width_5Bytes = (uint8_t)0x03
} nRF_Add_Width_TypeDef;

typedef enum {
  nRF_DataRate_1Mbps = (uint8_t)0x00,
  nRF_DataRate_2Mbps = (uint8_t)0x08
} nRF_DataRate_TypeDef;

typedef enum {
  nRF_OutPower_Tx_m18dBm = (uint8_t)0x00,
  nRF_OutPower_Tx_m12dBm = (uint8_t)0x02,
  nRF_OutPower_Tx_m6dBm = (uint8_t)0x04,
  nRF_OutPower_Tx_0dBm = (uint8_t)0x06
} nRF_OutPower_Tx_TypeDef;

#define CSS_GPIO GPIOB
#define CSS_PIN 4
#define CE_GPIO GPIOB
#define CE_PIN 3

static uint8_t nRF_payloadLength;

/* basic function */
void nRF_Delay(uint32_t);
void nRF_Set_Payload_Leng(uint8_t value);
uint8_t nRF_Get_Status_Reg();
void nRF_Write_One_Reg(uint8_t reg, uint8_t value);
uint8_t nRF_Read_One_Reg(uint8_t reg);
void nRF_Write_Multi_Regs(uint8_t reg, uint8_t *value, uint8_t len);
uint8_t *nRF_Read_Multi_Regs(uint8_t reg, uint8_t *ret, uint8_t len);

/* config function */
void nRF_Config(nRF_MaskInterrupt_TypeDef MaskInterrupt, nRF_Mode_TypeDef Mode, \
                nRF_AA_TypeDef AA, nRF_EN_Pipe_TypeDef EN_Pipe, nRF_Add_Width_TypeDef Add_Width, \
                uint8_t delay_reTrans, uint8_t num_reTrans, uint8_t RF_channel, \
                nRF_DataRate_TypeDef DataRate, nRF_OutPower_Tx_TypeDef OutPower, 
                uint8_t *RX_Add_P0, uint8_t *RX_Add_P1, \
                uint8_t RX_Add_P2, uint8_t RX_Add_P3, uint8_t RX_Add_P4, uint8_t RX_Add_P5, \
                uint8_t *TX_Add, uint8_t num_Byte_P0, uint8_t num_Byte_P1, uint8_t num_Byte_P2, \
                uint8_t num_Byte_P3, uint8_t num_Byte_P4, uint8_t num_Byte_P5);
      
uint8_t nRF_Is_Sending(void);
void nRF_Powerup_TX(void);
void nRF_Powerup_RX(void);
void nRF_Powerdown(void);
void nRF_Send(uint8_t *payload, uint8_t len, uint8_t clearFIFO);                  
                  
/* user function */
void User_nRF_Send(uint8_t *payload, uint8_t len);

#endif /* __nRF24_H */