#include <esp_now.h>
#include <WiFi.h>

typedef struct msgTrawnikRx {
  bool onOff;
};

typedef struct msgTrawnikTx {
  bool isRain;
  bool seqEnd;
};

msgTrawnikRx msgRx;
msgTrawnikTx msgTx;

uint8_t panel[] = {0x40, 0x4C, 0xCA, 0xF5, 0xA1, 0x94};

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&msgRx, incomingData, sizeof(msgRx));
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


