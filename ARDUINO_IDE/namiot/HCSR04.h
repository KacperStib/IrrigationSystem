#define TRIG 5
#define ECHO 6
//in centimeters
uint8_t tankHeight = 100;

void HCSR04init(){
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

uint8_t distance(){

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
 
  digitalWrite(TRIG, LOW);
  int Distance = pulseIn(ECHO, HIGH) / 58;

  return (uint8_t)Distance;
}

uint8_t waterPercentage(){
  float percent = (float) (100.0 - (float)distance() / tankHeight * 100.0);
  return (uint8_t)percent;
}
