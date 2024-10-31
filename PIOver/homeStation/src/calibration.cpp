#include "calibration.h"

TFT_eSPI tft = TFT_eSPI();

static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;
        /*
        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
        */
    }
}

void init_lvgl(){

  lv_init();
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
  
    ui_init();
}

/*
void btnR_pressAction(void)
{
  if (btnR.justPressed()) {
    btnR.drawSmoothButton(!btnR.getState(), 3, TFT_BLACK, btnR.getState() ? "OFF" : "ON");
    
    if (btnR.getState()){
      cmdN = 1;
    }
    else{
      cmdN = 0;
    }
    btnR.setPressTime(millis());

    msgNTx.onOff = cmdN;
    sendCommandN(namiot, msgNTx);
    //tft.setCursor(0, 160, 2);
    //tft.print("espnow: "); tft.print(cmdT);
  }
}

void btnN_pressAction(void)
{
  if (btnN.justPressed()) {
    btnN.drawSmoothButton(!btnN.getState(), 3, TFT_BLACK, btnN.getState() ? "OFF" : "ON");
    
    if (btnN.getState()){
      cmdT = 1;
    }
    else{
      cmdT = 0;
    }
    btnN.setPressTime(millis());

    msgTTx.onOff = cmdT;
    sendCommandT(trawnik, msgTTx);
    //tft.setCursor(0, 160, 2);
    //tft.print("espnow2: "); tft.print(cmdN);
  }
}
*/