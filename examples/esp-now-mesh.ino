#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  char command[5];
  int msgID;
} struct_message;

struct_message myData;
int lastReceivedMsgID = -1;

char myID = '2'; //Change this, it's unique for each device


// You need to include MAC addresses of all devices in the network
uint8_t device1[] = {0xB0, 0xA7, 0x32, 0x81, 0xEC, 0x78};
uint8_t device2[] = {0xD4, 0xD4, 0xDA, 0x5E, 0x22, 0x5C};
uint8_t device3[] = {0x84, 0xCC, 0xA8, 0x47, 0x9D, 0x7C};

const int ledPin = 1;
int msgCount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
  
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, device1, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, device2, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, device3, 6);
  esp_now_add_peer(&peerInfo);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readString();
    command.trim();

    strncpy(myData.command, command.c_str(), sizeof(myData.command));
    myData.msgID = msgCount++;

    sendCommand(myData);
  }
}

void sendCommand(struct_message commandData) {
  if (commandData.command[0] != myID) {
    esp_now_send(device1, (uint8_t *)&commandData, sizeof(commandData));
    esp_now_send(device2, (uint8_t *)&commandData, sizeof(commandData));
    esp_now_send(device3, (uint8_t *)&commandData, sizeof(commandData));
  }
}

void OnDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  // If this message has already seen, skip it
  if (myData.msgID == lastReceivedMsgID) {
    return;
  }
  
  lastReceivedMsgID = myData.msgID;
  
  String command = String(myData.command);
  
  if (command.charAt(0) == myID) {
    if (command.substring(1).equals("ON")) {
      digitalWrite(ledPin, HIGH);
    } else if (command.substring(1).equals("OFF")) {
      digitalWrite(ledPin, LOW);
    }
  }
  else {
    sendCommand(myData);
    }
}
