#include "LVGL_UI.h"



#if 1

static void sw_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e); // ��ȡ�¼�code
    lv_obj_t* sw = lv_event_get_target(e);   //��ȡĿ���¼�����
    if (code == LV_EVENT_VALUE_CHANGED) {   //ֵ�ı��¼�
        lv_obj_t* list = lv_event_get_user_data(e);  //��ȡ�¼��û�����
        if (lv_obj_has_state(sw, LV_STATE_CHECKED))
        	lv_obj_add_flag(list, LV_OBJ_FLAG_SCROLL_ONE); // ��������һ������
        else
        	lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLL_ONE);// �رչ���һ������

    }

}

static void lv_example_scroll_2(void)
{
    lv_obj_t* panel = lv_obj_create(lv_scr_act()); //������ǰ��������
    lv_obj_set_size(panel, 240, 120);  // ���ô�С
    lv_obj_set_scroll_snap_x(panel, LV_SCROLL_SNAP_CENTER); //����x�������snap����
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW); // ����LV_FLEX_FLOW_ROW��ʽ
    lv_obj_align(panel, LV_ALIGN_CENTER, 0, 20); //x���У�y��������20���ض���
    uint32_t i;
    for (i = 0; i < 10; i++)
    {
        lv_obj_t* btn = lv_btn_create(panel);  // ����button����
        lv_obj_set_size(btn, 150,lv_pct(100)); //���ô�С
        lv_obj_t* label = lv_label_create(btn); //����label
        if (i == 3) {
            lv_label_set_text_fmt(label, "Panel %d\nno snap", i); //������������
            lv_obj_clear_flag(btn, LV_OBJ_FLAG_SNAPPABLE); //���snap����
        }
        else {
            lv_label_set_text_fmt(label, "Panel %d", i); //������������
        }
        lv_obj_center(label); //������ʾ
    }
    lv_obj_update_snap(panel, LV_ANIM_ON); //����snap����
#if LV_USE_SWITCH
    /*Switch between "One scroll" and "Normal scroll" mode*/
    lv_obj_t* sw = lv_switch_create(lv_scr_act()); // ����switch����
    lv_obj_align(sw, LV_ALIGN_TOP_RIGHT, -20, 10); // �����Ҷ���
    lv_obj_add_event_cb(sw, sw_event_cb, LV_EVENT_ALL, panel); // �����¼�����
    lv_obj_t* label = lv_label_create(lv_scr_act());  // ����label
    lv_label_set_text(label, "One scroll"); // ��ʾ����
    lv_obj_align_to(label, sw, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);// ���뵽switch����
#endif
}




static void scroll_end_event(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);                                               // ��ȡ�¼��ĳ�ʼ����

    /* ��ȡ�¼����¼����� */
    if(lv_event_get_code(e) == LV_EVENT_SCROLL_END)
    {
        /* �ж��Ƿ��ڹ����� */
        if (lv_obj_is_scrolling(cont))
        {
            return;
        }

        lv_coord_t child_cnt = lv_obj_get_child_cnt(cont);                                  // ��ȡ�ӽ��������
        lv_coord_t mid_btn_index = (child_cnt - 1) / 2;                                     // �м�����λ��

        /* ��ȡ������y�����������ֵ */
        lv_area_t cont_a;
        lv_obj_get_coords(cont, &cont_a);                                                   // ��cont��������긴�Ƶ�cont_a
        lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_width(&cont_a) / 2;              // ��ȡ����Ŀ����ش�С/2

        /* ע�⣬�����������ʾ��������겻�������ģ�������������˲�ֵ */
        cont_y_center += 69;

        /* �����ӽ��� */
        for (lv_coord_t i = 0; i < child_cnt; i++) {
            lv_obj_t* child = lv_obj_get_child(cont, i);                                    // ͨ��������ȡ�Ӷ���

            /* ��ȡ�Ӷ���y�����������ֵ */
            lv_area_t child_a;
            lv_obj_get_coords(child, &child_a);
            lv_coord_t child_y_center = child_a.y1 + lv_area_get_width(&child_a) / 2;       // ��ȡ�����а�ť������ֵ�Ĵ�С/2
            /* �ӽ���������븸������������ʱ��˵����ǰ�����ڸ���������ʾ */
            if (child_y_center == cont_y_center)
            {
                /* ��ǰ��ʾ��������� */
                lv_coord_t current_btn_index = lv_obj_get_index(child);

                /* �жϽ����ƶ��������ݣ�������ǰ�����������Ϊ�м�λ�� */
                /* ��Ϊ���ڻ���������ʵ�ֵģ��������϶�������ʹ�ô˷�ʽ����������٣�һ�λ���̫�����ʱ�����׻����߽���ֿ������� */
                lv_coord_t move_btn_quantity = LV_ABS(current_btn_index - mid_btn_index);
                for (lv_coord_t j = 0; j < move_btn_quantity; j++)
                {
                    /* ���һ��� */
                    if (current_btn_index < mid_btn_index)
                    {
                        lv_obj_move_to_index(lv_obj_get_child(cont, child_cnt - 1), 0);                     // �����һ������������Ϊ��һ������
                        lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);          // lv_obj_get_child ͨ����������ȡ������Ӷ���
                    }
                    /* ���󻬶� */
                    if (current_btn_index > mid_btn_index)
                    {
                        lv_obj_move_to_index(lv_obj_get_child(cont, 0), child_cnt - 1);                     // ����һ�����������ֵ��Ϊ���һ������
                        lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);          // lv_obj_get_child ͨ����������ȡ������Ӷ���
                    }
                }
                /* ��֤���������ʾ */
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

    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);       // Ϊ�˷���ʵ�֣��Ȱѹ����Ķ�������
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

    /*---------------------------------------- ָ��������ʾ���� ----------------------------------------*/
    lv_coord_t mid_btn_index = (lv_obj_get_child_cnt(cont) - 1) / 2;                   // �������Ϊż�������м�������ȡ���Ľ�������Ϊ�м����
    lv_coord_t child_cnt = lv_obj_get_child_cnt(cont);                                 // ��ȡ�ӽ��������

    int roll_direction = mid_btn_index - mid_btn_index;                                      // ȷ����������

    /* ͨ��ѭ����ָ�������Ƶ�����λ�� */
    for (lv_coord_t i = 0; i < LV_ABS(roll_direction); i++)
    {
        if (roll_direction > 0)
        {
            lv_obj_move_to_index(lv_obj_get_child(cont, child_cnt - 1), 0);            // �����һ���������������Ϊ 0 ��������һ�����棩
        }
        else
        {
            lv_obj_move_to_index(lv_obj_get_child(cont, 0), child_cnt - 1);            // ����һ�����������ֵ��Ϊ���ֵ���������һ�����棩
        }
    }

    /*����ť��Ϊż��ʱ��ȷ����ť����*/
    lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);         // ������һ������ֱ�������丸�����Ͽɼ�
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

    //��������
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
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_KNOB);//ɾ������
    lv_obj_remove_style(Arc_Out, NULL, LV_PART_INDICATOR);//ɾ��������
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
    // lvgl_scroll_test();
    Eye_Create();
    // lv_example_scroll_2();
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



