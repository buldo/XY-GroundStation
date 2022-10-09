#include "DirectServoModeScreen.hpp"

DirectServoModeScreen::DirectServoModeScreen(Actuator * actuator)
{
    this->actuator = actuator;
}

DirectServoModeScreen::~DirectServoModeScreen()
{
}

void DirectServoModeScreen::Init(std::function<void(void)> goToSettingsCallback)
{
    goToSettings = goToSettingsCallback;

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
    labelTheta1Name = lv_label_create(cell_0_0);
    lv_label_set_text(labelTheta1Name, "Theta1:");
    lv_obj_center(labelTheta1Name);

    cell_0_1 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_0_1,
        LV_GRID_ALIGN_STRETCH, 1, 1,
        LV_GRID_ALIGN_STRETCH, 0, 1);
    labelTheta1Value = lv_label_create(cell_0_1);
    lv_obj_center(labelTheta1Value);

    cell_1_0 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_1_0,
        LV_GRID_ALIGN_STRETCH, 0, 1,
        LV_GRID_ALIGN_STRETCH, 1, 1);
    labelTheta2Name = lv_label_create(cell_1_0);
    lv_label_set_text(labelTheta2Name, "Theta2");
    lv_obj_center(labelTheta2Name);
    
    cell_1_1 = lv_obj_create(container);
    lv_obj_set_grid_cell(
        cell_1_1, 
        LV_GRID_ALIGN_STRETCH, 1, 1,
        LV_GRID_ALIGN_STRETCH, 1, 1);
    labelTheta2Value = lv_label_create(cell_1_1);
    lv_obj_center(labelTheta2Value);

    lv_obj_add_event_cb(screen, &DirectServoModeScreen::screenEvent, LV_EVENT_ALL, this);

    updateScreenValues();
}

void DirectServoModeScreen::Load(lv_indev_t * inputDevice)
{
    actuator->SetManualMode(true);
    actuator->SetServoPosition(90,90);
    lv_indev_set_group(inputDevice, group);
    lv_disp_load_scr(screen);
    updateScreenValues();
}

void DirectServoModeScreen::screenEvent(lv_event_t * e)
{
    DirectServoModeScreen * self = static_cast<DirectServoModeScreen*>(e->user_data);
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_KEY)
    {
        int32_t theta1 = self->actuator->GetTheta1();
        int32_t theta2 = self->actuator->GetTheta2();
        
        auto key = lv_event_get_key(e);
        if(key == LV_KEY_DOWN)
        {
            theta2 -= 1;
        }
        if(key == LV_KEY_UP)
        {
            theta2 += 1;
        }
        if(key == LV_KEY_LEFT)
        {
            theta1 -= 1;
        }
        if(key == LV_KEY_RIGHT)
        {
            theta1 += 1;
        }
        if(key == LV_KEY_ESC)
        {
            self->goToSettings();
        }

        theta1 = self->fixValues(theta1);
        theta2 = self->fixValues(theta2);

        self->actuator->SetServoPosition(theta1, theta2);
        self->updateScreenValues();
    }
}

void DirectServoModeScreen::updateScreenValues()
{
    lv_label_set_text_fmt(labelTheta1Value, "%d", actuator->GetTheta1());
    lv_label_set_text_fmt(labelTheta2Value, "%d", actuator->GetTheta2());
}

uint32_t DirectServoModeScreen::fixValues(int32_t value)
{
    if(value < 0)
    {
        return 0;
    }

    if(value > 180)
    {
        return 180;
    }
}