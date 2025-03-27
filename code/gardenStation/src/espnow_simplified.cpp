#include "espnow_simplified.h"

msgTrawnikRx msgRx;
msgTrawnikTx msgTx;

// adres MAC panelu
uint8_t panel[6] = {0x34, 0xB7, 0xDA, 0xF8, 0xC1, 0xC8};

// procedura przy odbierze wiadomosci z panelu
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&msgRx, incomingData, sizeof(msgRx));
}

// inicjalizacja ESP_NOW
void espnow_init(){
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    //Serial.println("ESP-NOW Init Failed");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

// dodaj polaczenie
void addPeer(uint8_t device[]){
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, device, 6);
  esp_now_add_peer(&peerInfo);
}

// wysylanie wiadomosci do panelu
void sendCommand(uint8_t* device, struct msgTrawnikTx commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}