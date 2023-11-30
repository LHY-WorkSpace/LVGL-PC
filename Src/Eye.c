#include "LVGL_UI.h"






// ��ʱ�루����ͼ����
// x1=xcos(��)-ysin(��);
// y1=ycos(��)+xsin(��);

// ˳ʱ�루ͼδ��������
// x1=xcos(��)+ysin(��);
// y1=ycos(��)-xsin(��);


//��ת�뾶
#define R_LEN (42)

//����ֱ��
#define EYE_SIZE    		(60)

//ͫ��ֱ��
#define EYE_HOLE_SIZE		(35)
//ͫ����Сֱ��(����)
#define EYE_HOLE_MIN_SIZE		(25)

//�߹�ֱ��
#define EYE_HIGHLIGHT_SIZE			(18)

//�߹��ƶ��Ƕȱ���(Խ���ƶ�ԽԶ)
#define EYE_HIGHLIGHT_ANGLE_G		(8)

//�ϲ��߹��ʼλ��
#define EYE_HIGHLIGHT_HIGH_X	( 12)
#define EYE_HIGHLIGHT_HIGH_Y	(-12)

//�²��߹��ʼλ��
#define EYE_HIGHLIGHT_LOW_X		(-15)
#define EYE_HIGHLIGHT_LOW_Y		( 15)


#define ROTATEDIR_FORWARD     ( 1)//˳ʱ��
#define ROTATEDIR_OPPOSITE    (-1)//��ʱ��

#define RADTODEG(x) ((x) * 57.295779513082320876798154814105f)
#define DEGTORAD(x) ((x) * 0.01745329251994329576923690768489f)

lv_obj_t *Eye_Group[4];
lv_obj_t *Eye_base[4];//ͫ��
lv_obj_t *Eye_in_high[4];
lv_obj_t *Eye_in_low[4];
lv_anim_t EyeBodyPath_Anim;
lv_anim_t EyeFocalize_Anim;

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

			lv_anim_set_delay(&EyeBodyPath_Anim, 0);
			//��ת����������۲�����
			lv_anim_set_repeat_count(&EyeFocalize_Anim, 2);
			lv_anim_start(&EyeFocalize_Anim);

		}
    }
}

//�������ද���ص�
static void ChangeEyeFocalize_CB(void *var, int32_t v)
{
	uint8_t i,j;
    int16_t x1,y1;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;

    for ( i = 0; i < 4; i++)
    {
		lv_obj_set_size(Eye_base[i],v,v);
		lv_obj_set_style_radius(Eye_base[i],v/2,LV_PART_MAIN);
		lv_obj_align_to(Eye_base[i],Eye_Group[i],LV_ALIGN_CENTER,0,0);

		//��ʱ��
		x1=(EYE_HIGHLIGHT_HIGH_X)*cos(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G))+(EYE_HIGHLIGHT_HIGH_Y)*sin(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G));
		y1=(EYE_HIGHLIGHT_HIGH_Y)*cos(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G))-(EYE_HIGHLIGHT_HIGH_X)*sin(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G)); 
		lv_obj_align_to(Eye_in_high[i],Eye_Group[i],LV_ALIGN_CENTER,x1,y1);
		lv_obj_set_size(Eye_in_high[i],EYE_HIGHLIGHT_SIZE+(EYE_HOLE_SIZE-v)/2,EYE_HIGHLIGHT_SIZE+(EYE_HOLE_SIZE-v)/2);

		//��ʱ��
		x1=(EYE_HIGHLIGHT_LOW_X)*cos(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G))+(EYE_HIGHLIGHT_LOW_Y)*sin(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G));
		y1=(EYE_HIGHLIGHT_LOW_Y)*cos(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G))-(EYE_HIGHLIGHT_LOW_X)*sin(DEGTORAD((EYE_HOLE_SIZE-v)*EYE_HIGHLIGHT_ANGLE_G));  
		lv_obj_align_to(Eye_in_low[i],Eye_Group[i],LV_ALIGN_CENTER,x1,y1);
		lv_obj_set_size(Eye_in_low[i],EYE_HIGHLIGHT_SIZE/2+(EYE_HOLE_SIZE-v)/2,EYE_HIGHLIGHT_SIZE/2+(EYE_HOLE_SIZE-v)/2);
    }
}


//������������
void Eye_BodyCreate()
{
    uint8_t i=0;

    for ( i = 0; i < 4; i++)
    {
		//���� 37,58,18   56,110,23   
		Eye_Group[i] = lv_obj_create(Face);
		lv_obj_set_size(Eye_Group[i],EYE_SIZE,EYE_SIZE);
		lv_obj_set_style_bg_color(Eye_Group[i],lv_color_make(56,110,23),LV_PART_MAIN);//ͫ����ɫ
		lv_obj_set_style_radius(Eye_Group[i],EYE_SIZE/2,LV_PART_MAIN);
		lv_obj_set_style_outline_width(Eye_Group[i],3,LV_PART_MAIN);
		lv_obj_set_style_outline_color(Eye_Group[i],lv_color_make(84,104,58),LV_PART_MAIN);//ͫ����������ɫ
		lv_obj_set_scrollbar_mode(Eye_Group[i],LV_SCROLLBAR_MODE_OFF);//�رչ�����
        lv_obj_align_to(Eye_Group[i],Face,LV_ALIGN_CENTER,Eye_Position[i][0],Eye_Position[i][1]);
		lv_obj_clear_flag(Eye_Group[i],LV_OBJ_FLAG_CLICKABLE );//�����϶�
        lv_obj_set_style_opa(Eye_Group[i],LV_OPA_TRANSP,LV_PART_MAIN);
		// lv_obj_set_style_clip_corner(Eye_Group[i],true,0);

		//ͫ��
		Eye_base[i] = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_base[i],EYE_HOLE_SIZE,EYE_HOLE_SIZE);
		lv_obj_set_style_radius(Eye_base[i],EYE_HOLE_SIZE/2,LV_PART_MAIN);
		lv_obj_align_to(Eye_base[i],Eye_Group[i],LV_ALIGN_CENTER,0,0);
		lv_obj_set_style_bg_color(Eye_base[i],lv_color_black(),LV_PART_MAIN);
		lv_obj_set_style_outline_width(Eye_base[i],5,LV_PART_MAIN);
		lv_obj_set_style_outline_color(Eye_base[i],lv_color_black(),LV_PART_MAIN);
		lv_obj_set_scrollbar_mode(Eye_base[i],LV_SCROLLBAR_MODE_OFF);
		lv_obj_clear_flag(Eye_base[i],LV_OBJ_FLAG_CLICKABLE );

		//�۲��߹�(�ϲ�)
		Eye_in_high[i] = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_in_high[i],EYE_HIGHLIGHT_SIZE,EYE_HIGHLIGHT_SIZE);
		lv_obj_set_style_radius(Eye_in_high[i],EYE_HIGHLIGHT_SIZE/2,LV_PART_MAIN);
		lv_obj_align_to(Eye_in_high[i],Eye_Group[i],LV_ALIGN_CENTER,EYE_HIGHLIGHT_HIGH_X,EYE_HIGHLIGHT_HIGH_Y);
		lv_obj_set_scrollbar_mode(Eye_in_high[i],LV_SCROLLBAR_MODE_OFF);
		lv_obj_clear_flag(Eye_in_high[i],LV_OBJ_FLAG_CLICKABLE );
		lv_obj_set_style_opa(Eye_in_high[i],150,LV_PART_MAIN);

		//�۲��߹�(�²�)
		Eye_in_low[i] = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_in_low[i],EYE_HIGHLIGHT_SIZE/2,EYE_HIGHLIGHT_SIZE/2);
		lv_obj_set_style_radius(Eye_in_low[i],EYE_HIGHLIGHT_SIZE/4,LV_PART_MAIN);
		lv_obj_align_to(Eye_in_low[i],Eye_Group[i],LV_ALIGN_CENTER,EYE_HIGHLIGHT_LOW_X,EYE_HIGHLIGHT_LOW_Y);
		lv_obj_set_scrollbar_mode(Eye_in_low[i],LV_SCROLLBAR_MODE_OFF);
		lv_obj_clear_flag(Eye_in_low[i],LV_OBJ_FLAG_CLICKABLE );
		lv_obj_set_style_opa(Eye_in_low[i],150,LV_PART_MAIN);
    }
}


// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_ease_in_out);
// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_linear);
// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);

//�������򶯻�
void Eye_BodyAnimPath()
{	
	//��������켣����
	lv_anim_init(&EyeBodyPath_Anim);
	lv_anim_set_var(&EyeBodyPath_Anim,Eye_Group);
	lv_anim_set_values(&EyeBodyPath_Anim,0,90);
	lv_anim_set_time(&EyeBodyPath_Anim, 300);
	lv_anim_set_delay(&EyeBodyPath_Anim, 500);
	lv_anim_set_exec_cb(&EyeBodyPath_Anim, Eye_BodyAnimPath_CB);
	lv_anim_set_path_cb(&EyeBodyPath_Anim,lv_anim_path_ease_in_out);
	lv_anim_set_repeat_delay(&EyeBodyPath_Anim,200);
	lv_anim_set_repeat_count(&EyeBodyPath_Anim, 3);

	lv_anim_start(&EyeBodyPath_Anim);
}


//����ͫ�׽��ද��
void EyeFocalizeAnimCreat()
{
	lv_anim_init(&EyeFocalize_Anim);
	lv_anim_set_var(&EyeFocalize_Anim,Eye_base);
	lv_anim_set_values(&EyeFocalize_Anim,EYE_HOLE_SIZE,EYE_HOLE_MIN_SIZE);
	lv_anim_set_time(&EyeFocalize_Anim, 200);
	lv_anim_set_delay(&EyeFocalize_Anim, 500);
	lv_anim_set_exec_cb(&EyeFocalize_Anim, ChangeEyeFocalize_CB);
	lv_anim_set_path_cb(&EyeFocalize_Anim,lv_anim_path_ease_in_out);
	lv_anim_set_playback_time(&EyeFocalize_Anim,200);
	lv_anim_set_playback_delay(&EyeFocalize_Anim,200);
	lv_anim_set_repeat_delay(&EyeFocalize_Anim,300);
	lv_anim_set_repeat_count(&EyeFocalize_Anim, 1);
}


//�����۾���ת����ʹ���
void RotateEye(uint8_t Dir ,uint8_t times)
{
    lv_anim_set_repeat_count(&EyeBodyPath_Anim, times);
	RotateDir = Dir;
    lv_anim_start(&EyeBodyPath_Anim);
}

//���õ���ͫ�׽������
void ChangeEyeFocalize(uint8_t times)
{
	lv_anim_set_repeat_count(&EyeFocalize_Anim, times);
	lv_anim_start(&EyeFocalize_Anim);
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
	EyeFocalizeAnimCreat();
}




void StartAnim( uint8_t Time)
{
	switch (Time)
	{
		case 1:
			RotateEye(ROTATEDIR_FORWARD, 1);
			break;
		case 2:
		/// Meter_Bg;
			ChangeEyeFocalize(1);
			// lv_scr_load_anim(Face,LV_SCR_LOAD_ANIM_FADE_OUT,1000,100,false);
			//MeterTest();
			// lv_scr_load_anim(Meter_Bg,LV_SCR_LOAD_ANIM_OVER_TOP,1000,100,false);

			break;	
		case 3:
			RotateEye(ROTATEDIR_OPPOSITE, 1);
			break;
		default:
			break;
	}
}
