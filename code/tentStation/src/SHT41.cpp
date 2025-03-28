#include "SHT41.h"

// pomiar temperatury i wilgotnosci i przypisanie pomiarow do wskaznikow
void SHT41measurment(float* T, float* RH){
  uint8_t buf[6];
  I2CwriteREG(SHT41_ADRESS, MED_PREC_MEAS);
  // delay zalezny od DATASHEETu
  delay(10);
  I2Cread(SHT41_ADRESS, buf, 6);

  // debug do czytania bajtow po kolei
  //for(int i = 0; i < 6 ; i++)
    //Serial.println(buf[i]);

  // value = MSB * 256 + LSB
  float t = (uint16_t)buf[0] * 256 + (uint16_t)buf[1];
  float rh = (uint16_t)buf[3] * 256 + (uint16_t)buf[4];
  // wzory z DATASHEETu
  *T = -45 + 175 * t / 65535;
  *RH = -6 + 125 * rh / 65535;
  
  // debug
  //Serial.printf("Temperature SHT41: %f\n", T);
  //Serial.printf("RH SHT41: %f %\n", RH);
}