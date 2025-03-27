#include "TSL2591.h"

// wlaczenie TSL2591
void TSLenable(){
	I2CwriteVAL(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ENABLE, TSL2591_ENABLE);
}

void TSLdisable(){
	I2CwriteVAL(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ENABLE, TSL2591_DISABLE);   
}

// wlaczenie TSLa oraz zapis podstawowowej konfiguracji do odpowiedniego rejsetru
void TSLconfig(){
  TSLenable();
	I2CwriteVAL(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CONTROL, TSL2591_INTEGRATIONTIME_300MS | TSL2591_GAIN_MED);
  //TSLdisable();
}

// funkcja testowa do odczytu ID
uint8_t TSLreadID(){
  //TSLenable();
	uint8_t buf;
  I2CwriteREG(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ID);
  delay(10);
  I2Cread(TSL2591_ADRESS, &buf, 1);
  //TSLdisable();
	return buf;
}

// funkcja do odczytu wartosci LUXow natezenia swiatla
float TSLreadLux(){
  //TSLenable();
  delay(500);
  uint8_t ch0[2];
  uint8_t ch1[2];

  I2CwriteREG(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN0_LOW);
  delay(10);
  I2Cread(TSL2591_ADRESS, ch0, 2);

  I2CwriteREG(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN1_LOW);
  delay(10);
  I2Cread(TSL2591_ADRESS, ch1, 2);

  // ch_x[1] * 256 + ch_x [0]
  uint16_t y = (ch0[1] << 8 | ch0[0]);
  uint32_t x = (ch1[1] << 8 | ch1[0]);
  
  // x * 65536
  x <<= 16;

  // porownanie bitow
  x |= y;

  //integration time 300, gain medium 25.0
  float divider = (300.0 * 25.0) / TSL2591_LUX_DF;

  // uint16_t lum = (uint16_t) x
  uint16_t lum = x & 0xFFFF;

  // x / 65536
  uint16_t ir = x >> 16;

  // wzor z DATASHEETu
  float lux = (((float)lum - (float)ir)) * (1.0F - ((float)ir / (float)lum)) / divider;

  //TSLdisable();
  
  return lux;
}