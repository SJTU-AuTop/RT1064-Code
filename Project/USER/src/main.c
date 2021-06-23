/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本


//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完

//下载代码前请根据自己使用的下载器在工程里设置下载器为自己所使用的

#include "headfile.h"

#include "timer_pit.h"
#include "encoder.h"
#include "buzzer.h"
#include "button.h"
#include "motor.h"
#include "elec.h"
#include "openart_mini.h"
#include "smotor.h"

#include "debugger.h"
#include "imgproc.h"

#include <stdio.h>

rt_sem_t camera_sem;

debugger_image_t img0 = CREATE_DEBUGGER_IMAGE("raw", MT9V03X_CSI_W, MT9V03X_CSI_H, NULL);
image_t img_raw = DEF_IMAGE(NULL, MT9V03X_CSI_W, MT9V03X_CSI_H);

int thres_value = 150;
debugger_param_t p0 = CREATE_DEBUGGER_PARAM("thres", 0, 255, 150, &thres_value);

int kp100 = -2500;
debugger_param_t p1 = CREATE_DEBUGGER_PARAM("kp100", -10000, 10000, -3000, &kp100);

int car_width = 54;
debugger_param_t p2 = CREATE_DEBUGGER_PARAM("car_width", 0, 250, 54, &car_width);

int begin_y = 220;
debugger_param_t p3 = CREATE_DEBUGGER_PARAM("begin_y", 0, MT9V03X_CSI_H, 220, &begin_y);

int pixel_per_meter = 102;
debugger_param_t p4 = CREATE_DEBUGGER_PARAM("pixel_per_meter", 0, MT9V03X_CSI_H, 102, &pixel_per_meter);

bool show_bin = false;
debugger_option_t opt0 = CREATE_DEBUGGER_OPTION("show_bin", false, &show_bin);

bool show_line = false;
debugger_option_t opt1 = CREATE_DEBUGGER_OPTION("show_line", false, &show_line);

bool show_approx = false;
debugger_option_t opt2 = CREATE_DEBUGGER_OPTION("show_approx", false, &show_approx);

AT_DTCM_SECTION_ALIGN(int pts1[MT9V03X_CSI_H][2], 8);
AT_DTCM_SECTION_ALIGN(int pts2[MT9V03X_CSI_H][2], 8);
AT_DTCM_SECTION_ALIGN(float pts1_inv[MT9V03X_CSI_H][2], 8);
AT_DTCM_SECTION_ALIGN(float pts2_inv[MT9V03X_CSI_H][2], 8);
AT_DTCM_SECTION_ALIGN(float line1[MT9V03X_CSI_H][2], 8);
AT_DTCM_SECTION_ALIGN(float line2[MT9V03X_CSI_H][2], 8);
AT_DTCM_SECTION_ALIGN(float pts_road[MT9V03X_CSI_H][2], 8);

#define DEBUG_PIN   D4

void cross_dot(const float x[3], const float y[3], float out[3]){
    out[0] = x[1]*y[2]-x[2]*y[1];
    out[1] = x[2]*y[0]-x[0]*y[2];
    out[2] = x[0]*y[1]-x[1]*y[0];
}

float K[3][3] = {
    {1.241016008672135e+02,                     0, 1.864993169331173e+02},
    {                    0, 1.241477111009435e+02, 1.174203927052049e+02},
    {                    0,                     0,                     1},
};

float D[5] = {0.141323308507051,-0.139460262349753,-0.002478722783453,9.106538935854130e-04,0.027173897921792};

extern int clip(int x, int low, int up);
extern float mapx[240][376];
extern float mapy[240][376];
extern pid_param_t servo_pid;

#define ROAD_HALF_WIDTH  (0.225)

void track_leftline(float line[][2], int num, float tracked[][2]){
    for(int i=2; i<num-2; i++){
        float dx = line[i+2][0] - line[i-2][0];
        float dy = line[i+2][1] - line[i-2][1];
        float dn = sqrt(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;
        tracked[i][0] = line[i][0] - dy * pixel_per_meter * ROAD_HALF_WIDTH;
        tracked[i][1] = line[i][1] + dx * pixel_per_meter * ROAD_HALF_WIDTH;
    }
}

void track_rightline(float line[][2], int num, float tracked[][2]){
    for(int i=2; i<num-2; i++){
        float dx = line[i+2][0] - line[i-2][0];
        float dy = line[i+2][1] - line[i-2][1];
        float dn = sqrt(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;
        tracked[i][0] = line[i][0] + dy * pixel_per_meter * ROAD_HALF_WIDTH;
        tracked[i][1] = line[i][1] - dx * pixel_per_meter * ROAD_HALF_WIDTH;
    }
}

float error, dx, dy;

int main(void)
{
	camera_sem = rt_sem_create("camera", 0, RT_IPC_FLAG_FIFO);

    mt9v03x_csi_init();
    icm20602_init_spi();
    
    encoder_init();
//    buzzer_init();
//    button_init();
    motor_init();
//    elec_init();
//    openart_mini();
    smotor_init();
    timer_pit_init();
    seekfree_wireless_init();
    
    pit_init();
    pit_start(PIT_CH3);
    
    // 
    gpio_init(DEBUG_PIN, GPI, 0, GPIO_PIN_CONFIG);
    
    debugger_init();
    debugger_register_image(&img0);
    debugger_register_param(&p0);
    debugger_register_param(&p1);
    debugger_register_param(&p2);
    debugger_register_param(&p3);
    debugger_register_param(&p4);
    debugger_register_option(&opt0);
    debugger_register_option(&opt1);
    debugger_register_option(&opt2);
    
    uint32_t t1, t2;
    
    EnableGlobalIRQ(0);
    while (1)
    {		//等待摄像头采集完毕
        rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        img_raw.data = mt9v03x_csi_image[0];
        img0.buffer = mt9v03x_csi_image[0];
        //开始处理摄像头图像
        t1 = pit_get_us(PIT_CH3);
        if(show_bin) {
            threshold(&img_raw, &img_raw, thres_value);
            int pt0[2] = {img_raw.width/2-car_width, begin_y};
            int pt1[2] = {0, begin_y};
            draw_line(&img_raw, pt0, pt1, 0);
            pt0[0] = img_raw.width/2+car_width;
            pt1[0] = img_raw.width-1;
            draw_line(&img_raw, pt0, pt1, 0);
        } else {
            int x1=img_raw.width/2-car_width, y1=begin_y, num1=sizeof(pts1)/sizeof(pts1[0]);
            for(;x1>0; x1--) if(AT_IMAGE(&img_raw, x1, y1) < thres_value) break;
            if(AT_IMAGE(&img_raw, x1+1, y1) >= thres_value) findline_lefthand_with_thres(&img_raw, thres_value, x1+1, y1, pts1, &num1);
            else num1 = 0;
            
            int x2=img_raw.width/2+car_width, y2=begin_y, num2=sizeof(pts2)/sizeof(pts2[0]);
            for(;x2<img_raw.width-1; x2++) if(AT_IMAGE(&img_raw, x2, y2) < thres_value) break;
            if(AT_IMAGE(&img_raw, x2-1, y2) >= thres_value) findline_righthand_with_thres(&img_raw, thres_value, x2-1, y2, pts2, &num2);
            else num2 = 0;
            
            for(int i=0; i<num1; i++) {
                pts1_inv[i][0] = mapx[pts1[i][1]][pts1[i][0]];
                pts1_inv[i][1] = mapy[pts1[i][1]][pts1[i][0]];
            }
            for(int i=0; i<num2; i++) {
                pts2_inv[i][0] = mapx[pts2[i][1]][pts2[i][0]];
                pts2_inv[i][1] = mapy[pts2[i][1]][pts2[i][0]];
            }

            track_rightline(pts2_inv, num2, pts_road);
            
            int line1_num=sizeof(line1)/sizeof(line1[0]);
            int line2_num=sizeof(line2)/sizeof(line2[0]);
            if(num1 > 10) approx_lines_f(pts1_inv, num1, 4, line1, &line1_num);
            else line1_num = 0;
            if(num2 > 10) approx_lines_f(pts2_inv, num2, 4, line2, &line2_num);
            else line2_num = 0;
            
            if(show_line){
                clear_image(&img_raw);
//                for(int i=0; i<num1; i++){
//                    AT_IMAGE(&img_raw, clip(pts1[i][0], 0, img_raw.width-1), clip(pts1[i][1], 0, img_raw.height-1)) = 255;
//                }
//                for(int i=0; i<num2; i++){
//                    AT_IMAGE(&img_raw, clip(pts2[i][0], 0, img_raw.width-1), clip(pts2[i][1], 0, img_raw.height-1)) = 255;
//                }
                for(int i=0; i<num1; i++){
                    AT_IMAGE(&img_raw, clip(pts1_inv[i][0], 0, img_raw.width-1), clip(pts1_inv[i][1], 0, img_raw.height-1)) = 255;
                }
                for(int i=0; i<num2; i++){
                    AT_IMAGE(&img_raw, clip(pts2_inv[i][0], 0, img_raw.width-1), clip(pts2_inv[i][1], 0, img_raw.height-1)) = 255;
                }
                for(int i=2; i<num2-2; i++){
                    AT_IMAGE(&img_raw, clip(pts_road[i][0], 0, img_raw.width-1), clip(pts_road[i][1], 0, img_raw.height-1)) = 255;
                }
            }else if(show_approx){
                clear_image(&img_raw);
                int pt0[2], pt1[2];
                for(int i=1; i<line1_num; i++){
                    pt0[0] = line1[i-1][0];
                    pt0[1] = line1[i-1][1];
                    pt1[0] = line1[i][0];
                    pt1[1] = line1[i][1];
                    draw_line(&img_raw, pt0, pt1, 255);
                }
                for(int i=1; i<line2_num; i++){
                    pt0[0] = line2[i-1][0];
                    pt0[1] = line2[i-1][1];
                    pt1[0] = line2[i][0];
                    pt1[1] = line2[i][1];
                    draw_line(&img_raw, pt0, pt1, 255);
                }
            }
            
            //根据图像计算出车模与赛道之间的位置偏差
            int idx = num2 < 103 ? num2 - 3 : 100;
            dx = (pts_road[idx][0] - img_raw.width / 2.) / pixel_per_meter;
            dy = (img_raw.height - pts_road[idx][1]) / pixel_per_meter;
            error = atan2f(dx, dy);
            
            //根据偏差进行PD计算
            servo_pid.kp = kp100 / 100.;
            float angle = pid_solve(&servo_pid, error);
            angle = MINMAX(angle, -13, 13);
            
            //PD计算之后的值用于寻迹舵机的控制
            smotor1_control(servo_duty(90 + angle));
        }
        
        
        // print debug information
        uint32_t tmp = pit_get_us(PIT_CH3);
        static uint8_t buffer[64];
        int len = snprintf((char*)buffer, sizeof(buffer), "process=%dus, period=%dus\r\n", tmp-t1, tmp-t2);
        t2 = tmp;
        
        if(gpio_get(DEBUG_PIN)) debugger_worker();
        else usb_cdc_send_buff(buffer, len);
    }
}

  



