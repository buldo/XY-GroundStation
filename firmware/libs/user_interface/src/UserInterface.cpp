#include "UserInterface.hpp"
#include "hardware/timer.h"
#include "board_startup.hpp"
#include "lcd_1in14.hpp"
#include <bit>

UserInterface::UserInterface(Actuator * actuator)
{
    this->actuator = actuator;
    settingsScreen = new SettingsScreen();
    mainScreen = new MainScreen();
    manualScreen = new ManualModeScreen(actuator);
    directServoScreen = new DirectServoModeScreen(actuator);
}

UserInterface::~UserInterface()
{
}

int UserInterface::Init()
{
    /* Buttons gpio init */
    for (const auto& key : keypadKeys)
    {
        gpio_init(key.pin);
        gpio_set_function(key.pin, GPIO_FUNC_NULL);
        gpio_set_dir(key.pin, GPIO_IN);
        gpio_pull_up(key.pin);
    }

    /* Display device init START */
    busy_wait_ms(100);
    DEV_SET_PWM(50);
    LCD_1IN14_Init(HORIZONTAL);
    LCD_1IN14_Clear(0x001F);

    add_repeating_timer_ms(lv_tick_value, &UserInterface::repeatingTimerCallback, this, &timer);
    lv_init();
    lv_disp_draw_buf_init(&displayBuffer, displayBuffer1, NULL, width*14);

    lv_disp_drv_init(&displayDriver);
    displayDriver.user_data = this;
    displayDriver.draw_buf = &displayBuffer;
    displayDriver.flush_cb = &UserInterface::my_flush_cb;
    displayDriver.hor_res = width;
    displayDriver.ver_res = height;
    displayDevice = lv_disp_drv_register(&displayDriver);
    /* Display device init END */

    /* Input device init START */
    lv_indev_drv_init(&inputDeviceDriver);
    inputDeviceDriver.user_data = this;
    inputDeviceDriver.type = LV_INDEV_TYPE_KEYPAD;
    inputDeviceDriver.read_cb = &UserInterface::keyboard_read;
    inputDevice = lv_indev_drv_register(&inputDeviceDriver);
    /* Input device init END */

    auto activateSettingsScreenCallback = [this]() { activateSettingsScreen(); };
    mainScreen->Init(activateSettingsScreenCallback);
    mainScreen->Load(inputDevice);

    auto activateMainScreenCallback = [this]() { activateMainScreen(); };
    auto activateManualScreenCallback = [this]() { activateManualScreen(); };
    auto activateDirectScreenCallback = [this]() { activateDirectServoScreen(); };
    settingsScreen->Init(activateMainScreenCallback, activateManualScreenCallback, activateDirectScreenCallback);

    manualScreen->Init(activateSettingsScreenCallback);

    directServoScreen->Init(activateSettingsScreenCallback);

    return 0;
}

void UserInterface::activateSettingsScreen()
{
    settingsScreen->Load(inputDevice);
}

void UserInterface::activateMainScreen()
{
    mainScreen->Load(inputDevice);
}

void UserInterface::activateManualScreen()
{
    manualScreen->Load(inputDevice);
}

void UserInterface::activateDirectServoScreen()
{
    directServoScreen->Load(inputDevice);
}

void UserInterface::my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color16_t * color_p)
{
    auto hh = area->y2 - area->y1 + 1;
    auto ww = area->x2 - area->x1 + 1;
    uint16_t image[ww*hh];

    for(size_t y = 0; y <hh; y++) 
    {
        size_t lineStartIndex = ww * y;
        for(size_t x = 0; x < ww; x++) 
        {
            size_t index = lineStartIndex + x;
            auto color = color_p->full;
            image[ index ] = std::byteswap(color);
            color_p++;
        }
    }

    LCD_1IN14_DisplayArea(area->x1, area->y1, area->x2, area->y2, image);

    lv_disp_flush_ready(disp_drv);
}

bool UserInterface::repeatingTimerCallback(struct repeating_timer *t) 
{
    UserInterface * self = static_cast<UserInterface*>(t->user_data);
    lv_tick_inc(self->lv_tick_value);
    lv_timer_handler();
    return true;
}

void UserInterface::keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
    UserInterface * self = static_cast<UserInterface*>(drv->user_data);
    uint32_t act_key = self->keypad_get_key();
    if(act_key != 0)
    {
        self->inputDeviceLastKey = act_key;
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = self->inputDeviceLastKey;
}

uint32_t UserInterface::keypad_get_key()
{
    for (const auto& key : keypadKeys)
    {
        auto currentVal = gpio_get(key.pin);
        if(currentVal == false)
        {
            return key.lvglKey;
        }
    }

    return 0;
}