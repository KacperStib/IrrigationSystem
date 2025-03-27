#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "espnow_simplified.h"
#include "clock.h"

extern bool cmdT;
extern bool cmdN;
extern bool autoTent;
extern bool autoGarden;
extern bool isWateringTent;
extern bool isWateringGarden;

// [0] - miesiac   [1] - dzien     [2] - godzina      [3] - minuta
extern uint8_t lastTentWatering[4];
extern uint8_t lastGardenWatering[4];
extern uint8_t lastRain[4];

void checkCmds();
void autoCmdsSender();