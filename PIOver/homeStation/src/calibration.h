#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <TFT_eSPI.h>

#include <lvgl.h>
#include "ui.h"

#include "espnow_simplified.h"

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

extern TFT_eSPI tft;        

void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p );
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data );
void init_lvgl();