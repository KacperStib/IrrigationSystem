// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: test

#include "ui.h"

void ui_Tent_screen_init(void)
{
    ui_Tent = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Tent, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Button5 = lv_btn_create(ui_Tent);
    lv_obj_set_width(ui_Button5, 100);
    lv_obj_set_height(ui_Button5, 50);
    lv_obj_set_x(ui_Button5, 0);
    lv_obj_set_y(ui_Button5, 120);
    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LTempIn = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LTempIn, 130);
    lv_obj_set_height(ui_LTempIn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LTempIn, -150);
    lv_obj_set_y(ui_LTempIn, -120);
    lv_obj_set_align(ui_LTempIn, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LTempIn, "Temperatura:");

    ui_Label10 = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label10, 0);
    lv_obj_set_y(ui_Label10, 120);
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "Powrot");

    ui_LSoilMois = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LSoilMois, 130);
    lv_obj_set_height(ui_LSoilMois, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LSoilMois, -150);
    lv_obj_set_y(ui_LSoilMois, -30);
    lv_obj_set_align(ui_LSoilMois, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LSoilMois, "Wilgotnosc gleby:");

    ui_LWaterLvl = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LWaterLvl, 130);
    lv_obj_set_height(ui_LWaterLvl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LWaterLvl, -150);
    lv_obj_set_y(ui_LWaterLvl, -60);
    lv_obj_set_align(ui_LWaterLvl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LWaterLvl, "Poziom cieczy:");

    ui_LRHIn = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LRHIn, 130);
    lv_obj_set_height(ui_LRHIn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LRHIn, -150);
    lv_obj_set_y(ui_LRHIn, -90);
    lv_obj_set_align(ui_LRHIn, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LRHIn, "Wilgotnosc:");

    ui_LTentAut = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LTentAut, 148);
    lv_obj_set_height(ui_LTentAut, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LTentAut, 80);
    lv_obj_set_y(ui_LTentAut, 50);
    lv_obj_set_align(ui_LTentAut, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LTentAut, "Tryb automatyczny:");

    ui_TentAut = lv_switch_create(ui_Tent);
    lv_obj_set_width(ui_TentAut, 50);
    lv_obj_set_height(ui_TentAut, 25);
    lv_obj_set_x(ui_TentAut, 190);
    lv_obj_set_y(ui_TentAut, 50);
    lv_obj_set_align(ui_TentAut, LV_ALIGN_CENTER);


    ui_SoilMois = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_SoilMois, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SoilMois, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SoilMois, -50);
    lv_obj_set_y(ui_SoilMois, -30);
    lv_obj_set_align(ui_SoilMois, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SoilMois, "");

    ui_WaterLvl = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_WaterLvl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WaterLvl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WaterLvl, -50);
    lv_obj_set_y(ui_WaterLvl, -60);
    lv_obj_set_align(ui_WaterLvl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WaterLvl, "");

    ui_RHIn = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_RHIn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RHIn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RHIn, -50);
    lv_obj_set_y(ui_RHIn, -90);
    lv_obj_set_align(ui_RHIn, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RHIn, "");

    ui_TempIn = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_TempIn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempIn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempIn, -50);
    lv_obj_set_y(ui_TempIn, -120);
    lv_obj_set_align(ui_TempIn, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempIn, "");

    ui_LLastWateringT = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LLastWateringT, 130);
    lv_obj_set_height(ui_LLastWateringT, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LLastWateringT, -150);
    lv_obj_set_y(ui_LLastWateringT, 0);
    lv_obj_set_align(ui_LLastWateringT, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LLastWateringT, "Ostatnie podlewanie:");

    ui_LastWateringT = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LastWateringT, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LastWateringT, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LastWateringT, -50);
    lv_obj_set_y(ui_LastWateringT, 0);
    lv_obj_set_align(ui_LastWateringT, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LastWateringT, "");

    ui_LcmdT = lv_label_create(ui_Tent);
    lv_obj_set_width(ui_LcmdT, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LcmdT, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LcmdT, -150);
    lv_obj_set_y(ui_LcmdT, 50);
    lv_obj_set_align(ui_LcmdT, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LcmdT, "Podlej rosliny:");

    ui_cmdT = lv_switch_create(ui_Tent);
    lv_obj_set_width(ui_cmdT, 50);
    lv_obj_set_height(ui_cmdT, 25);
    lv_obj_set_x(ui_cmdT, -50);
    lv_obj_set_y(ui_cmdT, 50);
    lv_obj_set_align(ui_cmdT, LV_ALIGN_CENTER);


    ui_SoilMoisBar = lv_bar_create(ui_Tent);
    lv_bar_set_value(ui_SoilMoisBar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_SoilMoisBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_SoilMoisBar, 150);
    lv_obj_set_height(ui_SoilMoisBar, 10);
    lv_obj_set_x(ui_SoilMoisBar, 100);
    lv_obj_set_y(ui_SoilMoisBar, -30);
    lv_obj_set_align(ui_SoilMoisBar, LV_ALIGN_CENTER);

    ui_WaterLvlBar = lv_bar_create(ui_Tent);
    lv_bar_set_value(ui_WaterLvlBar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_WaterLvlBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_WaterLvlBar, 150);
    lv_obj_set_height(ui_WaterLvlBar, 10);
    lv_obj_set_x(ui_WaterLvlBar, 100);
    lv_obj_set_y(ui_WaterLvlBar, -60);
    lv_obj_set_align(ui_WaterLvlBar, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_Button5, ui_event_Button5, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TentAut, ui_event_TentAut, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_cmdT, ui_event_cmdT, LV_EVENT_ALL, NULL);

}
