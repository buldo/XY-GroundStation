#pragma once

#include "lvgl.h"

class ManualModeScreen
{
private:
    lv_obj_t * screen;
    lv_group_t * group;
public:
    ManualModeScreen(/* args */);
    ~ManualModeScreen();

    void Load(lv_indev_t * inputDevice);
};


