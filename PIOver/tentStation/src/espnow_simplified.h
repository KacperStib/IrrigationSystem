#include <esp_now.h>
#include <WiFi.h>

typedef struct msgNamiotRx {
  bool onOff;
};

typedef struct msgNamiotTx {
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

msgNamiotRx msgRx;
msgNamiotTx msgTx;

uint8_t panel[] = {0x34, 0xB7, 0xDA, 0xF8, 0xC1, 0xC8};

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void espnow_init();
void addPeer(uint8_t device[]);
void sendCommand(uint8_t* device, struct msgNamiotTx commandData);