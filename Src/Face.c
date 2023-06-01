#include "LVGL_UI.h"



lv_obj_t *BackGround;
lv_obj_t *Face;
lv_obj_t *Btn[3];


void Face_Create()
{
    BackGround = lv_obj_create(lv_scr_act());
    lv_obj_set_size(BackGround,240,240);
    lv_obj_set_style_bg_color(BackGround,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(BackGround,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(BackGround,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(BackGround,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(BackGround,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(BackGround,LV_SCROLLBAR_MODE_OFF);




    Face = lv_obj_create(BackGround);
    lv_obj_set_size(Face,240-8*2,240-8*2);
    lv_obj_set_style_bg_color(Face,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Face,(240-8*2)/2,LV_PART_MAIN);

    //lv_obj_set_style_outline_pad();
    lv_obj_set_style_outline_opa(Face,LV_OPA_90,LV_PART_MAIN);
    lv_obj_set_style_outline_width(Face,8,LV_PART_MAIN);
    lv_obj_set_style_outline_color(Face,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);//ÑÛÇòÍâÂÖÀª

    //lv_obj_set_style_border_post();
    lv_obj_set_style_border_opa(Face,LV_OPA_80,LV_PART_MAIN);
    lv_obj_set_style_border_side(Face,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Face,lv_palette_darken(LV_PALETTE_GREY,3),LV_PART_MAIN);
    lv_obj_set_style_border_width(Face,15,LV_PART_MAIN);

    lv_obj_set_scrollbar_mode(Face,LV_SCROLLBAR_MODE_OFF);
    lv_obj_center(Face);


    // lv_scr_load(BackGround);
    // lv_scr_load(Face);


}


void Btn_Handle(lv_event_t *e)
{
	uint8_t i=0;
    lv_obj_t *Btntmp = lv_event_get_target(e);
    lv_event_code_t codetmp = lv_event_get_code(e);

    if( lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        for ( i = 0; i < 3; i++)
        {
            if(Btntmp == Btn[i])
            {
            StartAnim( i+1);
            printf(" %d \r\n",i+1);
            }
        }
    }
}



void Btn_Create()
{
	uint8_t i=0;

    for ( i = 0; i < 3; i++)
    {
        Btn[i] = lv_btn_create(lv_scr_act());
        lv_obj_align(Btn[i],LV_ALIGN_BOTTOM_LEFT+i,0,0);
        lv_obj_set_size(Btn[i],40,20);
        lv_obj_set_style_bg_color(Btn[i],lv_color_make(74,117,37),LV_PART_MAIN);
        lv_obj_add_event_cb(Btn[i],Btn_Handle,LV_EVENT_CLICKED,NULL);
    }

}



lv_obj_t *OPAbg;
lv_obj_t *TESTOBJ;
lv_anim_t OAPaNIM;

static void OPAAINMASD(void *var, int32_t v)
{
    printf("OPA :%d\r\n",v );
    lv_obj_set_style_opa(TESTOBJ,v,LV_PART_MAIN);


}


void OpaTest()
{

    OPAbg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(OPAbg,240,240);
    lv_obj_set_style_bg_color(OPAbg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(OPAbg,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(OPAbg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(OPAbg,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(OPAbg,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(OPAbg,LV_SCROLLBAR_MODE_OFF);


    TESTOBJ = lv_obj_create(OPAbg);
    lv_obj_set_size(TESTOBJ,100,100);
    lv_obj_set_style_bg_color(TESTOBJ,lv_color_make(56,110,23),LV_PART_MAIN);
    lv_obj_set_style_radius(TESTOBJ,20,LV_PART_MAIN);
    lv_obj_set_style_opa(TESTOBJ,LV_OPA_20,LV_PART_MAIN);


    lv_anim_init(&OAPaNIM);
    lv_anim_set_var(&OAPaNIM,TESTOBJ);
    lv_anim_set_values(&OAPaNIM,0,250);
    lv_anim_set_time(&OAPaNIM, 3000);
    lv_anim_set_delay(&OAPaNIM, 500);
    lv_anim_set_exec_cb(&OAPaNIM, OPAAINMASD);
    lv_anim_set_path_cb(&OAPaNIM,lv_anim_path_ease_in_out);
    lv_anim_set_repeat_delay(&OAPaNIM,200);
    lv_anim_set_repeat_count(&OAPaNIM, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&OAPaNIM);


}








void Main_UI()
{
    // Face_Create();
    // Eye_Main();
    // Btn_Create();
    OpaTest();
    // MeterTest();

}














