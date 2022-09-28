#include "ManualModeScreen.hpp"

ManualModeScreen::ManualModeScreen(Actuator * actuator)
{
}

ManualModeScreen::~ManualModeScreen()
{
}

void ManualModeScreen::Init()
{
    screen = lv_obj_create(NULL);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
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
    lv_label_set_text(labelElValue, "0");
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
    lv_label_set_text(labelAzValue, "0");
    lv_obj_center(labelAzValue);
}

void ManualModeScreen::Load(lv_indev_t * inputDevice)
{
    //lv_indev_set_group(inputDevice, screen);
    lv_disp_load_scr(screen);
}