#include "I2C.h"

// initialize I2C communication and return if it was successful
bool I2Cinit(){
  if(Wire.begin(I2C_SLAVE_SDA_PIN, I2C_SLAVE_SCL_PIN, 400000) == true)
    return true;
  else 
    return false;
}

// write register
bool I2CwriteREG(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C){
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  if (Wire.endTransmission() == 0)
    return true;
  else
    return false; 
}

// write value to register
bool I2CwriteVAL(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t VALUE_I2C){
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  Wire.write(VALUE_I2C);
  if (Wire.endTransmission() == 0)
    return true;
  else
    return false; 
}

// write 2 Byte command
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

// read data to buf
void I2Cread(uint8_t ADDRESS_I2C, uint8_t *buf, uint8_t bytesToReceive) {
  Wire.requestFrom(ADDRESS_I2C, bytesToReceive);
  Wire.readBytes(buf, bytesToReceive);
}
