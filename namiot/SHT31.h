#define SHT31_ADRESS 0x45

#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06 /**< Measurement High Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_MEDREP_STRETCH 0x2C0D /**< Measurement Medium Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_LOWREP_STRETCH 0x2C10 /**< Measurement Low Repeatability with Clock Stretch Enabled*/
#define SHT31_MEAS_HIGHREP 0x2400 /**< Measurement High Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_MEDREP 0x240B /**< Measurement Medium Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_LOWREP 0x2416 /**< Measurement Low Repeatability with Clock Stretch Disabled */
#define SHT31_READSTATUS 0xF32D   /**< Read Out of Status Register */
#define SHT31_CLEARSTATUS 0x3041  /**< Clear Status */
#define SHT31_SOFTRESET 0x30A2    /**< Soft Reset */
#define SHT31_HEATEREN 0x306D     /**< Heater Enable */
#define SHT31_HEATERDIS 0x3066    /**< Heater Disable */
#define SHT31_REG_HEATER_BIT 0x0d

void SHT31heaterEnable(){
  uint8_t cmd[2];
  uint16_t command = SHT31_HEATEREN;

  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF; 

  I2Cwrite(SHT31_ADRESS, cmd[0], cmd[1]);
}

void SHT31heaterDisable(){
  uint8_t cmd[2];
  uint16_t command = SHT31_HEATERDIS;

  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF; 

  I2Cwrite(SHT31_ADRESS, cmd[0], cmd[1]);
}

void SHT31measurment(float* T, float* RH){
  uint8_t buf[6];
  uint8_t cmd[2];
  uint16_t command = SHT31_MEAS_HIGHREP;

  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF; 

  I2Cread2(SHT31_ADRESS, cmd[0], cmd[1], buf, 6);

  //for(int i = 0; i < 6 ; i++)
    //Serial.println(buf[i]);

  float t = (uint16_t)buf[0] * 256 + (uint16_t)buf[1];
  float rh = (uint16_t)buf[3] * 256 + (uint16_t)buf[4];
  *T = -45 + 175 * t / 65535;
  *RH = 100 * rh / 65535;

  //Serial.printf("Temperature SHT31: %f\n", T);
  //Serial.printf("RH SHT31: %f %\n", RH);
}