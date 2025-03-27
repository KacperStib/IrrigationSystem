#include "HCSR04.h"

// dostosowac wysokosc zbiornika
uint8_t tankHeight = 100;

// set IOs
void HCSR04init(){
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

// odczyt odleglosci - standardowa procedura HCSR04
uint8_t distance(){

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(TRIG, LOW);
  int Distance = pulseIn(ECHO, HIGH) / 58;

  return (uint8_t)Distance;
}

// obliczanie wysokosci poziomu wody w [%] na podstawie wysokosci zbiornika
uint8_t waterPercentage(){
  float percent = (float) (100.0 - (float)distance() / tankHeight * 100.0);
  return (uint8_t)percent;
}
