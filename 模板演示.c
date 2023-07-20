










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


lv_obj_t *Btn_OK;
lv_obj_t *Btn_BACK;
lv_obj_t *Btn_DOWN;
lv_obj_t *Btn_UP;
lv_obj_t *Btn;
lv_obj_t *Btnnew;
lv_obj_t *Bg;

//***************************************************//
//  功能描述: LVGL 按键处理
//
//  参数: lv_event_t
//
//  返回值: lv_event_cb_t
//
//  说明: 无
//
//***************************************************//
void OKKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);
    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        printf("OK !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_color_white(),LV_PART_MAIN);
        lv_obj_set_style_bg_color(Target,lv_color_black(),LV_PART_SELECTED);
    }
}


void DownKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        printf("Down !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_GREEN),LV_PART_MAIN);
    }
}

void UpKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);
    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        printf("Up !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_BLUE),LV_PART_MAIN);
    }
}

void BackKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);
    lv_obj_t *Target = lv_event_get_target(Event);
    if( Code == LV_EVENT_CLICKED)
    {
        printf("Back !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    }
}

//***************************************************//
//  功能描述: LVGL 绘图和布局
//
//  参数:
//
//  返回值:
//
//  说明: 无
//
//***************************************************//
void Botton()
{
    Btn = lv_btn_create(lv_scr_act());
    lv_obj_align(Btn,LV_ALIGN_CENTER,0,0);
    lv_obj_set_size(Btn,100,100);
    lv_obj_set_style_bg_color(Btn,lv_palette_main( LV_PALETTE_BLUE),0);
    lv_obj_set_style_bg_grad_color(Btn, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_bg_grad_dir(Btn, LV_GRAD_DIR_HOR, 0);
    lv_obj_set_style_opa(Btn,LV_OPA_80,0);
    lv_obj_set_style_border_width(Btn,3,LV_PART_MAIN);
    lv_obj_set_style_shadow_color(Btn,lv_color_black(),0);
    lv_obj_set_style_shadow_ofs_x(Btn,3,0);
    lv_obj_add_flag(Btn,LV_OBJ_FLAG_CHECKABLE);
    // lv_obj_add_event_cb(Btn,Btn_Handle,LV_EVENT_ALL,NULL);

    lv_obj_t *label_A = lv_label_create(Btn);
    // lv_label_set_text(label_A,"1 2 3 4 5 6 7 8 9 ");
    lv_obj_set_align(label_A,LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(label_A, LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_size(label_A,80,50);
    lv_label_set_recolor(label_A,true);
    lv_label_set_text(label_A,"#FF0000 AAA---===***123456789#\n#00FF00 BBB+++---===#\n#0000FF CCC***---+++#\n");
    lv_obj_set_style_text_line_space(label_A,3,0);
    lv_obj_set_style_anim_speed(label_A,50,0);

    // lv_obj_t *label_B = lv_label_create(Btn);
    // lv_label_set_text(label_B,"1 2 3 4 5 6 7 8 9 ");
    // lv_obj_set_align(label_B,LV_ALIGN_BOTTOM_MID);
    // lv_label_set_long_mode(label_B, LV_LABEL_LONG_SCROLL );
    // lv_obj_set_size(label_B,40,50);


}


void KeyBtn_OK()
{
    Btn_OK = lv_btn_create(lv_scr_act());
    lv_obj_t *Lable = lv_label_create(Btn_OK);

    lv_obj_set_size(Btn_OK,30,20);
    lv_obj_set_pos(Btn_OK,5,190);
    lv_obj_set_style_border_side(Btn_OK,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_OK,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_OK,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_OK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_OK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_OK,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    //lv_label_set_text(Lable,"OK");
    lv_label_set_text(Lable,LV_SYMBOL_OK);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    lv_obj_add_event_cb(Btn_OK, OKKeyProcess ,LV_EVENT_CLICKED,NULL);

}

void  KeyBtn_BACK()
{
    Btn_BACK = lv_btn_create(lv_scr_act());

    lv_obj_t *Lable = lv_label_create(Btn_BACK);

    lv_obj_set_size(Btn_BACK,30,20);
    lv_obj_set_pos(Btn_BACK,205,190);
    lv_obj_set_style_border_side(Btn_BACK,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_BACK,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_BACK,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_BACK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_BACK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_BACK,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Back");
    lv_label_set_text(Lable,LV_SYMBOL_CLOSE);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    lv_obj_add_event_cb(Btn_BACK, BackKeyProcess ,LV_EVENT_CLICKED,NULL);


}

void  KeyBtn_UP()
{
    Btn_UP = lv_btn_create(lv_scr_act());
    lv_obj_t *Lable = lv_label_create(Btn_UP);

    lv_obj_set_size(Btn_UP,30,20);
    lv_obj_set_pos(Btn_UP,5,215);
    lv_obj_set_style_border_side(Btn_UP,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_UP,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_UP,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_UP,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_UP,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_UP,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Up");
    lv_label_set_text(Lable,LV_SYMBOL_UP);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    lv_obj_add_event_cb(Btn_UP, UpKeyProcess ,LV_EVENT_CLICKED,NULL);
}




void  KeyBtn_DOWN()
{
    Btn_DOWN = lv_btn_create(lv_scr_act());
    lv_obj_t *Lable = lv_label_create(Btn_DOWN);

    lv_obj_set_size(Btn_DOWN,30,20);
    lv_obj_set_pos(Btn_DOWN,205,215);

    lv_obj_set_style_border_side(Btn_DOWN,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_DOWN,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_DOWN,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_DOWN,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_DOWN,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_DOWN,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Down");
    lv_label_set_text(Lable,LV_SYMBOL_DOWN);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    lv_obj_add_event_cb(Btn_DOWN, DownKeyProcess ,LV_EVENT_CLICKED,NULL);

}



void BackGroung()
{
    lv_obj_t *Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Bg,240,240);
    lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Bg,0,LV_PART_MAIN);
    // lv_obj_set_style_outline_color(Bg,lv_color_black(),LV_PART_MAIN);
    // lv_obj_set_style_outline_width(Bg,5,LV_PART_MAIN);
    // lv_obj_set_style_bg_grad_color(Bg, lv_palette_main(LV_PALETTE_GREY), 0);
    // lv_obj_set_style_bg_grad_dir(Bg, LV_GRAD_DIR_VER, 0);


//    lv_obj_t *boxPad = lv_canvas_create(lv_scr_act());
//    lv_obj_set_size(boxPad,20,20);



}





static void mask_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);        //获取事件
    lv_obj_t * obj = lv_event_get_target(e);            //获取当前事件

    static int16_t mask_top_id = -1;                    //定义顶部遮罩
    static int16_t mask_bottom_id = -1;                 //定义底部遮罩

    if (code == LV_EVENT_COVER_CHECK) {                 //事件覆盖检查
        lv_event_set_cover_res(e, LV_COVER_RES_COVER); //设置封面检查结果

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {      //执行主绘图
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);     //获取对象字体
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);//获取对象字体行间距
        lv_coord_t font_h = lv_font_get_line_height(font);  //获取行高

        lv_area_t roller_coords;                        //设置绘制区域变量
        lv_obj_get_coords(obj, &roller_coords);         //复制一个对象的坐标到一个区域

        lv_area_t rect_area;                            //设置绘制区域变量
        rect_area.x1 = roller_coords.x1;                //获取到x1的值
        rect_area.x2 = roller_coords.x2;                //获取到x2的值
        rect_area.y1 = roller_coords.y1;                //获取到y1的值
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;           //获取到y2的值

        lv_draw_mask_fade_param_t * fade_mask_top = lv_malloc(sizeof(lv_draw_mask_fade_param_t));  //绘制蒙版褪色参数 顶部

        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);     //初始化一个淡出遮罩。
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);        //添加一个顶部绘制蒙版

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;      //获取y1坐标
        rect_area.y2 = roller_coords.y2;                            //获取y2坐标

        lv_draw_mask_fade_param_t * fade_mask_bottom =lv_malloc(sizeof(lv_draw_mask_fade_param_t));//绘制蒙版褪色参数 底部
        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);  //初始化一个淡出遮罩。
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);  //添加一个顶部绘制蒙版

    } else if (code == LV_EVENT_DRAW_POST_END) {                    //完成post绘制阶段(当所有子元素都绘制时)
        lv_draw_mask_fade_param_t * fade_mask_top = lv_draw_mask_remove_id(mask_top_id);        //移除蒙版
        lv_draw_mask_fade_param_t * fade_mask_bottom = lv_draw_mask_remove_id(mask_bottom_id);  //移除蒙版
        lv_draw_mask_free_param(fade_mask_top);                     //释放参数中的数据。
        lv_draw_mask_free_param(fade_mask_bottom);                  //释放参数中的数据。
        lv_free(fade_mask_top);                          //手动释放内存
        lv_free(fade_mask_bottom);                       //手动释放内存
        mask_top_id = -1;
        mask_bottom_id = -1;
    }
}

/*************************************************
 *  函数名称 :  roller_show_3
 *  参    数 ： e
 *  函数功能 ： 滚动回调显示
 *************************************************/
void roller_show_3(void)
{
    static lv_style_t style;                            //创建样式变量
    lv_style_init(&style);                              //初始化样式
    lv_style_set_bg_color(&style, lv_color_black());    //设置背景颜色
    lv_style_set_text_color(&style, lv_color_white());  //设置字体颜色
    lv_style_set_border_width(&style, 1);               //设置边框宽度
    lv_style_set_border_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 2);                    //设置边距
    lv_style_set_text_font(&style, &lv_font_montserrat_12);

    lv_obj_t *roller1 = lv_roller_create(lv_scr_act()); //创建roller对象
    lv_obj_add_style(roller1, &style, 0);               //添加样式
    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);  //设置对象的透明度

    lv_roller_set_options(roller1,                      //设置对象选项
                            "1\n"
                            "2\n"
                            "3\n"
                            "4\n"
                            "5\n"
                            "6\n"
                            "7\n"
                            "8\n"
                            "9\n"
                            "10\n"
                            "11\n"
                            "12",
                            LV_ROLLER_MODE_INFINITE);

    lv_obj_center(roller1);
    lv_roller_set_visible_row_count(roller1, 8);        //设置对象间距
    lv_obj_set_size(roller1,100,70);
    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);   //设置回调
}



void ArcCB(lv_event_t *Event)
{
    int16_t Val;
    lv_event_code_t Code = lv_event_get_code(Event);

    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_VALUE_CHANGED)
    {
       Val = lv_arc_get_value(Target);
        printf("Val: %d !! \r\n",Val);

    }
}

void Arc_Btn()
{
    lv_obj_t *Arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(Arc,100,100);
    lv_obj_set_style_arc_width(Arc,5,0);
    lv_arc_set_angles(Arc,10,350);
    // lv_arc_set_bg_angles(Arc,15,245);
    // lv_arc_set_bg_start_angle();
    // lv_arc_set_bg_end_angle();
    // lv_arc_set_change_rate(Arc,500);
    // lv_arc_set_start_angle();
    // lv_arc_set_end_angle();
    // lv_arc_set_mode(Arc,LV_ARC_MODE_NORMAL);
    lv_arc_set_range(Arc,10,500);
    // lv_arc_set_rotation(Arc,90);
    lv_arc_set_value(Arc,255);
    lv_obj_set_style_arc_color(Arc,lv_palette_main( LV_PALETTE_PINK),LV_PART_KNOB);
    lv_obj_set_style_arc_color(Arc,lv_palette_main( LV_PALETTE_GREEN),LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(Arc,lv_palette_main( LV_PALETTE_YELLOW),LV_PART_MAIN);
    // lv_obj_set_style_arc_img_src(Arc,10,LV_PART_INDICATOR);
    // lv_obj_set_style_arc_opa(Arc,LV_OPA_50,LV_PART_KNOB);
    // lv_obj_set_style_arc_rounded(Arc,100,0);

    lv_obj_add_event_cb(Arc,ArcCB,LV_EVENT_VALUE_CHANGED,NULL);
    lv_obj_center(Arc);
}




void BarCB(lv_event_t *Event)
{

   static int16_t Val =5;
    lv_event_code_t Code = lv_event_get_code(Event);

    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        Val++;
        lv_bar_set_value(Target,Val,LV_ANIM_ON);
        printf("Val: %d !! \r\n",Val);
    }

}


void BarTest()
{
    lv_obj_t *Bar = lv_bar_create(lv_scr_act());

    lv_bar_set_range(Bar,10,100);
    lv_obj_set_size(Bar, 200, 20);
    // lv_bar_set_start_value(Bar,10,LV_ANIM_ON);
    lv_bar_set_value(Bar,50,LV_ANIM_ON);

    lv_bar_set_mode(Bar,LV_BAR_MODE_NORMAL);
    lv_obj_center(Bar);

    lv_obj_add_event_cb(Bar,BarCB,LV_EVENT_CLICKED,NULL);
}


void CheckBoxCB(lv_event_t *Event)
{

   static int16_t Val =5;
    lv_event_code_t Code = lv_event_get_code(Event);

    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        Val++;
        lv_bar_set_value(Target,Val,LV_ANIM_ON);
        printf("Val: %d !! \r\n",Val);
    }

}




void CheckBox()
{
    lv_obj_t *Box = lv_checkbox_create(lv_scr_act());
    lv_checkbox_set_text(Box,"123456");
}


void SliderTest()
{
    lv_obj_t *Slider= lv_slider_create(lv_scr_act());
    lv_obj_set_size(Slider,200,15);
    lv_slider_set_mode(Slider,LV_SLIDER_MODE_SYMMETRICAL);

    lv_obj_set_style_bg_color(Slider,lv_palette_main( LV_PALETTE_PINK),LV_PART_KNOB);
    lv_obj_set_style_bg_color(Slider,lv_palette_main( LV_PALETTE_GREEN),LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(Slider,lv_palette_main( LV_PALETTE_YELLOW),LV_PART_MAIN);
    lv_obj_set_style_shadow_color(Slider,lv_palette_main( LV_PALETTE_RED ),LV_PART_INDICATOR);
    lv_obj_set_style_shadow_spread(Slider,50,LV_PART_INDICATOR);//渐变展开范围，应小于宽度
    lv_obj_set_style_shadow_opa(Slider,LV_OPA_60,LV_PART_INDICATOR);
    lv_obj_set_style_shadow_width(Slider,100,LV_PART_INDICATOR);//阴影宽度


    lv_obj_center(Slider);

}




void SwitchTest()
{
    lv_obj_t *Switch= lv_switch_create(lv_scr_act());

    lv_obj_set_size(Switch,50,30);
    lv_obj_set_style_bg_color(Switch,lv_palette_main( LV_PALETTE_GREEN),LV_PART_KNOB);
    lv_obj_set_style_bg_color(Switch,lv_palette_main( LV_PALETTE_YELLOW),LV_PART_MAIN);
    lv_obj_set_style_bg_color(Switch,lv_palette_main( LV_PALETTE_PINK),LV_PART_INDICATOR);

    lv_obj_set_style_shadow_color(Switch,lv_palette_main( LV_PALETTE_RED ),LV_PART_INDICATOR);
    lv_obj_set_style_shadow_spread(Switch,5,LV_PART_INDICATOR);//渐变展开范围，应小于宽度
    lv_obj_set_style_shadow_opa(Switch,LV_OPA_60,LV_PART_INDICATOR);
    lv_obj_set_style_shadow_width(Switch,10,LV_PART_INDICATOR);//阴影宽度
    lv_obj_center(Switch);
}





// static lv_obj_t * meter;
// static void set_value(void * indic, int32_t v)
// {
//     lv_meter_set_indicator_end_value(meter, indic, v);
// }
// void MeterTest()
// {
//     meter = lv_meter_create(lv_scr_act());
//     lv_obj_center(meter);
//     lv_obj_set_size(meter, 200, 200);

//     /*Remove the circle from the middle*/
//     lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

//     /*Add a scale first*/
//     lv_meter_scale_t * scale = lv_meter_add_scale(meter);
//     lv_meter_set_scale_ticks(meter, scale, 10, 2, 10, lv_palette_main(LV_PALETTE_RED));
//     lv_meter_set_scale_major_ticks(meter, scale, 2, 5, 20, lv_palette_main(LV_PALETTE_BLUE), 20);
//     lv_meter_set_scale_range(meter, scale, 0, 180, 180, 90);


//     // /*Add a three arc indicator*/
//     lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, scale, 5, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_meter_indicator_t * indic2 = lv_meter_add_arc(meter, scale, 5, lv_palette_main(LV_PALETTE_GREEN), 5);
//     lv_meter_indicator_t * indic3 = lv_meter_add_arc(meter, scale, 5, lv_palette_main(LV_PALETTE_BLUE), 10);

//     lv_img_dsc_t *dsc = lv_img_create(meter);
//     lv_meter_add_needle_line(meter, scale,2,lv_palette_main(LV_PALETTE_RED),1);
//     lv_meter_add_needle_img(meter,scale,dsc,0,0);
//     lv_meter_set_

//     // /*Create an animation to set the value*/
//     // lv_anim_t a;
//     // lv_anim_init(&a);
//     // lv_anim_set_exec_cb(&a, set_value);
//     // lv_anim_set_values(&a, 0, 100);
//     // lv_anim_set_repeat_delay(&a, 100);
//     // lv_anim_set_playback_delay(&a, 100);
//     // lv_anim_set_repeat_count(&a, LV_ANIM_PLAYTIME_INFINITE);

//     // lv_anim_set_time(&a, 2000);
//     // lv_anim_set_playback_time(&a, 500);
//     // lv_anim_set_var(&a, indic1);
//     // lv_anim_start(&a);

//     // lv_anim_set_time(&a, 1000);
//     // lv_anim_set_playback_time(&a, 1000);
//     // lv_anim_set_var(&a, indic2);
//     // lv_anim_start(&a);

//     // lv_anim_set_time(&a, 1000);
//     // lv_anim_set_playback_time(&a, 2000);
//     // lv_anim_set_var(&a, indic3);
//     // lv_anim_start(&a);

// }







static lv_obj_t * meter;
static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
    printf("%d \r\n",v);
}

void lv_meter_1(void)
{
    meter = lv_meter_create(lv_scr_act());
    lv_obj_center(meter);
    lv_obj_set_size(meter, 240, 240);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 51, 2, 10, lv_palette_main(LV_PALETTE_GREEN));
    lv_meter_set_scale_major_ticks(meter, scale, 5, 4, 15, lv_color_white(), 10);
    lv_obj_set_style_text_color(meter,lv_palette_main(LV_PALETTE_GREEN),0);
    lv_obj_set_style_bg_color(meter,lv_color_black(),0);

    lv_obj_set_style_bg_color(meter,lv_color_white(),LV_PART_INDICATOR);

    lv_meter_indicator_t * indic;

    /*Add a blue arc to the start*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 10);

    /*Make the tick lines blue at the start of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 1);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 10);

    /*Add a red arc to the end*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Make the tick lines red at the end of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 1);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_CYAN), -5);


    lv_obj_t *lable = lv_label_create(meter);
    lv_label_set_text(lable,"Speed");
    lv_obj_align(lable,LV_ALIGN_BOTTOM_MID,0,-50);
    lv_obj_set_style_text_color(lable,lv_palette_main(LV_PALETTE_BLUE),0);


    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_var(&a, indic);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_time(&a, 5000);
    lv_anim_set_repeat_delay(&a, 300);
    lv_anim_set_playback_time(&a, 1000);
    lv_anim_set_playback_delay(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}


void CB(lv_event_t * e)
{

}



void QQQQQ(void)
{
    static lv_style_t style_bg;
    static lv_style_t style_indic;

    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_border_width(&style_bg, 2);
    lv_style_set_pad_all(&style_bg, 6); /*To make the indicator smaller*/
    lv_style_set_radius(&style_bg, 6);
    lv_style_set_anim_time(&style_bg, 1000);

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main( LV_PALETTE_RED));
    lv_style_set_radius(&style_indic, 3);

    lv_obj_t * bar = lv_bar_create(lv_scr_act());
    lv_obj_remove_style_all(bar);  /*To have a clean start*/
    lv_obj_add_style(bar, &style_bg,  LV_PART_MAIN );
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);

    lv_obj_set_size(bar, 200, 20);
    lv_obj_center(bar);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);
    lv_obj_add_event_cb(bar,CB,LV_EVENT_CLICKED,NULL);
}



void QR_UI()
{

    lv_obj_t *UI = lv_obj_create(lv_scr_act());
    lv_obj_t *QR = lv_qrcode_create(UI,100,lv_color_black(),lv_color_white());
    lv_qrcode_update(QR,"12346798",8);
}







static void scroll_event_cb(lv_event_t * e)
{
    //>>>>>>>>>>>-----------------<!>---Link
    ///E1.----------------------------得到容器
    lv_obj_t * cont = lv_event_get_target(e); //通过绑定了该事件的对象，来获取这个对象

    ///E2.---------------------------通过一定算法，得到容器的y轴中心位置（目的：用于后面与子元素按钮进行y轴中心偏差比较）
    lv_area_t cont_a; //区域 cont_area
    lv_obj_get_coords(cont, &cont_a); //将cont的坐标赋值给cont_a (将cont_a约束为container的大小（200 * 200)  coords：坐标(x1,y1); (x2,y1); (x1,y2); (x2,y2)

    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2; //获取Container的y轴中心

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10; // 200*7 / 10 = 140

    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont); //child_cnt : child count 儿子数量 获取container里面元素个数

    ///E3.------------------遍历容器里面的子元素（按钮），以便操作这些元素的属性（用户垂直滚动时候，按钮发生水平偏移，并且设置不同的透明度）
    for(i = 0; i < child_cnt; i++)  //遍历Buttons
    {
        lv_obj_t * child = lv_obj_get_child(cont, i); //获取container的第i个button
        lv_area_t child_a; //创建一个属于儿子区域
        lv_obj_get_coords(child, &child_a); //将child_a约束为button的大小（200 * 200）
        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2; //计算得到button的y轴中心

        lv_coord_t diff_y = child_y_center - cont_y_center; // button的y轴中心 - Container的y轴中心 = Button相对于Container的垂直偏差
        diff_y = LV_ABS(diff_y); // 对偏差取绝对值（ABS）

        ///E3.1------------------根据偏差（按钮相对于容器的y方向中心位置）来产生不同的x值
        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) // diff_y >= 140
        {
            x = r; //x = 140
        }
        else     // diff_y < 140
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y; // 140 * 140  - diff_y的平方
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }
        ///E3.2--------------------根据x值，将button移动x个单位距离，根据r映射出不同的透明度值，设置按钮不同透明度
        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0); //将button 移动 x个单位距离

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);  //通过r的不同值，动态映射创建不透明度值 opa: opacity
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0); //给按钮应用不透明度值  opa: opacity
    }
}


void lv_example_soll_6(void)
{

    Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Bg,240,240);
    lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Bg,0,LV_PART_MAIN);

    ///祖父对象
    //lv_obj_t *screenA = lv_scr_act();
    ///父对象
    lv_obj_t * cont = lv_obj_create(lv_scr_act()); //在屏幕上创建一个container
    lv_obj_set_size(cont, 200, 200); //设置cont的尺寸： w200, h200  （正方形）
    lv_obj_set_style_bg_color(cont,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(cont,3,LV_PART_MAIN);
    lv_obj_set_style_border_color(cont,lv_color_white(),LV_PART_MAIN);
    lv_obj_center(cont);//让cont垂直水平居中（相对于父级）
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN );//设置cont的子级的layout: 弹性布局弹性流（flex-flow）(布局+滚动功能)
    ///对象的特性
    //1.添加事件 // Link---<!>----------------------------------->>>>>>>>>>>>
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);//给cont添加event，事件的回调函数、事件类型（Scroll）
    //2.设置样式
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0); //设置矩形圆角 LV_RADIUS_CIRCLE：圆角最大化
    lv_obj_set_style_clip_corner(cont, true, 0); //儿子超出部分隐藏
    lv_obj_set_scroll_dir(cont, LV_DIR_VER); //设置Scroll的允许方向direction：垂直方向
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER); //捕捉Cont Y方向的子对象，将他们与Container中心对齐 ； snap ：捕获；捕捉
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_ACTIVE);//隐藏scrollbar

    ///子对象
    uint32_t i;
    ///在container上创建若干个button

    lv_group_t *Group = lv_group_create();

    for(i = 0; i < 20; i++)
    {
        lv_obj_t * btn = lv_btn_create(cont); //在container上创建button
        lv_obj_set_width(btn, lv_pct(50)); //设置button的width = lv_pct(100); //pct : percentage 相对于父亲的宽度100%

        ///孙对象
        lv_obj_t * label = lv_label_create(btn); //在button上创建一个label（标签）
        lv_label_set_text_fmt(label, "Button %d", i);  //动态设置label的文本内容  fmt: format（格式）
        lv_group_add_obj(Group,btn);
    }

    lv_indev_set_group(lv_win32_encoder_device_object,Group);
    /*Update the buttons position manually for first*/ //首次手动更新按钮的位置
    lv_event_send(cont, LV_EVENT_SCROLL, NULL); //TODO

    /*Be sure the fist button is in the middle*/ //确保第一个按钮处于中间
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_ON); //第一个按钮是否以滚动动画，滚动到指定位置（默认位置）
}







// static void anim_x_cb(void * var, int32_t v)
// {
//     lv_obj_set_x(var, v);
// }

// static void sw_event_cb(lv_event_t * e)
// {
//     lv_obj_t * sw = lv_event_get_target(e);
//     lv_obj_t * label = lv_event_get_user_data(e);

//     if(lv_obj_has_state(sw, LV_STATE_CHECKED))
//     {
//         lv_anim_t a;
//         lv_anim_init(&a);
//         lv_anim_set_var(&a, label);
//         lv_anim_set_values(&a, lv_obj_get_x(label), 100);
//         lv_anim_set_time(&a, 500);
//         lv_anim_set_exec_cb(&a, anim_x_cb);
//         lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
//         lv_anim_start(&a);
//     }
//     else
//     {
//         lv_anim_t a;
//         lv_anim_init(&a);
//         lv_anim_set_var(&a, label);
//         lv_anim_set_values(&a, lv_obj_get_x(label), -lv_obj_get_width(label));
//         lv_anim_set_time(&a, 500);
//         lv_anim_set_exec_cb(&a, anim_x_cb);
//         lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
//         lv_anim_start(&a);
//     }

// }

// /**
//  * Start animation on an event
//  */
// void lv_example_anim_1(void)
// {
//     lv_obj_t * label = lv_label_create(lv_scr_act());
//     lv_label_set_text(label, "Hello animations!");
//     lv_obj_set_pos(label, 100, 10);


//     lv_obj_t * sw = lv_switch_create(lv_scr_act());
//     lv_obj_center(sw);
//     lv_obj_add_state(sw, LV_STATE_CHECKED);
//     lv_obj_add_event_cb(sw, sw_event_cb, LV_EVENT_VALUE_CHANGED, label);
// }




//***************************************************//
//  功能描述: LVGL UI绘制
//
//  参数: 无
//
//  返回值: 无
//
//  说明: 无
//
//***************************************************//
EXTERN_C lv_indev_t* lv_win32_encoder_device_object;
static void LVGL_Build_GUI()
{
    BackGroung();
    KeyBtn_OK();
    KeyBtn_BACK();
    KeyBtn_UP();
    KeyBtn_DOWN();
    // Arc_Btn();
    // BarTest();
    Botton();
    //CheckBox();
    // LineTest();
    //SliderTest();
    // SwitchTest();
    // MeterTest();
    // lv_meter_1();
    //AniTest();
    // roller_show_3();
    // QQQQQ();
    // QR_UI();

    lv_group_t *Group = lv_group_create();
    lv_group_add_obj(Group,Btn_OK);
    lv_group_add_obj(Group,Btn_BACK);
    lv_group_add_obj(Group,Btn_DOWN);
    lv_group_add_obj(Group,Btn_UP);
    lv_group_add_obj(Group,Btn);
    lv_indev_set_group(lv_win32_encoder_device_object,Group);

}


void GroupTest()
{
    lv_group_t *Group = lv_group_create();

    Btnnew = lv_btn_create(lv_scr_act());

    lv_obj_t *Lable = lv_label_create(Btnnew);

    lv_obj_set_size(Btnnew,50,30);
    lv_obj_center(Btnnew);
   // lv_obj_set_pos(Btnnew,205,215);

    lv_obj_set_style_border_side(Btnnew,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btnnew,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_DOWN,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_DOWN,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_DOWN,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_DOWN,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Down");
    lv_label_set_text(Lable,LV_SYMBOL_DOWN);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    lv_group_add_obj(Group,Btnnew);
   // lv_obj_add_event_cb(Btnnew, DownKeyProcess ,LV_EVENT_CLICKED,NULL);
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







#if 1

static void sw_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e); // 获取事件code
    lv_obj_t* sw = lv_event_get_target(e);   //获取目标事件对象
    if (code == LV_EVENT_VALUE_CHANGED) {   //值改变事件
        lv_obj_t* list = lv_event_get_user_data(e);  //获取事件用户数据
        if (lv_obj_has_state(sw, LV_STATE_CHECKED))
        	lv_obj_add_flag(list, LV_OBJ_FLAG_SCROLL_ONE); // 开启滚动一屏功能
        else
        	lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLL_ONE);// 关闭滚动一屏功能

    }

}

static void lv_example_scroll_2(void)
{
    lv_obj_t* panel = lv_obj_create(lv_scr_act()); //创建当前活动界面对象
    lv_obj_set_size(panel, 240, 120);  // 设置大小
    lv_obj_set_scroll_snap_x(panel, LV_SCROLL_SNAP_CENTER); //设置x方向滚动snap特性
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW); // 设置LV_FLEX_FLOW_ROW方式
    lv_obj_align(panel, LV_ALIGN_CENTER, 0, 20); //x居中，y居中向下20像素对齐
    uint32_t i;
    for (i = 0; i < 10; i++)
    {
        lv_obj_t* btn = lv_btn_create(panel);  // 创建button对象
        lv_obj_set_size(btn, 150,lv_pct(100)); //设置大小
        lv_obj_t* label = lv_label_create(btn); //创建label
        if (i == 3) {
            lv_label_set_text_fmt(label, "Panel %d\nno snap", i); //设置文字内容
            lv_obj_clear_flag(btn, LV_OBJ_FLAG_SNAPPABLE); //清除snap特性
        }
        else {
            lv_label_set_text_fmt(label, "Panel %d", i); //设置文字内容
        }
        lv_obj_center(label); //居中显示
    }
    lv_obj_update_snap(panel, LV_ANIM_ON); //开启snap动画
#if LV_USE_SWITCH
    /*Switch between "One scroll" and "Normal scroll" mode*/
    lv_obj_t* sw = lv_switch_create(lv_scr_act()); // 创建switch对象
    lv_obj_align(sw, LV_ALIGN_TOP_RIGHT, -20, 10); // 顶部右对齐
    lv_obj_add_event_cb(sw, sw_event_cb, LV_EVENT_ALL, panel); // 开关事件设置
    lv_obj_t* label = lv_label_create(lv_scr_act());  // 创建label
    lv_label_set_text(label, "One scroll"); // 显示文字
    lv_obj_align_to(label, sw, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);// 对齐到switch开关
#endif
}




static void scroll_end_event(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);                                               // 获取事件的初始对象

    /* 获取事件的事件代码 */
    if(lv_event_get_code(e) == LV_EVENT_SCROLL_END)
    {
        /* 判断是否在滚动中 */
        if (lv_obj_is_scrolling(cont))
        {
            return;
        }

        lv_coord_t child_cnt = lv_obj_get_child_cnt(cont);                                  // 获取子界面的数量
        lv_coord_t mid_btn_index = (child_cnt - 1) / 2;                                     // 中间界面的位置

        /* 获取父对象y轴的中心坐标值 */
        lv_area_t cont_a;
        lv_obj_get_coords(cont, &cont_a);                                                   // 将cont对象的坐标复制到cont_a
        lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_width(&cont_a) / 2;              // 获取界面的宽像素大小/2

        /* 注意，这里的中心显示界面的坐标不在正中心，所以这里加上了差值 */
        cont_y_center += 69;

        /* 遍历子界面 */
        for (lv_coord_t i = 0; i < child_cnt; i++) {
            lv_obj_t* child = lv_obj_get_child(cont, i);                                    // 通过索引获取子对象

            /* 获取子对象y轴的中心坐标值 */
            lv_area_t child_a;
            lv_obj_get_coords(child, &child_a);
            lv_coord_t child_y_center = child_a.y1 + lv_area_get_width(&child_a) / 2;       // 获取界面中按钮宽像素值的大小/2
            /* 子界面的坐标与父界面的坐标相等时，说明当前界面在父界面中显示 */
            if (child_y_center == cont_y_center)
            {
                /* 当前显示界面的索引 */
                lv_coord_t current_btn_index = lv_obj_get_index(child);

                /* 判断界面移动的数数据，并将当前界面的索引改为中间位置 */
                /* 因为是在滑动结束后实现的，建议界面较多的情况下使用此方式，当界面较少，一次滑动太多界面时，容易滑倒边界出现卡顿现象 */
                lv_coord_t move_btn_quantity = LV_ABS(current_btn_index - mid_btn_index);
                for (lv_coord_t j = 0; j < move_btn_quantity; j++)
                {
                    /* 向右滑动 */
                    if (current_btn_index < mid_btn_index)
                    {
                        lv_obj_move_to_index(lv_obj_get_child(cont, child_cnt - 1), 0);                     // 将最后一个界面索引改为第一个界面
                        lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);          // lv_obj_get_child 通过子索引获取对象的子对象
                    }
                    /* 向左滑动 */
                    if (current_btn_index > mid_btn_index)
                    {
                        lv_obj_move_to_index(lv_obj_get_child(cont, 0), child_cnt - 1);                     // 将第一个界面的索引值改为最后一个界面
                        lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);          // lv_obj_get_child 通过子索引获取对象的子对象
                    }
                }
                /* 保证界面居中显示 */
                lv_obj_set_style_translate_y(lv_obj_get_child(cont, mid_btn_index), 0, 0);
                break;
            }
        }
    }
}

static void scroll_event_cb(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for(i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) {
            x = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

/**
 * Translate the object as they scroll
 */
void lvgl_scroll_test(void)
{
    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 200, 200);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);

    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);       // 为了方便实现，先把滚动的动画屏蔽
    lv_obj_add_event_cb(cont, scroll_end_event, LV_EVENT_SCROLL_END, NULL);

    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    uint32_t i;
    for(i = 0; i < 20; i++)
    {
        lv_obj_t * btn = lv_btn_create(cont);
        lv_obj_set_width(btn, lv_pct(100));

        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Button %"LV_PRIu32, i);
    }

    /*---------------------------------------- 指定中心显示界面 ----------------------------------------*/
    lv_coord_t mid_btn_index = (lv_obj_get_child_cnt(cont) - 1) / 2;                   // 如果界面为偶数，将中间数向下取整的界面设置为中间界面
    lv_coord_t child_cnt = lv_obj_get_child_cnt(cont);                                 // 获取子界面的数量

    int roll_direction = mid_btn_index - mid_btn_index;                                      // 确定滚动方向

    /* 通过循环将指定界面移到中心位置 */
    for (lv_coord_t i = 0; i < LV_ABS(roll_direction); i++)
    {
        if (roll_direction > 0)
        {
            lv_obj_move_to_index(lv_obj_get_child(cont, child_cnt - 1), 0);            // 将最后一个界面的索引更改为 0 （移至第一个界面）
        }
        else
        {
            lv_obj_move_to_index(lv_obj_get_child(cont, 0), child_cnt - 1);            // 将第一个界面的索引值改为最大值（移至最后一个界面）
        }
    }

    /*当按钮数为偶数时，确保按钮居中*/
    lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);         // 滚动到一个对象，直到它在其父对象上可见
}




#endif




#if 0

#define UI_SIZE    (100)



lv_obj_t *Arc_Out;
lv_obj_t *ALL_Bg;
lv_obj_t *Arc_In;
lv_obj_t *Center;
lv_group_t *Group;
lv_anim_t Anima;
lv_obj_t *Btn;
lv_obj_t *Btn_Start;
lv_obj_t *text,*Atext;
BarState_e BarState = Charing;


void BarAnimation_CB(void * var, int32_t v)
{
    printf(" BarAnim Val: %d \r\n",v);

    if( BarState != InRelease)
    {
        lv_obj_set_style_arc_width(Arc_Out,10-v,LV_PART_MAIN);
    }
    else
    {
        lv_arc_set_value(Arc_In,100 - v);

        if(v == 100)
        {
            lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
        }
    }
    lv_label_set_text_fmt(text,"%d%s",lv_arc_get_value(Arc_In),"%");
}



void Btn_CB(lv_event_t *e)
{
    printf(" Btn_CB \r\n");
    if( lv_event_get_code(e) == LV_EVENT_PRESSED)
    {
        if( BarState == Full)
        {
            lv_anim_set_values(&Anima,0,100);
            lv_anim_set_time(&Anima, 3000);
            lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
            lv_anim_set_repeat_count(&Anima, 1);
            lv_anim_start(&Anima);
            lv_obj_add_flag(Arc_Out,LV_OBJ_FLAG_HIDDEN);

            lv_group_add_obj(Group,Arc_In);
            lv_group_focus_obj(Arc_In);
            lv_group_remove_obj(Btn);

            BarState = InRelease;
        }

    }
}


void Arc_Out_CB(lv_event_t *e)
{
    printf(" Arc_Out_CB \r\n");

    if(lv_arc_get_value(Arc_In) == 100)
    {
        lv_obj_clear_flag(Btn,LV_OBJ_FLAG_HIDDEN);
    }

}

void Arc_In_CB(lv_event_t *e)
{
    int16_t Arc_Val=0;

    Arc_Val = lv_arc_get_value(Arc_In);

    printf("Angle %d  State  %d\r\n",Arc_Val,BarState);

    if( Arc_Val == 100)
    {
        lv_obj_set_style_arc_color(Arc_In,lv_palette_main( LV_PALETTE_YELLOW),LV_PART_INDICATOR);
        lv_group_add_obj(Group,Btn);
        lv_group_focus_obj(Btn);
        lv_group_remove_obj(Arc_In);
        BarState = Full;
    }

    if(Arc_Val == 1)
    {
        lv_obj_set_style_arc_color(Arc_In,lv_palette_main( LV_PALETTE_BLUE),LV_PART_INDICATOR);
        lv_obj_clear_flag(Arc_Out,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
        BarState = Charing;
    }

    lv_arc_set_bg_angles(Arc_Out,lv_arc_get_angle_start(Arc_In),lv_arc_get_angle_end(Arc_In));

    switch (BarState)
    {
        case Charing:
                lv_anim_set_var(&Anima,Arc_Out);
                lv_anim_set_values(&Anima,0,10);
                lv_anim_set_time(&Anima, 500);
                lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
                lv_anim_set_repeat_count(&Anima, 1);
                lv_anim_start(&Anima);
            break;
        case Full:
                lv_anim_set_values(&Anima,0,10);
                lv_anim_set_time(&Anima, 500);
                lv_anim_set_repeat_delay(&Anima, 500);
                lv_anim_set_repeat_count(&Anima, LV_ANIM_PLAYTIME_INFINITE);
                lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
                lv_anim_start(&Anima);
            break;
        case InRelease:
            break;
        default:
            break;
    }

}

void StateBar()
{

    //创建背景
    ALL_Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ALL_Bg,240,240);
    lv_obj_set_style_bg_color(ALL_Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(ALL_Bg,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(ALL_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(ALL_Bg,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(ALL_Bg,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(ALL_Bg,LV_SCROLLBAR_MODE_OFF);


    Arc_Out =lv_arc_create(ALL_Bg);
    lv_obj_set_size(Arc_Out,UI_SIZE,UI_SIZE);
    lv_obj_set_style_arc_color(Arc_Out,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_arc_opa(Arc_Out,LV_OPA_50,LV_PART_MAIN);
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_KNOB);//删除把手
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_INDICATOR);//删除进度条
    lv_obj_set_style_arc_rounded(Arc_Out,0,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_Out,10,LV_PART_MAIN);
    lv_arc_set_value(Arc_Out,0);
    lv_obj_align(Arc_Out,LV_ALIGN_BOTTOM_LEFT,-5,10);
    lv_obj_add_event_cb(Arc_Out,Arc_Out_CB,LV_EVENT_DRAW_MAIN_END,NULL);

    Arc_In =lv_arc_create(ALL_Bg);
    lv_obj_set_size(Arc_In,UI_SIZE-25,UI_SIZE-25);
    lv_obj_align_to(Arc_In,Arc_Out,LV_ALIGN_CENTER,0,0);
    lv_obj_set_style_arc_color(Arc_In,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_arc_opa(Arc_In,LV_OPA_50,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_In,5,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_In,5,LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(Arc_In,0,LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(Arc_In,0,LV_PART_INDICATOR);
    lv_arc_set_value(Arc_In,0);
    lv_obj_remove_style(Arc_In, NULL, LV_PART_KNOB);
    lv_obj_add_event_cb(Arc_In,Arc_In_CB,LV_EVENT_VALUE_CHANGED,NULL);
    lv_arc_set_bg_angles(Arc_Out,lv_arc_get_angle_start(Arc_In),lv_arc_get_angle_end(Arc_In));


    Center = lv_obj_create(ALL_Bg);
    lv_obj_set_size(Center,UI_SIZE-45,UI_SIZE-45);
    lv_obj_set_style_radius(Center,LV_RADIUS_CIRCLE,0);
    lv_obj_set_style_bg_opa(Center,LV_OPA_50,LV_PART_MAIN);
    lv_obj_set_style_bg_color(Center,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_border_width(Center,0,LV_PART_MAIN);
    lv_obj_align_to(Center,Arc_In,LV_ALIGN_CENTER,0,0);


    text = lv_label_create(ALL_Bg);
    lv_obj_set_style_text_color(text,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_text_opa(text,LV_OPA_COVER,LV_PART_MAIN);
    lv_label_set_text_fmt(text,"%d%s",lv_arc_get_value(Arc_In),"%");
    lv_obj_set_style_text_font(text,&lv_font_montserrat_10,LV_PART_MAIN);
    lv_obj_align_to(text,Center,LV_ALIGN_BOTTOM_MID,-3,15);


    Btn = lv_btn_create(ALL_Bg);
    Btn_Start = lv_label_create(Btn);
    lv_obj_set_size(Btn,8,10);
    lv_obj_set_style_radius(Btn,0,LV_PART_MAIN);
    lv_label_set_text(Btn_Start,"V");
    lv_obj_set_style_text_font(Btn_Start,&lv_font_montserrat_10,LV_PART_MAIN);
    lv_obj_align(Btn_Start,LV_ALIGN_CENTER,0,0);
    lv_obj_add_event_cb(Btn,Btn_CB,LV_EVENT_PRESSED,NULL);
    lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
    lv_obj_align_to(Btn,Arc_In,LV_ALIGN_BOTTOM_RIGHT,-13,0);


    Atext = lv_label_create(ALL_Bg);
    lv_obj_set_style_text_color(Atext,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_flex_flow(Center,LV_FLEX_FLOW_ROW,LV_PART_MAIN);
    lv_label_set_text_fmt(Atext,LV_SYMBOL_DOWN"\n"LV_SYMBOL_DOWN"\n"LV_SYMBOL_DOWN);
    lv_obj_set_style_text_font(Atext,&lv_font_montserrat_10,LV_PART_MAIN);
    lv_obj_align_to(Atext,Center,LV_ALIGN_CENTER,0,0);


    lv_anim_init(&Anima);

    Group = lv_group_create();
    lv_group_add_obj(Group,Arc_In);
    lv_indev_set_group(lv_win32_encoder_device_object,Group);

}

#endif






lv_obj_t *ui_ImageN[24];
lv_anim_t Indec;


static void Eye_BodyAnimPath_CB(void *var, int32_t v)
{
    uint8_t i;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;

    for ( i = 0; i < v; i++)
    {
        lv_obj_clear_flag(ui_ImageN[i], LV_OBJ_FLAG_HIDDEN);      /// Flags
    }
    printf("%d\r\n",v);
}







    for (i = 0; i < 24; i++)
    {
        ui_ImageN[i] = lv_img_create(ui_Screen1);
        lv_img_set_src(ui_ImageN[i], &ui_img_akf_png);
        lv_obj_set_width(ui_ImageN[i], LV_SIZE_CONTENT);   /// 27
        lv_obj_set_height(ui_ImageN[i], LV_SIZE_CONTENT);    /// 92
        lv_obj_set_x(ui_ImageN[i], -15);
        lv_obj_set_y(ui_ImageN[i], -63);
        lv_obj_set_align(ui_ImageN[i], LV_ALIGN_CENTER);
        lv_obj_add_flag(ui_ImageN[i], LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
        lv_obj_clear_flag(ui_ImageN[i], LV_OBJ_FLAG_SCROLLABLE);      /// Flags
        lv_img_set_pivot(ui_ImageN[i], 27, 109);
        lv_img_set_angle(ui_ImageN[i], (i+1)*150);
        lv_obj_add_flag(ui_ImageN[i], LV_OBJ_FLAG_HIDDEN);     /// Flags
    }

    lv_anim_init(&Indec);
    lv_anim_set_var(&Indec,ui_ImageN);
    lv_anim_set_values(&Indec,0,24);
    lv_anim_set_time(&Indec, 24000);
    lv_anim_set_delay(&Indec,100);
    lv_anim_set_exec_cb(&Indec, Eye_BodyAnimPath_CB);
    lv_anim_set_path_cb(&Indec,lv_anim_path_linear);
    lv_anim_set_repeat_delay(&Indec,1000);
    lv_anim_set_repeat_count(&Indec, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&Indec);






