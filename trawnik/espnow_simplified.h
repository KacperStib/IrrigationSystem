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

msg message;

uint8_t device1[] = {0xB0, 0xA7, 0x32, 0x81, 0xEC, 0x78};
uint8_t device2[] = {0xD4, 0xD4, 0xDA, 0x5E, 0x22, 0x5C};
uint8_t device3[] = {0x84, 0xCC, 0xA8, 0x47, 0x9D, 0x7C};

void espnow_init(){
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}

void addPeer(uint8_t device){
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, device, 6);
  esp_now_add_peer(&peerInfo);
}

void sendCommand(uint8_t device, struct_message commandData) {
  esp_now_send(device, (uint8_t *)&commandData, sizeof(commandData));
}

void OnDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
  memcpy(&message, incomingData, sizeof(message));
}
