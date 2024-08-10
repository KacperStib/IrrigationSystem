#include "i2c.h"
#include "TSL2591.h"
#include "SHT41.h"

void setup() {
  Serial.begin(9600);
  I2Cinit();
  TSLconfig();
}

void loop() {
  uint8_t id = TSLreadID();
  uint32_t lux = TSLreadLux();
  Serial.println(id);
  Serial.println(lux);
  Serial.println();
  SHTmeasurment();
  delay(2000);
}
