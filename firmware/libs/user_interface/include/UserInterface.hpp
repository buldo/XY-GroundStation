#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "KeypadKey.hpp"
#include "MainScreen.hpp"

#include "pico/stdlib.h"
#include "lvgl.h"
#include <array>

class UserInterface
{
private:
    /* Output device START*/
    static const int width = 240;
    static const int height = 135;
    const int lv_tick_value = 5;
    repeating_timer timer;
    lv_disp_draw_buf_t displayBuffer;
    lv_color_t displayBuffer1[width * 10];
    lv_color_t displayBuffer2[width * 10];
    lv_disp_drv_t displayDriver;
    lv_disp_t * displayDevice;
    /* Output device END*/

    /* Input device START */
    lv_indev_drv_t inputDeviceDriver;
    lv_indev_t * inputDevice;
    uint32_t inputDeviceLastKey = 0;
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

    /* Screens START */
    MainScreen mainScreen;
    /* Screens END */

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