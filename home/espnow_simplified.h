#include <esp_now.h>
#include <WiFi.h>

bool newN = 0;

typedef struct msgNamiot {
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

typedef struct msgTrawnikTx {
  bool onOff;
};

typedef struct msgTrawnikRx {
  bool isRain;
  bool seqEnd;
};

msgTrawnikRx msgTRx;
msgTrawnikTx msgTTx;
msgNamiot msgN;

uint8_t panel[] = {0x40, 0x4C, 0xCA, 0xF5, 0xA1, 0x94};
uint8_t trawnik[] = {0x64, 0xE8, 0x33, 0x88, 0x2F, 0x3C};
uint8_t namiot[] = {0x64, 0xE8, 0x33, 0x88, 0x0B, 0x04};

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  if(memcmp(mac_addr, trawnik, sizeof(trawnik)) == 0)
    memcpy(&msgTRx, incomingData, sizeof(msgT));
  else if(memcmp(mac_addr, namiot, sizeof(namiot)) == 0){
    memcpy(&msgN, incomingData, sizeof(msgN));
    newN = 1;
  }
}

void espnow_init(){
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    //Serial.println("ESP-NOW Init Failed");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void addPeer(uint8_t device[]){
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, device, 6);
  esp_now_add_peer(&peerInfo);
}

void sendCommand(uint8_t* device, struct msgTrawnikTx commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}


