#include "I2C.h"
#include "TSL2591.h"
#include "SHT41.h"
#include "SHT31.h"
#include "PROBES.h"
#include "HCSR04.h"
#include "BMP280.h"
#include "espnow_simplified.h"

#define VALVE 4

float lux, tIn, rhIn, tOut, rhOut, p1, p2, p3, average, waterLvl, preasure;
bool wateringCmd = false;
bool watering_en = false;
bool automation = false;
uint8_t duration = 0;
uint32_t lastMillis = 0;

void measurement();
void watering();
void wateringSequence();

// freeRTOS tasks
void measurementTask(void *pvParameters){
  for(;;){
    measurement();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void wateringTask(void *pvParameters){
  for(;;){
    watering();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(9600);
  
  // inicjalizacja komunikacji I2C
  if(!I2Cinit())
    Serial.println("I2C init OK");
  else
    Serial.println("I2C INIT ERROR");

  // konfiguracja sensorow
  TSLconfig();
  HCSR04init();
  BMPinit();

  // inicjalizacja ESP_NOW i dodanie polaczenia
  espnow_init();
  addPeer(panel);

  // pin config
  pinMode(VALVE, OUTPUT);

  // pomiar z sensorow - 10S
  xTaskCreate(measurementTask, "MeasurementTask", 4096, NULL, 2, NULL);

  // oblsuga nawadniania - 1S
  xTaskCreate(wateringTask, "WateringTask", 2048, NULL, 1, NULL);
}

void loop() {
  // chill
}

// pomiar oraz przygotowanie do wysylki
void measurement(){
  //TSL - lux
  lux = TSLreadLux();
  //Serial.printf("Lux TSL2591: %f\n", lux);
  msgTx.lux = lux;

  //SHT41 - temp i wilgotnosc wewnatrz
  SHT41measurment(&tIn, &rhIn);
  //Serial.printf("SHT41: T: %f RH: %f\n", tIn, rhIn);
  msgTx.tempInside = tIn;
  msgTx.rhInside = rhIn;

  //SHT31 - temp i wilgotnosc na zewwnatrz
  SHT31heaterEnable();
  vTaskDelay(500 / portTICK_PERIOD_MS);
  SHT31heaterDisable();
  vTaskDelay(2500 / portTICK_PERIOD_MS);
  SHT31measurment(&tOut, &rhOut);
  //Serial.printf("SHT31: T: %f RH: %f\n\n", tOut, rhOut);
  msgTx.tempOutside = tOut;
  msgTx.rhOutside = rhOut;

  // wilgotnosc gleby
  p1 = measure(PROBE1);
  p2 = measure(PROBE2);
  p3 = measure(PROBE3);
  average = calculateAverage();
  //Serial.printf("PROBES: 1: %f, 2: %f, 3: %f\n", p1, p2, p3);
  msgTx.probe1 = p1;
  msgTx.probe2 = p2;
  msgTx.probe3 = p3;
  msgTx.probesAvg = average;

  // poziom wody w zbiorniku
  waterLvl = waterPercentage();
  //Serial.printf("Distance: %d, Level: %d %\n", distance(), waterLvl);
  msgTx.waterLvl = waterLvl;

  // cisnienie
  preasure = readPreasure();
  msgTx.preasure = preasure;
  
  // wyslij informacje do panela
  sendCommand(panel, msgTx);
}

// procedura do nawdaniania
void watering(){
  // przypisz komendy z wiadomosci do zmiennych globalnych
  wateringCmd = msgRx.onOff;
  automation = msgRx.autom;
  duration = msgRx.duration;

  // scenariusz manulany
  if (wateringCmd && !watering_en){
    digitalWrite(VALVE, HIGH);
    watering_en = true;
  }
  else if (!wateringCmd && watering_en){
    digitalWrite(VALVE, LOW);
    watering_en = false;
    msgTx.seqEnd = true;
    sendCommand(panel, msgTx);
    msgTx.seqEnd = false;
  }

  // scenatriusz automatyczny
  if(automation){
    wateringSequence();
    automation = false;
    msgRx.autom = false;
  }
}

// sekwencja automatycznego nawadniania
void wateringSequence(){
  lastMillis = millis();
  digitalWrite(VALVE, HIGH);
  while(millis() - lastMillis <= duration * 100){
    delay(1000);
  }
  digitalWrite(VALVE, LOW);
  msgTx.seqEnd = true;
  sendCommand(panel, msgTx);
  msgTx.seqEnd = false;
}