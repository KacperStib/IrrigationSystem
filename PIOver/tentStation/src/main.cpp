#include "I2C.h"
#include "TSL2591.h"
#include "SHT41.h"
#include "SHT31.h"
#include "PROBES.h"
#include "HCSR04.h"
#include "espnow_simplified.h"

#define VALVE 4

float lux, tIn, rhIn, tOut, rhOut, p1, p2, p3, waterLvl;
bool wateringCmd = 0;

void wateringSequence();

void setup() {
  Serial.begin(9600);
  
  // initialize I2C communication
  if(!I2Cinit())
    Serial.println("I2C init OK");
  else
    Serial.println("I2C INIT ERROR");

  // config sensors if needed
  TSLconfig();
  HCSR04init();

  // init esp now and add peer
  espnow_init();
  addPeer(panel);

  pinMode(VALVE, OUTPUT);
}

// in loop measurements from sensors and assign it esp now msg
void loop() {

  //TSL - lux
  lux = TSLreadLux();
  //Serial.printf("Lux TSL2591: %f\n", lux);
  msgTx.lux = lux;

  //SHT41 - Inside
  SHT41measurment(&tIn, &rhIn);
  //Serial.printf("SHT41: T: %f RH: %f\n", tIn, rhIn);
  msgTx.tempInside = tIn;
  msgTx.rhInside = rhIn;

  //SHT31 - Outside
  SHT31heaterEnable();
  delay(500);
  SHT31heaterDisable();
  delay(5000);
  SHT31measurment(&tOut, &rhOut);
  //Serial.printf("SHT31: T: %f RH: %f\n\n", tOut, rhOut);
  msgTx.tempOutside = tOut;
  msgTx.rhOutside = rhOut;

  //PROBES
  p1 = measurement(PROBE1);
  p2 = measurement(PROBE2);
  p3 = measurement(PROBE3);
  //Serial.printf("PROBES: 1: %f, 2: %f, 3: %f\n", p1, p2, p3);
  msgTx.probe1 = p1;
  msgTx.probe2 = p2;
  msgTx.probe3 = p3;

  //WATER LEVEL
  waterLvl = waterPercentage();
  //Serial.printf("Distance: %d, Level: %d %\n", distance(), waterLvl);
  msgTx.waterLvl = waterLvl;

  // send command to panel
  sendCommand(panel, msgTx);

  // assign received command to local variable
  wateringCmd = msgRx.onOff;
  //Serial.println(wateringCmd);
  if(wateringCmd /*&& millis() - lastRain() >= RAIN_DELAY * 1000 * 60*/){
    wateringSequence();
  }

  delay(2000);
}

void wateringSequence(){
  digitalWrite(VALVE, 1);
  delay(5000);
  digitalWrite(VALVE, 0);
  msgTx.seqEnd = 1;
  sendCommand(panel, msgTx);
  msgTx.seqEnd = 0;
}