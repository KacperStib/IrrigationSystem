#include "I2C.h"
#include "TSL2591.h"
#include "SHT41.h"
#include "SHT31.h"
#include "PROBES.h"
#include "HCSR04.h"
#include "espnow_simplified.h"

float lux, tIn, rhIn, tOut, rhOut, p1, p2, p3, waterLvl;
bool wateringCmd = 0;

void wateringSequence(){
  digitalWrite(4, 1);
  delay(5000);
  digitalWrite(4, 0);
  msgTx.seqEnd = 1;
  sendCommand(panel, msgTx);
  msgTx.seqEnd = 0;
}

void setup() {
  Serial.begin(9600);
  
  if(!I2Cinit())
    Serial.println("I2C init OK");
  else
    Serial.println("I2C INIT ERROR");

  TSLconfig();
  HCSR04init();
  espnow_init();
  addPeer(panel);

  pinMode(4, OUTPUT); //VALVE
}

void loop() {

  //TSL - lux
  lux = TSLreadLux();
  Serial.printf("Lux TSL2591: %f\n", lux);
  msgTx.lux = lux;

  //SHT41 - Inside
  SHT41measurment(&tIn, &rhIn);
  Serial.printf("SHT41: T: %f RH: %f\n", tIn, rhIn);
  msgTx.tempInside = tIn;
  msgTx.rhInside = rhIn;

  //SHT31 - Outside
  SHT31heaterEnable();
  delay(500);
  SHT31heaterDisable();
  delay(5000);
  SHT31measurment(&tOut, &rhOut);
  Serial.printf("SHT31: T: %f RH: %f\n\n", tOut, rhOut);
  msgTx.tempOutside = tOut;
  msgTx.rhOutside = rhOut;

  //PROBES
  p1 = measurement(PROBE1);
  p2 = measurement(PROBE2);
  p3 = measurement(PROBE3);
  Serial.printf("PROBES: 1: %f, 2: %f, 3: %f\n", p1, p2, p3);
  msgTx.probe1 = p1;
  msgTx.probe2 = p2;
  msgTx.probe3 = p3;

  //WATER LEVEL
  waterLvl = waterPercentage();
  Serial.printf("Distance: %d, Level: %d %\n", distance(), waterLvl);
  msgTx.waterLvl = waterLvl;

  sendCommand(panel, msgTx);

  wateringCmd = msgRx.onOff;
  Serial.println(wateringCmd);
  if(wateringCmd /*&& millis() - lastRain() >= RAIN_DELAY * 1000 * 60*/){
    wateringSequence();
  }

  delay(2000);
}

