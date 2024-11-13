#include "errorHandler.h"

uint8_t err = 0;

// sprawdz stan bledow, jesli wystapil ustaw odpowiedni BIT, jesli zniknal - wyczysc BIT
void errorChecker(){
    if (msgNRx.waterLvl < 20){
        bitSet(err, LOW_WATER_LVL);
    }
    else {
        bitClear(err, LOW_WATER_LVL);
    }

    if (msgNRx.probe1 < 50 || msgNRx.probe2 < 50 || msgNRx.probe3 < 50){
        bitSet(err, LOW_SOIL_MOIS);
    }
    else {
        bitClear(err, LOW_SOIL_MOIS);
    }

    if (msgNRx.tempInside > 50){
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