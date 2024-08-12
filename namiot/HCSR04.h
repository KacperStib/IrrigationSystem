#define TRIG
#define ECHO

void HCSR04init{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

uint8_t distance(){

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(Trig, LOW);
  float EchoTime = pulseIn(Echo, HIGH);
  float Distance = EchoTime / 58;

  return distance;
}
