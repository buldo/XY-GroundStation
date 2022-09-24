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
    
    menuGroup = lv_group_create();
    menuGroup->editing = 0;
    manualModeButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, manualModeButton);
    lv_obj_align(manualModeButton, LV_ALIGN_TOP_LEFT, 10, 10);
    manualModeLabel = lv_label_create(manualModeButton);
    lv_label_set_text(manualModeLabel,"Manual mode");
    lv_obj_add_event_cb(manualModeButton, &SettingsScreen::menuEvent, LV_EVENT_ALL, this);

    configureRcModuleButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, configureRcModuleButton);
    configureRcModuleLabel = lv_label_create(configureRcModuleButton);
    lv_label_set_text(configureRcModuleLabel,"Configure RC BT module");
    lv_obj_align(configureRcModuleButton, LV_ALIGN_TOP_LEFT, 10, 50);
    lv_obj_add_event_cb(configureRcModuleButton, &SettingsScreen::menuEvent, LV_EVENT_ALL, this);

    configureStationModuleButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, configureStationModuleButton);
    configureStationModuleLabel = lv_label_create(configureStationModuleButton);
    lv_label_set_text(configureStationModuleLabel,"Configure station BT module");
    lv_obj_align(configureStationModuleButton, LV_ALIGN_TOP_LEFT, 10, 90);
    lv_obj_add_event_cb(configureStationModuleButton, &SettingsScreen::menuEvent, LV_EVENT_ALL, this);
}

void SettingsScreen::menuEvent(lv_event_t * e)
{
    SettingsScreen * self = static_cast<SettingsScreen*>(e->user_data);
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_KEY)
    {
        auto key = lv_event_get_key(e);
        if(key == LV_KEY_DOWN)
        {
            lv_group_focus_next(self->menuGroup);
        }
        if(key == LV_KEY_UP)
        {
            lv_group_focus_prev(self->menuGroup);
        }
    }
    if(event_code == LV_EVENT_PRESSED) {
        
        //_ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}

void SettingsScreen::Load(lv_indev_t * inputDevice)
{
    lv_indev_set_group(inputDevice, menuGroup);
    lv_disp_load_scr(screen);
}