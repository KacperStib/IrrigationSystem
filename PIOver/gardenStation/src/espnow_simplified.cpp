#include "espnow_simplified.h"

msgTrawnikRx msgRx;
msgTrawnikTx msgTx;

uint8_t panel[6] = {0x34, 0xB7, 0xDA, 0xF8, 0xC1, 0xC8};

// called when data is received 
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&msgRx, incomingData, sizeof(msgRx));
}

// init esp now and register OnDataRecv function
void espnow_init(){
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    //Serial.println("ESP-NOW Init Failed");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

// adding peer - MAC addr
void addPeer(uint8_t device[]){
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, device, 6);
  esp_now_add_peer(&peerInfo);
}

// sending data
void sendCommand(uint8_t* device, struct msgTrawnikTx commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}