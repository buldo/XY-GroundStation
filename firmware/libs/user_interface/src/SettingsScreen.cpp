#include "SettingsScreen.hpp"


SettingsScreen::SettingsScreen(/* args */)
{
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::Init(
    std::function<void(void)> goToMainCallback,
    std::function<void(void)> goToManualCallback,
    std::function<void(void)> goToDirectCallback)
{
    goToMain = goToMainCallback;
    goToManual = goToManualCallback;
    goToDirect = goToDirectCallback;
    
    screen = lv_obj_create(NULL);
    // lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    menuGroup = lv_group_create();
    menuGroup->editing = 0;

    manualModeButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, manualModeButton);
    lv_obj_align(manualModeButton, LV_ALIGN_TOP_LEFT, 10, 10);
    manualModeLabel = lv_label_create(manualModeButton);
    lv_label_set_text(manualModeLabel,"Manual mode");
    lv_obj_add_event_cb(manualModeButton, &SettingsScreen::menuEvent, LV_EVENT_ALL, this);

    directModeButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, directModeButton);
    lv_obj_align(directModeButton, LV_ALIGN_TOP_LEFT, 10, 50);
    directModeLabel = lv_label_create(directModeButton);
    lv_label_set_text(directModeLabel,"Direct mode");
    lv_obj_add_event_cb(directModeButton, &SettingsScreen::menuEvent, LV_EVENT_ALL, this);

    configureRcModuleButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, configureRcModuleButton);
    configureRcModuleLabel = lv_label_create(configureRcModuleButton);
    lv_label_set_text(configureRcModuleLabel,"Configure RC BT module");
    lv_obj_align(configureRcModuleButton, LV_ALIGN_TOP_LEFT, 10, 90);
    lv_obj_add_event_cb(configureRcModuleButton, &SettingsScreen::menuEvent, LV_EVENT_ALL, this);

    configureStationModuleButton = lv_btn_create(screen);
    lv_group_add_obj(menuGroup, configureStationModuleButton);
    configureStationModuleLabel = lv_label_create(configureStationModuleButton);
    lv_label_set_text(configureStationModuleLabel,"Configure station BT module");
    lv_obj_align(configureStationModuleButton, LV_ALIGN_TOP_LEFT, 10, 130);
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
        if(key == LV_KEY_ESC)
        {
            self->goToMain();
        }
    }
    if(event_code == LV_EVENT_PRESSED && e->target == self->manualModeButton) {
        self->goToManual();
    }
    if(event_code == LV_EVENT_PRESSED && e->target == self->directModeButton) {
        self->goToDirect();
    }
}

void SettingsScreen::Load(lv_indev_t * inputDevice)
{
    lv_indev_set_group(inputDevice, menuGroup);
    lv_disp_load_scr(screen);
}