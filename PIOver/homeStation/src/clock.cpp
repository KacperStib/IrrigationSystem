#include "clock.h"

Bonezegei_DS1307 rtc(0x68);
char buf[50];
uint8_t lastMin = 0;

// try to run clock on registers instead of libaray
/*
void begin(){
  I2Cinit();
  I2CwriteREG(DS1307_ADRESS, DS1307_EN_REG);
}

void setFormat(uint8_t format, uint8_t AMPM){
  I2CwriteVAL(DS1307_ADRESS, DS1307_SET_REG, format);
}
*/

// set RTC based on CompileTime if RTC has to be adjust
void setRTC(){
  using namespace CompileTime;
  
  // start RTC
  rtc.begin();
  rtc.setFormat(24);        //Set 12 Hours Format

  // set RTC
  //rtc.setAMPM(1);           //Set AM or PM    0 = AM  1 =PM
  //sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
  //rtc.setTime(buf);  //Set Time    Hour:Minute:Seconds
  //sprintf(buf, "%02d/%02d/%d", month, day, year);
  //rtc.setDate(buf);
}

// print time in serialport and on screen
void printTime(){
  if (rtc.getTime()) {
    // debug
    // Serial.printf("Time %02d:%02d:%02d ", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
    // Serial.printf("Date %02d-%02d-%d \n", rtc.getMonth(), rtc.getDay(), (uint16_t) rtc.getYear() + 2000);
    
    // display date and time on screen
    if (rtc.getMinute() != lastMin){
      sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
      lv_label_set_text(ui_Time, buf);

      sprintf(buf, "%02d . %02d . %d", rtc.getDate(), rtc.getMonth(), (uint16_t) rtc.getYear() + 1920);
      lv_label_set_text(ui_Date, buf);
    }
  }
}