#ifndef  EYE_H
#define  EYE_H

extern lv_anim_t EyeBodyPath_Anim[4];
extern lv_anim_t EyeFocalize_Anim[4];

//�����۾���ת����ʹ���
void RotateEye(uint8_t Dir ,uint8_t times);

//���õ���ͫ�׽������
void ChangeEyeFocalize(uint8_t times);

void Eye_Main(void);
void StartAnim( uint8_t Time);
#endif

