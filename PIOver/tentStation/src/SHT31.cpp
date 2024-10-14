#include "SHT31.h"

// enable heater
void SHT31heaterEnable(){
 I2Cwrite2B(SHT31_ADRESS, SHT31_HEATEREN);
}

// disable heater
void SHT31heaterDisable(){
  I2Cwrite2B(SHT31_ADRESS, SHT31_HEATERDIS);
}

// measure temperature and humidty and assign it to pointers
void SHT31measurment(float* T, float* RH){
  uint8_t buf[6];
  I2Cwrite2B(SHT31_ADRESS, SHT31_MEAS_HIGHREP);
  // adjust delay with datasheet based on measurment resolution
  delay(20);
  I2Cread(SHT31_ADRESS, buf, 6);

  // debug to read each Byte
  //for(int i = 0; i < 6 ; i++)
    //Serial.println(buf[i]);

  // value = MSB * 256 + LSB
  float t = (uint16_t)buf[0] * 256 + (uint16_t)buf[1];
  float rh = (uint16_t)buf[3] * 256 + (uint16_t)buf[4];
  // calculation based on datasheet
  *T = -45 + 175 * t / 65535;
  *RH = 100 * rh / 65535;

  // debug
  //Serial.printf("Temperature SHT31: %f\n", T);
  //Serial.printf("RH SHT31: %f %\n", RH);
}