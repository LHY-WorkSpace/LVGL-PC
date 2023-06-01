#include "LVGL_UI.h"


void img()
{
	static lv_obj_t *BackGround;

    BackGround = lv_obj_create(lv_scr_act());
    lv_obj_set_size(BackGround,320,320);
    lv_obj_set_style_bg_color(BackGround,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(BackGround,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(BackGround,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(BackGround,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(BackGround,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(BackGround,LV_SCROLLBAR_MODE_OFF);


	lv_fs_dir_t d;
	if (lv_fs_dir_open(&d, "X:/Img") == LV_FS_RES_OK)
	{
		char b[200];
		memset(b, 0, 200);
		while (lv_fs_dir_read(&d, b) == LV_FS_RES_OK)
		{
			printf("%s\n", b);
		}
	}
	else
	{
		printf("Err Code %d\n", lv_fs_dir_open(&d, "/"));
	}
	lv_fs_dir_close(&d);



	lv_obj_t * img;



	img = lv_img_create(BackGround);
	lv_img_set_src(img,"X:/Img/123.png");
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);



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
	lv_demo_benchmark();
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
	// img();
    Main_UI();
	// LVGL_Demo();

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



