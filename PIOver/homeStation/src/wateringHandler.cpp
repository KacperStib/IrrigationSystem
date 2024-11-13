#include "wateringHandler.h"

bool cmdN = false;
bool cmdT = false;
bool autoTent = false;
bool autoGarden = false;
bool sendTent = false;
bool sendGarden = false;
bool isWateringTent = false;
bool isWateringGarden = false;

// informacje o ostanich zdarzeniach [0] - dzien, [1] - godzina
uint8_t lastTentWatering[2] = {0, 0};
uint8_t lastGardenWatering[2] = {0, 0};
uint8_t lastRain[2] = {0, 0};

// sprawdz komendy wybrane przez uzytkowanika
void checkCmds()
{   
    // ON / OFF
    switch(cmdToFunc){
      case TENT_WATER_CMD:
        cmdN = !cmdN;
        msgNTx.onOff = cmdN;
        sendCommandN(namiot, msgNTx);
        cmdToFunc = 0;
        break;
      
      // obsluga trybu automatycznego przez autoCmdsSender() lub wylaczenie ponizej
      case TENT_AUT_CMD:
        autoTent = !autoTent;
        if (!autoTent){
            msgNTx.autom = autoTent;
            msgNTx.duration = tentMinutes;
            sendCommandN(namiot, msgNTx);
        }
        cmdToFunc = 0;
        break;

      // ON / OFF
      case GARDEN_WATER_CMD:
        cmdT = !cmdT;
        msgTTx.onOff = cmdT;
        msgTTx.section = section;
        sendCommandT(trawnik, msgTTx);
        cmdToFunc = 0;
        break;

       // obsluga trybu automatycznego przez autoCmdsSender() lub wylaczenie ponizej
      case GARDEN_AUT_CMD:
        autoGarden = !autoGarden;
        if (!autoGarden){
            msgTTx.autom = autoGarden;
            msgTTx.duration = gardenMinutes;
            sendCommandT(trawnik, msgTTx);
        }
        cmdToFunc = 0;
        break;

      default:
        break;
    }
}

// oblsuga trybu automatycznego
void autoCmdsSender(){
    // automatyzacja namiotu
    if (autoTent && !isWateringTent){
        // send only if 1. HOUR OK  OR 2. SOIL MOISTURE IS LOW
        // wyslij jesli 1. godzina podlewania LUB 2. niski poziom wilgotnosci gleby
        if (((rtc.getHour() == 8 || rtc.getHour() == 20) && (lastTentWatering[1] != rtc.getHour() || (lastTentWatering[0] != rtc.getDay() && lastTentWatering[1] == rtc.getHour()))) 
            /*|| msgNRx.probe1 < 50 || msgNRx.probe2 < 50 || msgNRx.probe3 < 50*/){
            sendTent = true;
        }
        if(sendTent){
            msgNTx.autom = autoTent;
            msgNTx.duration = tentMinutes;
            sendCommandN(namiot, msgNTx);
            sendTent = false;
            isWateringTent = true;
        }
    } 

    // automatyzacja ogrodu
    if (autoGarden && isWateringGarden){
        // wyslij jesli 1. godzina podlewania ORAZ 2. nie bylo deszczu
        if (((rtc.getHour() == 8 || rtc.getHour() == 20) && (lastGardenWatering[1] != rtc.getHour() || (lastGardenWatering[0] != rtc.getDay() && lastGardenWatering[1] == rtc.getHour())))){
            sendGarden = true;
        }
        if(sendTent){
            msgTTx.autom = autoGarden;
            msgTTx.duration = gardenMinutes;
            sendCommandT(trawnik, msgTTx);
            sendGarden = false;
        }
    } 
}