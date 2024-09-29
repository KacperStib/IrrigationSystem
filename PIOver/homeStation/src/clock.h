#include <Arduino.h>
#include <Bonezegei_DS1307.h>
#include "CompileTime.h"  
#include "calibration.h"

Bonezegei_DS1307 rtc(0x68);
char buf[50];

void setRTC();
void printT();