// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: test

#include "ui.h"

void ui_MainMenu_screen_init(void)
{
    ui_MainMenu = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainMenu, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_GardenB = lv_btn_create(ui_MainMenu);
    lv_obj_set_width(ui_GardenB, 150);
    lv_obj_set_height(ui_GardenB, 75);
    lv_obj_set_x(ui_GardenB, -122);
    lv_obj_set_y(ui_GardenB, 101);
    lv_obj_set_align(ui_GardenB, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GardenB, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_GardenB, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TentB = lv_btn_create(ui_MainMenu);
    lv_obj_set_width(ui_TentB, 150);
    lv_obj_set_height(ui_TentB, 75);
    lv_obj_set_x(ui_TentB, 125);
    lv_obj_set_y(ui_TentB, 99);
    lv_obj_set_align(ui_TentB, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_TentB, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_TentB, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_GLabel = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_GLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GLabel, -124);
    lv_obj_set_y(ui_GLabel, 103);
    lv_obj_set_align(ui_GLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_GLabel, "Ogrod");

    ui_TLabel1 = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_TLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TLabel1, 122);
    lv_obj_set_y(ui_TLabel1, 101);
    lv_obj_set_align(ui_TLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TLabel1, "Namiot");

    ui_Label1 = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, 581);
    lv_obj_set_y(ui_Label1, -95);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    ui_TLabel = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_TLabel, 130);
    lv_obj_set_height(ui_TLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TLabel, -150);
    lv_obj_set_y(ui_TLabel, -120);
    lv_obj_set_align(ui_TLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TLabel, "Temperatura:");

    ui_PLabel = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_PLabel, 130);
    lv_obj_set_height(ui_PLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PLabel, -150);
    lv_obj_set_y(ui_PLabel, -30);
    lv_obj_set_align(ui_PLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PLabel, "Cisnienie:");

    ui_LLabel = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_LLabel, 130);
    lv_obj_set_height(ui_LLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LLabel, -150);
    lv_obj_set_y(ui_LLabel, -60);
    lv_obj_set_align(ui_LLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LLabel, "Naslonecznienie:");

    ui_HLabel = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_HLabel, 130);
    lv_obj_set_height(ui_HLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_HLabel, -150);
    lv_obj_set_y(ui_HLabel, -90);
    lv_obj_set_align(ui_HLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HLabel, "Wilgotnosc:");

    ui_TempOut = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_TempOut, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempOut, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempOut, -60);
    lv_obj_set_y(ui_TempOut, -120);
    lv_obj_set_align(ui_TempOut, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempOut, "");

    ui_RHOut = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_RHOut, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RHOut, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RHOut, -60);
    lv_obj_set_y(ui_RHOut, -90);
    lv_obj_set_align(ui_RHOut, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RHOut, "");

    ui_Lux = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_Lux, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Lux, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Lux, -60);
    lv_obj_set_y(ui_Lux, -60);
    lv_obj_set_align(ui_Lux, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Lux, "");

    ui_Preasure = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_Preasure, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Preasure, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Preasure, -60);
    lv_obj_set_y(ui_Preasure, -30);
    lv_obj_set_align(ui_Preasure, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Preasure, "");

    ui_Time = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_Time, 140);
    lv_obj_set_height(ui_Time, 46);
    lv_obj_set_x(ui_Time, 130);
    lv_obj_set_y(ui_Time, -100);
    lv_obj_set_align(ui_Time, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Time, "00 : 00");
    lv_obj_set_style_text_align(ui_Time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Time, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Time, lv_color_hex(0xE50707), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_Date, 140);
    lv_obj_set_height(ui_Date, 24);
    lv_obj_set_x(ui_Date, 130);
    lv_obj_set_y(ui_Date, -50);
    lv_obj_set_align(ui_Date, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Date, "01 . 01 . 2000");
    lv_obj_set_style_text_align(ui_Date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Date, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_GardenB, ui_event_GardenB, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TentB, ui_event_TentB, LV_EVENT_ALL, NULL);
    uic_TempOut = ui_TempOut;

}
