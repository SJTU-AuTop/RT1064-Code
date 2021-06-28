#include "yroad.h"
#include "motor.h"
#include "main.h"

enum yroad_type_e yroad_type = YROAD_NONE;

int64_t yroad_encoder = 0;

void check_yroad(){
    bool Yfound = Ypt0_found && Ypt1_found;
    // 状态切换
    if(yroad_type == YROAD_NONE && Yfound){
        yroad_type = YROAD_FOUND;
        yroad_encoder = get_total_encoder();
    }
}

void run_yroad(){
    bool Yfound = Ypt0_found && Ypt1_found;
    // 状态切换
    if(yroad_type == YROAD_FOUND){
        // TODO: check openart
        static int cnt = 0;
        if(++cnt % 2) yroad_type = YROAD_LEFT_RUN;
        else yroad_type = YROAD_RIGHT_RUN;        
    }else if(yroad_type == YROAD_LEFT_RUN && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER){
        yroad_type = YROAD_LEFT_OUT;
    }else if(yroad_type == YROAD_RIGHT_RUN && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER){
        yroad_type = YROAD_RIGHT_OUT;
    }else if(yroad_type == YROAD_LEFT_OUT && !Yfound){
        yroad_type = YROAD_NONE;
    }else if(yroad_type == YROAD_RIGHT_OUT && !Yfound){
        yroad_type = YROAD_NONE;
    }

    if(yroad_type == YROAD_LEFT_RUN || yroad_type == YROAD_LEFT_OUT){
        track_type = TRACK_LEFT;
    }else if(yroad_type == YROAD_LEFT_RUN || yroad_type == YROAD_LEFT_OUT){
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
