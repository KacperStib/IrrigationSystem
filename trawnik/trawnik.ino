#include "defines.h"
#include "espnow_simplified.h"

uint32_t lastMillis;
uint32_t lastRain;

bool isRain = 0;
bool wateringCmd = 0;

void IRAM_ATTR rain(){
  isRain = 1;
}

void setup() {
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);

  digitalWrite(VALVE1, HIGH);
  digitalWrite(VALVE2, HIGH);
  digitalWrite(VALVE3, HIGH);
  digitalWrite(VALVE4, HIGH);
  
  Serial.begin(115200);
  espnow_init();
  addPeer(panel);
}

void loop() {

  if(isRain){
    msgTx.isRain = isRain;
    sendCommand(panel, msgTx);
    lastRain = millis();
    isRain = 0;
  }

  wateringCmd = msgRx.onOff;
  Serial.println(wateringCmd);
  if(wateringCmd /*&& millis() - lastRain() >= RAIN_DELAY * 1000 * 60*/){
    wateringSequence();
  }
  delay(500);
}

void openValve(uint8_t VALVE){
  lastMillis = millis();
  digitalWrite(VALVE, LOW);
  while(millis() - lastMillis <= WATERING_TIME * 100 * 6){ //ma byc 1000 * 60
    delay(5000);
  }
  digitalWrite(VALVE, HIGH);
}

void wateringSequence(){
  openValve(VALVE1);
  openValve(VALVE2);
  openValve(VALVE3);
  openValve(VALVE4);
}
