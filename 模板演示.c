










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
//  ��������: LVGL ��������
//
//  ����: lv_event_t
//
//  ����ֵ: lv_event_cb_t
//
//  ˵��: ��
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
//  ��������: LVGL ��ͼ�Ͳ���
//
//  ����:
//
//  ����ֵ:
//
//  ˵��: ��
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
    lv_event_code_t code = lv_event_get_code(e);        //��ȡ�¼�
    lv_obj_t * obj = lv_event_get_target(e);            //��ȡ��ǰ�¼�

    static int16_t mask_top_id = -1;                    //���嶥������
    static int16_t mask_bottom_id = -1;                 //����ײ�����

    if (code == LV_EVENT_COVER_CHECK) {                 //�¼����Ǽ��
        lv_event_set_cover_res(e, LV_COVER_RES_COVER); //���÷�������

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {      //ִ������ͼ
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);     //��ȡ��������
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);//��ȡ���������м��
        lv_coord_t font_h = lv_font_get_line_height(font);  //��ȡ�и�

        lv_area_t roller_coords;                        //���û����������
        lv_obj_get_coords(obj, &roller_coords);         //����һ����������굽һ������

        lv_area_t rect_area;                            //���û����������
        rect_area.x1 = roller_coords.x1;                //��ȡ��x1��ֵ
        rect_area.x2 = roller_coords.x2;                //��ȡ��x2��ֵ
        rect_area.y1 = roller_coords.y1;                //��ȡ��y1��ֵ
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;           //��ȡ��y2��ֵ

        lv_draw_mask_fade_param_t * fade_mask_top = lv_malloc(sizeof(lv_draw_mask_fade_param_t));  //�����ɰ���ɫ���� ����

        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);     //��ʼ��һ���������֡�
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);        //���һ�����������ɰ�

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;      //��ȡy1����
        rect_area.y2 = roller_coords.y2;                            //��ȡy2����

        lv_draw_mask_fade_param_t * fade_mask_bottom =lv_malloc(sizeof(lv_draw_mask_fade_param_t));//�����ɰ���ɫ���� �ײ�
        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);  //��ʼ��һ���������֡�
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);  //���һ�����������ɰ�

    } else if (code == LV_EVENT_DRAW_POST_END) {                    //���post���ƽ׶�(��������Ԫ�ض�����ʱ)
        lv_draw_mask_fade_param_t * fade_mask_top = lv_draw_mask_remove_id(mask_top_id);        //�Ƴ��ɰ�
        lv_draw_mask_fade_param_t * fade_mask_bottom = lv_draw_mask_remove_id(mask_bottom_id);  //�Ƴ��ɰ�
        lv_draw_mask_free_param(fade_mask_top);                     //�ͷŲ����е����ݡ�
        lv_draw_mask_free_param(fade_mask_bottom);                  //�ͷŲ����е����ݡ�
        lv_free(fade_mask_top);                          //�ֶ��ͷ��ڴ�
        lv_free(fade_mask_bottom);                       //�ֶ��ͷ��ڴ�
        mask_top_id = -1;
        mask_bottom_id = -1;
    }
}

/*************************************************
 *  �������� :  roller_show_3
 *  ��    �� �� e
 *  �������� �� �����ص���ʾ
 *************************************************/
void roller_show_3(void)
{
    static lv_style_t style;                            //������ʽ����
    lv_style_init(&style);                              //��ʼ����ʽ
    lv_style_set_bg_color(&style, lv_color_black());    //���ñ�����ɫ
    lv_style_set_text_color(&style, lv_color_white());  //����������ɫ
    lv_style_set_border_width(&style, 1);               //���ñ߿���
    lv_style_set_border_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 2);                    //���ñ߾�
    lv_style_set_text_font(&style, &lv_font_montserrat_12);

    lv_obj_t *roller1 = lv_roller_create(lv_scr_act()); //����roller����
    lv_obj_add_style(roller1, &style, 0);               //�����ʽ
    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);  //���ö����͸����

    lv_roller_set_options(roller1,                      //���ö���ѡ��
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
    lv_roller_set_visible_row_count(roller1, 8);        //���ö�����
    lv_obj_set_size(roller1,100,70);
    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);   //���ûص�
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
    lv_obj_set_style_shadow_spread(Slider,50,LV_PART_INDICATOR);//����չ����Χ��ӦС�ڿ��
    lv_obj_set_style_shadow_opa(Slider,LV_OPA_60,LV_PART_INDICATOR);
    lv_obj_set_style_shadow_width(Slider,100,LV_PART_INDICATOR);//��Ӱ���


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
    lv_obj_set_style_shadow_spread(Switch,5,LV_PART_INDICATOR);//����չ����Χ��ӦС�ڿ��
    lv_obj_set_style_shadow_opa(Switch,LV_OPA_60,LV_PART_INDICATOR);
    lv_obj_set_style_shadow_width(Switch,10,LV_PART_INDICATOR);//��Ӱ���
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
    ///E1.----------------------------�õ�����
    lv_obj_t * cont = lv_event_get_target(e); //ͨ�����˸��¼��Ķ�������ȡ�������

    ///E2.---------------------------ͨ��һ���㷨���õ�������y������λ�ã�Ŀ�ģ����ں�������Ԫ�ذ�ť����y������ƫ��Ƚϣ�
    lv_area_t cont_a; //���� cont_area
    lv_obj_get_coords(cont, &cont_a); //��cont�����긳ֵ��cont_a (��cont_aԼ��Ϊcontainer�Ĵ�С��200 * 200)  coords������(x1,y1); (x2,y1); (x1,y2); (x2,y2)

    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2; //��ȡContainer��y������

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10; // 200*7 / 10 = 140

    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont); //child_cnt : child count �������� ��ȡcontainer����Ԫ�ظ���

    ///E3.------------------���������������Ԫ�أ���ť�����Ա������ЩԪ�ص����ԣ��û���ֱ����ʱ�򣬰�ť����ˮƽƫ�ƣ��������ò�ͬ��͸���ȣ�
    for(i = 0; i < child_cnt; i++)  //����Buttons
    {
        lv_obj_t * child = lv_obj_get_child(cont, i); //��ȡcontainer�ĵ�i��button
        lv_area_t child_a; //����һ�����ڶ�������
        lv_obj_get_coords(child, &child_a); //��child_aԼ��Ϊbutton�Ĵ�С��200 * 200��
        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2; //����õ�button��y������

        lv_coord_t diff_y = child_y_center - cont_y_center; // button��y������ - Container��y������ = Button�����Container�Ĵ�ֱƫ��
        diff_y = LV_ABS(diff_y); // ��ƫ��ȡ����ֵ��ABS��

        ///E3.1------------------����ƫ���ť�����������y��������λ�ã���������ͬ��xֵ
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
            uint32_t x_sqr = r * r - diff_y * diff_y; // 140 * 140  - diff_y��ƽ��
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }
        ///E3.2--------------------����xֵ����button�ƶ�x����λ���룬����rӳ�����ͬ��͸����ֵ�����ð�ť��ͬ͸����
        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0); //��button �ƶ� x����λ����

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);  //ͨ��r�Ĳ�ֵͬ����̬ӳ�䴴����͸����ֵ opa: opacity
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0); //����ťӦ�ò�͸����ֵ  opa: opacity
    }
}


void lv_example_soll_6(void)
{

    Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Bg,240,240);
    lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Bg,0,LV_PART_MAIN);

    ///�游����
    //lv_obj_t *screenA = lv_scr_act();
    ///������
    lv_obj_t * cont = lv_obj_create(lv_scr_act()); //����Ļ�ϴ���һ��container
    lv_obj_set_size(cont, 200, 200); //����cont�ĳߴ磺 w200, h200  �������Σ�
    lv_obj_set_style_bg_color(cont,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(cont,3,LV_PART_MAIN);
    lv_obj_set_style_border_color(cont,lv_color_white(),LV_PART_MAIN);
    lv_obj_center(cont);//��cont��ֱˮƽ���У�����ڸ�����
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN );//����cont���Ӽ���layout: ���Բ��ֵ�������flex-flow��(����+��������)
    ///���������
    //1.����¼� // Link---<!>----------------------------------->>>>>>>>>>>>
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);//��cont���event���¼��Ļص��������¼����ͣ�Scroll��
    //2.������ʽ
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0); //���þ���Բ�� LV_RADIUS_CIRCLE��Բ�����
    lv_obj_set_style_clip_corner(cont, true, 0); //���ӳ�����������
    lv_obj_set_scroll_dir(cont, LV_DIR_VER); //����Scroll��������direction����ֱ����
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER); //��׽Cont Y������Ӷ��󣬽�������Container���Ķ��� �� snap �����񣻲�׽
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_ACTIVE);//����scrollbar

    ///�Ӷ���
    uint32_t i;
    ///��container�ϴ������ɸ�button

    lv_group_t *Group = lv_group_create();

    for(i = 0; i < 20; i++)
    {
        lv_obj_t * btn = lv_btn_create(cont); //��container�ϴ���button
        lv_obj_set_width(btn, lv_pct(50)); //����button��width = lv_pct(100); //pct : percentage ����ڸ��׵Ŀ��100%

        ///�����
        lv_obj_t * label = lv_label_create(btn); //��button�ϴ���һ��label����ǩ��
        lv_label_set_text_fmt(label, "Button %d", i);  //��̬����label���ı�����  fmt: format����ʽ��
        lv_group_add_obj(Group,btn);
    }

    lv_indev_set_group(lv_win32_encoder_device_object,Group);
    /*Update the buttons position manually for first*/ //�״��ֶ����°�ť��λ��
    lv_event_send(cont, LV_EVENT_SCROLL, NULL); //TODO

    /*Be sure the fist button is in the middle*/ //ȷ����һ����ť�����м�
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_ON); //��һ����ť�Ƿ��Թ���������������ָ��λ�ã�Ĭ��λ�ã�
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
//  ��������: LVGL UI����
//
//  ����: ��
//
//  ����ֵ: ��
//
//  ˵��: ��
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

lv_obj_t *ALL_Bg;
void BarAnimation_CB(void * var, int32_t v)
{
    // lv_obj_set_style_border_color(var,lv_palette_main( LV_PALETTE_GREEN),LV_PART_MAIN);
    // lv_obj_set_style_border_opa(var,LV_OPA_50,LV_PART_MAIN);
    // lv_obj_set_style_border_width(var,v,LV_PART_MAIN);

    lv_obj_t *ArcOut = (lv_obj_t *)var;

   /// lv_obj_set_size(ArcOut,100,100);
   lv_obj_set_style_arc_width(ArcOut,10-v,LV_PART_MAIN);

    //printf("size %d  width %d \r\n",lv_obj_get_x(ArcOut),v);

    // lv_obj_set_style_bg_grad_color(var, lv_palette_main(LV_PALETTE_GREEN), 0);
    // lv_obj_set_style_bg_grad_dir(var, LV_GRAD_DIR_HOR, 0);
    // lv_obj_set_style_bg_grad_
    // lv_obj_set_style_bg_grad_stop();


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

        if(Charging == )
        {
            lv_anim_set_var(&Anima,UserData);
            lv_anim_set_values(&Anima,0,10);
            lv_anim_set_time(&Anima, 500);
            lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
            lv_anim_set_repeat_count(&Anima, 1);
            lv_anim_start(&Anima);
        }





    }
    
    if(Arc_Val == 0)
    {
        lv_obj_set_style_arc_color(Target,lv_palette_main( LV_PALETTE_BLUE),LV_PART_INDICATOR);
        lv_obj_clear_flag(UserData,LV_OBJ_FLAG_HIDDEN);
    }

    lv_arc_set_bg_angles(UserData,lv_arc_get_angle_start(Target),lv_arc_get_angle_end(Target));

}

void StateBar()
{

    //��������
    ALL_Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ALL_Bg,240,240);
    lv_obj_set_style_bg_color(ALL_Bg,lv_color_black(),LV_PART_MAIN);

    lv_obj_t *Arc_Out =lv_arc_create(ALL_Bg); 

    lv_obj_set_size(Arc_Out,100,100);
    lv_obj_set_style_arc_color(Arc_Out,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_arc_opa(Arc_Out,LV_OPA_50,LV_PART_MAIN);
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_KNOB);//ɾ������
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_INDICATOR);//ɾ��������
    lv_obj_set_style_arc_rounded(Arc_Out,0,LV_PART_MAIN);
    lv_obj_set_style_arc_width(Arc_Out,10,LV_PART_MAIN);
    lv_arc_set_value(Arc_Out,0);

    lv_obj_align(Arc_Out,LV_ALIGN_BOTTOM_LEFT,0,0);


    lv_obj_t *Arc_In =lv_arc_create(ALL_Bg); 

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


    lv_obj_t *Center = lv_obj_create(ALL_Bg); 
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
    lv_obj_align(Btn,LV_ALIGN_BOTTOM_RIGHT,-5,0);
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
//  ��������: LVGL Demo����
//
//  ����: ��
//
//  ����ֵ: ��
//
//  ˵��: ��
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
//  ��������: LVGL��ʼ��
//
//  ����: ��
//
//  ����ֵ: ��
//
//  ˵��: ��
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
//  ��������: LVGL��ʱ����
//
//  ����: ��
//
//  ����ֵ: ��
//
//  ˵��: ��
//
//***************************************************//
void LVGL_Task()
{
    lv_task_handler();
}


















