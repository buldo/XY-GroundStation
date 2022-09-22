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
typedef void (*flush_cb_t)(_lv_disp_drv_t *, lv_area_t *, lv_color_t *);

int UserInterface::Init() 
{
    busy_wait_ms(100);
    DEV_SET_PWM(50);
    // /* LCD Init */
    LCD_1IN14_Init(HORIZONTAL);
    LCD_1IN14_Clear(0x001F);

    add_repeating_timer_ms(lv_tick_value, &UserInterface::repeatingTimerCallback, this, &timer);
    lv_init();
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, width*10);

              /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.user_data = this;
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = &UserInterface::my_flush_cb;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = width;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = height;
    
    disp = lv_disp_drv_register(&disp_drv);


    
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center "
                      "and wrap long text automatically.");
    lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);

    return 0;
}

void UserInterface::my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color16_t * color_p)
{
    UserInterface * self = static_cast<UserInterface*>(disp_drv->user_data);
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
     *`put_px` is just an example, it needs to be implemented by you.*/
    
    //LCD_1IN14_DisplayArea(area->x1, area->y1, area->x2, area->y2, (uint16_t*)color_p);
    
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            LCD_1IN14_DisplayPoint(x,y,  color_p->full);
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

bool UserInterface::repeatingTimerCallback(struct repeating_timer *t) 
{
    UserInterface * self = static_cast<UserInterface*>(t->user_data);
    lv_tick_inc(self->lv_tick_value);
    lv_timer_handler();
    return true;
}