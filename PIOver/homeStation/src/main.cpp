#include "espnow_simplified.h"       
#include "calibration.h"
#include "clock.h"
#include "wateringHandler.h"
#include "errorHandler.h"

char pc = '%';

void checkMsgs();

// freeRTOS tasks
void checkTimeTask(void *pvParameters){
  for(;;){
    printTime();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void checkMsgsTask(void *pvParameters){
  for(;;){
    checkMsgs();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void lvglAndCmdsTask(void *pvParameters){
  for(;;){
    checkCmds();
    lv_timer_handler();
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
  
}

void automationTask(void *pvParameters){
  for(;;){
    autoCmdsSender();
    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
}

void errorHandlerTask(void *pvParameters){
  for(;;){
    errorHandler();
    // delays included in errorHandler()
  }
}

void setup() {
  CompileTime::setCompileTime(6);
  Serial.begin(115200);

  init_tft();
  init_lvgl();

  setRTC();

  // initialize esp now and add peers
  espnow_init();
  addPeer(trawnik);
  addPeer(namiot);

  // refresh time - 10 S
  xTaskCreate(checkTimeTask, "CheckTimeTask", 2048, NULL, 1, NULL);

  // check msgs - 10 S
  xTaskCreate(checkMsgsTask, "CheckMsgsTask", 4096, NULL, 2, NULL);

  // check lvgl and gui commands - 20 MS
  xTaskCreate(lvglAndCmdsTask, "lvglAndCmdsTask", 4096, NULL, 3, NULL);

  // send automatic cmds - 1 M
  xTaskCreate(automationTask, "automationTask", 2048, NULL, 4, NULL);

  // error handler - 10 S
  xTaskCreate(errorHandlerTask, "errorHandlerTask", 2048, NULL, 5, NULL);
}

void loop() {
}

void checkMsgs(){
 if(newT){
  /* TRAWNIK */
  // rain info
  if(msgTRx.isRain){
    sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
    lv_label_set_text(ui_LastRain, buf);
    lastRain[0] = rtc.getDay();
    lastRain[1] = rtc.getHour();
  }
  // watering info
  if(msgTRx.seqEnd){
    sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
    lv_label_set_text(ui_LastWateringG, buf);
    lastGardenWatering[0] = rtc.getDay();
    lastGardenWatering[1] = rtc.getHour();
    sendGarden = false;
    isWateringGarden = false;
  }
  /* TRAWNIK */
  newT = 0;
 }
 
  if(newN){
    /* PANEL GLOWNY */
    // temperatura zewn
    sprintf(buf, "%.2f °C", msgNRx.tempOutside);
    lv_label_set_text(ui_TempOut, buf);
    // wilgotnosc zewn
    sprintf(buf, "%.2f %c", msgNRx.rhOutside, pc);
    lv_label_set_text(ui_RHOut, buf);
    // natezenie swiatla
    sprintf(buf, "%.2f Lux", msgNRx.lux);
    lv_label_set_text(ui_Lux, buf);
    // cisnienie
    sprintf(buf, "%d hPa", msgNRx.preasure);
    lv_label_set_text(ui_Preasure, buf);
    /* PANEL GLOWNY */

    /* NAMIOT */
    // temperatura wenw
    sprintf(buf, "%.2f °C", msgNRx.tempInside);
    lv_label_set_text(ui_TempIn, buf);
    // wilgotnosc wewn
    sprintf(buf, "%.2f %c", msgNRx.rhInside, pc);
    lv_label_set_text(ui_RHIn, buf);
    // poziom wody
    sprintf(buf, "%d %c", msgNRx.waterLvl, pc);
    lv_label_set_text(ui_WaterLvl, buf);
    lv_bar_set_value(ui_WaterLvlBar, msgNRx.waterLvl, LV_ANIM_OFF); // bar
    // wilgotnosc gleby
    sprintf(buf, " %d %c", msgNRx.probesAvg, pc);
    lv_label_set_text(ui_SoilMois, buf);
    lv_bar_set_value(ui_SoilMoisBar, msgNRx.probesAvg, LV_ANIM_OFF); // bar
    // ostatnie podlewanie
    if(msgNRx.seqEnd){
      sprintf(buf, "%02d:%02d", rtc.getHour(), rtc.getMinute());
      lv_label_set_text(ui_LastWateringT, buf);
      lastTentWatering[0] = rtc.getDay();
      lastTentWatering[1] = rtc.getHour();
      sendTent = false;
      isWateringTent = false;
    }
    errorChecker();
    /* NAMIOT */
    newN = 0;
  }
}