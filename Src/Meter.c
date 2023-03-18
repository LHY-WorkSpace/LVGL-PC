#include "LVGL_UI.h"





lv_obj_t *Meter_Bg;
lv_obj_t *Meter_main;
lv_obj_t *Btn[3];


void Meter_Create()
{
    // Meter_Bg = lv_obj_create(NULL);
    // lv_obj_set_size(Meter_Bg,240,240);
    // lv_obj_set_style_bg_color(Meter_Bg,lv_color_black(),LV_PART_MAIN);
    // lv_obj_set_style_radius(Meter_Bg,0,LV_PART_MAIN);
    // lv_obj_set_style_border_side(Meter_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    // lv_obj_set_style_border_color(Meter_Bg,lv_color_white(),LV_PART_MAIN);
    // lv_obj_set_style_border_width(Meter_Bg,0,LV_PART_MAIN);
    // lv_obj_set_scrollbar_mode(Meter_Bg,LV_SCROLLBAR_MODE_OFF);

    // Face = lv_obj_create(Meter_Bg);
    // lv_obj_set_size(Face,240,240);
    // lv_obj_set_style_bg_color(Face,lv_color_black(),LV_PART_MAIN);
    // lv_obj_set_style_radius(Face,120,LV_PART_MAIN);
    // lv_obj_set_style_border_side(Face,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    // lv_obj_set_style_border_color(Face,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    // lv_obj_set_style_border_width(Face,5,LV_PART_MAIN);
    // lv_obj_set_scrollbar_mode(Face,LV_SCROLLBAR_MODE_OFF);
    // lv_obj_center(Face);

}


// void Btn_Handle(lv_event_t *e)
// {
// 	uint8_t i=0;
//     lv_obj_t *Btntmp = lv_event_get_target(e);
//     lv_event_code_t codetmp = lv_event_get_code(e);

//     if( lv_event_get_code(e) == LV_EVENT_CLICKED)
//     {
//         for ( i = 0; i < 3; i++)
//         {
//             if(Btntmp == Btn[i])
//             {
//             StartAnim( i+1);
//             printf(" %d \r\n",i+1);
//             }
//         }
//     }
// }



// void Btn_Create()
// {
// 	uint8_t i=0;

//     for ( i = 0; i < 3; i++)
//     {
//         Btn[i] = lv_btn_create(lv_scr_act());
//         lv_obj_align(Btn[i],LV_ALIGN_BOTTOM_LEFT+i,0,0);
//         lv_obj_set_size(Btn[i],40,20);
//         lv_obj_set_style_bg_color(Btn[i],lv_color_make(74,117,37),LV_PART_MAIN);
//         lv_obj_add_event_cb(Btn[i],Btn_Handle,LV_EVENT_CLICKED,NULL);
//     }

// }



static lv_obj_t * meter;
static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
    printf("%d \r\n",v);
}

void MeterTest(void)
{

    Meter_Bg = lv_obj_create(NULL);
    lv_obj_set_size(Meter_Bg,240,240);
    lv_obj_set_style_bg_color(Meter_Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Meter_Bg,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(Meter_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Meter_Bg,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Meter_Bg,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(Meter_Bg,LV_SCROLLBAR_MODE_OFF);



    meter = lv_meter_create(Meter_Bg);
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















