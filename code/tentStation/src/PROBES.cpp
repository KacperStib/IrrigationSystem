#include "PROBES.h"

// pomiar ADC na pinach esp32 oraz ich zamiana na %
// esp32 C3 analog read 0 - 4095 -> 0.0 V - 3.3 V
float measure(uint8_t PROBE){
  float meas = analogRead(PROBE) / 4095.0;
  float val = 100 - (meas * 100);
  return val;
}

// obliczanie sredniej
float calculateAverage(){
  // licznik inkrementowany tylko gdy pomiar > 0 , jesli == 0 to znaczy ze czujnik nie jest podlaczony lub wystapila awaria
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
