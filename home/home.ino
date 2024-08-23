 #include <Bonezegei_DS1307.h>
#include <FS.h>
#include "Free_Fonts.h" 
#include <TFT_eSPI.h>              
#include <TFT_eWidget.h>  
#include "espnow_simplified.h"         

TFT_eSPI tft = TFT_eSPI();        
#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

ButtonWidget btnR = ButtonWidget(&tft);
ButtonWidget btnN = ButtonWidget(&tft);
Bonezegei_DS1307 rtc(0x68);

#define BUTTON_W 100
#define BUTTON_H 50

// Create an array of button instances to use in for() loops
// This is more useful where large numbers of buttons are employed
ButtonWidget* btn[] = {&btnR, &btnN};;
uint8_t buttonCount = sizeof(btn) / sizeof(btn[0]);
bool cmd = 0;

void btnR_pressAction(void)
{
  if (btnR.justPressed()) {
    btnR.drawSmoothButton(!btnR.getState(), 3, TFT_BLACK, btnR.getState() ? "OFF" : "ON");
    Serial.print("Button toggled: ");
    if (btnR.getState()){
      Serial.println("ON");
      cmd = 1;
    }
    else{
      cmd = 0;
      Serial.println("OFF");
    }
    btnR.setPressTime(millis());

    msgTTx.onOff = cmd;
    sendCommand(trawnik, msgTTx);
    tft.setCursor(0, 160, 2);
    tft.print("espnow: "); tft.print(cmd);
  }

  // if button pressed for more than 1 sec...
  if (millis() - btnR.getPressTime() >= 1000) {
    Serial.println("Stop pressing my buttton.......");
  }
  else Serial.println("Right button is being pressed");
}

void btnR_releaseAction(void)
{
  // Not action
}

void btnN_pressAction(void)
{
  if (btnN.justPressed()) {
    btnN.drawSmoothButton(!btnN.getState(), 3, TFT_BLACK, btnN.getState() ? "OFF" : "ON");
    Serial.print("Button toggled: ");
    if (btnN.getState()){
      Serial.println("ON");
    }
    else{
      Serial.println("OFF");
    }
    btnN.setPressTime(millis());
  }

  // if button pressed for more than 1 sec...
  if (millis() - btnN.getPressTime() >= 1000) {
    Serial.println("Stop pressing my buttton.......");
  }
  else Serial.println("Right button is being pressed");
}

void btnN_releaseAction(void)
{
  // Not action
}

void initButtons() {
  uint16_t x = (tft.width() - BUTTON_W) / 2;
  uint16_t y = tft.height() / 2 - BUTTON_H - 10;

  btnN.initButtonUL(x, y, BUTTON_W, BUTTON_H, TFT_WHITE, TFT_BLACK, TFT_GREEN, "OFF", 1);
  btnN.setPressAction(btnN_pressAction);
  //btnR.setReleaseAction(btnR_releaseAction);
  btnN.drawSmoothButton(false, 3, TFT_BLACK); // 3 is outline width, TFT_BLACK is the surrounding background colour for anti-aliasing

  y = tft.height() / 2 + 10;
  btnR.initButtonUL(x, y, BUTTON_W, BUTTON_H, TFT_WHITE, TFT_BLACK, TFT_GREEN, "OFF", 1);
  btnR.setPressAction(btnR_pressAction);
  //btnR.setReleaseAction(btnR_releaseAction);
  btnR.drawSmoothButton(false, 3, TFT_BLACK); // 3 is outline width, TFT_BLACK is the surrounding background colour for anti-aliasing
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
  char buf[50];
  
  sprintf(buf, "%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
  tft.print("Time: "); tft.print(buf);

  tft.setCursor(160, 0, 2);
  sprintf(buf, "%02d-%02d-%d", rtc.getMonth(), rtc.getDate(), rtc.getYear());
  tft.print("Date: "); tft.print(buf); 
  }
}

void checkMsgs(){
buf[50];

 if(newTRx){
  if(msgTRx.isRain){
   tft.setCursor(0, 50, 2);
   sprintf(buf, "Last Rain: %02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
   tft.print(buf);
  }

  if(msgTRx.seqEnd){
   tft.setCursor(160, 50, 2);
   sprintf(buf, "Last Grass Watering: %02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
   tft.print(buf);
  }
  
 newT = 0;

  if(newN){
    tft.setCursor(0, 400, 2);
    sprintf(buf, "Lux: %02f Temp: %02f", msgN.lux, msgN.tempOutside);
    tft.print(buf);
    newN = 0;
  }
}

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate();
  initButtons();

  rtc.begin();
  rtc.setFormat(12);        //Set 12 Hours Format
  rtc.setAMPM(1);           //Set AM or PM    0 = AM  1 =PM
  rtc.setTime("11:59:30");  //Set Time    Hour:Minute:Seconds
  rtc.setDate("1/27/24");

  espnow_init();
  addPeer(trawnik);
  addPeer(namiot);
}

void loop() {
  static uint32_t scanTime = millis();

  uint16_t t_x = 9999, t_y = 9999; // To store the touch coordinates

  printT();
  // Scan keys every 50ms at most
  if (millis() - scanTime >= 50) {
    // Pressed will be set true if there is a valid touch on the screen
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

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!LittleFS.begin()) {
    Serial.println("formatting file system");
    LittleFS.format();
    LittleFS.begin();
  }

  // check if calibration file exists and size is correct
  if (LittleFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      LittleFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = LittleFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = LittleFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}
