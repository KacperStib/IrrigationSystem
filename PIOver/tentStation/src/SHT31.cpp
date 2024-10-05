#include "SHT31.h"

void SHT31heaterEnable(){
  /*
  uint8_t cmd[2];
  uint16_t command = SHT31_HEATEREN;
  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF; 
  I2Cwrite(SHT31_ADRESS, cmd[0], cmd[1]);
  */
 I2Cwrite2B(SHT31_ADRESS, SHT31_HEATEREN);
}

void SHT31heaterDisable(){
  /*
  uint8_t cmd[2];
  uint16_t command = SHT31_HEATERDIS;
  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF; 
  I2Cwrite(SHT31_ADRESS, cmd[0], cmd[1]);
  */
  I2Cwrite2B(SHT31_ADRESS, SHT31_HEATERDIS);
}

void SHT31measurment(float* T, float* RH){
  uint8_t buf[6];
  /*
  uint8_t cmd[2];
  uint16_t command = SHT31_MEAS_HIGHREP;
  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF; 
  I2Cread2(SHT31_ADRESS, cmd[0], cmd[1], buf, 6);
  */
  I2Cwrite2B(SHT31_ADRESS, SHT31_MEAS_HIGHREP);
  delay(20);
  I2Cread(SHT31_ADRESS, buf, 6);
  //for(int i = 0; i < 6 ; i++)
    //Serial.println(buf[i]);

  float t = (uint16_t)buf[0] * 256 + (uint16_t)buf[1];
  float rh = (uint16_t)buf[3] * 256 + (uint16_t)buf[4];
  *T = -45 + 175 * t / 65535;
  *RH = 100 * rh / 65535;

  //Serial.printf("Temperature SHT31: %f\n", T);
  //Serial.printf("RH SHT31: %f %\n", RH);
}