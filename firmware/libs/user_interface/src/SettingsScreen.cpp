#include "SettingsScreen.hpp"


SettingsScreen::SettingsScreen(/* args */)
{
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::Init()
{
    screen = lv_obj_create(NULL);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    label = lv_label_create(screen);
    lv_obj_set_width(label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(label, 0);
    lv_obj_set_y(label, 0);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "Settings");


    group = lv_group_create();
    lv_group_add_obj(group, screen);

    lv_obj_add_event_cb(screen, &SettingsScreen::screenEvent, LV_EVENT_ALL, this);
}

void SettingsScreen::screenEvent(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        //_ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}

void SettingsScreen::Load(lv_indev_t * inputDevice)
{
    lv_indev_set_group(inputDevice, group);
    lv_disp_load_scr(screen);
}