#include <Arduino.h>
#include <FS.h>
#include <TFT_eSPI.h>
#include <TFT_eWidget.h> 

#include "espnow_simplified.h"

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false
#define BUTTON_W 100
#define BUTTON_H 50

extern TFT_eSPI tft;        

extern ButtonWidget btnR;
extern ButtonWidget btnN;

extern ButtonWidget* btn[2];
extern uint8_t buttonCount;

void touch_calibrate();
void btnR_pressAction(void);
void btnR_releaseAction(void);
void btnN_pressAction(void);
void btnN_releaseAction(void);
void initButtons();