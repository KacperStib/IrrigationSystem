#include <Arduino.h>

#include "defines.h"
#include "espnow_simplified.h"

// timestamps
uint32_t lastMillis;
uint32_t lastRain;

bool isRain = 0;
bool wateringCmd = 0;
bool watering_en = false;
bool automation = false;
uint8_t section = 0;
uint8_t duration = 0;
uint8_t mapValves[4] = {10, 9, 8, 7};

// set flag when rain is detected
void IRAM_ATTR rain(){
  isRain = 1;
}

void openValve(uint8_t VALVE);
void wateringSequence();
void sectionSelector(uint8_t sec);
void pinCfg();

void setup() {
  pinCfg();
  Serial.begin(9600);
  espnow_init();
  addPeer(panel);
}

void loop() {

  // if rain detected send to panel and write timestamp
  if(isRain){
    detachInterrupt(RAIN_SENSOR);
    int read = analogRead(RAIN_SENSOR);
    if (read > 2200){
      msgTx.isRain = isRain;
      sendCommand(panel, msgTx);
      lastRain = millis();
    }
    isRain = 0;
    msgTx.isRain = isRain;
  }

  // check if there are new msgs 
  wateringCmd = msgRx.onOff;
  section = msgRx.section;
  automation = msgRx.autom;
  duration = msgRx.duration;

  if (automation){
    wateringSequence();
    automation = false;
    msgRx.autom = false;
  }
  if (wateringCmd && !watering_en){
    digitalWrite(mapValves[section - 1], LOW);
    watering_en = true;
  }
  else if (!wateringCmd && watering_en){
    digitalWrite(mapValves[section - 1], HIGH);
    watering_en = false;
    msgTx.seqEnd = true;
    sendCommand(panel, msgTx);
    msgTx.seqEnd = false;
  }

  delay(500);
}

void pinCfg(){
  // set IOs
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
  pinMode(RAIN_SENSOR, INPUT);

  // write HIGH to close RELAY
  digitalWrite(VALVE1, HIGH);
  digitalWrite(VALVE2, HIGH);
  digitalWrite(VALVE3, HIGH);
  digitalWrite(VALVE4, HIGH);

  // attach interrupt to detect rain
  attachInterrupt(RAIN_SENSOR, rain, RISING);
}

// procedure to open one valve
void openValve(uint8_t VALVE){
  lastMillis = millis();
  digitalWrite(VALVE, LOW);
  // adjust watering time
  while(millis() - lastMillis <= duration * 100){
    delay(1000);
  }
  digitalWrite(VALVE, HIGH);
}

// procedure of watering whole garden
void wateringSequence(){
  openValve(VALVE1);
  openValve(VALVE2);
  openValve(VALVE3);
  openValve(VALVE4);
  // send msg to panel that watering has ended
  msgTx.seqEnd = true;
  sendCommand(panel, msgTx);
  msgTx.seqEnd = false;
}
