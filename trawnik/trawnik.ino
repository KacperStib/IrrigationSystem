uint32_t lastMillis;
uint32_t lastRain;

bool isRain = 0;
bool wateringCmd = 0;

void IRAM_ATTR rain(){
  isRain = 1;
}

void setup() {

}

void loop() {

  if(isRain){
    //espnow send timestamp;
    lastRain = millis();
    isRain = 0;
  }

  if(wateringCmd && millis() - lastRain() >= RAIN_DELAY * 1000 * 60){
    wateringSequence();
  }
  
}

void openValve(uint8_t VALVE){
  lastMillis = millis();
  digitalWrite(VALVE, HIGH);
  while(millis() - lastMillis <= WATERING_TIME * 1000 * 60){
    delay(5000)
  }
}

void wateringSequence(){
  openValve(VALVE1);
  openValve(VALVE2);
  openValve(VALVE3);
  openValve(VALVE4);
}
