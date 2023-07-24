// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: Watch

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_BoostModeA
void ui_BoostModeA_screen_init(void);
lv_obj_t * ui_BoostModeA;
lv_obj_t * ui_ChargeIndecB[4];
lv_obj_t * ui_ChargeIndecA[4];
lv_obj_t * ui_MainIndecA[16];
lv_obj_t * ui_MainIndecB[6];
lv_obj_t * ui_BoxSide;
lv_obj_t * ui_SecNumBox;
lv_obj_t * ui_SecNum;
lv_obj_t * ui_SecLable;

// SCREEN: ui_BoostModeB
void ui_BoostModeB_screen_init(void);
lv_obj_t * ui_BoostModeB;
lv_obj_t * ui_MainIndeotor[5];
lv_obj_t * ui_Triangle;
lv_obj_t * ui_SmallPointWhite[12];
lv_obj_t * ui_SmallPoint[12];
lv_obj_t * ui_SecConut;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_smallindecotr_[1] = {&ui_img_smallindecotr_1_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    //ui_BoostModeA_screen_init();
    ui_BoostModeB_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_BoostModeB);
}
