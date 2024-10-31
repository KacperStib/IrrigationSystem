#include "espnow_simplified.h"       
#include "calibration.h"
#include "clock.h"

void checkMsgs();
void checkCmds();

void setup() {
  CompileTime::setCompileTime(6);
  Serial.begin(115200);

  // initialize TFT screen
  tft.begin();
  tft.setRotation(3);
  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  tft.setTouch( calData );
  init_lvgl();

  setRTC();

  // initialize esp now and add peers
  espnow_init();
  addPeer(trawnik);
  addPeer(namiot);
}

int cnt = 0;
int pres = 50;

void loop() {

  static uint32_t scanTime = millis();

  printT();
  checkMsgs();
  checkCmds();
  //test
  cnt++;
  if(cnt==100){
    sprintf(buf, "%d", pres);
    lv_label_set_text(ui_Preasure, buf);
    pres++; cnt = 0;
  }
  // end test

  lv_timer_handler(); /* let the GUI do its work */
  delay( 20 );
}


void checkMsgs(){
 if(newT){
  /* TRAWNIK */
  if(msgTRx.isRain){
   sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
   lv_label_set_text(ui_LastRain, buf);
  }

  if(msgTRx.seqEnd){
   sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
   lv_label_set_text(ui_LastWateringG, buf);
  }
  /* TRAWNIK */
  newT = 0;
 }
 
  if(newN){
    /* PANEL GLOWNY */
    // temperatura zewn
    sprintf(buf, "%.2f", msgNRx.tempOutside);
    lv_label_set_text(ui_TempOut, buf);
    // wilgotnosc zewn
    sprintf(buf, "%.2f", msgNRx.rhOutside);
    lv_label_set_text(ui_RHOut, buf);
    // natezenie swiatla
    sprintf(buf, "%.2f", msgNRx.lux);
    lv_label_set_text(ui_Lux, buf);
    /* PANEL GLOWNY */

    /* NAMIOT */
    // temperatura wenw
    sprintf(buf, "%.2f", msgNRx.tempInside);
    lv_label_set_text(ui_TempIn, buf);
    // wilgotnosc wewn
    sprintf(buf, "%.2f", msgNRx.rhInside);
    lv_label_set_text(ui_RHIn, buf);
    // poziom wody
    sprintf(buf, "%d", msgNRx.waterLvl);
    lv_label_set_text(ui_WaterLvl, buf);
    lv_bar_set_value(ui_WaterLvlBar, msgNRx.waterLvl, LV_ANIM_OFF); // bar
    // wilgotnosc gleby
    sprintf(buf, " %d", msgNRx.probe2);
    lv_label_set_text(ui_SoilMois, buf);
    lv_bar_set_value(ui_SoilMoisBar, msgNRx.probe2, LV_ANIM_OFF); // bar
    // ostatnie podlewanie
    if(msgNRx.seqEnd){
      sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
      lv_label_set_text(ui_LastWateringT, buf);
    }
    /* NAMIOT */
    newN = 0;
  }
}


void checkCmds()
{
    switch(cmdToFunc){
      case TENT_WATER_CMD:
        cmdN = !cmdN;
        msgNTx.onOff = cmdN;
        sendCommandN(namiot, msgNTx);
        cmdToFunc = 0;
        break;

      case GARDEN_WATER_CMD:
        cmdT = !cmdT;
        msgTTx.onOff = cmdT;
        sendCommandT(trawnik, msgTTx);
        cmdToFunc = 0;
        break;

      default:
        break;
    }
}
