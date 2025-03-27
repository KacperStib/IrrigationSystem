#include <Arduino.h>
#include "espnow_simplified.h"
#include "ui.h"

#define LOW_WATER_LVL 0
#define LOW_SOIL_MOIS 1
#define HIGH_TEMP 2

#define WATER_LVL_MIN 20
#define SOIL_MOIS_MIN 50
#define TEMP_MAX 40

extern uint8_t err;

void errorChecker();
void errorHandler();