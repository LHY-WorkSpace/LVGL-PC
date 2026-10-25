#include "LVGL_UI.h"

#define SCREEN_SIZE     (240)

// 表盘大小
#define METER_OUT_MAX_SIZE       (380)
#define METER_IN_MAX_SIZE        (240)

// 表盘计数最大值
#define METER_OUT_MAX_VAL       (100)
#define METER_IN_MAX_VAL        (600)

static lv_obj_t * Meter_Bg;
static lv_obj_t * Meter_Out;
static lv_obj_t * Meter_In;
static lv_meter_indicator_t * Pointer_Out;
static lv_meter_indicator_t * Pointer_In;
static lv_obj_t * Battery;
static lv_obj_t * BatteryVal;
static lv_anim_t Meter_Out_Anim;
static lv_anim_t Meter_In_Anim;
static lv_obj_t *ChargeVal;
static lv_obj_t *ChargeUnit;
static lv_obj_t *WarningSymbol;
static int32_t  Pointer_Out_Val = 0;
static int32_t  Pointer_In_Val = 0;

static void Set_MeterOut_CB(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(Meter_Out, Pointer_Out, v);
    Pointer_Out_Val = v;
    if( v < 20 )
    {
        lv_label_set_text(Battery,LV_SYMBOL_BATTERY_EMPTY);
    }
    else if( v < 40 )
    {
        lv_label_set_text(Battery,LV_SYMBOL_BATTERY_1);
    }
    else if( v < 60 )
    {
        lv_label_set_text(Battery,LV_SYMBOL_BATTERY_2);
    }
    else if( v < 80 )
    {
        lv_label_set_text(Battery,LV_SYMBOL_BATTERY_3);
    }
    else
    {
        lv_label_set_text(Battery,LV_SYMBOL_BATTERY_FULL);
    }

    //修改电量显示数值
    lv_label_set_text_fmt(BatteryVal,"%d%%",v);
    // printf("Out %d \r\n",v);
}

static void Set_MeterIn_CB(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(Meter_In, Pointer_In, v);
    Pointer_In_Val = v;

    //修改速度显示数值
    lv_label_set_text_fmt(ChargeVal,"%d",v);
    if( v >= (METER_IN_MAX_VAL/2) )
    {
        lv_obj_clear_flag(WarningSymbol,LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(WarningSymbol,LV_OBJ_FLAG_HIDDEN);
    }
    // printf("In %d \r\n",v);
}

void MeterOut_ChangeVal(int32_t NewVal,uint32_t Playtime)
{
    lv_meter_set_indicator_value(Meter_Out, Pointer_Out, Pointer_Out_Val);
    lv_anim_set_time(&Meter_Out_Anim, Playtime);
    lv_anim_set_delay(&Meter_Out_Anim, 0);
    lv_anim_set_repeat_count(&Meter_Out_Anim, 0);
    lv_anim_set_values(&Meter_Out_Anim, Pointer_Out_Val, NewVal);
    lv_anim_start(&Meter_Out_Anim);
}

void MeterIn_ChangeVal(int32_t NewVal,uint32_t Playtime)
{
    lv_meter_set_indicator_value(Meter_In, Pointer_In, Pointer_In_Val);
    lv_anim_set_time(&Meter_In_Anim, Playtime);
    lv_anim_set_delay(&Meter_In_Anim, 0);
    lv_anim_set_repeat_count(&Meter_In_Anim, 0);
    lv_anim_set_values(&Meter_In_Anim, Pointer_In_Val, NewVal);
    lv_anim_start(&Meter_In_Anim);
}

void anim_deleted_callback(lv_anim_t* anim) 
{
    if(anim->current_value == 100)
    {
        MeterOut_ChangeVal(0,5000);//外盘开始倒数放电
        MeterIn_ChangeVal(METER_IN_MAX_VAL,5000);//内盘开始正数充能
    }
}

void btn_Insert_CB(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);
    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        MeterOut_ChangeVal(METER_OUT_MAX_VAL,500);
    }
}


void btn_Pop_CB(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);
    lv_obj_t *Target = lv_event_get_target(Event);
    if( Code == LV_EVENT_CLICKED)
    {
        MeterOut_ChangeVal(0,500);
        MeterIn_ChangeVal(0,500);
    }
}

void btn_Click_CB(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);
    lv_obj_t *Target = lv_event_get_target(Event);
    if( Code == LV_EVENT_CLICKED)
    {
        MeterOut_ChangeVal(0,500);
        MeterIn_ChangeVal(0,500);
    }
}



static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * bar = lv_event_get_target(e); // 获取触发事件的滑块对象
    int32_t value = lv_slider_get_value(bar); // 获取当前值
    printf("Slider value: %d\r\n", value);      // 打印值（或执行其他操作）
}

void MeterTest(void)
{
    lv_meter_indicator_t * indic;
    lv_coord_t Rad_Out = METER_OUT_MAX_SIZE;
    lv_coord_t Rad_In = METER_IN_MAX_SIZE;
    lv_coord_t Offset = 14;
    // lv_color_t Bg_color = lv_color_make(150, 210, 66);
    lv_color_t Bg_color = lv_color_make(170, 223, 90);

    Meter_Bg = lv_obj_create(NULL);
    lv_obj_set_size(Meter_Bg,SCREEN_SIZE,SCREEN_SIZE);
    lv_obj_set_style_bg_color(Meter_Bg,Bg_color,LV_PART_MAIN);
    lv_obj_set_style_radius(Meter_Bg,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(Meter_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Meter_Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Meter_Bg,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(Meter_Bg,LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(Meter_Bg,LV_OBJ_FLAG_SCROLLABLE );

    // 外盘
    Meter_Out = lv_meter_create(Meter_Bg);
    lv_obj_set_style_text_color(Meter_Out,lv_color_black(),0);
    lv_obj_set_style_bg_color(Meter_Out,Bg_color,LV_PART_MAIN);//表盘背景
    lv_obj_set_style_bg_color(Meter_Out,lv_color_white(),LV_PART_INDICATOR);//指针原点
    lv_obj_set_style_pad_all(Meter_Out,0,0);//刻度偏移
    lv_obj_set_scrollbar_mode(Meter_Out,LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(Meter_Out,LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_size(Meter_Out, Rad_Out, Rad_Out);
    lv_obj_align_to(Meter_Out,Meter_Bg,LV_ALIGN_TOP_LEFT,SCREEN_SIZE-(Rad_Out/2)-Offset,SCREEN_SIZE-(Rad_Out/2)-Offset);
    lv_obj_set_style_border_color(Meter_Out,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Meter_Out,4,LV_PART_MAIN);
    // 刻度样式
    lv_meter_scale_t * scale = lv_meter_add_scale(Meter_Out);
    lv_meter_set_scale_ticks(Meter_Out, scale, 9, 2, 8, lv_color_white());//小刻度个数，宽度，长度
    lv_meter_set_scale_major_ticks(Meter_Out, scale, 2, 4, 13, lv_color_white(), 13);//大刻度：间隔，宽度，长度，颜色，数值与边缘的距离
    lv_meter_set_scale_range(Meter_Out, scale,0,METER_OUT_MAX_VAL,90,180);//数值范围0-5，扇形夹角90度，旋转角度180
    lv_obj_set_style_text_font(Meter_Out, &lv_font_montserrat_14, LV_PART_MAIN);//数值字体

    indic = lv_meter_add_scale_lines(Meter_Out, scale, lv_color_black(), lv_color_black(), false, 0);//最后参数：原来刻度样式基础上加宽多少
    lv_meter_set_indicator_start_value(Meter_Out, indic, 0);
    lv_meter_set_indicator_end_value(Meter_Out, indic, METER_OUT_MAX_VAL);

    // //分段弧度
    indic = lv_meter_add_arc(Meter_Out, scale, 6, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(Meter_Out, indic, 0);
    lv_meter_set_indicator_end_value(Meter_Out, indic, 25);

    indic = lv_meter_add_arc(Meter_Out, scale, 6, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_meter_set_indicator_start_value(Meter_Out, indic, 25);
    lv_meter_set_indicator_end_value(Meter_Out, indic, 50);

    indic = lv_meter_add_arc(Meter_Out, scale, 6, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_meter_set_indicator_start_value(Meter_Out, indic, 50);
    lv_meter_set_indicator_end_value(Meter_Out, indic, 75);
    
    indic = lv_meter_add_arc(Meter_Out, scale, 6, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(Meter_Out, indic, 75);
    lv_meter_set_indicator_end_value(Meter_Out, indic, 100);

    // 指针样式
    Pointer_Out = lv_meter_add_needle_line(Meter_Out, scale, 3, lv_palette_main(LV_PALETTE_BLUE), -35);
    lv_meter_set_indicator_value(Meter_Out, Pointer_Out, 0);///必须传入指针样式的句柄

    // 内盘
    Meter_In = lv_meter_create(Meter_Bg);
    lv_obj_set_style_text_color(Meter_In,lv_color_black(),0);
    lv_obj_set_style_bg_color(Meter_In,Bg_color,0);
    lv_obj_set_style_bg_color(Meter_In,lv_color_black(),LV_PART_INDICATOR);//指针圆点
    lv_obj_set_style_pad_all(Meter_In,0,0);
    lv_obj_set_scrollbar_mode(Meter_In,LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(Meter_In,LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_size(Meter_In, Rad_In, Rad_In);
    lv_obj_align_to(Meter_In,Meter_Bg,LV_ALIGN_TOP_LEFT,SCREEN_SIZE-(Rad_In/2)-Offset,SCREEN_SIZE-(Rad_In/2)-Offset);
    lv_obj_set_style_border_color(Meter_In,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Meter_In,4,LV_PART_MAIN);

    // 刻度样式
    scale = lv_meter_add_scale(Meter_In);
    lv_meter_set_scale_ticks(Meter_In, scale, 7, 2, 8, lv_color_white());//小刻度个数，宽度，长度
    lv_meter_set_scale_major_ticks(Meter_In, scale, 2, 4, 12, lv_color_white(), 13);//大刻度：间隔，宽度，长度，颜色，数值与边缘的距离
    lv_meter_set_scale_range(Meter_In, scale,0,METER_IN_MAX_VAL,90,180);//数值范围0-5，扇形夹角90度，旋转角度180
    lv_obj_set_style_text_font(Meter_In, &lv_font_montserrat_14, LV_PART_MAIN);//数值字体

    indic = lv_meter_add_scale_lines(Meter_In, scale, lv_color_black(), lv_color_black(), false, 0);//最后参数：原来刻度样式基础上加宽多少
    lv_meter_set_indicator_start_value(Meter_In, indic, 0);
    lv_meter_set_indicator_end_value(Meter_In, indic, METER_IN_MAX_VAL);

    indic = lv_meter_add_arc(Meter_In, scale, 6, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_meter_set_indicator_start_value(Meter_In, indic, 0);
    lv_meter_set_indicator_end_value(Meter_In, indic, 200);

    indic = lv_meter_add_arc(Meter_In, scale, 6, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(Meter_In, indic, 200);
    lv_meter_set_indicator_end_value(Meter_In, indic, 400);
    
    indic = lv_meter_add_arc(Meter_In, scale, 6, lv_palette_main(LV_PALETTE_DEEP_PURPLE), 0);
    lv_meter_set_indicator_start_value(Meter_In, indic, 400);
    lv_meter_set_indicator_end_value(Meter_In, indic, 600);

    // 指针样式
    Pointer_In = lv_meter_add_needle_line(Meter_In, scale, 3, lv_palette_main(LV_PALETTE_RED), -35);
    lv_meter_set_indicator_value(Meter_In, Pointer_In, 0);///必须传入指针样式的句柄

    //电池图标
    Battery = lv_label_create(Meter_Bg);
    lv_label_set_text(Battery,LV_SYMBOL_BATTERY_EMPTY);
    lv_obj_set_style_text_font(Battery, &lv_font_montserrat_20, LV_PART_MAIN);
    // lv_obj_set_style_transform_angle(Battery,-900,LV_PART_MAIN);
    lv_obj_align(Battery,LV_ALIGN_TOP_RIGHT,-3,10);
    lv_obj_set_style_text_color(Battery,lv_color_black(),0);

    //电量数值
    BatteryVal = lv_label_create(Meter_Bg);
    lv_label_set_text_fmt(BatteryVal,"%d%%",0);
    lv_obj_set_style_text_font(BatteryVal, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_align(BatteryVal,LV_ALIGN_TOP_RIGHT,-30,10);
    lv_obj_set_style_text_color(BatteryVal,lv_color_black(),0);

    //充能图标
    lv_obj_t * Charge = lv_label_create(Meter_Bg);
    lv_label_set_text(Charge,LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_font(Charge, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_align(Charge,LV_ALIGN_TOP_RIGHT,-5,80);
    lv_obj_set_style_text_color(Charge,lv_color_black(),0);

    //充能单位
    ChargeUnit = lv_label_create(Meter_In);
    lv_label_set_text(ChargeUnit,"m/s");
    lv_obj_set_style_text_font(ChargeUnit, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_align(ChargeUnit,LV_ALIGN_TOP_LEFT,60,95);//70,90);
    lv_obj_set_style_text_color(ChargeUnit,lv_color_black(),0);

    //充能数值
    ChargeVal = lv_label_create(Meter_In);
    lv_label_set_text_fmt(ChargeVal,"%d",0);
    lv_obj_set_style_text_font(ChargeVal, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_align(ChargeVal,LV_ALIGN_TOP_LEFT,60,75);
    lv_obj_set_style_text_color(ChargeVal,lv_color_black(),0);

    //警告图标
    WarningSymbol = lv_label_create(Meter_Bg);
    lv_label_set_text(WarningSymbol,LV_SYMBOL_WARNING);
    lv_obj_set_style_text_font(WarningSymbol, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_align(WarningSymbol,LV_ALIGN_TOP_RIGHT,-40,160);//-2
    lv_obj_set_style_text_color(WarningSymbol,lv_palette_main(LV_PALETTE_RED),0);
    lv_obj_add_flag(WarningSymbol,LV_OBJ_FLAG_HIDDEN);


	lv_group_t * KeyGroup = lv_group_create();


    lv_obj_t *Btn_Insert;
    Btn_Insert = lv_btn_create(Meter_Bg);
    lv_obj_set_size(Btn_Insert,30,30);
    lv_obj_align(Btn_Insert,LV_ALIGN_TOP_LEFT,0,0);
    lv_obj_set_style_border_side(Btn_Insert,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_Insert,2,LV_PART_MAIN);
    lv_obj_clear_flag(Btn_Insert,LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_add_event_cb(Btn_Insert, btn_Insert_CB ,LV_EVENT_CLICKED,NULL);


    lv_obj_t *Btn_Pop;
    Btn_Pop = lv_btn_create(Meter_Bg);
    lv_obj_set_size(Btn_Pop,30,30);
    lv_obj_align(Btn_Pop,LV_ALIGN_TOP_LEFT,60,0);
    lv_obj_set_style_border_side(Btn_Pop,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_Pop,2,LV_PART_MAIN);
    lv_obj_clear_flag(Btn_Pop,LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_add_event_cb(Btn_Pop, btn_Pop_CB ,LV_EVENT_CLICKED,NULL);


    lv_obj_t *Btn_Click;
    Btn_Click = lv_btn_create(Meter_Bg);
    lv_obj_set_size(Btn_Click,30,30);
    lv_obj_align(Btn_Click,LV_ALIGN_TOP_LEFT,120,0);
    lv_obj_set_style_border_side(Btn_Click,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_Click,2,LV_PART_MAIN);
    lv_obj_clear_flag(Btn_Click,LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_add_event_cb(Btn_Click, btn_Click_CB ,LV_EVENT_CLICKED,NULL);


    // lv_obj_add_flag(Btn_Click,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(Btn_Insert,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(Btn_Pop,LV_OBJ_FLAG_HIDDEN);



	// lv_group_add_obj(KeyGroup, Btn_Insert);
	// lv_group_add_obj(KeyGroup, Btn_Pop);
	// lv_group_add_obj(KeyGroup, Btn_Click);

	// lv_indev_set_group(indev_keypad, KeyGroup);

    //外盘动画
    lv_anim_init(&Meter_Out_Anim);
    lv_anim_set_exec_cb(&Meter_Out_Anim, Set_MeterOut_CB);
    lv_anim_set_deleted_cb(&Meter_Out_Anim,anim_deleted_callback);
    lv_anim_set_var(&Meter_Out_Anim, Pointer_Out);
    lv_anim_set_values(&Meter_Out_Anim, 0, 0);
    lv_anim_set_time(&Meter_Out_Anim, 1000);
    lv_anim_set_repeat_count(&Meter_Out_Anim, 0);
    lv_anim_set_path_cb(&Meter_Out_Anim,lv_anim_path_bounce);


    //内盘动画
    lv_anim_set_exec_cb(&Meter_In_Anim, Set_MeterIn_CB);
    lv_anim_set_var(&Meter_In_Anim, Pointer_In);
    lv_anim_set_values(&Meter_In_Anim, 0, 0);
    lv_anim_set_time(&Meter_In_Anim, 1000);
    lv_anim_set_repeat_count(&Meter_In_Anim, 0);
    lv_anim_set_path_cb(&Meter_In_Anim,lv_anim_path_bounce);

    // lv_anim_start(&Meter_In_Anim);
    // lv_anim_start(&Meter_Out_Anim);

    lv_obj_t * bar = lv_bar_create(Meter_Bg);
    lv_obj_set_pos(bar, 10, 80);
    lv_obj_set_size(bar, 16, 180);
    lv_bar_set_range(bar, 0, 100);
    lv_bar_set_mode(bar,LV_BAR_MODE_NORMAL);
    lv_bar_set_value(bar, 80, LV_ANIM_OFF);
    // lv_slider_set_mode(bar,LV_SLIDER_MODE_NORMAL);
    // lv_slider_set_value(bar, 80, LV_ANIM_OFF);
    lv_obj_set_style_radius(bar,0,LV_PART_INDICATOR);
    lv_obj_set_style_radius(bar,0,LV_PART_MAIN);
    lv_obj_add_event_cb(bar, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

}




void SF_Sniper_UI()
{
    MeterTest();
    lv_disp_load_scr(Meter_Bg);
}


// void LVGL_Init()
// {
//     ST7789_Init();
//     lv_init();
// 	lv_port_disp_init();
// 	lv_port_indev_init();
//     // ui_init();
// 	SF_Sniper_UI();
// 	TimeTask_Init(1);
// }

// void LVGL_Task()
// {
//     lv_task_handler();
// }














