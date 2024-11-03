#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

#ifndef ESPNOW_SIMPLIFIED_H
#define ESPNOW_SIMPLIFIED_H

extern bool newN;
extern bool newT;

struct msgNamiotTx {
  bool onOff;
  bool autom;
  uint8_t duration;
};

struct msgNamiotRx {
  float lux;
  float tempInside;
  float rhInside;
  float tempOutside;
  float rhOutside;
  uint8_t waterLvl;
  uint8_t probe1;
  uint8_t probe2;
  uint8_t probe3;
  bool onOff;
  bool seqEnd;
};

struct msgTrawnikTx {
  bool onOff;
  uint8_t section;
  bool autom;
  uint8_t duration;
};

struct msgTrawnikRx {
  bool isRain;
  bool seqEnd;
};

extern msgTrawnikRx msgTRx;
extern msgTrawnikTx msgTTx;
extern msgNamiotRx msgNRx;
extern msgNamiotTx msgNTx;

extern uint8_t panel[6];
extern uint8_t trawnik[6];
extern uint8_t namiot[6];

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void espnow_init();
void addPeer(uint8_t device[]);
void sendCommandT(uint8_t* device, struct msgTrawnikTx commandData);
void sendCommandN(uint8_t* device, struct msgNamiotTx commandData);

#endif