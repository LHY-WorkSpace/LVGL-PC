
#include "LVGL_UI.h"


lv_obj_t *Desktop_BG;
lv_obj_t *Btn[3];
lv_anim_t MoveFaceToTopRight_Anim;

void DesktopCreate()
{
    Desktop_BG = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Desktop_BG,SCR_W,SCR_H);
    lv_obj_set_style_bg_color(Desktop_BG,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Desktop_BG,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(Desktop_BG,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Desktop_BG,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Desktop_BG,0,LV_PART_MAIN);
    lv_obj_clear_flag(Desktop_BG,LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_scrollbar_mode(Desktop_BG,LV_SCROLLBAR_MODE_OFF);
    lv_obj_center(Desktop_BG);

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
                printf(" %d \r\n",i+1);
                // if(i ==1)
                // {
                //     lv_anim_start(&MoveFaceToTopRight_Anim);
                // }
                // else
                {
                    StartAnim( i+1);
                }

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
    //MoveFaceToTopRightAnim();
    //lv_anim_start(&MoveFaceToTopRight_Anim);

}

void MoveFaceToTopRightAnim_CB(void *var, int32_t v)
{
	uint8_t i,j;
    int16_t x1,y1;

    lv_obj_t *Obj_tmp = (lv_obj_t *)var;
    
    if( Obj_tmp == Face)
    {
        lv_obj_align(Face,LV_ALIGN_CENTER,v,-v);
    }
}

lv_anim_timeline_t *lv_anim_timeline;

void MoveFaceToTopRightAnim()
{
    uint8_t i,j;
    uint32_t Time=0;

    lv_anim_init(&MoveFaceToTopRight_Anim);
    lv_anim_set_var(&MoveFaceToTopRight_Anim,Face);
    lv_anim_set_values(&MoveFaceToTopRight_Anim,0,200);
    lv_anim_set_time(&MoveFaceToTopRight_Anim, 1000);
    lv_anim_set_delay(&MoveFaceToTopRight_Anim, 0);
    lv_anim_set_exec_cb(&MoveFaceToTopRight_Anim, MoveFaceToTopRightAnim_CB);
    lv_anim_set_path_cb(&MoveFaceToTopRight_Anim,lv_anim_path_ease_in_out);


    lv_anim_timeline = lv_anim_timeline_create();

    Time += lv_anim_get_playtime(&EyeBodyPath_Anim[0]);
    Time += lv_anim_get_playtime(&EyeFocalize_Anim[0])*2;

    for ( i = 0; i < 4; i++)
    {
        lv_anim_timeline_add(lv_anim_timeline,0,&EyeBodyPath_Anim[i]);
    }
    lv_anim_timeline_add(lv_anim_timeline,Time-500,&MoveFaceToTopRight_Anim);


    // lv_anim_timeline_add(lv_anim_timeline,0,);
    lv_anim_count_running();
    lv_anim_timeline_start(lv_anim_timeline);


}








void Load_Image()
{




    
}



