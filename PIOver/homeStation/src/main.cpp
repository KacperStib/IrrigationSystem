#include "espnow_simplified.h"       
#include "calibration.h"
#include "clock.h"

uint8_t pageSelector = 0;

void checkMsgs();

void setup() {
  CompileTime::setCompileTime(6);
  Serial.begin(115200);

  // initialize TFT screen
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  touch_calibrate();
  initButtons();

  setRTC();

  // initialize esp now and add peers
  espnow_init();
  addPeer(trawnik);
  addPeer(namiot);
}

void loop() {
  // adjust scan time on touch
  static uint32_t scanTime = millis();

  uint16_t t_x = 9999, t_y = 9999; // To store the touch coordinates

  printT();
  checkMsgs();

  // Scan keys every 50ms at most
  if (millis() - scanTime >= 50) {
    bool pressed = tft.getTouch(&t_x, &t_y);
    scanTime = millis();
    
    for (uint8_t b = 0; b < buttonCount; b++) {
      if (pressed) {
        if (btn[b]->contains(t_x, t_y)) {
          btn[b]->press(true);
          btn[b]->pressAction();
        }
      }
      else {
        btn[b]->press(false);
        btn[b]->releaseAction();
      }
    }
  }
}

// check if there are new msgs and display them
void checkMsgs(){

 if(newT){
  if(msgTRx.isRain){
   tft.setCursor(0, 60, 2);
   sprintf(buf, "Last Rain: %02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
   tft.print(buf);
  }

  if(msgTRx.seqEnd){
   tft.setCursor(0, 80, 2);
   sprintf(buf, "Last Grass Watering: %02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
   tft.print(buf);
  }

  newT = 0;
 }
 
  if(newN){

    if(msgNRx.seqEnd){
      tft.setCursor(0, 320, 2);
      sprintf(buf, "Last Crops Watering: %02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
      tft.print(buf);
    }

    tft.setCursor(0, 340, 2);
    sprintf(buf, "Lux: %02f", msgNRx.lux);
    tft.print(buf);

    tft.setCursor(0, 360, 2);
    sprintf(buf, "Inside:   Temp: %02f RH: %02f", msgNRx.tempOutside, msgNRx.rhOutside);
    tft.print(buf);

    tft.setCursor(0, 380, 2);
    sprintf(buf, "Outside:   Temp: %02f RH: %02f", msgNRx.tempInside, msgNRx.rhInside);
    tft.print(buf);
    
    tft.setCursor(0, 400, 2);
    sprintf(buf, "PROBES: 1: %d, 2: %d, 3: %d", msgNRx.probe1, msgNRx.probe2, msgNRx.probe3);
    tft.print(buf);

    tft.setCursor(0, 420, 2);
    sprintf(buf, "Water level: %d %", msgNRx.waterLvl);
    tft.print(buf);
   
    newN = 0;
  }
}