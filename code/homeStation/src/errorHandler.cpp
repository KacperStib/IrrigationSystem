#include "errorHandler.h"

uint8_t err = 0;

// sprawdz stan bledow, jesli wystapil ustaw odpowiedni BIT, jesli zniknal - wyczysc BIT
void errorChecker(){
    if (msgNRx.waterLvl < WATER_LVL_MIN){
        bitSet(err, LOW_WATER_LVL);
    }
    else {
        bitClear(err, LOW_WATER_LVL);
    }

    if (msgNRx.probe1 < SOIL_MOIS_MIN || msgNRx.probe2 < SOIL_MOIS_MIN || msgNRx.probe3 < SOIL_MOIS_MIN){
        bitSet(err, LOW_SOIL_MOIS);
    }
    else {
        bitClear(err, LOW_SOIL_MOIS);
    }

    if (msgNRx.tempInside > TEMP_MAX){
        bitSet(err, HIGH_TEMP);
    }
    else {
        bitClear(err, HIGH_TEMP);
    }
}

// wyswietlanie errorow na ekranie
void errorHandler(){
    if (bitRead(err, LOW_WATER_LVL)){
        lv_label_set_text(ui_Error, "Niski poziom wody w zbiorniku !");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    if (bitRead(err, LOW_SOIL_MOIS)){
        lv_label_set_text(ui_Error, "Niski poziom wilgotnosci gleby !");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    if (bitRead(err, HIGH_TEMP)){
        lv_label_set_text(ui_Error, "Wysoka temperatura w namiocie !");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    if (err == 0)
      vTaskDelay(10000 / portTICK_PERIOD_MS);
}