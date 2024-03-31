#ifndef FEE_AT24C128_H_
#define FEE_AT24C128_H_

#include "stdint.h"
#include "stm32h7xx_hal.h"

void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_PageErase (uint16_t page);

void EEPROM_Write_NUM (uint16_t page, uint16_t offset, float  fdata);
float EEPROM_Read_NUM (uint16_t page, uint16_t offset);

#endif /* FEE_AT24C128_H_ */
