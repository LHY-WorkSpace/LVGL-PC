#include "LVGL_UI.h"




void Main_UI()
{
	DesktopCreate();
    Face_Main();
    Btn_Create();
    // MeterTest();

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

    //Main_UI();


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



