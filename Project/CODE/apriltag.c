#include "apriltag.h"
#include "motor.h"
#include "buzzer.h"
#include "camera_param.h"
#include "main.h"

enum apriltag_type_e apriltag_type = APRILTAG_NONE;

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
            
            int local_thres = 0;
            for(int dy=-apriltag_half_size; dy<=apriltag_half_size; dy++){
                for(int dx=-apriltag_half_size; dx<=apriltag_half_size; dx++){
                    local_thres += AT_IMAGE_CLIP(&img_raw, pt[0]+dx, pt[1]+dy);
                }
            }
            local_thres = local_thres / total_cnt - 5;
            
            int black_cnt = 0,bound_cnt = 0;
            for(int dy=-apriltag_half_size; dy<=apriltag_half_size; dy++){
                for(int dx=-apriltag_half_size; dx<=apriltag_half_size; dx++){
                    black_cnt += AT_IMAGE_CLIP(&img_raw, pt[0]+dx, pt[1]+dy) < local_thres;
                    bound_cnt += abs(AT_IMAGE_CLIP(&img_raw, pt[0]+dx, pt[1]+dy)
                                     - AT_IMAGE_CLIP(&img_raw, pt[0]+dx+1, pt[1]+dy)) > 50;
                                       
                }
            }
            
            if(black_cnt > total_cnt/4 && bound_cnt> total_cnt/15){
                if(i < 0.4/sample_dist)
                    apriltag_type = APRILTAG_FOUND;
                else
                    apriltag_type = APRILTAG_MAYBE;
                //rt_mb_send(buzzer_mailbox, 2);
                motor_l.target_encoder = motor_l.total_encoder;
                motor_r.target_encoder = motor_r.total_encoder;
                break;
            }
        }
    }
}
