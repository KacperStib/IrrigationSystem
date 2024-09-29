#include "PROBES.h"

float measurement(uint8_t PROBE){
  float meas = analogRead(PROBE);
  float val = 100 - (meas * 100 / 3.3);
  return val;
}

float calculateAverage(){
  float val1 = measurement(PROBE1);
  float val2 = measurement(PROBE2);
  float val3 = measurement(PROBE3);

  float avg = (val1 + val2 + val3) / 3.0;

  return avg;
}
