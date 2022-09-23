#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "pico/stdlib.h"
#include "lvgl.h"
#include <array>

class UserInterface
{
private:

    struct KeypadKey
    {
        uint pin;
        uint32_t lvglKey;
    };    

    static const int width = 240;
    static const int height = 135;
    const int lv_tick_value = 5;
    repeating_timer timer;

    lv_disp_draw_buf_t disp_buf;
    lv_color_t buf_1[width * 10];
    lv_color_t buf_2[width * 10];
    lv_disp_drv_t disp_drv;
    lv_disp_t * disp;

    /* Input device START */
    lv_indev_drv_t indev_drv;
    lv_indev_t * my_indev;
    uint32_t last_key = 0;
    std::array<KeypadKey, 7> keypadKeys = 
    {
        KeypadKey{  2, LV_KEY_UP },
        KeypadKey{ 18, LV_KEY_DOWN },
        KeypadKey{ 16, LV_KEY_LEFT },
        KeypadKey{ 20, LV_KEY_RIGHT },
        KeypadKey{  3, LV_KEY_ENTER },
        KeypadKey{ 15, LV_KEY_ESC },
        KeypadKey{ 17, LV_KEY_END },
    };
    /* Input device END */
public:
    UserInterface(/* args */);
    ~UserInterface();
    int Init();
private:
    static bool repeatingTimerCallback(struct repeating_timer *t);
    static void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
    static void keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data);

    uint32_t keypad_get_key();
};

#endif // USER_INTERFACE_H_