#include "LVGL_UI.h"

#ifdef ON_PC
    #include <stdlib.h>
    #include <unistd.h>
    #include "lvgl/lvgl.h"
    #include "lv_drivers/win32drv/win32drv.h"
    #include <windows.h>
#else
    #include "IncludeFile.h"
#endif


lv_obj_t *Arc_Out;
lv_obj_t *ALL_Bg;
lv_obj_t *Arc_In;
lv_obj_t *Center;

void BarAnimation_CB(void * var, int32_t v)
{
    // lv_obj_set_style_border_color(var,lv_palette_main( LV_PALETTE_GREEN),LV_PART_MAIN);
    // lv_obj_set_style_border_opa(var,LV_OPA_50,LV_PART_MAIN);
    // lv_obj_set_style_border_width(var,v,LV_PART_MAIN);

    lv_obj_t *ArcOut = (lv_obj_t *)var;
   lv_obj_set_style_arc_width(ArcOut,10-v,LV_PART_MAIN);
    //printf("size %d  width %d \r\n",lv_obj_get_x(ArcOut),v);
}



void Btn_CB(lv_event_t *e)
{
    lv_obj_t *Target = lv_event_get_target(e);
    lv_obj_t *UserData = lv_event_get_user_data(e);
    printf(" Btn_CB \r\n");
    if( lv_event_get_code(e) == LV_EVENT_PRESSED)
    {
        lv_obj_add_flag(UserData,LV_OBJ_FLAG_HIDDEN);
    }
}


void Arc_Out_CB(lv_event_t *e)
{
    lv_obj_t *Target = lv_event_get_target(e);
    lv_obj_t *UserData = lv_event_get_user_data(e);

    printf(" Arc_Out_CB \r\n");
    // printf("Angle : %d \r\n ",lv_arc_get_bg_angle_end(Target));
    if(lv_arc_get_bg_angle_end(Target) == 45)
    {
        lv_obj_clear_flag(UserData,LV_OBJ_FLAG_HIDDEN);
    }

}





void Arc_In_CB(lv_event_t *e)
{
    int16_t Arc_Val=0;
    static  lv_anim_t Anima;

    lv_obj_t *Target = lv_event_get_target(e);
    lv_obj_t *UserData = lv_event_get_user_data(e);
    // printf("size %d  \r\n",lv_obj_get_width(UserData));

    Arc_Val = lv_arc_get_value(Target);

    lv_anim_init(&Anima);

    printf("%d\r\n",Arc_Val);

    if( Arc_Val == 100)
    {
        lv_obj_set_style_arc_color(Target,lv_palette_main( LV_PALETTE_YELLOW),LV_PART_INDICATOR);
    }
    else
    {

    }
    
    if(Arc_Val == 0)
    {
        lv_obj_set_style_arc_color(Target,lv_palette_main( LV_PALETTE_BLUE),LV_PART_INDICATOR);
        lv_obj_clear_flag(UserData,LV_OBJ_FLAG_HIDDEN);
    }

    lv_arc_set_bg_angles(UserData,lv_arc_get_angle_start(Target),lv_arc_get_angle_end(Target));
    lv_anim_set_var(&Anima,UserData);
    lv_anim_set_values(&Anima,0,10);
    lv_anim_set_time(&Anima, 500);
    lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
    lv_anim_set_repeat_count(&Anima, 1);
    lv_anim_start(&Anima);
}

void StateBar()
{

    //创建背景
    ALL_Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ALL_Bg,240,240);
    lv_obj_set_style_bg_color(ALL_Bg,lv_color_black(),LV_PART_MAIN);

    Arc_Out =lv_arc_create(ALL_Bg); 

    lv_obj_set_size(Arc_Out,100,100);
    lv_obj_set_style_arc_color(Arc_Out,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_arc_opa(Arc_Out,LV_OPA_50,LV_PART_MAIN);
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_KNOB);//删除把手
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_INDICATOR);//删除进度条
    lv_obj_set_style_arc_rounded(Arc_Out,0,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_Out,10,LV_PART_MAIN);
    lv_arc_set_value(Arc_Out,0);
    lv_obj_align(Arc_Out,LV_ALIGN_BOTTOM_LEFT,0,0);


    Arc_In =lv_arc_create(ALL_Bg); 
    lv_obj_set_size(Arc_In,75,75);
    lv_obj_align_to(Arc_In,Arc_Out,LV_ALIGN_CENTER,0,0);
    lv_obj_set_style_arc_color(Arc_In,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_arc_opa(Arc_In,LV_OPA_50,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_In,5,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_In,5,LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(Arc_In,0,LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(Arc_In,0,LV_PART_INDICATOR);
    lv_arc_set_value(Arc_In,0);
    lv_obj_remove_style(Arc_In, NULL, LV_PART_KNOB);
    lv_obj_add_event_cb(Arc_In,Arc_In_CB,LV_EVENT_VALUE_CHANGED,Arc_Out);
    lv_arc_set_bg_angles(Arc_Out,lv_arc_get_angle_start(Arc_In),lv_arc_get_angle_end(Arc_In));


    Center = lv_obj_create(ALL_Bg); 
    lv_obj_set_size(Center,55,55);
    lv_obj_align_to(Center,Arc_In,LV_ALIGN_CENTER,0,0);
    lv_obj_set_style_radius(Center,LV_RADIUS_CIRCLE,0);
    lv_obj_set_style_opa(Center,LV_OPA_50,LV_PART_MAIN);
    lv_obj_set_style_bg_color(Center,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);


    
    lv_obj_t *text = lv_label_create(Center);
    lv_obj_set_style_text_color(text,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_text_opa(text,LV_OPA_COVER,LV_PART_MAIN);
    lv_label_set_text_fmt(text,"%d\%",10);
    lv_obj_align_to(text,Center,LV_ALIGN_CENTER,0,10);



    lv_obj_t *Btn = lv_btn_create(Arc_In);
    lv_obj_t *Btn_Start = lv_label_create(Btn);

    lv_obj_set_size(Btn,15,15);
    lv_label_set_text(Btn_Start,"V");
    lv_obj_align(Btn,LV_ALIGN_BOTTOM_RIGHT,-10,0);
    lv_obj_align(Btn_Start,LV_ALIGN_CENTER,0,0);
    lv_obj_add_event_cb(Btn,Btn_CB,LV_EVENT_PRESSED,Arc_Out);
    lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(Arc_Out,Arc_Out_CB,LV_EVENT_DRAW_MAIN_END,Btn);




    lv_group_t *Group = lv_group_create();
    lv_group_add_obj(Group,Arc_In);
    lv_group_add_obj(Group,Btn);
    lv_indev_set_group(lv_win32_encoder_device_object,Group);

}




//***************************************************//
//  功能描述: LVGL Demo测试
//
//  参数: 无
//
//  返回值: 无
//
//  说明: 无
//
//***************************************************//
void LVGL_Demo()
{
	// lv_ex_keyboard_1();
	// lv_demo_stress();
	// lv_demo_benchmark();
	// lv_demo_keypad_encoder();
}

//***************************************************//
//  功能描述: LVGL初始化
//
//  参数: 无
//
//  返回值: 无
//
//  说明: 无
//
//***************************************************//
void LVGL_Init()
{
#ifndef ON_PC
    lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
#endif

    StateBar();
    // LVGL_Build_GUI();
    // lv_example_soll_6();
    // LVGL_Demo();

    // BackGroung();
    // GroupTest();
}


//***************************************************//
//  功能描述: LVGL定时任务
//
//  参数: 无
//
//  返回值: 无
//
//  说明: 无
//
//***************************************************//
void LVGL_Task()
{
    lv_task_handler();
}



