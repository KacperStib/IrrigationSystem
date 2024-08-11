#include "i2c.h"
#include "TSL2591.h"
#include "SHT41.h"
#include "SHT31.h"

void setup() {
  Serial.begin(9600);
  I2Cinit();
  TSLconfig();
}

void loop() {
  Serial.printf("Lux TSL2591: %f\n", TSLreadLux());
  SHT41measurment();
  SHT31heaterEnable();
  delay(500);
  SHT31heaterDisable();
  delay(5000);
  SHT31measurment();
  Serial.println();
  delay(2000);
}
