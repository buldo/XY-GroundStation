#pragma once

#include "lvgl.h"

class MainScreen
{
private:
    lv_obj_t * screen;
    lv_obj_t * label;
    lv_group_t * group;
    /* data */
public:
    MainScreen(/* args */);
    ~MainScreen();
    void Init();
    void Load(lv_indev_t * inputDevice);

private:
    static void screenEvent(lv_event_t * e);
};
