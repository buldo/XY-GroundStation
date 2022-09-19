#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "pico/stdlib.h"
#include "lvgl.h"

class UserInterface
{
private:
    const int lv_tick_value = 5;
    repeating_timer timer;

    lv_disp_draw_buf_t disp_buf;
    lv_color_t buf_1[MY_DISP_HOR_RES * 10];
    lv_color_t buf_2[MY_DISP_HOR_RES * 10];

public:
    UserInterface(/* args */);
    ~UserInterface();
    int Init();
private:
    static bool repeatingTimerCallback(struct repeating_timer *t);
};

#endif // USER_INTERFACE_H_