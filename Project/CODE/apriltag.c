#include "apriltag.h"
#include "motor.h"
#include "buzzer.h"
#include "camera_param.h"
#include "main.h"
#include "openart_mini.h"

enum apriltag_type_e apriltag_type = APRILTAG_NONE;

const char* apriltag_type_name[APRILTAG_NUM] = {
    "APRILTAG_NONE",
    "APRILTAG_MAYBE",
    "APRILTAG_FOUND",
    "APRILTAG_LEAVE",
};

extern openart_param_t openart;

int32_t apriltag_time = -10000;

int64_t apriltag_encoder = -10000;

// 0:左中线找apriltag
// 1:右中线找apriltag
// 0-1相互交替
int apriltag_cnt = 0;
float (*apriltag_rpts)[2];
int apriltag_rpts_num;

// “一坨”的区域大小
const int apriltag_half_size = 15 / 2;
// “一坨”的灰度阈值
const int apriltag_block_thres = 150;

void check_apriltag(){
    if(apriltag_type == APRILTAG_NONE || apriltag_type == APRILTAG_MAYBE){
        apriltag_type = APRILTAG_NONE;
        //存在L角点,区分车库与Apriltag
        if(Lpt0_found && Lpt0_rpts0s_id < 0.5 / sample_dist) return;
        if(Lpt1_found && Lpt1_rpts1s_id < 0.5 / sample_dist) return;
        
        apriltag_cnt=1-apriltag_cnt;
        if(apriltag_cnt == 0){
            apriltag_rpts = rptsc0;
            apriltag_rpts_num = rptsc0_num;
        }else{
            apriltag_rpts = rptsc1;
            apriltag_rpts_num = rptsc1_num;
        }
        int pt[2];
        for(int i=0.1/sample_dist; i<MIN(1./sample_dist, apriltag_rpts_num); i++){
            if(!map_inv(apriltag_rpts[i], pt)) continue;
            if(pt[1] > MT9V03X_CSI_H - 120) continue;
            AT_IMAGE(&img_raw, pt[0], pt[1]) = 0;

            int total_cnt = (apriltag_half_size*2+1)*(apriltag_half_size*2+1);
            
            //自适应阈值
            int local_thres = 0;
            for(int dy=-apriltag_half_size; dy<=apriltag_half_size; dy++){
                for(int dx=-apriltag_half_size; dx<=apriltag_half_size; dx++){
                    local_thres += AT_IMAGE_CLIP(&img_raw, pt[0]+dx, pt[1]+dy);
                }
            }
            local_thres = local_thres / total_cnt - 5;

            //存储跳变点与黑色点个数
            int black_cnt = 0,bound_cnt = 0;
            for(int dy=-apriltag_half_size; dy<=apriltag_half_size; dy++){
                for(int dx=-apriltag_half_size; dx<=apriltag_half_size; dx++){
                    black_cnt += AT_IMAGE_CLIP(&img_raw, pt[0]+dx, pt[1]+dy) < local_thres;
                    bound_cnt += abs(AT_IMAGE_CLIP(&img_raw, pt[0]+dx, pt[1]+dy)
                                     - AT_IMAGE_CLIP(&img_raw, pt[0]+dx+1, pt[1]+dy)) > 40;
                                       
                }
            }
            
            if(black_cnt > total_cnt/5 && bound_cnt> total_cnt/20){
              if(i < 0.5/sample_dist){
                  //记录位置,用于位置环,存储第一次found的位置用于位置环
                if(apriltag_type != APRILTAG_MAYBE && apriltag_type != APRILTAG_FOUND){
                    motor_l.target_encoder = motor_l.total_encoder;
                    motor_r.target_encoder = motor_r.total_encoder;
                  }  
                 apriltag_type = APRILTAG_FOUND;

                  apriltag_encoder = get_total_encoder();
                  apriltag_time = rt_tick_get_millisecond();

                  rt_mb_send(buzzer_mailbox, 1);

                 // draw circle
                 draw_o(&img_raw, pt[0], pt[1], 8, 0);

              }
              else{
                if(apriltag_type != APRILTAG_MAYBE){
                    motor_l.target_encoder = motor_l.total_encoder;
                    motor_r.target_encoder = motor_r.total_encoder;
                  }
                  apriltag_type = APRILTAG_MAYBE;
                  rt_mb_send(buzzer_mailbox, 1);

                  apriltag_encoder = get_total_encoder();
                  apriltag_time = rt_tick_get_millisecond();

                  // draw circle
                  draw_o(&img_raw, pt[0], pt[1], 8, 0);

              }
                //记录等待位置,超出1m清掉
                openart.aprilwaitencoder = get_total_encoder();
                break;
            }
        }
    }else if(apriltag_type == APRILTAG_LEAVE){
        if(get_total_encoder() - apriltag_encoder > 1. * ENCODER_PER_METER){
            apriltag_type = APRILTAG_NONE;
        }
    }
}
