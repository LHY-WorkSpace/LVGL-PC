#include "LVGL_UI.h"



lv_obj_t *Face;
lv_obj_t *Head_In;
lv_obj_t *Head_Out;
static void Head_Create()
{


    Head_Out = lv_obj_create(Desktop_BG);
    lv_obj_set_size(Head_Out,480,480);
    lv_obj_set_style_bg_color(Head_Out,lv_palette_darken(LV_PALETTE_GREY,2),LV_PART_MAIN);
    lv_obj_set_style_radius(Head_Out,240,LV_PART_MAIN);

    // lv_obj_set_style_border_opa(Head_In,LV_OPA_80,LV_PART_MAIN);
    // lv_obj_set_style_border_side(Head_In,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    // lv_obj_set_style_border_color(Head_In,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Head_Out,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(Head_Out,LV_SCROLLBAR_MODE_OFF);
    lv_obj_center(Head_Out);





    Head_In = lv_obj_create(Head_Out);
    lv_obj_set_size(Head_In,320,320);
    lv_obj_set_style_bg_color(Head_In,lv_palette_darken(LV_PALETTE_GREY,3),LV_PART_MAIN);
    lv_obj_set_style_radius(Head_In,160,LV_PART_MAIN);

    // //lv_obj_set_style_outline_pad();
    // lv_obj_set_style_outline_opa(Head_In,LV_OPA_80,LV_PART_MAIN);
    // lv_obj_set_style_outline_width(Head_In,8,LV_PART_MAIN);
    // lv_obj_set_style_outline_color(Head_In,lv_color_black(),LV_PART_MAIN);//眼球外轮廓

    // //lv_obj_set_style_border_post();
    lv_obj_set_style_border_opa(Head_In,LV_OPA_80,LV_PART_MAIN);
    lv_obj_set_style_border_side(Head_In,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Head_In,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_border_width(Head_In,2,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(Head_In,LV_SCROLLBAR_MODE_OFF);
    lv_obj_center(Head_In);


}




// !!!添加头部线条
void LineForHead()
{
    // lv_point_t Point={0,0};
    // lv_obj_t *Line = lv_line_create(Head_In); 
    // lv_point_t Point={0,0};

    // x1=(Eye_Position[Eye_Position[i][2]][0])*cos(DEGTORAD(v))+(Eye_Position[Eye_Position[i][2]][1])*sin(DEGTORAD(v));
    // y1=(Eye_Position[Eye_Position[i][2]][1])*cos(DEGTORAD(v))-(Eye_Position[Eye_Position[i][2]][0])*sin(DEGTORAD(v));  


    // lv_line_set_points(Line,&,1);


}








static void Face_Create()
{
    // Face = lv_obj_create(Head_In);
    Face = lv_obj_create(Img);
    lv_obj_set_size(Face,240,240);
    lv_obj_set_style_bg_color(Face,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Face,120,LV_PART_MAIN);

    //lv_obj_set_style_outline_pad();
    lv_obj_set_style_outline_opa(Face,LV_OPA_80,LV_PART_MAIN);
    lv_obj_set_style_outline_width(Face,4,LV_PART_MAIN);
    lv_obj_set_style_outline_color(Face,lv_color_black(),LV_PART_MAIN);//眼球外轮廓

    //lv_obj_set_style_border_post();
    lv_obj_set_style_border_opa(Face,LV_OPA_80,LV_PART_MAIN);
    lv_obj_set_style_border_side(Face,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Face,lv_palette_darken(LV_PALETTE_GREY,3),LV_PART_MAIN);
    lv_obj_set_style_border_width(Face,4,LV_PART_MAIN);

    lv_obj_set_scrollbar_mode(Face,LV_SCROLLBAR_MODE_OFF);

    // lv_obj_align(Face,LV_ALIGN_TOP_RIGHT,0,0);
    // lv_obj_center(Face);
    lv_obj_set_pos(Face,1083,225);

}

void Face_Main()
{
    Head_Create();
    Face_Create();
    Eye_Main();
}

















