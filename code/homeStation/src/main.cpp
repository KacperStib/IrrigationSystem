#include "espnow_simplified.h"       
#include "calibration.h"
#include "clock.h"
#include "wateringHandler.h"
#include "errorHandler.h"
#include "EEPROM_24c32.h"

char pc = '%';

// deklaracja funkcji
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

  // inicjalizacja wyswietlacza
  init_tft();
  init_lvgl();

  // inicjalizacja zegara RTC
  setRTC();

  // inicjalizacja ESP_NOW oraz dodanie polaczen
  espnow_init();
  addPeer(trawnik);
  addPeer(namiot);

  // srpawdz czas - 10 S
  xTaskCreate(checkTimeTask, "CheckTimeTask", 2048, NULL, 1, NULL);

  // sprawdz wiadomosci - 10 S
  xTaskCreate(checkMsgsTask, "CheckMsgsTask", 4096, NULL, 2, NULL);

  // odswiez wyswietlacz i sprawdz dane o nacisku - 20 MS
  xTaskCreate(lvglAndCmdsTask, "lvglAndCmdsTask", 4096, NULL, 3, NULL);

  // obsluga trybu automatycznego - 1 M
  xTaskCreate(automationTask, "automationTask", 2048, NULL, 4, NULL);

  // obsluga errorow - 10 S
  xTaskCreate(errorHandlerTask, "errorHandlerTask", 2048, NULL, 5, NULL);
  
  // odczytaj z eeprom ostatnie czasy zdarzen
  // i2cFlag = true;
  // eepromRead(TENT_MONTH_REG, &lastTentWatering[0]);
  // eepromRead(TENT_DAY_REG, &lastTentWatering[1]);
  // eepromRead(TENT_HOUR_REG, &lastTentWatering[2]);
  // eepromRead(TENT_MINUTE_REG, &lastTentWatering[3]);

  // eepromRead(GARDEN_MONTH_REG, &lastGardenWatering[0]);
  // eepromRead(GARDEN_DAY_REG, &lastGardenWatering[1]);
  // eepromRead(GARDEN_HOUR_REG, &lastGardenWatering[2]);
  // eepromRead(GARDEN_MINUTE_REG, &lastGardenWatering[3]);

  // eepromRead(RAIN_MONTH_REG, &lastRain[0]);
  // eepromRead(RAIN_DAY_REG, &lastRain[1]);
  // eepromRead(RAIN_HOUR_REG, &lastRain[2]);
  // eepromRead(RAIN_MINUTE_REG, &lastRain[3]);
  // i2cFlag = false;
  
  // ustaw czasy zdarzen na wyswietlaczu
  sprintf(buf, "%02d:%02d", lastTentWatering[2], lastTentWatering[3]);
  lv_label_set_text(ui_LastWateringT, buf);

  sprintf(buf, "%02d:%02d", lastGardenWatering[2], lastGardenWatering[3]);
  lv_label_set_text(ui_LastWateringG, buf);

  sprintf(buf, "%02d:%02d", lastRain[2], lastRain[3]);
  lv_label_set_text(ui_LastRain, buf);
}

void loop() {
}

void checkMsgs(){
 if(newT){
  /* TRAWNIK */
  // deszcz
  if(isRain){
    // przechowuj informacje o ostatnim deszczu
    lastRain[0] = rtc.getMonth();
    lastRain[1] = rtc.getDate();
    lastRain[2] = rtc.getHour();
    lastRain[3] = rtc.getMinute();
    // zapisz do eeprom
    i2cFlag = true;
    eepromWrite(RAIN_MONTH_REG, lastRain[0]);
    delay(10);
    eepromWrite(RAIN_DAY_REG, lastRain[1]);
    delay(10);
    eepromWrite(RAIN_HOUR_REG, lastRain[2]);
    delay(10);
    eepromWrite(RAIN_MINUTE_REG, lastRain[3]);
    delay(10);
    i2cFlag = false;
    // wypisz informacje na panelu
    sprintf(buf, "%02d:%02d", lastRain[2], lastRain[3]);
    lv_label_set_text(ui_LastRain, buf);
    isRain = false;
  }
  // nawdanianie
  if(seqEndT){
    // przechowuj informacje o ostatnim nawadnianiu
    lastGardenWatering[0] = rtc.getMonth();
    lastGardenWatering[1] = rtc.getDate();
    lastGardenWatering[2] = rtc.getHour();
    lastGardenWatering[3] = rtc.getMinute();
    // zapisz do eeprom
    i2cFlag = true;
    eepromWrite(GARDEN_MONTH_REG, lastGardenWatering[0]);
    delay(10);
    eepromWrite(GARDEN_DAY_REG, lastGardenWatering[1]);
    delay(10);
    eepromWrite(GARDEN_HOUR_REG, lastGardenWatering[2]);
    delay(10);
    eepromWrite(GARDEN_MINUTE_REG, lastGardenWatering[3]);
    delay(10);
    i2cFlag = false;
    // wypisz informacje na panelu
    sprintf(buf, "%02d:%02d", lastGardenWatering[2], lastGardenWatering[3]);
    lv_label_set_text(ui_LastWateringG, buf);
    // ustaw flagi trybu automatycznego
    isWateringGarden = false;
    seqEndT = false;
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
    sprintf(buf, "%.2f lx", msgNRx.lux);
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
    if(seqEndN){
      // przechowuj informacje o ostatnim nawadnianiu
      lastTentWatering[0] = rtc.getMonth();
      lastTentWatering[1] = rtc.getDate();
      lastTentWatering[2] = rtc.getHour();
      lastTentWatering[3] = rtc.getMinute();
      // zapisz do eeprom
      i2cFlag = true;
      eepromWrite(TENT_MONTH_REG, lastTentWatering[0]);
      delay(10);
      eepromWrite(TENT_DAY_REG, lastTentWatering[1]);
      delay(10);
      eepromWrite(TENT_HOUR_REG, lastTentWatering[2]);
      delay(10);
      eepromWrite(TENT_MINUTE_REG, lastTentWatering[3]);
      delay(10);
      i2cFlag = false;
      // wypisz informacje na panelu
      sprintf(buf, "%02d:%02d", lastTentWatering[2], lastTentWatering[3]);
      lv_label_set_text(ui_LastWateringT, buf);
      // ustaw flagi trybu automatycznego
      isWateringTent = false;
      seqEndN = false;
    }
    errorChecker();
    /* NAMIOT */
    newN = 0;
  }
}