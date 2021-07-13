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


#include "headfile.h"
#include "main.h"
#include "cross.h"
#include "yroad.h"
#include "circle.h"
#include "garage.h"
#include "apriltag.h"

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
#include "attitude_solution.h"
#include "openart_mini.h"
#include "camera_param.h"

#include <stdio.h>

#define DEBUGGER_PIN    D4

void process_image();
void find_corners();
void check_straight();

//舵机控制偏差
float angle;

rt_sem_t camera_sem;

debugger_image_t img0 = CREATE_DEBUGGER_IMAGE("raw", MT9V03X_CSI_W, MT9V03X_CSI_H, NULL);
image_t img_raw = DEF_IMAGE(NULL, MT9V03X_CSI_W, MT9V03X_CSI_H);

AT_DTCM_SECTION_ALIGN(uint8_t img_thres_data[MT9V03X_CSI_H][MT9V03X_CSI_W], 64);
debugger_image_t img1 = CREATE_DEBUGGER_IMAGE("thres", MT9V03X_CSI_W, MT9V03X_CSI_H, img_thres_data);
image_t img_thres = DEF_IMAGE((uint8_t*)img_thres_data, MT9V03X_CSI_W, MT9V03X_CSI_H);

AT_DTCM_SECTION_ALIGN(uint8_t img_line_data[MT9V03X_CSI_H][MT9V03X_CSI_W], 64);
debugger_image_t img2 = CREATE_DEBUGGER_IMAGE("line", MT9V03X_CSI_W, MT9V03X_CSI_H, img_line_data);
image_t img_line = DEF_IMAGE((uint8_t*)img_line_data, MT9V03X_CSI_W, MT9V03X_CSI_H);

float thres = 140;
debugger_param_t p0 = CREATE_DEBUGGER_PARAM("thres", 0, 255, 1, &thres);

float block_size = 7;
debugger_param_t p1 = CREATE_DEBUGGER_PARAM("block_size", 1, 21, 2, &block_size);

float clip_value = 2;
debugger_param_t p2 = CREATE_DEBUGGER_PARAM("clip_value", -20, 20, 1, &clip_value);

float begin_x = 30;
debugger_param_t p3 = CREATE_DEBUGGER_PARAM("begin_x", 0, MT9V03X_CSI_W/2, 1, &begin_x);

float begin_y = 174;
debugger_param_t p4 = CREATE_DEBUGGER_PARAM("begin_y", 0, MT9V03X_CSI_H, 1, &begin_y);

float line_blur_kernel = 7;
debugger_param_t p5 = CREATE_DEBUGGER_PARAM("line_blur_kernel", 1, 49, 2, &line_blur_kernel);

float pixel_per_meter = 102;
debugger_param_t p6 = CREATE_DEBUGGER_PARAM("pixel_per_meter", 0, 200, 1, &pixel_per_meter);

float sample_dist = 0.02;
debugger_param_t p7 = CREATE_DEBUGGER_PARAM("sample_dist", 1e-2, 0.4, 1e-2, &sample_dist);

float angle_dist = 0.2;
debugger_param_t p8 = CREATE_DEBUGGER_PARAM("angle_dist", 0, 0.4, 1e-2, &angle_dist);

float far_rate = 0.5;

debugger_param_t p9 = CREATE_DEBUGGER_PARAM("servo_kp", -100, 100, 1e-2, &servo_pid.kp);

float aim_distance = 0.68; // 纯跟踪前视距离
debugger_param_t p10 = CREATE_DEBUGGER_PARAM("aim_distance", 1e-2, 1, 1e-2, &aim_distance);

bool line_show_sample = true;
debugger_option_t opt0 = CREATE_DEBUGGER_OPTION("line_show_sample", &line_show_sample);

bool line_show_blur = false;
debugger_option_t opt1 = CREATE_DEBUGGER_OPTION("line_show_blur", &line_show_blur);

bool track_left = false;
debugger_option_t opt2 = CREATE_DEBUGGER_OPTION("track_left", &track_left);

// 原图左右边线
AT_DTCM_SECTION_ALIGN(int ipts0[POINTS_MAX_LEN][2], 8);
AT_DTCM_SECTION_ALIGN(int ipts1[POINTS_MAX_LEN][2], 8);
int ipts0_num, ipts1_num;
// 变换后左右边线
AT_DTCM_SECTION_ALIGN(float rpts0[POINTS_MAX_LEN][2], 8);
AT_DTCM_SECTION_ALIGN(float rpts1[POINTS_MAX_LEN][2], 8);
int rpts0_num, rpts1_num;
// 变换后左右边线+滤波
AT_DTCM_SECTION_ALIGN(float rpts0b[POINTS_MAX_LEN][2], 8);
AT_DTCM_SECTION_ALIGN(float rpts1b[POINTS_MAX_LEN][2], 8);
int rpts0b_num, rpts1b_num;
// 变换后左右边线+等距采样
AT_DTCM_SECTION_ALIGN(float rpts0s[POINTS_MAX_LEN][2], 8);
AT_DTCM_SECTION_ALIGN(float rpts1s[POINTS_MAX_LEN][2], 8);
int rpts0s_num, rpts1s_num;
// 左右边线局部角度变化率
AT_DTCM_SECTION_ALIGN(float rpts0a[POINTS_MAX_LEN], 8);
AT_DTCM_SECTION_ALIGN(float rpts1a[POINTS_MAX_LEN], 8);
int rpts0a_num, rpts1a_num;
// 左右边线局部角度变化率+非极大抑制
AT_DTCM_SECTION_ALIGN(float rpts0an[POINTS_MAX_LEN], 8);
AT_DTCM_SECTION_ALIGN(float rpts1an[POINTS_MAX_LEN], 8);
int rpts0an_num, rpts1an_num;
// 左/右中线
AT_DTCM_SECTION_ALIGN(float rptsc0[POINTS_MAX_LEN][2], 8);
AT_DTCM_SECTION_ALIGN(float rptsc1[POINTS_MAX_LEN][2], 8);
int rptsc0_num, rptsc1_num;
// 中线
float (*rpts)[2];
int rpts_num;
// 归一化中线
AT_DTCM_SECTION_ALIGN(float rptsn[POINTS_MAX_LEN][2], 8);
int rptsn_num;

// Y角点
int Ypt0_rpts0s_id, Ypt1_rpts1s_id;
bool Ypt0_found, Ypt1_found;

// L角点
int Lpt0_rpts0s_id, Lpt1_rpts1s_id;
bool Lpt0_found, Lpt1_found;

// 长直道
bool is_straight0, is_straight1;

// 弯道
bool is_turn0, is_turn1;

// 当前巡线模式
enum track_type_e track_type = TRACK_RIGHT;


int kxk = 0;
void flag_out(void)
{
    static uint8_t data[23];
    data[0] = 0xAA;
    data[1] = 0xFF;
    data[2] = 0xF1;
    data[3] = 17;
    
    data[4] = BYTE1(circle_type);
    data[5] = BYTE0(circle_type);
    data[6] = BYTE1(yroad_type);
    data[7] = BYTE0(yroad_type);
    data[8] = BYTE1(cross_type);
    data[9] = BYTE0(cross_type);
    data[10] = BYTE1(garage_type);
    data[11] = BYTE0(garage_type);
    
    
    data[12] = Lpt0_rpts0s_id * Lpt0_found;
    data[13] = Lpt1_rpts1s_id * Lpt1_found;
    
    data[14] = Ypt0_rpts0s_id * Ypt0_found;
    data[15] = Ypt1_rpts1s_id * Ypt1_found;
    
    
    data[16] = BYTE0(enable_adc);
    
    data[17] = BYTE0(rptsc0_num);
    data[18] = BYTE0(rptsc1_num);
    
    data[19] = BYTE0(is_straight0);
    data[20] = BYTE0(is_straight1);
    
    uint8_t sumcheck = 0; 
    uint8_t addcheck = 0; 
    for(uint8_t i=0; i < data[3]+4; i++) 
    { 
      sumcheck += data[i]; //从帧头开始，对每一字节进行求和，直到DATA区结
      addcheck += sumcheck;   //每一字节的求和操作，进行一次sumcheck的加 }
    } 
    data[21] = sumcheck;
    data[22] = addcheck;
    
    seekfree_wireless_send_buff(data, sizeof(data));
}


void print_all(){
    static char buffer[128];
    int len = 0;
    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t", apriltag_type);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t", yroad_type);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%f\t%f\t", motor_l.target_speed, motor_r.target_speed);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%f\t%f\t", motor_l.encoder_speed, motor_r.encoder_speed);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t%d\t", (int32_t)motor_l.total_encoder, (int32_t)motor_r.total_encoder);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t%d\t", motor_l.duty, motor_r.duty);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%f\t%f\t", angle, eulerAngle.yaw);
    
    // FIX CIRCLE

//    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t%d\t", Lpt0_found*Lpt0_rpts0s_id, Lpt1_found*Lpt1_rpts1s_id);
    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t%d\t", rpts0s_num, rpts1s_num);
//    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\t%d\t", is_straight0, is_straight1);
//    len += snprintf(buffer+len, sizeof(buffer)-len, "%f\t%f\t", rpts0s[0][0], rpts1s[0][0]);

//    extern float target_speed;
//    len += snprintf(buffer+len, sizeof(buffer)-len, "%f\t", target_speed);
    
    len += snprintf(buffer+len, sizeof(buffer)-len, "%d\n", (int32_t)pit_get_ms(TIMER_PIT));
    seekfree_wireless_send_buff((uint8_t*)buffer, len);
}

int main(void)
{
    camera_sem = rt_sem_create("camera", 0, RT_IPC_FLAG_FIFO);

    mt9v03x_csi_init();
    icm20602_init_spi();
    //陀螺仪零漂矫正
    gyroOffset_init();
    
    encoder_init();
    buzzer_init();
//    button_init();
    motor_init();
    elec_init();
//    display_init();
    openart_mini();
    smotor_init();
    timer_pit_init();
    seekfree_wireless_init();
    
    pit_init();
    pit_start(TIMER_PIT);
    
    // 
    gpio_init(DEBUGGER_PIN, GPI, 0, GPIO_PIN_CONFIG);
    gpio_init(D27, GPI, 0, GPIO_PIN_CONFIG);
    if(gpio_get(D27) == 0) garage_type = GARAGE_OUT_LEFT;
    else garage_type = GARAGE_OUT_RIGHT;
    
    debugger_init();
    debugger_register_image(&img0);
    debugger_register_image(&img1);
    debugger_register_image(&img2);
    debugger_register_param(&p0);
    debugger_register_param(&p1);
    debugger_register_param(&p2);
    debugger_register_param(&p3);
    debugger_register_param(&p4);
    debugger_register_param(&p5);
    debugger_register_param(&p6);
    debugger_register_param(&p7);
    debugger_register_param(&p8);
    debugger_register_param(&p9);
    debugger_register_param(&p10);
    debugger_register_option(&opt0);
    debugger_register_option(&opt1);
    debugger_register_option(&opt2);
    
    uint64_t current_encoder;

    EnableGlobalIRQ(0);
    
    //while(1);
    
    while (1)
    {
        //等待摄像头采集完毕
        rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        img_raw.data = mt9v03x_csi_image[0];
        img0.buffer = mt9v03x_csi_image[0];
        
        uint32_t t1 = pit_get_us(TIMER_PIT);
        //开始处理摄像头图像
        process_image();
        find_corners();

        aim_distance = 0.58;
        
        // 单侧线少，切换巡线方向  切外向圆
       
       if(rpts0s_num < rpts1s_num/2 && rpts0s_num<60){
            track_type = TRACK_RIGHT;
        }else if(rpts1s_num < rpts0s_num/2 && rpts1s_num<60){
            track_type = TRACK_LEFT;
        }else if(rpts0s_num<20 && rpts1s_num>rpts0s_num){
            track_type = TRACK_RIGHT;
        }else if(rpts1s_num<20 && rpts0s_num>rpts1s_num){
            track_type = TRACK_LEFT;
        }

        check_garage();
        if(!enable_adc && garage_type == GARAGE_NONE 
            && get_total_encoder() - openart.aprilencoder>ENCODER_PER_METER
                && angle<3 && cross_type==CROSS_NONE) check_apriltag();
        
       
        if(garage_type == GARAGE_NONE) check_cross();
        if(garage_type == GARAGE_NONE && cross_type == CROSS_NONE && circle_type == CIRCLE_NONE) check_yroad();
        if(garage_type == GARAGE_NONE && cross_type == CROSS_NONE && yroad_type == YROAD_NONE) check_circle();
        
        if(cross_type != CROSS_NONE) {circle_type = CIRCLE_NONE;yroad_type = YROAD_NONE;}
        if(yroad_type != YROAD_NONE) run_yroad();
        if(cross_type != CROSS_NONE) run_cross();
        if(circle_type != CIRCLE_NONE) run_circle();
        if(garage_type != GARAGE_NONE) run_garage();
        
        //车库 ,十字清Aprltag标志
        if(garage_type !=GARAGE_NONE || cross_type!=CROSS_NONE) apriltag_type = APRILTAG_NONE;


        // 中线跟踪
        if(cross_type != CROSS_IN)
        {
            if(track_type == TRACK_LEFT){
                rpts = rptsc0;
                rpts_num = rptsc0_num;
            }else{
                rpts = rptsc1;
                rpts_num = rptsc1_num;
            }
        }
        else
        {
            if(track_type == TRACK_LEFT){
                track_leftline(far_rpts0s + far_Lpt0_rpts0s_id, far_rpts0s_num - far_Lpt0_rpts0s_id, rpts, (int)round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
                rpts_num = far_rpts0s_num - far_Lpt0_rpts0s_id;
            }else{
                track_rightline(far_rpts1s + far_Lpt1_rpts1s_id, far_rpts1s_num - far_Lpt1_rpts1s_id, rpts, (int)round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
                rpts_num = far_rpts1s_num - far_Lpt1_rpts1s_id;
            }
        }

        // 车轮对应点
        float cx = mapx[MT9V03X_CSI_W/2][(int)(MT9V03X_CSI_H*0.78f)];
        float cy = mapy[MT9V03X_CSI_W/2][(int)(MT9V03X_CSI_H*0.78f)];
        
        // 找最近点
        float min_dist = 1e10;
        int begin_id = -1;
        for(int i=0; i<rpts_num; i++){
            float dx = rpts[i][0] - cx;
            float dy = rpts[i][1] - cy;
            float dist = sqrt(dx*dx+dy*dy);
            if(dist < min_dist) {
                min_dist = dist;
                begin_id = i;
            }
        }
        
        if(garage_type == GARAGE_IN_LEFT || garage_type == GARAGE_IN_RIGHT || cross_type == CROSS_IN) begin_id = 0;

        if(begin_id >= 0 && rpts_num-begin_id>=3){
            // 归一化中线
            rpts[begin_id][0] = cx;
            rpts[begin_id][1] = cy;
            rptsn_num = sizeof(rptsn)/sizeof(rptsn[0]);
            resample_points(rpts+begin_id, rpts_num-begin_id, rptsn, &rptsn_num, sample_dist * pixel_per_meter);

            //根据图像计算出车模与赛道之间的位置偏差
            int aim_idx = clip(round(aim_distance/sample_dist), 0, rptsn_num-1);
            
            int aim_idx_near = clip(round(0.25/sample_dist), 0, rptsn_num-1);

          
            float dx = rptsn[aim_idx][0] - cx;
            float dy = cy - rptsn[aim_idx][1] + 0.2 * pixel_per_meter;
            float dn = sqrt(dx*dx+dy*dy);
            float error = -atan2f(dx, dy) * 180 / PI;
            assert(!isnan(error));
            
            float dx_near = rptsn[aim_idx_near][0] - cx;
            float dy_near = cy - rptsn[aim_idx_near][1] + 0.2 * pixel_per_meter;
            float dn_near = sqrt(dx_near*dx_near+dy_near*dy_near);
            float error_near = -atan2f(dx_near, dy_near) * 180 / PI;
            assert(!isnan(error_near));
            
            //根据偏差进行PD计算
            //float angle = pid_solve(&servo_pid, error);
            float pure_angle = -atanf(pixel_per_meter*2*0.2*dx/dn/dn) / PI * 180 / SMOTOR_RATE;
            angle = pid_solve(&servo_pid,pure_angle );
            //angle = pid_solve(&servo_pid, error * far_rate + error_near * (1 - far_rate));
            angle = MINMAX(angle, -14.5, 14.5);
           

            //PD计算之后的值用于寻迹舵机的控制
            if(!enable_adc) smotor1_control(servo_duty(SMOTOR1_CENTER + angle));
            else{
                smotor1_control(servo_duty(SMOTOR1_CENTER));
                yroad_type = YROAD_NONE;
                circle_type = CIRCLE_NONE;
                cross_type = CROSS_NONE;
                garage_type = GARAGE_NONE;
                apriltag_type = APRILTAG_NONE;
            }            
        }else{
            rptsn_num = 0;
        }
        
        // 绘制调试图像
        if(gpio_get(DEBUGGER_PIN)){
            // 原图绘制中线
//            for(int i=0; i<rptsn_num; i++){
//                int pt[2];
//                if(map_inv(rptsn[i], pt)){ 
//                    AT_IMAGE(&img_raw, clip(pt[0], 0, img_raw.width-1), clip(pt[1], 0, img_raw.height-1)) = 0;
//                }
//            }
            
            // 绘制二值化图像
            if(p_active_image == &img1) {
                //threshold(&img_raw, &img_thres, low_thres, 0, 255);
                adaptive_threshold(&img_raw, &img_thres, block_size, clip_value, 0, 255);
                for(int i=0; i<img_thres.width/2 - begin_x; i++){
                    AT_IMAGE(&img_thres,(int)i ,(int)begin_y) = 0;
                }
                for(int i=img_thres.width/2 + begin_x; i<img_thres.width; i++){
                    AT_IMAGE(&img_thres, (int)i ,(int)begin_y) = 0;
                }
            }

            //
            clear_image(&img_line);
            // 绘制道路元素
            draw_yroad();
            draw_circle();
            draw_cross();

            // 绘制道路线            
            for(int i=0; i<rpts0s_num; i++){
                AT_IMAGE(&img_line, clip(rpts0s[i][0], 0, img_line.width-1), clip(rpts0s[i][1], 0, img_line.height-1)) = 255;
            }
            for(int i=0; i<rpts1s_num; i++){
                AT_IMAGE(&img_line, clip(rpts1s[i][0], 0, img_line.width-1), clip(rpts1s[i][1], 0, img_line.height-1)) = 255;
            }
            for(int i=0; i<rptsn_num; i++){
                AT_IMAGE(&img_line, clip(rptsn[i][0], 0, img_line.width-1), clip(rptsn[i][1], 0, img_line.height-1)) = 255;
            }
            // 绘制锚点
            int aim_idx = clip(round(aim_distance/sample_dist), 0, rptsn_num-1);
            draw_x(&img_line, rptsn[aim_idx][0], rptsn[aim_idx][1], 3, 255);
            // 绘制角点
            if(Lpt0_found){
                draw_x(&img_line, rpts0s[Lpt0_rpts0s_id][0], rpts0s[Lpt0_rpts0s_id][1], 3, 255);
            }
            if(Lpt1_found){
                draw_x(&img_line, rpts1s[Lpt1_rpts1s_id][0], rpts1s[Lpt1_rpts1s_id][1], 3, 255);
            }
        }
        
        // print debug information
        uint32_t t2 = pit_get_us(TIMER_PIT);
        static uint8_t buffer[64];
        int len = snprintf((char*)buffer, sizeof(buffer), "main time: %fms\n", (t2-t1)/1000.f);
        //extern float target_speed;
        //int len = snprintf((char*)buffer, sizeof(buffer), "target_speed: %f\n", target_speed);
        
        static int cnt = 0;
        
        if(gpio_get(DEBUGGER_PIN)) {
            
            if(++cnt % 4 == 0) debugger_worker();
        }
        //flag_out();
        //wireless_show();
        //seekfree_wireless_send_buff(buffer, len);
        
        
        print_all();
        
        check_openart();
    }
}

void process_image(){
    // 原图找边线
    int x1=img_raw.width/2-begin_x, y1=begin_y;
    ipts0_num=sizeof(ipts0)/sizeof(ipts0[0]);
    for(;x1>0; x1--) if(AT_IMAGE(&img_raw, x1-1, y1) < thres) break;
    if(AT_IMAGE(&img_raw, x1, y1) >= thres) findline_lefthand_adaptive(&img_raw, block_size, clip_value, x1, y1, ipts0, &ipts0_num);
    else ipts0_num = 0;
    int x2=img_raw.width/2+begin_x, y2=begin_y;
    ipts1_num=sizeof(ipts1)/sizeof(ipts1[0]);
    for(;x2<img_raw.width-1; x2++) if(AT_IMAGE(&img_raw, x2+1, y2) < thres) break;
    if(AT_IMAGE(&img_raw, x2, y2) >= thres) findline_righthand_adaptive(&img_raw, block_size, clip_value, x2, y2, ipts1, &ipts1_num);
    else ipts1_num = 0;
    
    // 去畸变+透视变换
    for(int i=0; i<ipts0_num; i++) {
        rpts0[i][0] = mapx[ipts0[i][1]][ipts0[i][0]];
        rpts0[i][1] = mapy[ipts0[i][1]][ipts0[i][0]];
    }
    rpts0_num = ipts0_num;
    for(int i=0; i<ipts1_num; i++) {
        rpts1[i][0] = mapx[ipts1[i][1]][ipts1[i][0]];
        rpts1[i][1] = mapy[ipts1[i][1]][ipts1[i][0]];
    }
    rpts1_num = ipts1_num;
    
    
    // 边线滤波
    blur_points(rpts0, rpts0_num, rpts0b, (int)round(line_blur_kernel));
    rpts0b_num = rpts0_num;
    blur_points(rpts1, rpts1_num, rpts1b, (int)round(line_blur_kernel));
    rpts1b_num = rpts1_num;
    
    // 边线等距采样
    rpts0s_num = sizeof(rpts0s)/sizeof(rpts0s[0]);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, sample_dist * pixel_per_meter);
    rpts1s_num = sizeof(rpts1s)/sizeof(rpts1s[0]);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, sample_dist * pixel_per_meter);
    
    // 边线局部角度变化率
    local_angle_points(rpts0s, rpts0s_num, rpts0a, (int)round(angle_dist / sample_dist));
    rpts0a_num = rpts0s_num;
    local_angle_points(rpts1s, rpts1s_num, rpts1a, (int)round(angle_dist / sample_dist));
    rpts1a_num = rpts1s_num;
    
    // 角度变化率非极大抑制
    nms_angle(rpts0a, rpts0a_num, rpts0an, (int)round(angle_dist / sample_dist) * 2 + 1);
    rpts0an_num = rpts0a_num;
    nms_angle(rpts1a, rpts1a_num, rpts1an, (int)round(angle_dist / sample_dist) * 2 + 1);
    rpts1an_num = rpts1a_num;
    
    // 左右中线跟踪
    track_leftline(rpts0s, rpts0s_num, rptsc0, (int)round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    rptsc0_num = rpts0s_num;
    track_rightline(rpts1s, rpts1s_num, rptsc1, (int)round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    rptsc1_num = rpts1s_num;
}

void find_corners() {
    // 识别Y,L拐点
    Ypt0_found = Ypt1_found = Lpt0_found = Lpt1_found = false;
    is_straight0 = rpts0s_num > 1. / sample_dist;
    is_straight1 = rpts1s_num > 1. / sample_dist;
    for(int i=0; i<rpts0s_num; i++){
        if(rpts0an[i] == 0) continue;
        int im1 = clip(i-(int)round(angle_dist / sample_dist), 0, rpts0s_num-1);
        int ip1 = clip(i+(int)round(angle_dist / sample_dist), 0, rpts0s_num-1);
        float conf = fabs(rpts0a[i]) - (fabs(rpts0a[im1]) + fabs(rpts0a[ip1])) / 2;
        if(Ypt0_found == false && 30. / 180. * PI < conf && conf < 65. / 180. * PI && i < 0.8 / sample_dist){
            Ypt0_rpts0s_id = i;
            Ypt0_found = true;
        }
        if(Lpt0_found == false && 70. / 180. * PI < conf && conf < 140. / 180. * PI  && i < 0.8 / sample_dist){
            Lpt0_rpts0s_id = i;
            Lpt0_found = true;
        }
        
        if(conf > 5. / 180. * PI && i < 1.0 / sample_dist) is_straight0 = false;
        if(Ypt0_found == true && Lpt0_found == true && is_straight0 == false) break;
    }
    for(int i=0; i<rpts1s_num; i++){
        if(rpts1an[i] == 0) continue;
        int im1 = clip(i-(int)round(angle_dist / sample_dist), 0, rpts1s_num-1);
        int ip1 = clip(i+(int)round(angle_dist / sample_dist), 0, rpts1s_num-1);
        float conf = fabs(rpts1a[i]) - (fabs(rpts1a[im1]) + fabs(rpts1a[ip1])) / 2;
        if(Ypt1_found == false && 30. / 180. * PI < conf && conf < 65. / 180. * PI && i < 0.8 / sample_dist){
            Ypt1_rpts1s_id = i;
            Ypt1_found = true;
        }
        if(Lpt1_found == false && 70. / 180. * PI < conf && conf < 140. / 180. * PI && i < 0.8 / sample_dist){
            Lpt1_rpts1s_id = i;
            Lpt1_found = true;
        }
        
        if(conf > 5. / 180. * PI && i < 1.0 / sample_dist) is_straight1 = false;
        
        if(Ypt1_found == true && Lpt1_found == true && is_straight1 == false) break;
    }
    // Y点二次检查
    if(Ypt0_found && Ypt1_found){
        float dx = rpts0s[Ypt0_rpts0s_id][0] - rpts1s[Ypt1_rpts1s_id][0];
        float dy = rpts0s[Ypt0_rpts0s_id][1] - rpts1s[Ypt1_rpts1s_id][1];
        float dn = sqrtf(dx*dx+dy*dy);
        if(fabs(dn - 0.45 * pixel_per_meter) < 0.15 * pixel_per_meter){
            float dwx = rpts0s[clip(Ypt0_rpts0s_id+50, 0, rpts0s_num-1)][0] - rpts1s[clip(Ypt1_rpts1s_id+50, 0, rpts1s_num-1)][0];
            float dwy = rpts0s[clip(Ypt0_rpts0s_id+50, 0, rpts0s_num-1)][1] - rpts1s[clip(Ypt1_rpts1s_id+50, 0, rpts1s_num-1)][1];
            float dwn = sqrtf(dwx*dwx+dwy*dwy);
            if(!(dwn > 0.7 * pixel_per_meter && rpts0s[clip(Ypt0_rpts0s_id+50, 0, rpts0s_num-1)][0] < rpts0s[Ypt0_rpts0s_id][0] &&
                                              rpts1s[clip(Ypt1_rpts1s_id+50, 0, rpts1s_num-1)][0] > rpts1s[Ypt1_rpts1s_id][0])){
                Ypt0_found = Ypt1_found = false;
            }
        }else{
            Ypt0_found = Ypt1_found = false;
        }
    }
    // L点二次检查，车库模式不检查
    if(garage_type == GARAGE_NONE){    
        if(Lpt0_found && Lpt1_found){
            float dx = rpts0s[Lpt0_rpts0s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
            float dy = rpts0s[Lpt0_rpts0s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
            float dn = sqrtf(dx*dx+dy*dy);
            if(fabs(dn - 0.45 * pixel_per_meter) < 0.15 * pixel_per_meter){
                float dwx = rpts0s[clip(Lpt0_rpts0s_id+50, 0, rpts0s_num-1)][0] - rpts1s[clip(Lpt1_rpts1s_id+50, 0, rpts1s_num-1)][0];
                float dwy = rpts0s[clip(Lpt0_rpts0s_id+50, 0, rpts0s_num-1)][1] - rpts1s[clip(Lpt1_rpts1s_id+50, 0, rpts1s_num-1)][1];
                float dwn = sqrtf(dwx*dwx+dwy*dwy);
                if(!(dwn > 0.7 * pixel_per_meter && rpts0s[clip(Lpt0_rpts0s_id+50, 0, rpts0s_num-1)][0] < rpts0s[Lpt0_rpts0s_id][0] &&
                                                  rpts1s[clip(Lpt1_rpts1s_id+50, 0, rpts1s_num-1)][0] > rpts1s[Lpt1_rpts1s_id][0])){
                    Lpt0_found = Lpt1_found = false;
                }
            }else{
                Lpt0_found = Lpt1_found = false;
            }
        }
    }
}

int clip(int x, int low, int up){
    return x>up?up:x<low?low:x;
}

float fclip(float x, float low, float up){
    return x>up?up:x<low?low:x;
}

