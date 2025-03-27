#include "SHT31.h"

// wlacz grzalke
void SHT31heaterEnable(){
 I2Cwrite2B(SHT31_ADRESS, SHT31_HEATEREN);
}

// wylacz grzalke
void SHT31heaterDisable(){
  I2Cwrite2B(SHT31_ADRESS, SHT31_HEATERDIS);
}

// pomiar temperatury i wilgotnosci i przypisanie pomiarow do wskaznikow
void SHT31measurment(float* T, float* RH){
  uint8_t buf[6];
  I2Cwrite2B(SHT31_ADRESS, SHT31_MEAS_HIGHREP);
  // delay zalezny od DATASHEETu
  delay(20);
  I2Cread(SHT31_ADRESS, buf, 6);

  // debug do czytania bajtow po kolei
  //for(int i = 0; i < 6 ; i++)
    //Serial.println(buf[i]);

  // value = MSB * 256 + LSB
  float t = (uint16_t)buf[0] * 256 + (uint16_t)buf[1];
  float rh = (uint16_t)buf[3] * 256 + (uint16_t)buf[4];
  // wzory z DATASHEETu
  *T = -45 + 175 * t / 65535;
  *RH = 100 * rh / 65535;

  // debug
  //Serial.printf("Temperature SHT31: %f\n", T);
  //Serial.printf("RH SHT31: %f %\n", RH);
}