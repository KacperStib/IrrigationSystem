#include <esp_now.h>
#include <WiFi.h>

// esp now msgs
struct msgTrawnikRx {
  bool onOff;
};

struct msgTrawnikTx {
  bool isRain;
  bool seqEnd;
};

extern msgTrawnikRx msgRx;
extern msgTrawnikTx msgTx;

extern uint8_t panel[6];

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void espnow_init();
void addPeer(uint8_t device[]);
void sendCommand(uint8_t* device, struct msgTrawnikTx commandData);