#pragma once

#include "lvgl.h"
#include <functional>

class MainScreen
{
private:
    lv_obj_t * screen;
    lv_obj_t * label;
    lv_group_t * group;

    std::function<void(void)> goToSettings;
public:
    MainScreen();
    ~MainScreen();
    void Init(std::function<void(void)> goToSettingsCallback);
    void Load(lv_indev_t * inputDevice);

private:
    static void screenEvent(lv_event_t * e);
};
