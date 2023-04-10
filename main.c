
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/win32drv/win32drv.h"

#include <windows.h>
#include "LVGL_UI.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/


//  https://www.cnblogs.com/frozencandles/p/16375392.html


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    // lv_win32_init(hInstance, SW_SHOWNORMAL, SCR_W, SCR_H, NULL);
    lv_fs_win32_init();
// LV_USE_FS_FATFS();
    lv_png_init();
    lv_win32_init(hInstance, SW_SHOWNORMAL, 500, 500, NULL);

    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");


    lv_fs_dir_t d;
    if (lv_fs_dir_open(&d, "S:/") == LV_FS_RES_OK)
    {
        char b[500];
        memset(b, 0, sizeof(b));
        while (lv_fs_dir_read(&d, b) == LV_FS_RES_OK)
        {
            LV_LOG_USER("%s\n", b);
        }
        lv_fs_dir_close(&d);
    }
    else
    {
         LV_LOG_USER("fs Err %d\n",lv_fs_dir_open(&d, "/"));
    }



    lv_obj_t *Img = lv_img_create(lv_scr_act());
    lv_img_set_src(Img,"S:/Image/test.png");
    lv_obj_align(Img,LV_ALIGN_CENTER,0,0);










    /*Run the demo*/
    // lv_demo_widgets();
    //lv_demo_benchmark();
    //LVGL_Init();
    
    while(!lv_win32_quit_signal) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        LVGL_Task();
        usleep(10);       /*Just to let the system breath*/
    }
    return 0;
}
