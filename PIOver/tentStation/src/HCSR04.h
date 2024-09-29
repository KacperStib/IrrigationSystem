#include <Arduino.h>
#include "I2C.h"

#define TRIG 5
#define ECHO 6

void HCSR04init();
uint8_t distance();
