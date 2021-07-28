#include "yroad.h"
#include "motor.h"
#include "main.h"
#include "openart_mini.h"
#include "buzzer.h"

enum yroad_type_e yroad_type = YROAD_NONE;


const char *yroad_type_name[YROAD_NUM] = {
        "YROAD_NONE",
        "YROAD_FOUND", "YROAD_NEAR",
        "YROAD_LEFT_RUN", "YROAD_RIGHT_RUN",
        "YROAD_LEFT_OUT", "YROAD_RIGHT_OUT",
};

extern enum yroad_type_e yroad_type;

// 编码器，防止重复触发等情况
int64_t yroad_encoder = -10000;

// 记录第一圈的转向方向
bool first_right;

// 记录第几个三岔
int16_t yroad_cnt = 0;


void check_yroad() {
    bool Yfound = Ypt0_found && Ypt1_found;
    // 状态切换
    //两个Y角点进三叉
    if (yroad_type == YROAD_NONE && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER) {
        yroad_type = YROAD_FOUND;
        yroad_encoder = get_total_encoder();
    }
}

void run_yroad() {
    bool Yfound = Ypt0_found && Ypt1_found;
    // 状态切换
    if (yroad_type == YROAD_FOUND || yroad_type == YROAD_NEAR) {
        // wait for openart
        aim_distance = 0.4;
        if (Yfound && (Ypt0_rpts0s_id < 0.2 / sample_dist || Ypt1_rpts1s_id < 0.2 / sample_dist)) {
            yroad_type = YROAD_NEAR;
        }


        if (yroad_cnt >= 1) {
            // 第二次三岔直接走
            if (first_right) yroad_type = YROAD_LEFT_RUN;
            else yroad_type = YROAD_RIGHT_RUN;
            rt_mb_send(buzzer_mailbox, 1);
        } else {
            // 第一次三叉识别数字
            openart.openart_mode = NUM_MODE;
            // 找最近1.5s内的识别结果
            if (rt_tick_get_millisecond() - openart.receiver_time < 1500) {
                //偶数左转，奇数右转
                if (openart.openart_result == 0) {
                    yroad_type = YROAD_LEFT_RUN;
                    first_right = false;
                    rt_mb_send(buzzer_mailbox, 1);
                } else {
                    yroad_type = YROAD_RIGHT_RUN;
                    first_right = true;
                    rt_mb_send(buzzer_mailbox, 2);
                }
                yroad_cnt++;
            }
        }
        // 没识别的情况下，走过了三岔口
        if (get_total_encoder() - yroad_encoder > ENCODER_PER_METER * 2) {
            // 未识别,蒙一个清掉标志
            if (track_type == TRACK_LEFT) {
                yroad_type = YROAD_LEFT_RUN;
                first_right = false;
            } else {
                yroad_type = YROAD_RIGHT_RUN;
                first_right = true;
            }
            yroad_cnt++;
        }
    } else if (yroad_type == YROAD_LEFT_RUN && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER * 1.5) {
        yroad_type = YROAD_LEFT_OUT;
    } else if (yroad_type == YROAD_RIGHT_RUN && Yfound && get_total_encoder() - yroad_encoder > ENCODER_PER_METER * 1.5) {
        yroad_type = YROAD_RIGHT_OUT;
    } else if (yroad_type == YROAD_LEFT_OUT && !Yfound) {
        yroad_type = YROAD_NONE;
        yroad_encoder = get_total_encoder();
    } else if (yroad_type == YROAD_RIGHT_OUT && !Yfound) {
        yroad_type = YROAD_NONE;
        yroad_encoder = get_total_encoder();
    }

    if (yroad_type == YROAD_LEFT_RUN || yroad_type == YROAD_LEFT_OUT) {
        track_type = TRACK_LEFT;
    } else if (yroad_type == YROAD_RIGHT_RUN || yroad_type == YROAD_RIGHT_OUT) {
        track_type = TRACK_RIGHT;
    }
}

void draw_yroad() {
    bool Yfound = Ypt0_found && Ypt1_found;
    if (Yfound) {
        draw_o(&img_line, rpts0s[Ypt0_rpts0s_id][0], rpts0s[Ypt0_rpts0s_id][1], 3, 255);
        draw_o(&img_line, rpts1s[Ypt1_rpts1s_id][0], rpts1s[Ypt1_rpts1s_id][1], 3, 255);
    }
}
