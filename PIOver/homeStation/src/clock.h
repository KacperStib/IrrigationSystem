#include <Arduino.h>
#include <Bonezegei_DS1307.h>
#include "CompileTime.h"  
#include "calibration.h"

extern Bonezegei_DS1307 rtc;
extern char buf[50];

void setRTC();
void printT();