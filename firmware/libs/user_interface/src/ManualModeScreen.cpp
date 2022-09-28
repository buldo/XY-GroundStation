#include "ManualModeScreen.hpp"

ManualModeScreen::ManualModeScreen(Actuator * actuator)
{
    this->actuator = actuator;
}

ManualModeScreen::~ManualModeScreen()
{
}

void ManualModeScreen::Init()
{
    screen = lv_obj_create(NULL);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    group = lv_group_create();
    lv_group_add_obj(group, screen);
    
    container = lv_obj_create(screen);
    lv_obj_set_size(container, lv_pct(100), lv_pct(100));
    lv_obj_center(container);
    lv_obj_set_grid_dsc_array(container, col_dsc, row_dsc);

    cell_0_0 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_0_0,
        LV_GRID_ALIGN_STRETCH, 0, 1,
        LV_GRID_ALIGN_STRETCH, 0, 1);
    labelElName = lv_label_create(cell_0_0);
    lv_label_set_text(labelElName, "El:");
    lv_obj_center(labelElName);

    cell_0_1 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_0_1,
        LV_GRID_ALIGN_STRETCH, 1, 1,
        LV_GRID_ALIGN_STRETCH, 0, 1);
    labelElValue = lv_label_create(cell_0_1);
    lv_obj_center(labelElValue);

    cell_1_0 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_1_0,
        LV_GRID_ALIGN_STRETCH, 0, 1,
        LV_GRID_ALIGN_STRETCH, 1, 1);
    labelAzName = lv_label_create(cell_1_0);
    lv_label_set_text(labelAzName, "Az");
    lv_obj_center(labelAzName);
    
    cell_1_1 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_1_1, 
        LV_GRID_ALIGN_STRETCH, 1, 1,
        LV_GRID_ALIGN_STRETCH, 1, 1);
    labelAzValue = lv_label_create(cell_1_1);
    lv_obj_center(labelAzValue);

    lv_obj_add_event_cb(screen, &ManualModeScreen::screenEvent, LV_EVENT_ALL, this);

    updateScreenValues();
}

void ManualModeScreen::Load(lv_indev_t * inputDevice)
{
    actuator->SetManualMode(true);
    lv_indev_set_group(inputDevice, group);
    lv_disp_load_scr(screen);
}

void ManualModeScreen::screenEvent(lv_event_t * e)
{
    ManualModeScreen * self = static_cast<ManualModeScreen*>(e->user_data);
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_KEY)
    {
        int32_t az = self->actuator->GetAz();
        int32_t el = self->actuator->GetEl();
        
        auto key = lv_event_get_key(e);
        if(key == LV_KEY_DOWN)
        {
            el -= 1;
        }
        if(key == LV_KEY_UP)
        {
            el += 1;
        }
        if(key == LV_KEY_LEFT)
        {
            az -= 1;
        }
        if(key == LV_KEY_RIGHT)
        {
            az += 1;
        }

        self->actuator->SetPosition(az, el);
        self->updateScreenValues();
    }
}

void ManualModeScreen::updateScreenValues()
{
    lv_label_set_text_fmt(labelElValue, "%d", actuator->GetEl());
    lv_label_set_text_fmt(labelAzValue, "%d", actuator->GetAz());
}