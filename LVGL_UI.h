#ifndef  LVGL_UI_H
#define  LVGL_UI_H

#define ON_PC


typedef enum
{
    Charing,
    Full,
    InRelease
}BarState_e;






void LVGL_Init(void);
void LVGL_Task(void);
#endif


