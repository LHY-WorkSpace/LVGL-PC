#ifndef  LVGL_UI_H
#define  LVGL_UI_H



#define ON_PC


#ifdef ON_PC
    #include <stdlib.h>
    #include <unistd.h>
    #include "lvgl/lvgl.h"
    #include "lv_drivers/win32drv/win32drv.h"
    #include <windows.h>
#else
    #include "IncludeFile.h"
#endif

#include "Eye.h"



typedef enum
{
    Charing,
    Full,
    InRelease
}BarState_e;

void LVGL_Init(void);
void LVGL_Task(void);
#endif


