#include "LVGL_UI.h"

#define EYE_SIZE_W    (lv_obj_get_width(lv_scr_act())/4)



lv_obj_t *Eye_G[4];


lv_obj_t *Eye_Group[4];
lv_anim_t Anima_Eye_Group[4];

int8_t Eye_Position[4][2]=
{
    {0,-70},    //上
    {70,0},     //右
    {0,70},     //下
    {-70,0},     //左
};


static void Animation_CB(void *var, int32_t v)
{
    uint8_t i,j;
    int16_t x,y;
   static uint8_t Flag = 0xff;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;


    x = lv_obj_get_x(Eye_Group[0]);
    y = lv_obj_get_y(Eye_Group[0]);

    for ( i = 0; i < 4; i++)
    {
        if( Eye_tmp == Eye_Group[0] )//eye[0]
        {
            for ( j = 0; j < 4; j++)
            {
                if( x == Eye_Position[j][0] && y == Eye_Position[j][1])//找eye[0]的基准位置，
                {
                    Flag = j;
                }
            }

            if(Flag != 0xff)//到达基准点位置
            {
                for( i = 0; i < 4; i++)
                {
                    //重新设置每个eye的位置
                    lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER, Eye_Position[(Flag+i)%4][0], Eye_Position[(Flag+i)%4][1]);
                }

                break;
            }
            else//未到达基准点位置,执行移动效果
            {
                for( i = 0; i < 4; i++)
                {
                    lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER, Eye_Position[(Flag+i+1)%4][0]+v, Eye_Position[(Flag+i+1)%4][1]+v);
                }
            }
        }
    }

    // lv_obj_align_to(Eye_Group[0],Face,LV_ALIGN_CENTER,0-v,v-70);
    // lv_obj_align_to(Eye_Group[1],Face,LV_ALIGN_CENTER,70-v,0-v);
    // lv_obj_align_to(Eye_Group[2],Face,LV_ALIGN_CENTER,0+v,70-v);
    // lv_obj_align_to(Eye_Group[3],Face,LV_ALIGN_CENTER,-70+v,0+v);

}



void Eye_Create()
{
    uint8_t i=0;

    for ( i = 0; i < 4; i++)
    {
        Eye_Group[i] = lv_obj_create(Face);
        lv_obj_set_size(Eye_Group[i],EYE_SIZE_W,EYE_SIZE_W);
        lv_obj_set_style_bg_color(Eye_Group[i],lv_color_white(),LV_PART_MAIN);
        lv_obj_set_style_radius(Eye_Group[i],EYE_SIZE_W/2,LV_PART_MAIN);
        lv_obj_set_style_outline_width(Eye_Group[i],3,LV_PART_MAIN);
        lv_obj_set_style_outline_color(Eye_Group[i],lv_palette_main(LV_PALETTE_RED),LV_PART_MAIN);

        lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,Eye_Position[i][0],Eye_Position[i][1]);

        lv_anim_init(&Anima_Eye_Group[i]);
        lv_anim_set_var(&Anima_Eye_Group[i],Eye_Group[i]);
        lv_anim_set_values(&Anima_Eye_Group[i],0,70);
        lv_anim_set_time(&Anima_Eye_Group[i], 500);
        lv_anim_set_exec_cb(&Anima_Eye_Group[i], Animation_CB);
        lv_anim_set_path_cb(&Anima_Eye_Group[i],lv_anim_path_ease_in_out);

        lv_anim_set_repeat_delay(&Anima_Eye_Group[i],500);
        lv_anim_set_repeat_count(&Anima_Eye_Group[i], LV_ANIM_PLAYTIME_INFINITE);

    }

    for ( i = 0; i < 4; i++)
    {
        lv_anim_start(&Anima_Eye_Group[i]);
    }


    // lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,70,0);
    // lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,0,70);
    // lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,-70,0);


    // lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_ease_in_out);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);//==
    // lv_anim_set_path_cb(&Anima,lv_anim_path_bounce);//==
    // lv_anim_set_path_cb(&Anima,lv_anim_path_overshoot);
    // lv_anim_set_path_cb(&Anima,lv_anim_path_step);


    // lv_anim_set_repeat_delay(&Anima_Eye1,500);
    // lv_anim_set_repeat_count(&Anima_Eye1, LV_ANIM_PLAYTIME_INFINITE);
    // lv_anim_start(&Anima_Eye1);


    // lv_anim_timeline_t *Timeline = lv_anim_timeline_create();
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_add(Timeline,0,&Anima);
    // lv_anim_timeline_start();

}






















