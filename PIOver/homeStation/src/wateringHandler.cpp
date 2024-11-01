#include "wateringHandler.h"
#include "clock.h"

bool autoTent = false;
bool autoGarden = false;

uint32_t millisTent = 0;
uint32_t millisGarden = 0;

void wateringHandler(){
    if (autoTent){
        if (rtc.getHour() == 8 || rtc.getHour() == 20 || msgNRx.probe1 < 50 || msgNRx.probe2 < 50 || msgNRx.probe3 < 50){
            msgNTx.autom = true;
            sendCommandN(namiot, msgNTx);
            msgNTx.autom = false;
        }
    }

    if (autoGarden){
        if (rtc.getHour() == 8 || rtc.getHour() == 20){
            msgTTx.onOff = true;
            sendCommandT(trawnik, msgTTx);
        }
    }
}