#include "i2c.h"
#include "TSL2591.h"
#include "SHT41.h"
#include "SHT31.h"

float lux, tIn, rhIn, tOut, rhOut;

void setup() {
  Serial.begin(9600);
  I2Cinit();
  TSLconfig();
}

void loop() {
  lux = TSLreadLux();
  Serial.printf("Lux TSL2591: %f\n", lux);

  SHT41measurment(&tIn, &rhIn);
  Serial.printf("SHT41: T: %f RH: %f\n", tIn, rhIn);

  SHT31heaterEnable();
  delay(500);
  SHT31heaterDisable();
  delay(5000);
  SHT31measurment(&tOut, &rhOut);

  Serial.printf("SHT31: T: %f RH: %f\n\n", tOut, rhOut);

  delay(2000);
}
