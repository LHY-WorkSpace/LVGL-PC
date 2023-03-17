#include "LVGL_UI.h"






// ��ʱ�루����ͼ����
// x1=xcos(��)-ysin(��);
// y1=ycos(��)+xsin(��);

// ˳ʱ�루ͼδ��������
// x1=xcos(��)+ysin(��);
// y1=ycos(��)-xsin(��);


//��ת�뾶
#define R_LEN (47)
#define EYE_SIZE_W    		(60)
#define EYE_HOLE_SIZE_W		(40)

#define ROTATEDIR_FORWARD     ( 1)//˳ʱ��
#define ROTATEDIR_OPPOSITE    (-1)//��ʱ��

#define RADTODEG(x) ((x) * 57.295779513082320876798154814105f)
#define DEGTORAD(x) ((x) * 0.01745329251994329576923690768489f)

lv_obj_t *Eye_Group[4];
lv_anim_t EyeBodyPath_Anim[4];
lv_obj_t *Eye_base[4];//ͫ��
lv_anim_t EyeFocalize_Anim[4];
uint8_t RotateDir = ROTATEDIR_OPPOSITE;

/*
	|
 2  |  3
---------
 1  |  0
	|
*/
 //������
int8_t Eye_Position[4][3]=
{
    { R_LEN,  R_LEN, 0},
    {-R_LEN,  R_LEN, 1},
    {-R_LEN, -R_LEN, 2},
    { R_LEN, -R_LEN, 3},
};

 ///// ʮ����
// int8_t Eye_Position[4][3]=
// {
//     {0,      -R_LEN, 0},     //��
//     {R_LEN,  0,      1},     //��
//     {0,      R_LEN,  2},     //��
//     {-R_LEN, 0,      3},     //��
// };

//�����켣�����ص�
static void Eye_BodyAnimPath_CB(void *var, int32_t v)
{
    uint8_t i,j;
    int16_t x1,y1;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;

    for ( i = 0; i < 4; i++)
    {
        if(Eye_tmp == Eye_Group[i])
        {
			if( RotateDir == 1)
			{
				//˳ʱ��
				x1=(Eye_Position[Eye_Position[i][2]][0])*cos(DEGTORAD(v))-(Eye_Position[Eye_Position[i][2]][1])*sin(DEGTORAD(v));
				y1=(Eye_Position[Eye_Position[i][2]][1])*cos(DEGTORAD(v))+(Eye_Position[Eye_Position[i][2]][0])*sin(DEGTORAD(v));  
			}
			else
			{
				//��ʱ��
				x1=(Eye_Position[Eye_Position[i][2]][0])*cos(DEGTORAD(v))+(Eye_Position[Eye_Position[i][2]][1])*sin(DEGTORAD(v));
				y1=(Eye_Position[Eye_Position[i][2]][1])*cos(DEGTORAD(v))-(Eye_Position[Eye_Position[i][2]][0])*sin(DEGTORAD(v));  
			}

			lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,x1,y1);

			if( v == 90)
			{
				Eye_Position[i][2] = (Eye_Position[i][2] +RotateDir)%4;

				lv_anim_set_delay(&EyeBodyPath_Anim[i], 0);
				//��ת����������۲�����
				lv_anim_set_repeat_count(&EyeFocalize_Anim[i], 2);
				lv_anim_start(&EyeFocalize_Anim[i]);

			}
        }
    }
}

//�������ද���ص�
static void ChangeEyeFocalize_CB(void *var, int32_t v)
{
	uint8_t i,j;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;

    for ( i = 0; i < 4; i++)
    {
        if(Eye_tmp == Eye_base[i])
        {
			lv_obj_set_size(Eye_tmp,v,v);
			lv_obj_set_style_radius(Eye_tmp,v/2,LV_PART_MAIN);
			lv_obj_align_to(Eye_tmp,Eye_Group[i],LV_ALIGN_CENTER,0,0);
        }
    }
}


//������������
void Eye_BodyCreate()
{
    uint8_t i=0;
	lv_obj_t *Eye_in;

    for ( i = 0; i < 4; i++)
    {
		//����
		Eye_Group[i] = lv_obj_create(Face);
		lv_obj_set_size(Eye_Group[i],EYE_SIZE_W,EYE_SIZE_W);
		lv_obj_set_style_bg_color(Eye_Group[i],lv_color_make(56,110,23),LV_PART_MAIN);
		lv_obj_set_style_radius(Eye_Group[i],EYE_SIZE_W/2,LV_PART_MAIN);
		lv_obj_set_style_outline_width(Eye_Group[i],3,LV_PART_MAIN);
		lv_obj_set_style_outline_color(Eye_Group[i],lv_color_make(84,104,58),LV_PART_MAIN);

		//ͫ��
		Eye_base[i] = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_base[i],EYE_HOLE_SIZE_W,EYE_HOLE_SIZE_W);
		lv_obj_set_style_radius(Eye_base[i],EYE_HOLE_SIZE_W/2,LV_PART_MAIN);
		lv_obj_align_to(Eye_base[i],Eye_Group[i],LV_ALIGN_CENTER,0,0);
		lv_obj_set_style_bg_color(Eye_base[i],lv_color_black(),LV_PART_MAIN);
		lv_obj_set_scrollbar_mode(Eye_base[i],LV_SCROLLBAR_MODE_OFF);

		//�۲��߹�
		Eye_in = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_in,12,12);
		lv_obj_set_style_radius(Eye_in,6,LV_PART_MAIN);
		lv_obj_align_to(Eye_in,Eye_Group[i],LV_ALIGN_TOP_RIGHT,5,-7);
		lv_obj_set_scrollbar_mode(Eye_in,LV_SCROLLBAR_MODE_OFF);

		lv_obj_set_scrollbar_mode(Eye_Group[i],LV_SCROLLBAR_MODE_OFF);//�رչ�����
        lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,Eye_Position[i][0],Eye_Position[i][1]);

    }
}


// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_ease_in_out);
// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_linear);
// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);

//�������򶯻�
void Eye_BodyAnimPath()
{	
	uint8_t i=0;

	for ( i = 0; i < 4; i++)
    {
		//��������켣����
        lv_anim_init(&EyeBodyPath_Anim[i]);
        lv_anim_set_var(&EyeBodyPath_Anim[i],Eye_Group[i]);
        lv_anim_set_values(&EyeBodyPath_Anim[i],0,90);
        lv_anim_set_time(&EyeBodyPath_Anim[i], 300);
		lv_anim_set_delay(&EyeBodyPath_Anim[i], 500);
        lv_anim_set_exec_cb(&EyeBodyPath_Anim[i], Eye_BodyAnimPath_CB);
        lv_anim_set_path_cb(&EyeBodyPath_Anim[i],lv_anim_path_ease_in_out);
        lv_anim_set_repeat_delay(&EyeBodyPath_Anim[i],200);
        lv_anim_set_repeat_count(&EyeBodyPath_Anim[i], 3);
    }
	
    for ( i = 0; i < 4; i++)
    {
        lv_anim_start(&EyeBodyPath_Anim[i]);
    }
}


//����ͫ�׽��ද��
void EyeFocalizeAnimCreat()
{
	uint8_t i=0;

	for (i = 0; i < 4; i++)
	{
		lv_anim_init(&EyeFocalize_Anim[i]);
        lv_anim_set_var(&EyeFocalize_Anim[i],Eye_base[i]);
        lv_anim_set_values(&EyeFocalize_Anim[i],EYE_HOLE_SIZE_W,30);
        lv_anim_set_time(&EyeFocalize_Anim[i], 200);
		lv_anim_set_delay(&EyeFocalize_Anim[i], 500);//1500
        lv_anim_set_exec_cb(&EyeFocalize_Anim[i], ChangeEyeFocalize_CB);
        lv_anim_set_path_cb(&EyeFocalize_Anim[i],lv_anim_path_ease_in_out);
		lv_anim_set_playback_time(&EyeFocalize_Anim[i],200);
		lv_anim_set_playback_delay(&EyeFocalize_Anim[i],200);
        lv_anim_set_repeat_delay(&EyeFocalize_Anim[i],300);
        lv_anim_set_repeat_count(&EyeFocalize_Anim[i], 1);

	}

}


//�����۾���ת����ʹ���
void RotateEye(uint8_t Dir ,uint8_t times)
{
	uint8_t i=0;

    for ( i = 0; i < 4; i++)
    {
    	lv_anim_set_repeat_count(&EyeBodyPath_Anim[i], times);
	}

	RotateDir = Dir;

    for ( i = 0; i < 4; i++)
    {
        lv_anim_start(&EyeBodyPath_Anim[i]);
    }
}

//���õ���ͫ�׽������
void ChangeEyeFocalize(uint8_t times)
{
	uint8_t i=0;

    for ( i = 0; i < 4; i++)
    {
        lv_anim_set_repeat_count(&EyeFocalize_Anim[i], times);
    }

    for ( i = 0; i < 4; i++)
    {
        lv_anim_start(&EyeFocalize_Anim[i]);
    }

}

//�����۵���ɫ
void SetEyeBgColor(lv_palette_t color)
{
	uint8_t i=0;

    for ( i = 0; i < 4; i++)
    {
		// lv_obj_set_style_bg_color(Eye_Group[i],lv_palette_darken(color,2),LV_PART_MAIN);
		lv_obj_set_style_bg_color(Eye_Group[i],lv_palette_main(color),LV_PART_MAIN);
    }
}


void Eye_Main()
{
	Eye_BodyCreate();
	Eye_BodyAnimPath();
	EyeFocalizeAnimCreat();

}




void StartAnim( uint8_t Time)
{
	uint8_t i=0;

    for ( i = 0; i < 4; i++)
    {
		switch (Time)
		{
			case 1:
				RotateEye(ROTATEDIR_FORWARD, 1);
				break;
			case 2:
				ChangeEyeFocalize(1);
				break;	
			case 3:
				RotateEye(ROTATEDIR_OPPOSITE, 1);
				break;
			default:
				break;
		}
    }

}
