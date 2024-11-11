/* TODO */
#include "BMP280.h"

uint16_t ucalibDig[2];
int16_t calibDig[12];
int32_t tFine;

// initialize BMP normal mode, high sampling andfilter
void BMPinit(){
  I2CwriteVAL(0x76, BMP280_REGISTER_CONTROL, (MODE_NORMAL | (SAMPLING_X16 << 2) | (SAMPLING_X16 << 5)));
  I2CwriteVAL(0x76, BMP280_REGISTER_CONFIG, ((FILTER_X16 << 2) | (STANDBY_MS_05 << 5)));
  readCoefs();
}

// read TFine to calculate preassure (but dont need to calculate whole temperature)
void readTFine(){
  int32_t var1, var2;
  uint8_t buf[3];
  I2CwriteREG(0x76, BMP280_REGISTER_TEMPDATA);
  I2Cread(0x76, buf, 3);
  int32_t adc_T = int32_t(buf[0]) << 16 | uint32_t(buf[1]) << 8 | uint32_t(buf[2]);
  adc_T >>= 4;

  var1 = ((((adc_T >> 3) - ((int32_t)ucalibDig[0] << 1))) * ((int32_t)calibDig[1])) >> 11;

  var2 = (((((adc_T >> 4) - ((int32_t)ucalibDig[0])) * ((adc_T >> 4) - ((int32_t)ucalibDig[0]))) >> 12) * ((int32_t)calibDig[2])) >> 14;

  tFine = var1 + var2;
}

// readCoefs for Tfine and preasure calculations
void readCoefs(){
  uint8_t buf[2];
  uint16_t temp;

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_T1);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  ucalibDig[0] = (temp >> 8) | (temp << 8);

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_T2);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[1] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_T3);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[2] = int16_t ((temp >> 8) | (temp << 8));

  //////////////////////////////////////////////////////////////////////////////////
  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P1);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  ucalibDig[1] = (temp >> 8) | (temp << 8);

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P2);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[4] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P3);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[5] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P4);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[6] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P5);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[7] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P6);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[8] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P7);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[9] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P8);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[10] = int16_t ((temp >> 8) | (temp << 8));

  I2CwriteREG(0x76, BMP280_REGISTER_DIG_P9);
  I2Cread(0x76, buf, 2);
  temp = uint16_t(buf[0]) << 8 | uint16_t(buf[1]);
  calibDig[11] = int16_t ((temp >> 8) | (temp << 8));
}

// read and calculate preasure based on datasheet
float readPreasure(){
  int64_t var1, var2, p;
  readTFine();
  uint8_t buf[3];
  I2CwriteREG(0x76, BMP280_REGISTER_PRESSUREDATA);
  I2Cread(0x76, buf, 3);
  int32_t adc_P = int32_t(buf[0]) << 16 | uint32_t(buf[1]) << 8 | uint32_t(buf[2]);
  adc_P >>= 4;

  var1 = ((int64_t)tFine) - 128000;
  var2 = var1 * var1 * (int64_t)calibDig[8];
  var2 = var2 + ((var1 * (int64_t)calibDig[7]) << 17);
  var2 = var2 + (((int64_t)calibDig[6]) << 35);
  var1 = ((var1 * var1 * (int64_t)calibDig[5]) >> 8) + ((var1 * (int64_t)calibDig[4]) << 12);
  var1 =(((((int64_t)1) << 47) + var1)) * ((int64_t)ucalibDig[1]) >> 33;

  if (var1 == 0) {
    return 0; // avoid exception caused by division by zero
  }

  p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)calibDig[11]) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)calibDig[10]) * p) >> 19;

  p = ((p + var1 + var2) >> 8) + (((int64_t)calibDig[9]) << 4);

  // division by 100 to aqcuire hPa instead of raw Pa
  return (float)p / 25600;
}