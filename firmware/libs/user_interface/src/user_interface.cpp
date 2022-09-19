#include "user_interface.hpp"
#include "hardware/timer.h"
#include "board_startup.hpp"
#include "lcd_1in14.hpp"


UserInterface::UserInterface(/* args */)
{
}

UserInterface::~UserInterface()
{
}

int UserInterface::Init() 
{
    busy_wait_ms(100);
    DEV_SET_PWM(50);
    // /* LCD Init */
    LCD_1IN14_Init(HORIZONTAL);
    LCD_1IN14_Clear(0x001F);

    add_repeating_timer_ms(lv_tick_value, &UserInterface::repeatingTimerCallback, this, &timer);

    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, MY_DISP_HOR_RES*10);
    return 0;
}

bool UserInterface::repeatingTimerCallback(struct repeating_timer *t) 
{
    UserInterface * self = static_cast<UserInterface*>(t->user_data);
    lv_tick_inc(self->lv_tick_value);
    lv_timer_handler();
    return true;
}