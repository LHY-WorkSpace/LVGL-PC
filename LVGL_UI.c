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
lv_obj_t *Bg;
lv_obj_t *Btn;


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

    if( Code == LV_EVENT_CLICKED)
    {
        printf("OK !! \r\n");
        // lv_obj_set_style_bg_color(Bg,lv_color_white(),LV_PART_MAIN);
        lv_obj_clear_flag(Btn,LV_OBJ_FLAG_HIDDEN);
    }
}


void DownKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        printf("Down !! \r\n");
        // lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_GREEN),LV_PART_MAIN);
    }
}

void UpKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        printf("Up !! \r\n");
        // lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_BLUE),LV_PART_MAIN);
        // lv_obj_add_flag(Roll,LV_OBJ_FLAG_SCROLL_ONE);
    }
}

void BackKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        printf("Back !! \r\n");
        // lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
        lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
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
    lv_obj_set_style_border_width(Btn,3,LV_PART_MAIN);
    lv_obj_set_style_shadow_color(Btn,lv_color_black(),0);
    lv_obj_set_style_shadow_ofs_x(Btn,3,0);
    lv_obj_add_flag(Btn,LV_OBJ_FLAG_CHECKABLE);
    // lv_obj_add_event_cb(Btn,Btn_Handle,LV_EVENT_ALL,NULL);

    lv_obj_t *label_A = lv_label_create(Btn);
    lv_label_set_text(label_A,"1 2 3 4 5 6 7 8 9 ");
    lv_obj_set_align(label_A,LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(label_A, LV_LABEL_LONG_SCROLL );
    lv_obj_set_size(label_A,40,50);


    lv_obj_t *label_B = lv_label_create(Btn);
    lv_label_set_text(label_B,"1 2 3 4 5 6 7 8 9 ");
    lv_obj_set_align(label_B,LV_ALIGN_BOTTOM_MID);
    lv_label_set_long_mode(label_B, LV_LABEL_LONG_SCROLL );
    lv_obj_set_size(label_B,40,50);

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
    Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Bg,240,240);
    lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Bg,0,LV_PART_MAIN);
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
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED); //设置封面检查结果

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
    lv_style_set_border_width(&style, 0);               //设置边框宽度
    lv_style_set_pad_all(&style, 0);                    //设置边距
    lv_obj_add_style(lv_scr_act(), &style, 0);          //添加样式

    lv_obj_t *roller1 = lv_roller_create(lv_scr_act()); //创建roller对象
    lv_obj_add_style(roller1, &style, 0);               //添加样式
    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);  //设置对象的透明度

    lv_obj_set_style_text_font(roller1, &lv_font_montserrat_12, LV_PART_SELECTED);  //设置对象字体

    lv_roller_set_options(roller1,                      //设置对象选项
                        "January\n"
                        "February\n"
                        "March\n"
                        "April\n"
                        "May\n"
                        "June\n"
                        "July\n"
                        "August\n"
                        "September\n"
                        "October\n"
                        "November\n"
                        "December",
                        LV_ROLLER_MODE_NORMAL);

    lv_obj_center(roller1);                             //居中对象
    lv_roller_set_visible_row_count(roller1, 3);        //设置对象间距
    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);   //设置回调
}


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
static void LVGL_Build_GUI()
{
    BackGroung();
    // KeyBtn_OK();
    // KeyBtn_BACK();
    // KeyBtn_UP();
    // KeyBtn_DOWN();
    // Botton();
    roller_show_3();
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

    LVGL_Build_GUI();
    //LVGL_Demo();
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



