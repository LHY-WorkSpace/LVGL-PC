#include "LVGL_UI.h"

#define EYE_SIZE_W    (lv_obj_get_width(lv_scr_act())/4)



lv_obj_t *ALL_Bg;
lv_obj_t *Main;

lv_obj_t *EYE_1;
lv_obj_t *EYE_2;
lv_obj_t *EYE_3;
lv_obj_t *EYE_4;
lv_obj_t *EYE_CENTER;
lv_anim_t Anima;


static void Animation_CB(void *var, int32_t v)
{
    lv_obj_align_to(EYE_1,Main,LV_ALIGN_CENTER,0-v,v-70);
    lv_obj_align_to(EYE_2,Main,LV_ALIGN_CENTER,70-v,0-v);
    lv_obj_align_to(EYE_3,Main,LV_ALIGN_CENTER,0+v,70-v);
    lv_obj_align_to(EYE_4,Main,LV_ALIGN_CENTER,-70+v,0+v);
}


void Eye_Create()
{
    //´´½¨±³¾°
    ALL_Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ALL_Bg,240,240);
    lv_obj_set_style_bg_color(ALL_Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(ALL_Bg,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(ALL_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(ALL_Bg,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(ALL_Bg,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(ALL_Bg,LV_SCROLLBAR_MODE_OFF);

    Main = lv_obj_create(ALL_Bg);
    lv_obj_set_size(Main,240,240);
    lv_obj_set_style_bg_color(Main,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Main,120,LV_PART_MAIN);
    lv_obj_set_style_border_side(Main,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Main,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_border_width(Main,5,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(Main,LV_SCROLLBAR_MODE_OFF);
    lv_obj_center(Main);


    EYE_1 = lv_obj_create(Main);
    lv_obj_set_size(EYE_1,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_1,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_1,EYE_SIZE_W/2,LV_PART_MAIN);
    

    EYE_2 = lv_obj_create(Main);
    lv_obj_set_size(EYE_2,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_2,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_2,EYE_SIZE_W/2,LV_PART_MAIN);

    EYE_3 = lv_obj_create(Main);
    lv_obj_set_size(EYE_3,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_3,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_3,EYE_SIZE_W/2,LV_PART_MAIN);

    EYE_4 = lv_obj_create(Main);
    lv_obj_set_size(EYE_4,EYE_SIZE_W,EYE_SIZE_W);
    lv_obj_set_style_bg_color(EYE_4,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_radius(EYE_4,EYE_SIZE_W/2,LV_PART_MAIN);


    // lv_obj_set_flex_align(EYE_2,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_CENTER);
    // lv_obj_set_flex_align(EYE_3,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_END);
    // lv_obj_set_flex_align(EYE_1,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_START);

    lv_obj_align_to(EYE_1,Main,LV_ALIGN_CENTER,0,-70);
    lv_obj_align_to(EYE_2,Main,LV_ALIGN_CENTER,70,0);
    lv_obj_align_to(EYE_3,Main,LV_ALIGN_CENTER,0,70);
    lv_obj_align_to(EYE_4,Main,LV_ALIGN_CENTER,-70,0);


    lv_anim_init(&Anima);

    lv_anim_set_var(&Anima,EYE_1);
    lv_anim_set_values(&Anima,0,70);
    lv_anim_set_time(&Anima, 800);
    lv_anim_set_exec_cb(&Anima, Animation_CB);

    lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in_out);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);//==
    // lv_anim_set_path_cb(&Anima,lv_anim_path_bounce);//==
    // lv_anim_set_path_cb(&Anima,lv_anim_path_overshoot);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_step);

    lv_anim_set_repeat_count(&Anima, LV_ANIM_PLAYTIME_INFINITE);

    lv_anim_start(&Anima);


    printf(" Size %d \r\n",sizeof(lv_obj_t));
    // lv_anim_timeline_t *Timeline = lv_anim_timeline_create();
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_start();

}


