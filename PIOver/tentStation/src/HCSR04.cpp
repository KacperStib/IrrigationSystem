#include "HCSR04.h"

// adjust tank height
uint8_t tankHeight = 100;

// set IOs
void HCSR04init(){
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

// read distance - standard HC-SR04 procedure
uint8_t distance(){

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(TRIG, LOW);
  int Distance = pulseIn(ECHO, HIGH) / 58;

  return (uint8_t)Distance;
}

// calculate water height (in %) based on declared tank height
uint8_t waterPercentage(){
  float percent = (float) (100.0 - (float)distance() / tankHeight * 100.0);
  return (uint8_t)percent;
}
