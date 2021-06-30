#include "yroad.h"
#include "motor.h"
#include "main.h"

enum yroad_type_e yroad_type = YROAD_NONE;

int64_t yroad_encoder = 0;

int16_t yroad_cnt = 0;

uint32_t yroad_stop_timer = 0;

int32_t normal_speed = 0;

void check_yroad(){
    bool Yfound = Ypt0_found && Ypt1_found;
    // 状态切换
    if(yroad_type == YROAD_NONE && Yfound && get_total_encoder()-yroad_encoder >ENCODER_PER_METER ){
        yroad_type = YROAD_FOUND;
        yroad_encoder = get_total_encoder();
        yroad_stop_timer = pit_get_ms(TIMER_PIT);
        normal_speed = motor_l.target_speed;
        motor_l.target_speed = 0;
        motor_r.target_speed = 0;
        motor_l.motor_mode = MODE_STOP;
        motor_r.motor_mode = MODE_STOP;
    }
}

void run_yroad(){
    bool Yfound = Ypt0_found && Ypt1_found;
    // 状态切换
    if(yroad_type == YROAD_FOUND){
        // TODO: check openart
        
        if(pit_get_ms(TIMER_PIT) - yroad_stop_timer > 2000){
            motor_l.target_speed = normal_speed;
            motor_r.target_speed = normal_speed;
            
            if(yroad_cnt == 0) yroad_type = YROAD_LEFT_RUN;
            else yroad_type = YROAD_RIGHT_RUN;
        }
        
    }else if(yroad_type == YROAD_LEFT_RUN && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER){
        yroad_type = YROAD_LEFT_OUT;
    }else if(yroad_type == YROAD_RIGHT_RUN && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER){
        yroad_type = YROAD_RIGHT_OUT;
    }else if(yroad_type == YROAD_LEFT_OUT && !Yfound){
        yroad_cnt = (1-yroad_cnt);
        yroad_type = YROAD_NONE;
        yroad_encoder = get_total_encoder();
    }else if(yroad_type == YROAD_RIGHT_OUT && !Yfound){
        yroad_cnt = (1-yroad_cnt);
        yroad_type = YROAD_NONE;
        yroad_encoder = get_total_encoder();
    }

    if(yroad_type == YROAD_LEFT_RUN || yroad_type == YROAD_LEFT_OUT){
        track_type = TRACK_LEFT;
    }else if(yroad_type == YROAD_RIGHT_RUN || yroad_type == YROAD_RIGHT_OUT){
        track_type = TRACK_RIGHT;
    }
}

void draw_yroad(){
    bool Yfound = Ypt0_found && Ypt1_found;
    if(Yfound){
        draw_o(&img_line, rpts0s[Ypt0_rpts0s_id][0], rpts0s[Ypt0_rpts0s_id][1], 3);
        draw_o(&img_line, rpts1s[Ypt1_rpts1s_id][0], rpts1s[Ypt1_rpts1s_id][1], 3);
    }
}
