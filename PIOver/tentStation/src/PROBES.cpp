#include "PROBES.h"

// measure voltage on probe and scale to [%]
// esp32 C3 analog read 0 - 4095 -> 0.0 V - 3.3 V
float measurement(uint8_t PROBE){
  float meas = analogRead(PROBE) / 4095.0;
  float val = 100 - (meas * 100);
  return val;
}

// calculate average - not used
float calculateAverage(){
  float val1 = measurement(PROBE1);
  float val2 = measurement(PROBE2);
  float val3 = measurement(PROBE3);

  float avg = (val1 + val2 + val3) / 3.0;

  return avg;
}
