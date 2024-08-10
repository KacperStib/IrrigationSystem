#include <Wire.h>

#define I2C_SLAVE_SDA_PIN 8
#define I2C_SLAVE_SCL_PIN 9

void I2Cinit(){
  if(Wire.begin() == true)
    Serial.println("I2C init OK");
  else 
    Serial.println("I2C INIT ERROR");
}

//uint8_t data[10]; // Adjust size as needed
//uint8_t  = sizeof(data);
//I2Cread(0x68, 0x3B, data, bytesToReceive); // For example, reading 6 bytes from register 0x3B

void I2Cread(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t *buf, uint8_t bytesToReceive) {
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
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
