#include "calibration.h"

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

void btnR_pressAction(void)
{
  if (btnR.justPressed()) {
    btnR.drawSmoothButton(!btnR.getState(), 3, TFT_BLACK, btnR.getState() ? "OFF" : "ON");
    
    if (btnR.getState()){
      cmdT = 1;
    }
    else{
      cmdT = 0;
    }
    btnR.setPressTime(millis());

    msgTTx.onOff = cmdT;
    sendCommandT(trawnik, msgTTx);
    //tft.setCursor(0, 160, 2);
    //tft.print("espnow: "); tft.print(cmdT);
  }
}

void btnR_releaseAction(void)
{
  // Not action
}

void btnN_pressAction(void)
{
  if (btnN.justPressed()) {
    btnN.drawSmoothButton(!btnN.getState(), 3, TFT_BLACK, btnN.getState() ? "OFF" : "ON");
    
    if (btnN.getState()){
      cmdN = 1;
    }
    else{
      cmdN = 0;
    }
    btnN.setPressTime(millis());

    msgNTx.onOff = cmdN;
    sendCommandN(namiot, msgNTx);
    //tft.setCursor(0, 160, 2);
    //tft.print("espnow2: "); tft.print(cmdN);
  }
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