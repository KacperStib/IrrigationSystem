#include <Arduino.h>
#include <Wire.h>
#include "I2C.h"
#include "clock.h"

#define EEPROM_ADRESS 0x50

#define TENT_MONTH_REG 0x00
#define TENT_DAY_REG 0x01
#define TENT_HOUR_REG 0x02
#define TENT_MINUTE_REG 0x03

#define GARDEN_MONTH_REG 0x04
#define GARDEN_DAY_REG 0x05
#define GARDEN_HOUR_REG 0x06
#define GARDEN_MINUTE_REG 0x07

#define RAIN_MONTH_REG 0x08
#define RAIN_DAY_REG 0x09
#define RAIN_HOUR_REG 0xA
#define RAIN_MINUTE_REG 0xB

bool eepromWrite(uint8_t REG, uint8_t VAL);
void eepromRead(uint8_t REG, uint8_t *BUF);
