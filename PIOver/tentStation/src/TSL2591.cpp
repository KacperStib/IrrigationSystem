#include "TSL2591.h"

//uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t VALUE_I2C
//I2Cread(uint8_t ADDRESS_I2C, uint8_t REGISTER_I2C, uint8_t *buf, bytestorecei)
//gain tsl.setGain(TSL2591_GAIN_MED); 0x10
//timeing tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS); 0x02

void TSLenable(){
	I2CwriteVAL(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ENABLE, TSL2591_ENABLE);
}

void TSLdisable(){
	I2CwriteVAL(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ENABLE, TSL2591_DISABLE);   
}

void TSLconfig(){
  TSLenable();
	I2CwriteVAL(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CONTROL, TSL2591_INTEGRATIONTIME_300MS | TSL2591_GAIN_MED);
  //TSLdisable();
}

uint8_t TSLreadID(){
  //TSLenable();
	uint8_t buf;
	//I2Cread(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ID, &buf, 1);
  I2CwriteREG(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_ID);
  delay(10);
  I2Cread(TSL2591_ADRESS, &buf, 1);
  //TSLdisable();
	return buf;
}

float TSLreadLux(){
  //TSLenable();
  delay(500);
  uint8_t ch0[2];
  uint8_t ch1[2];

  /*
  I2Cread(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN0_LOW, ch0, 2);
  I2Cread(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN1_LOW, ch1, 2);
  */
  I2CwriteREG(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN0_LOW);
  delay(10);
  I2Cread(TSL2591_ADRESS, ch0, 2);

  I2CwriteREG(TSL2591_ADRESS, TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN1_LOW);
  delay(10);
  I2Cread(TSL2591_ADRESS, ch1, 2);
  uint16_t y = (ch0[1] << 8 | ch0[0]);
  uint32_t x = (ch1[1] << 8 | ch1[0]);
  x <<= 16;
  x |= y;

  //integration time 300, gain medium 25.0
  float divider = (300.0 * 25.0) / TSL2591_LUX_DF;

  uint16_t lum = x & 0xFFFF;
  uint16_t ir = x>> 16;

  float lux = (((float)lum - (float)ir)) * (1.0F - ((float)ir / (float)lum)) / divider;

  //TSLdisable();
  
  return lux;
}