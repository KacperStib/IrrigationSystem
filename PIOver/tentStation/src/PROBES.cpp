#include "PROBES.h"

// measure voltage on probe and scale to [%]
// esp32 C3 analog read 0 - 4095 -> 0.0 V - 3.3 V
float measure(uint8_t PROBE){
  float meas = analogRead(PROBE) / 4095.0;
  float val = 100 - (meas * 100);
  return val;
}

// calculate average - not used
float calculateAverage(){
  // increment counter only if measurement > 0, if not no sensor is connected
  uint8_t ctr = 0;
  float avg = 0;

  float val1 = measure(PROBE1);
  if (val1 > 0)
    ctr++;
  float val2 = measure(PROBE2);
  if (val2 > 0)
    ctr++;
  float val3 = measure(PROBE3);
  if (val3 > 0)
    ctr++;

  if (ctr > 0)
    avg = (val1 + val2 + val3) / ctr;

  return avg;
}
