#include <esp_now.h>
#include <WiFi.h>

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

typedef struct msgTrawnik {
  bool onOff;
  bool isRain;
  bool seqEnd;
};

msgNamiot msg;

uint8_t panel[] = {0x34, 0xB7, 0xDA, 0xF8, 0xC1, 0xC8};

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&msg, incomingData, sizeof(msg));
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

void sendCommand(uint8_t* device, struct msgNamiot commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}
