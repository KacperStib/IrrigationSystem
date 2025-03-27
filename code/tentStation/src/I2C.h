#include <Wire.h>

#define I2C_SLAVE_SDA_PIN 8
#define I2C_SLAVE_SCL_PIN 9

bool I2Cinit();
/*
void I2Cread(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t *buf, uint8_t bytesToReceive);
bool I2Cwrite(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t VALUE_I2C);
void I2Cread2(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C1, uint8_t REGISTER_I2C2, uint8_t *buf, uint8_t bytesToReceive);
*/

bool I2CwriteREG(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C);
bool I2CwriteVAL(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t VALUE_I2C);
bool I2Cwrite2B(uint8_t ADDRESS_I2C, uint16_t CMD);
void I2Cread(uint8_t ADDRESS_I2C, uint8_t *buf, uint8_t bytesToReceive);
