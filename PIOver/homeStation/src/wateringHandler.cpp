#include "wateringHandler.h"

bool cmdN = false;
bool cmdT = false;
bool autoTent = false;
bool autoGarden = false;
bool sendTent = false;
bool sendGarden = false;
bool isWateringTent = false;
bool isWateringGarden = false;

// store last watering and rain days[0] + hours[1]
uint8_t lastTentWatering[2] = {0, 0};
uint8_t lastGardenWatering[2] = {0, 0};
uint8_t lastRain[2] = {0, 0};

// check command from GUI
void checkCmds()
{   
    // simple ON / OFF
    switch(cmdToFunc){
      case TENT_WATER_CMD:
        cmdN = !cmdN;
        msgNTx.onOff = cmdN;
        sendCommandN(namiot, msgNTx);
        cmdToFunc = 0;
        break;
      
      // if auto - handled by autoCmdsSender(), else turn off auto
      case TENT_AUT_CMD:
        autoTent = !autoTent;
        if (!autoTent){
            msgNTx.autom = autoTent;
            msgNTx.duration = tentMinutes;
            sendCommandN(namiot, msgNTx);
        }
        cmdToFunc = 0;
        break;

      // simple ON / OFF
      case GARDEN_WATER_CMD:
        cmdT = !cmdT;
        msgTTx.onOff = cmdT;
        msgTTx.section = section;
        sendCommandT(trawnik, msgTTx);
        cmdToFunc = 0;
        break;

       // if auto - handled by autoCmdsSender(), else turn off auto
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

// handle automatic watering
void autoCmdsSender(){
    // tent automation
    if (autoTent && !isWateringTent){
        // send only if 1. HOUR OK  OR 2. SOIL MOISTURE IS LOW
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

    // garden automation
    if (autoGarden && isWateringGarden){
        // send only if 1. HOUR OK AND 2. NO RAIN IN LAST X HOURS
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