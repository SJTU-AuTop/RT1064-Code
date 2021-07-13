#include "circle.h"
#include "motor.h"
#include "main.h"

enum circle_type_e circle_type = CIRCLE_NONE;

const char* circle_type_name[CIRCLE_NUM] = {
    "CIRCLE_NONE",
    "CIRCLE_LEFT_BEGIN",  "CIRCLE_LEFT_IN",  "CIRCLE_LEFT_RUNNING",  "CIRCLE_LEFT_OUT",  "CIRCLE_LEFT_END",
    "CIRCLE_RIGHT_BEGIN", "CIRCLE_RIGHT_IN", "CIRCLE_RIGHT_RUNNING", "CIRCLE_RIGHT_OUT", "CIRCLE_RIGHT_END",  
};

int64_t circle_encoder;

int none_left_line = 0, none_right_line = 0;
int have_left_line = 0, have_right_line = 0;

void check_circle(){
    if(circle_type == CIRCLE_NONE && Lpt0_found && !Lpt1_found && is_straight1){
        circle_type = CIRCLE_LEFT_BEGIN;
    }
    if(circle_type == CIRCLE_NONE && !Lpt0_found && Lpt1_found && is_straight0){
        circle_type = CIRCLE_RIGHT_BEGIN;
    }
}

void run_circle(){
    int64_t current_encoder = get_total_encoder();
    //if(circle_type!=CIRCLE_NONE) aim_distance = 0.63;
    
    // 左环开始，寻外直道右线
    if(circle_type == CIRCLE_LEFT_BEGIN){
        track_type = TRACK_RIGHT;

        //先丢左线后有线
        if(rpts0s_num < 0.2 / sample_dist)  { none_left_line++;}
        if(rpts0s_num > 1.0 / sample_dist && none_left_line > 2)
        {
            have_left_line ++ ;
            if(have_left_line > 1)
            {
                circle_type = CIRCLE_LEFT_IN;
                none_left_line = 0;
                have_left_line = 0;
                circle_encoder = current_encoder;
            }
        }
    }
        //入环，寻内圆左线
    else if(circle_type == CIRCLE_LEFT_IN){
        track_type = TRACK_LEFT;
        //aim_distance = 0.5;

        //编码器打表过1/4圆   应修正为右线为转弯无拐点
        if(rpts0s_num < 0.2 / sample_dist || current_encoder - circle_encoder >= ENCODER_PER_METER * (3.14 *  1/2))
        {circle_type = CIRCLE_LEFT_RUNNING;}
    }
    //正常巡线，寻外圆右线
    else if(circle_type == CIRCLE_LEFT_RUNNING){
        track_type = TRACK_RIGHT;
        if(Lpt1_found) rpts1s_num = rptsc1_num = Lpt1_rpts1s_id;
        //aim_distance = 0.5;
        //外环拐点(右L点)
        if(Lpt1_found && Lpt1_rpts1s_id < 0.4 / sample_dist)
        {
            circle_type = CIRCLE_LEFT_OUT;
        }
    }
    //出环，寻内圆
    else if(circle_type == CIRCLE_LEFT_OUT){
        //aim_distance = 0.5;
        track_type = TRACK_LEFT;

        //右线长度加倾斜角度  应修正为右线找到且为直线

        if(is_straight1)
        { 
            circle_type = CIRCLE_LEFT_END;
        }
        
    
    }
    //走过圆环，寻右线
    else if(circle_type == CIRCLE_LEFT_END){
        //aim_distance = 0.5;
        track_type = TRACK_RIGHT;
            //左线先丢后有
        if(rpts0_num < 0.2 / sample_dist)  { none_left_line++;}
        if(rpts0_num > 1.0 / sample_dist && none_left_line > 3)
        { circle_type = CIRCLE_NONE;
            none_left_line = 0;}
    }
    //右环控制，前期寻左直道
    else if(circle_type == CIRCLE_RIGHT_BEGIN){
        
        track_type = TRACK_LEFT;

        //先丢右线后有线
        if(rpts1_num < 0.2 / sample_dist)  { none_right_line++;}
        if(rpts1_num > 1.0 / sample_dist && none_right_line > 2)
        {
            have_right_line ++ ;
            if(have_right_line > 1)
            {
                circle_type = CIRCLE_RIGHT_IN;
                none_right_line = 0;
                have_right_line = 0;
                circle_encoder = current_encoder;
            }
        }
    }
    //入右环，寻右内圆环
    else if(circle_type == CIRCLE_RIGHT_IN){
        track_type = TRACK_RIGHT;

        //aim_distance = 0.5;

        //编码器打表过1/4圆   应修正为左线为转弯无拐点
        if(rpts1_num < 0.2 / sample_dist || current_encoder - circle_encoder >= ENCODER_PER_METER * (3.14 *  1/2))
        {circle_type = CIRCLE_RIGHT_RUNNING;}

    }
    //正常巡线，寻外圆左线
    else if(circle_type == CIRCLE_RIGHT_RUNNING){
        track_type = TRACK_LEFT;
        //aim_distance = 0.5;
        //外环存在拐点,可再加拐点距离判据(左L点)
        if(Lpt0_found) rpts0s_num = rptsc0_num = Lpt0_rpts0s_id;
        if(Lpt0_found && Lpt0_rpts0s_id < 0.4 / sample_dist)
        {
            circle_type = CIRCLE_RIGHT_OUT;
        }
    }
    //出环，寻内圆
    else if(circle_type == CIRCLE_RIGHT_OUT){
        track_type = TRACK_RIGHT;
        //aim_distance = 0.5;
        //左长度加倾斜角度  应修正左右线找到且为直线
        //if((rpts1_num >100 && !Lpt1_found))  {have_right_line++;}
        if(is_straight0)
        { 
            circle_type = CIRCLE_RIGHT_END;
        }
    }
    //走过圆环，寻左线
    else if(circle_type == CIRCLE_RIGHT_END){
        //aim_distance = 0.5;
        track_type = TRACK_LEFT;
        //左线先丢后有
        if(rpts1_num < 0.2 / sample_dist)  { none_right_line++;}
        if(rpts1_num > 1.0 / sample_dist && none_right_line > 2)
        { 
            circle_type = CIRCLE_NONE;
            none_right_line = 0;
        }
    }
}

void draw_circle(){
    
}

