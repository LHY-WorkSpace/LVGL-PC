#ifndef  EYE_H
#define  EYE_H





extern lv_obj_t *Eye_Group[4];
extern lv_obj_t *Eye_base[4];//ͫ��
extern lv_obj_t *Eye_in_high[4];
extern lv_obj_t *Eye_in_low[4];
extern lv_anim_t EyeBodyPath_Anim;
extern lv_anim_t EyeFocalize_Anim;




//�����۾���ת����ʹ���
void RotateEye(uint8_t Dir ,uint8_t times);

//���õ���ͫ�׽������
void ChangeEyeFocalize(uint8_t times);

void Eye_Main(void);
void StartAnim( uint8_t Time);
#endif

