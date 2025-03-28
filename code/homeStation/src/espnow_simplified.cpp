#include "espnow_simplified.h"

bool newN = 0;
bool newT = 0;

bool seqEndN = false;
bool seqEndT = false;
bool isRain = false;

msgTrawnikRx msgTRx;
msgTrawnikTx msgTTx;
msgNamiotRx msgNRx;
msgNamiotTx msgNTx;

// adresy MAC poszczegolnych stacji
uint8_t panel[6] = {0x40, 0x4C, 0xCA, 0xF5, 0xA1, 0x94};
uint8_t trawnik[6] = {0x64, 0xE8, 0x33, 0x88, 0x2F, 0x3C};
uint8_t namiot[6] = {0x64, 0xE8, 0x33, 0x88, 0x0B, 0x04};

// po otrzymaniu wiadomosci skopiuj do zmiennych przechowywanych w urzadzeniu i ustaw flage odbioru
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  if(memcmp(mac_addr, trawnik, sizeof(trawnik)) == 0){
    memcpy(&msgTRx, incomingData, sizeof(msgTRx));
    newT = 1;
    if(msgTRx.isRain)
      isRain = msgTRx.isRain;
    if(msgTRx.seqEnd)
      seqEndT = msgTRx.seqEnd;
  }
  else if(memcmp(mac_addr, namiot, sizeof(namiot)) == 0){
    memcpy(&msgNRx, incomingData, sizeof(msgNRx));
    newN = 1;
    if(msgNRx.seqEnd)
      seqEndN = msgNRx.seqEnd;
  }
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

// wyslij komende do odpowiedniej stacji
void sendCommandT(uint8_t* device, struct msgTrawnikTx commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}

void sendCommandN(uint8_t* device, struct msgNamiotTx commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}