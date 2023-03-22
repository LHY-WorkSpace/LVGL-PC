#ifndef  EYE_H
#define  EYE_H

extern lv_anim_t EyeBodyPath_Anim[4];
extern lv_anim_t EyeFocalize_Anim[4];

//设置眼睛旋转方向和次数
void RotateEye(uint8_t Dir ,uint8_t times);

//设置调整瞳孔焦距次数
void ChangeEyeFocalize(uint8_t times);

void Eye_Main(void);
void StartAnim( uint8_t Time);
#endif

