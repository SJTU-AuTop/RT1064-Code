#include "cross.h"
#include "motor.h"
#include "main.h"

enum cross_type_e cross_type = CROSS_NONE;

float normal_begin_x, normal_begin_y;

int64_t cross_encoder;

void check_cross(){
    bool Xfound = Lpt0_found && Lpt1_found;
    if(cross_type == CROSS_NONE && Xfound)  cross_type = CROSS_BEGIN;

    
}

void run_cross() {
    bool Xfound = Lpt0_found && Lpt1_found;
    int64_t current_encoder = get_total_encoder();
    float Lpt0y = rpts0s[Lpt0_rpts0s_id][1];
    float Lpt1y = rpts1s[Lpt1_rpts1s_id][1];
    //检测到十字，先按照近线走
    if(cross_type == CROSS_BEGIN)
    {
        aim_distence = 0.68;
        //近角点过少，进入远线控制
        if((Xfound && (Lpt0_rpts0s_id < 30 && Lpt1_rpts1s_id < 30)) || (rpts1_num <30 || rpts0_num<30))
        {
            normal_begin_x = begin_x;
            normal_begin_y = begin_y;
            cross_type = CROSS_IN;
            cross_encoder = current_encoder;
            begin_x = ((rpts1s[Lpt1_rpts1s_id][1] + rpts1s[Lpt1_rpts1s_id][1])/2 - MT9V03X_CSI_W/2);
        }
    }
    //远线控制进十字,begin_y渐变靠近防丢线
    else if(cross_type == CROSS_IN)
    {
        aim_distence = 0.6;
        float dis = (current_encoder - cross_encoder) / (ENCODER_PER_METER * 0.8);
        begin_y = (int) (dis * (normal_begin_y  - 48) + 48);
        
    begin_x = Xfound? ((rpts1s[Lpt1_rpts1s_id][1] + rpts1s[Lpt1_rpts1s_id][1])/2 - MT9V03X_CSI_W/2) : 0;
       
        
        if(rpts0_num<30) {track_type = TRACK_RIGHT;}
        else if(rpts1_num<30) {track_type = TRACK_LEFT;}
            //编码器打表过空白期
        if(current_encoder - cross_encoder > ENCODER_PER_METER* 0.65)
        {
            cross_type = CROSS_NONE;
             begin_x = normal_begin_x;
            begin_y = normal_begin_y;
        }
    }
    // //常规巡线，切回找线
    // else if(cross_type == CROSS_RUNNING)
    // {
    //     begin_x = normal_begin_x;
    //     begin_y = normal_begin_y;
    //     aim_distence = 0.1;

    //     if(rpts0s[rpts0s_num-1][0] > MT9V03X_CSI_W/2 ||  rpts1s_num < aim_distence / sample_dist + 20)  track_type = TRACK_LEFT;
    //     else if(rpts1s[rpts1s_num-1][0] < MT9V03X_CSI_W/2 ||  rpts0s_num < aim_distence / sample_dist + 20)  track_type = TRACK_RIGHT;
    //     else track_type = TRACK_RIGHT;

    //     //识别到一个角点，且拐点较近
    //     if(Xfound && ((road_type1 == CROSS && corner_y1 > MT9V03X_CSI_H -25) || (road_type2 == CROSS  && corner_y2 >MT9V03X_CSI_H -25)))
    //     {
    //         cross_type = CROSS_OUT;
    //         cross_encoder = current_encoder ;
    //     }
    // }
    // //寻远线，编码器
    // else if(cross_type == CROSS_OUT)
    // {
    //     anchor_num = 15;
    //     float dis = (current_encoder - cross_encoder) / (ENCODER_PER_METER *6/10);
    //     begin_y = (int) (dis * (150 - 50) + 50);
    //     car_width = 0;
    //     if(current_encoder - cross_encoder > ENCODER_PER_METER* 6/10)
    //     {
    //         cross_type = CROSS_NONE;
    //     }
    // }
}

void draw_cross(){

}
