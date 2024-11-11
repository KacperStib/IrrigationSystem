#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "espnow_simplified.h"
#include "clock.h"

extern bool cmdT;
extern bool cmdN;
extern bool autoTent;
extern bool autoGarden;
extern bool sendTent;
extern bool sendGarden;
extern bool isWateringTent;
extern bool isWateringGarden;

// [0] - day   [1] - hour
extern uint8_t lastTentWatering[2];
extern uint8_t lastGardenWatering[2];
extern uint8_t lastRain[2];

void checkCmds();
void autoCmdsSender();