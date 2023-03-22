#ifndef  LVGL_UI_H
#define  LVGL_UI_H



#define ON_PC


#ifdef ON_PC
    #include <stdlib.h>
    #include <unistd.h>
    #include "lvgl/lvgl.h"
    #include "lv_drivers/win32drv/win32drv.h"
    #include <windows.h>
    #include <math.h> 
#else
    #include "IncludeFile.h"
    #define cos        FastCos
    #define sin        FastSin

#endif

#include "../Src/Eye.h"
#include "../Src/Face.h"
#include "../Src/Meter.h"
#include "../Src/Desktop.h"


void LVGL_Init(void);
void LVGL_Task(void);
#endif


