#include <Arduino.h>

#define TRIG 5
#define ECHO 6

extern uint8_t tankHeight;

void HCSR04init();
uint8_t distance();
uint8_t waterPercentage();