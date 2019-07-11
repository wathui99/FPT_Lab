#ifndef __nRF24_H
#define __nRF24_H

#include <stdint.h>
#include "mymacro.h"
#include "nRF24_PinMap.h"
#include "spi.h"
#include "gpio.h"

#define CSS_GPIO GPIOB
#define CSS_PIN 4
#define CE_GPIO GPIOB
#define CE_PIN 3

#define CSS_HIGH() (sbi(GPIOB, 4))
#define CSS_LOW() (cbi(GPIOB, 4))

static uint8_t nRF_payloadLength;

void nRF_Set_Payload_Leng(uint8_t value);
uint8_t nRF_Get_Status_Reg();
void nRF_Write_One_Reg(uint8_t reg, uint8_t value);
uint8_t nRF_Read_One_Reg(uint8_t reg);

#endif /* __nRF24_H */