#pragma once

#include "lvgl.h"

class SettingsScreen
{
private:
    lv_obj_t * screen;

    lv_group_t * menuGroup;
    lv_obj_t * manualModeButton;
    lv_obj_t * manualModeLabel;
    lv_obj_t * configureRcModuleButton;
    lv_obj_t * configureRcModuleLabel;
    lv_obj_t * configureStationModuleButton;
    lv_obj_t * configureStationModuleLabel;

public:
    SettingsScreen(/* args */);
    ~SettingsScreen();
    void Init();
    void Load(lv_indev_t * inputDevice);

private:
    static void menuEvent(lv_event_t * e);
};
