#include <Arduino.h>
#include "espnow_simplified.h"
#include "ui.h"

#define LOW_WATER_LVL 0
#define LOW_SOIL_MOIS 1
#define HIGH_TEMP 2

extern uint8_t err;

void errorChecker();
void errorHandler();