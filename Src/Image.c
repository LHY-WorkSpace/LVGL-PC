#include "LVGL_UI.h"


void ScanFile()
{
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
         LV_LOG_USER("FS Err %d\n",lv_fs_dir_open(&d, "/"));
    }
}

lv_anim_t TEst_anim;

lv_obj_t *Img;

void Img_AnimCB(void *var, int32_t v)
{
    uint8_t i,j;
    int16_t x1,y1;
    // lv_img_set_zoom(Img,LV_IMG_ZOOM_NONE/v); 
     lv_img_set_angle(Img,v);
}



void Load_Image()
{
    ScanFile();

    Img = lv_img_create(lv_scr_act());
    lv_img_set_src(Img,"S:/Image/123_B.png");
    lv_obj_align(Img,LV_ALIGN_CENTER,0,0);

    //抗锯齿
    // lv_img_set_antialias(Img,TRUE);

    //设置旋转中心点,默认为图片中心
    // lv_img_set_pivot();

    // lv_img_set_size_mode();
   
    //缩放
    lv_img_set_zoom(Img,LV_IMG_ZOOM_NONE); 


    // lv_anim_init(&TEst_anim);
    // lv_anim_set_var(&TEst_anim,Img);
    // lv_anim_set_values(&TEst_anim,0,3599);
    // lv_anim_set_time(&TEst_anim, 5000);
    // lv_anim_set_delay(&TEst_anim, 1000);
    // lv_anim_set_exec_cb(&TEst_anim, Img_AnimCB);
    // lv_anim_set_path_cb(&TEst_anim,lv_anim_path_ease_in_out);
    // lv_anim_set_repeat_delay(&TEst_anim,1000);
    // lv_anim_set_repeat_count(&TEst_anim, 3);
    // lv_anim_start(&TEst_anim);

}
















