#include "I2C.h"
#include "TSL2591.h"
#include "SHT41.h"
#include "SHT31.h"
#include "espnow_simplified.h"

float lux, tIn, rhIn, tOut, rhOut;
bool wateringCmd = 0;

void setup() {
  Serial.begin(9600);
  I2Cinit();
  TSLconfig();
  espnow_init();
  addPeer(panel);

  pinMode(4, OUTPUT); //VALVE
}

void loop() {
  lux = TSLreadLux();
  Serial.printf("Lux TSL2591: %f\n", lux);
  msgTx.lux = lux;

  SHT41measurment(&tIn, &rhIn);
  Serial.printf("SHT41: T: %f RH: %f\n", tIn, rhIn);
  msgTx.tempInside = tIn;
  msgTx.rhInside = rhIn;

  SHT31heaterEnable();
  delay(500);
  SHT31heaterDisable();
  delay(5000);
  SHT31measurment(&tOut, &rhOut);
  Serial.printf("SHT31: T: %f RH: %f\n\n", tOut, rhOut);
  msgTx.tempOutside = tOut;
  msgTx.rhOutside = rhOut;

  sendCommand(panel, msgTx);

  wateringCmd = msgRx.onOff;
  Serial.println(wateringCmd);
  if(wateringCmd /*&& millis() - lastRain() >= RAIN_DELAY * 1000 * 60*/){
    wateringSequence();
  }

  delay(2000);
}

void wateringSequence(){
  digitalWrite(4, 1);
  delay(5000);
  digitalWrite(4, 0);
}
