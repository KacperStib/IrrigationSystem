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
uint8_t mapValves[4] = {5, 6, 7, 10};

// ustaw flage gdy spadnie deszcz
void IRAM_ATTR rain(){
  isRain = 1;
}

// deklaracja funkcji
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

  // jesli wykrytu deszcz wyslij informacje do panelu i wyczysc flage
  if(isRain){
    msgTx.isRain = isRain;
    sendCommand(panel, msgTx);
    isRain = 0;
    msgTx.isRain = isRain;
  }

  // sprawdz nowe wiadomosci i przypisz do zmiennych globalnych
  wateringCmd = msgRx.onOff;
  section = msgRx.section;
  automation = msgRx.autom;
  duration = msgRx.duration;

  // scenariusz automatyczny
  if (automation){
    wateringSequence();
    automation = false;
    msgRx.autom = false;
  }

  // scenariusz manualny
  if (wateringCmd && !watering_en){
    digitalWrite(mapValves[section - 1], HIGH);
    watering_en = true;
  }
  else if (!wateringCmd && watering_en){
    digitalWrite(mapValves[section - 1], LOW);
    watering_en = false;
    msgTx.seqEnd = true;
    sendCommand(panel, msgTx);
    msgTx.seqEnd = false;
  }

  delay(500);
}

void pinCfg(){
  // ustaw piny IO
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
  pinMode(RAIN_SENSOR, INPUT);

  // ustaw przerwanie do detekcji deszczu
  attachInterrupt(RAIN_SENSOR, rain, RISING);
}

// procedura otwarcia pojedynczego zaworu
void openValve(uint8_t VALVE){
  lastMillis = millis();
  digitalWrite(VALVE, HIGH);
  // do testow duration * 100, normalnie duration * 60000 (zamiana milisekund na minuty)
  while(millis() - lastMillis <= duration * 100){
    delay(1000);
  }
  digitalWrite(VALVE, LOW);
}

// procedura nawadniania calego ogrodu
void wateringSequence(){
  openValve(VALVE1);
  openValve(VALVE2);
  openValve(VALVE3);
  openValve(VALVE4);
  // wyslij informacje do panelu jesli zakonczono
  msgTx.seqEnd = true;
  sendCommand(panel, msgTx);
  msgTx.seqEnd = false;
}
