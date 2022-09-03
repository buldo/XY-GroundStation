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

    return 0;
}