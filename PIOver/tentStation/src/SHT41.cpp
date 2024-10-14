#include "SHT41.h"

void SHT41measurment(float* T, float* RH){
  uint8_t buf[6];
  I2CwriteREG(SHT41_ADRESS, MED_PREC_MEAS);
  // adjust delay with datasheet based on measurment resolution
  delay(10);
  I2Cread(SHT41_ADRESS, buf, 6);

  // debug to read each Byte
  //for(int i = 0; i < 6 ; i++)
    //Serial.println(buf[i]);

  // value = MSB * 256 + LSB
  float t = (uint16_t)buf[0] * 256 + (uint16_t)buf[1];
  float rh = (uint16_t)buf[3] * 256 + (uint16_t)buf[4];
  // calculation based on datasheet
  *T = -45 + 175 * t / 65535;
  *RH = -6 + 125 * rh / 65535;
  
  // debug
  //Serial.printf("Temperature SHT41: %f\n", T);
  //Serial.printf("RH SHT41: %f %\n", RH);
}