#include "clock.h"

Bonezegei_DS1307 rtc(0x68);
char buf[50];

void setRTC(){
  using namespace CompileTime;
  
  rtc.begin();
  rtc.setFormat(24);        //Set 12 Hours Format
  //rtc.setAMPM(1);           //Set AM or PM    0 = AM  1 =PM
  sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
  rtc.setTime(buf);  //Set Time    Hour:Minute:Seconds
  sprintf(buf, "%02d/%02d/%d", month, day, year);
  rtc.setDate(buf);
}

void printT(){
  static uint32_t printTime = millis();
  if ((millis() - printTime) >= 1000) {
    printTime = millis();
    if (rtc.getTime()) {
      Serial.printf("Time %02d:%02d:%02d ", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
      if (rtc.getFormat() == 12) {  // returns 12 or 24 hour format
        if (rtc.getAMPM()) {  //return 0 = AM  1 = PM
          Serial.print("PM  ");
        } else {
          Serial.print("AM  ");
        }
      }
    }
    Serial.printf("Date %02d-%02d-%d \n", rtc.getMonth(), rtc.getDate(), rtc.getYear());

  tft.setCursor(0, 0, 2);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  
  sprintf(buf, "%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
  tft.print("Time: "); tft.print(buf);

  tft.setCursor(160, 0, 2);
  sprintf(buf, "%02d-%02d-%d", rtc.getMonth(), rtc.getDate(), rtc.getYear());
  tft.print("Date: "); tft.print(buf); 
  }
}