#include "LVGL_UI.h"

#define EYE_SIZE_W    (lv_obj_get_width(lv_scr_act())/4)


lv_obj_t *EYE_1;
lv_obj_t *EYE_2;
lv_obj_t *EYE_3;
lv_obj_t *EYE_4;
lv_obj_t *EYE_CENTER;
lv_anim_t Anima;


static void Animation_CB(void *var, int32_t v)
{
    lv_obj_align_to(EYE_1,Face,LV_ALIGN_CENTER,0-v,v-70);
    lv_obj_align_to(EYE_2,Face,LV_ALIGN_CENTER,70-v,0-v);
    lv_obj_align_to(EYE_3,Face,LV_ALIGN_CENTER,0+v,70-v);
    lv_obj_align_to(EYE_4,Face,LV_ALIGN_CENTER,-70+v,0+v);
}



void Eye_Create()
{

    EYE_1 = lv_obj_create(Face);
    lv_obj_set_size(EYE_1,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_1,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_1,EYE_SIZE_W/2,LV_PART_MAIN);

    lv_obj_set_style_outline_width(EYE_1,3,LV_PART_MAIN);
    lv_obj_set_style_outline_color(EYE_1,lv_palette_main(LV_PALETTE_RED),LV_PART_MAIN);

    EYE_2 = lv_obj_create(Face);
    lv_obj_set_size(EYE_2,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_2,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_2,EYE_SIZE_W/2,LV_PART_MAIN);

    EYE_3 = lv_obj_create(Face);
    lv_obj_set_size(EYE_3,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_3,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_3,EYE_SIZE_W/2,LV_PART_MAIN);

    EYE_4 = lv_obj_create(Face);
    lv_obj_set_size(EYE_4,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_4,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_4,EYE_SIZE_W/2,LV_PART_MAIN);

    lv_obj_align_to(EYE_1,Face,LV_ALIGN_CENTER,0,-70);
    lv_obj_align_to(EYE_2,Face,LV_ALIGN_CENTER,70,0);
    lv_obj_align_to(EYE_3,Face,LV_ALIGN_CENTER,0,70);
    lv_obj_align_to(EYE_4,Face,LV_ALIGN_CENTER,-70,0);


    lv_anim_init(&Anima);

    lv_anim_set_var(&Anima,EYE_1);
    lv_anim_set_values(&Anima,0,70);
    lv_anim_set_time(&Anima, 500);
    lv_anim_set_exec_cb(&Anima, Animation_CB);

    lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in_out);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);//==
    // lv_anim_set_path_cb(&Anima,lv_anim_path_bounce);//==
    // lv_anim_set_path_cb(&Anima,lv_anim_path_overshoot);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_step);


    lv_anim_set_repeat_delay(&Anima,500);
    lv_anim_set_repeat_count(&Anima, LV_ANIM_PLAYTIME_INFINITE);
    lv_anim_start(&Anima);


    // lv_anim_timeline_t *Timeline = lv_anim_timeline_create();
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_start();

}

















