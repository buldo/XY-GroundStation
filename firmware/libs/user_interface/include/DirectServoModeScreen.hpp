#pragma once

#include "lvgl.h"
#include "Actuator.hpp"
#include <functional>

class DirectServoModeScreen
{
private:
    lv_obj_t * screen;
    lv_group_t * group;

    lv_coord_t col_dsc[3] = {LV_GRID_FR(1), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};
    lv_coord_t row_dsc[3] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_t * container;

    lv_obj_t * labelTheta1Name;
    lv_obj_t * cell_0_0;

    lv_obj_t * labelTheta1Value;
    lv_obj_t * cell_0_1;

    lv_obj_t * labelTheta2Name;
    lv_obj_t * cell_1_0;

    lv_obj_t * labelTheta2Value;
    lv_obj_t * cell_1_1;

    Actuator * actuator;

    std::function<void(void)> goToSettings;
public:
    DirectServoModeScreen(Actuator * actuator);
    ~DirectServoModeScreen();

    void Load(lv_indev_t * inputDevice);
    void Init(std::function<void(void)> goToSettingsCallback);
    static void screenEvent(lv_event_t * e);
    void updateScreenValues();
    uint32_t fixValues(int32_t value);
};


