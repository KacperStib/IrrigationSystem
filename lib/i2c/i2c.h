#include <Wire.h>

#define I2C_SLAVE_SDA_PIN 20
#define I2C_SLAVE_SCL_PIN 21

void I2Cinit(uint8_t ADRESS){
  if(Wire.begin(ADRESS, I2C_SLAVE_SDA_PIN, I2C_SLAVE_SCL_PIN, 400000) == true)
    Serial.println("I2C init OK");
  else 
    Serial.println("I2C INIT ERROR");
}

//uint8_t data[10]; // Adjust size as needed
//uint8_t  = sizeof(data);
//I2Cread(0x68, 0x3B, data, bytesToReceive); // For example, reading 6 bytes from register 0x3B

void I2Cread(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t *buf) {
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(REGISTER_I2C);
  Wire.endTransmission(false); // Send repeated start condition
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
