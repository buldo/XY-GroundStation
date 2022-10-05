#pragma once

#include "lvgl.h"
#include <functional>

class SettingsScreen
{
private:
    lv_obj_t * screen;

    lv_group_t * menuGroup;

    lv_obj_t * manualModeButton;
    lv_obj_t * manualModeLabel;

    lv_obj_t * directModeButton;
    lv_obj_t * directModeLabel;

    lv_obj_t * configureRcModuleButton;
    lv_obj_t * configureRcModuleLabel;

    lv_obj_t * configureStationModuleButton;
    lv_obj_t * configureStationModuleLabel;

    std::function<void(void)> goToMain;
    std::function<void(void)> goToManual;
    std::function<void(void)> goToDirect;
public:
    SettingsScreen(/* args */);
    ~SettingsScreen();
    void Init(
        std::function<void(void)> goToMainCallback,
        std::function<void(void)> goToManualCallback,
        std::function<void(void)> goToDirectCallback);
    void Load(lv_indev_t * inputDevice);

private:
    static void menuEvent(lv_event_t * e);
};
