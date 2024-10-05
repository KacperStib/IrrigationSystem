#include "I2C.h"

bool I2Cinit(){
  if(Wire.begin(I2C_SLAVE_SDA_PIN, I2C_SLAVE_SCL_PIN, 400000) == true)
    return true;
  else 
    return false;
}

//uint8_t data[10]; // Adjust size as needed
//uint8_t  = sizeof(data);
//I2Cread(0x68, 0x3B, data, bytesToReceive); // For example, reading 6 bytes from register 0x3B

/*
void I2Cread(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t *buf, uint8_t bytesToReceive) {
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(ADDRESS_I2C, bytesToReceive);
  Wire.readBytes(buf, bytesToReceive);
}

bool I2Cwrite(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t VALUE_I2C){
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  Wire.write(VALUE_I2C);
  if (Wire.endTransmission() == 0)
    return true;
  else
    return false; 
}

void I2Cread2(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C1, uint8_t REGISTER_I2C2, uint8_t *buf, uint8_t bytesToReceive){
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C1);
  Wire.write(REGISTER_I2C2);
  Wire.endTransmission();
  delay(20);
  Wire.requestFrom(ADDRESS_I2C, bytesToReceive);
  Wire.readBytes(buf, bytesToReceive);
}
*/

//to change
bool I2CwriteREG(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C){
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  if (Wire.endTransmission() == 0)
    return true;
  else
    return false; 
}

bool I2CwriteVAL(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t VALUE_I2C){
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  Wire.write(VALUE_I2C);
  if (Wire.endTransmission() == 0)
    return true;
  else
    return false; 
}

bool I2Cwrite2B(uint8_t ADDRESS_I2C, uint16_t CMD){
  uint8_t cmd[2];
  cmd[0] = CMD >> 8;
  cmd[1] = CMD & 0xFF;

  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(cmd[0]);
  Wire.write(cmd[1]);
  if (Wire.endTransmission() == 0)
    return true;
  else
    return false; 
}

void I2Cread(uint8_t ADDRESS_I2C, uint8_t *buf, uint8_t bytesToReceive) {
  Wire.requestFrom(ADDRESS_I2C, bytesToReceive);
  Wire.readBytes(buf, bytesToReceive);
}

