#include <esp_now.h>
#include <WiFi.h>

struct msgNamiotRx {
  bool onOff;
  bool autom;
};

struct msgNamiotTx {
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

extern msgNamiotRx msgRx;
extern msgNamiotTx msgTx;

extern uint8_t panel[6];

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void espnow_init();
void addPeer(uint8_t device[]);
void sendCommand(uint8_t* device, struct msgNamiotTx commandData);