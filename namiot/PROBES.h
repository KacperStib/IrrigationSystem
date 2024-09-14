#define PROBE1 2
#define PROBE2 1
#define PROBE3 0

float measurment(uint8_t PROBE){
  float meas = analogRead(PROBE);
  float val = 100 - (meas * 100 / 3.3);
  return val;
}

float calculateAverage(){
  float val1 = measruement(PROBE1);
  float val2 = measruement(PROBE2);
  float val3 = measruement(PROBE3);

  float avg = (val1 + val2 + val3) / 3.0;

  return avg;
}
