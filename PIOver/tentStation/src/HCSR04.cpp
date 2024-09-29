#include "HCSR04.h"

void HCSR04init(){
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

uint8_t distance(){

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(TRIG, LOW);
  float EchoTime = pulseIn(ECHO, HIGH);
  float Distance = EchoTime / 58;

  return (uint8_t)Distance;
}
