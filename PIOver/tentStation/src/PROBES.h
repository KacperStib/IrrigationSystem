#include <Arduino.h>
#include "I2C.h"

#define PROBE1 2
#define PROBE2 1
#define PROBE3 0

float measurment(uint8_t PROBE);
float calculateAverage();