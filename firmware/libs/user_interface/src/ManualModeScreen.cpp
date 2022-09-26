#include "ManualModeScreen.hpp"

ManualModeScreen::ManualModeScreen(/* args */)
{
}

ManualModeScreen::~ManualModeScreen()
{
}

void ManualModeScreen::Load(lv_indev_t * inputDevice)
{
    lv_indev_set_group(inputDevice, group);
    lv_disp_load_scr(screen);
}