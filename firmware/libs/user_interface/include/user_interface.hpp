#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "pico/stdlib.h"
#include "lvgl.h"

class UserInterface
{
private:
    static const int width = 240;
    static const int height = 135;
    const int lv_tick_value = 5;
    repeating_timer timer;

    lv_disp_draw_buf_t disp_buf;
    lv_color_t buf_1[width * 10];
    lv_color_t buf_2[width * 10];
    lv_disp_drv_t disp_drv;
    lv_disp_t * disp;

public:
    UserInterface(/* args */);
    ~UserInterface();
    int Init();
private:
    static bool repeatingTimerCallback(struct repeating_timer *t);
    static void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
};

#endif // USER_INTERFACE_H_