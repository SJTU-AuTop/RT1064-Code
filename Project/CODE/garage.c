#include "garage.h"
#include "camera_param.h"
#include "attitude_solution.h"
#include "buzzer.h"
#include "main.h"


enum garage_type_e garage_type = GARAGE_OUT_LEFT;

bool garage_yaw_init = false;
float garage_yaw = 0;

float angle_diff(float a1, float a2){
    float c1 = cosf(a1 / 180 * PI);
    float s1 = sinf(a1 / 180 * PI);
    float c2 = cosf(a2 / 180 * PI);
    float s2 = sinf(a2 / 180 * PI);
    float c = c1*c2+s1*s2;
    float s = s1*c2-s2*c1;
    return atan2f(s, c) * 180 / PI;
}

int zebra_cross_flag_begin = 0;
int zebra_cross_flag0[30];
int zebra_cross_flag0_num = 0;
int zebra_cross_flag1[30];
int zebra_cross_flag1_num = 0;

void check_garage(){
    if(!garage_yaw_init){
        garage_yaw = eulerAngle.yaw;
        garage_yaw_init = true;
    }
    if(garage_type == GARAGE_NONE){
        if(Lpt0_found && !Lpt1_found){
            if(rpts1s_num > 0)
                track_rightline(rpts1s, rpts1s_num, rpts, (int)round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
            rpts_num = rpts1s_num;
        }else if(Lpt1_found && !Lpt0_found){
            if(rpts1s_num > 0)
                track_leftline(rpts0s, rpts0s_num, rpts, (int)round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
            rpts_num = rpts0s_num;
        }else{
            rpts_num = 0;
        }
        int pt[2];
        if(rpts_num == 0) return;
        for(int i=20; i<MIN(80, rpts_num-1); i++){
            if(!map_inv(rpts[MIN(i, rpts_num-1)], pt)) return;
            draw_x(&img_raw, pt[0], pt[1], 3, 0);
            
            zebra_cross_flag_begin = AT_IMAGE(&img_raw, pt[0], pt[1]) > thres;
            
            memset(zebra_cross_flag0, 0, sizeof(zebra_cross_flag0));
            zebra_cross_flag0_num = 0;
            for(int x=pt[0]-1; x>=MAX(0, pt[0]-50); x--){
                if(zebra_cross_flag_begin == 0){ // even white, odd black
                    if(zebra_cross_flag0_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current even, current white
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    }else if(zebra_cross_flag0_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current even, current black
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    }else if(zebra_cross_flag0_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current odd, current white
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    }else if(zebra_cross_flag0_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current odd, current black
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    }
                }else{ // even black, odd white
                    if(zebra_cross_flag0_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current even, current white
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    }else if(zebra_cross_flag0_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current even, current black
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    }else if(zebra_cross_flag0_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current odd, current white
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    }else if(zebra_cross_flag0_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current odd, current black
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    }
                }
            }
            
            memset(zebra_cross_flag1, 0, sizeof(zebra_cross_flag1));
            zebra_cross_flag1_num = 0;
            for(int x=pt[0]+1; x<=MIN(img_raw.width-1, pt[0]+50); x++){
                if(zebra_cross_flag_begin == 0){ // even white, odd black
                    if(zebra_cross_flag1_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current even, current white
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    }else if(zebra_cross_flag1_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current even, current black
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    }else if(zebra_cross_flag1_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current odd, current white
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    }else if(zebra_cross_flag1_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current odd, current black
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    }
                }else{ // even black, odd white
                    if(zebra_cross_flag1_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current even, current white
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    }else if(zebra_cross_flag1_num%2==0 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current even, current black
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    }else if(zebra_cross_flag1_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])>thres) { // current odd, current white
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    }else if(zebra_cross_flag1_num%2==1 && AT_IMAGE(&img_raw, x, pt[1])<thres) { // current odd, current black
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    }
                }
            }
            
            int i0=1;
            for(; i0<zebra_cross_flag0_num-1; i0++){
                if(abs(zebra_cross_flag0[i0+1]-zebra_cross_flag0[i0])>=10) break;
            }
            bool is_zebra0 = i0>6;
            
            int i1=1;
            for(; i1<zebra_cross_flag1_num-1; i1++){
                if(abs(zebra_cross_flag1[i1+1]-zebra_cross_flag1[i1])>=10) break;
            }
            bool is_zebra1 = i1>6;
            
            if(is_zebra0 && is_zebra1){
                if(Lpt0_found && !Lpt1_found){
                    garage_type = GARAGE_IN_LEFT;
                    garage_yaw = eulerAngle.yaw;
                    break;
                }else if(!Lpt0_found && Lpt1_found){
                    garage_type = GARAGE_IN_RIGHT;
                    garage_yaw = eulerAngle.yaw;
                    break;
                }
            }
        }
    }
}

void run_garage(){
    switch(garage_type){
        case GARAGE_OUT_LEFT:
            aim_distance = 0.2;
            track_type = TRACK_LEFT;
            if(angle_diff(eulerAngle.yaw, garage_yaw) > 45){
                garage_type = GARAGE_NONE;
            }
            break;
        case GARAGE_OUT_RIGHT:
            aim_distance = 0.2;
            track_type = TRACK_RIGHT;
            if(angle_diff(eulerAngle.yaw, garage_yaw) < -45){
                garage_type = GARAGE_NONE;
            }
            break;
        case GARAGE_IN_LEFT:
            aim_distance = 0.2;
            track_type = TRACK_LEFT;
            if(angle_diff(eulerAngle.yaw, garage_yaw) > 45 && Lpt0_found && Lpt0_rpts0s_id < 30 && Lpt1_found && Lpt1_rpts1s_id < 30){
                garage_type = GARAGE_STOP;
                rt_mb_send(buzzer_mailbox, 2);
            }
            break;
        case GARAGE_IN_RIGHT:
            aim_distance = 0.2;
            track_type = TRACK_RIGHT;
            if(angle_diff(eulerAngle.yaw, garage_yaw) > 45 && Lpt0_found && Lpt0_rpts0s_id < 30 && Lpt1_found && Lpt1_rpts1s_id < 30){
                garage_type = GARAGE_STOP;
                rt_mb_send(buzzer_mailbox, 2);
            }
            break;
        default:
            (void)0;
    }
}