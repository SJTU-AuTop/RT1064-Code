#include "garage.h"
#include "camera_param.h"
#include "attitude_solution.h"
#include "buzzer.h"
#include "motor.h"
#include "smotor.h"
#include "main.h"


enum garage_type_e garage_type = GARAGE_OUT_LEFT;

const char *garage_type_name[GARAGE_NUM] = {
        "GARAGE_NONE",
        "GARAGE_OUT_LEFT", "GARAGE_OUT_RIGHT",
        "GARAGE_FOUND_LEFT", "GARAGE_FOUND_RIGHT",
        "GARAGE_IN_LEFT", "GARAGE_IN_RIGHT",
        "GARAGE_PASS_LEFT", "GARAGE_PASS_RIGHT",
        "GARAGE_STOP",
};

bool garage_yaw_init = false;
float garage_yaw = 0;

// 记录当前第几次车库
int garage_num = 0;
// 编码器，用于防止重复触发等情况。
int64_t garage_encoder = 0;

float angle_diff(float a1, float a2) {
    float c1 = cosf(a1 / 180 * PI);
    float s1 = sinf(a1 / 180 * PI);
    float c2 = cosf(a2 / 180 * PI);
    float s2 = sinf(a2 / 180 * PI);
    float c = c1 * c2 + s1 * s2;
    float s = s1 * c2 - s2 * c1;
    return atan2f(s, c) * 180 / PI;
}

int zebra_cross_flag_begin = 0;
int zebra_cross_flag0[30];
int zebra_cross_flag0_num = 0;
int zebra_cross_flag1[30];
int zebra_cross_flag1_num = 0;

float (*garage_rpts)[2];
int garage_rpts_num;

void check_garage() {
    // 记录出库陀螺仪初值
    if (!garage_yaw_init) {
        garage_yaw = eulerAngle.yaw;
        garage_yaw_init = true;
    }
    // 非车库模式下识别车库
    if (garage_type == GARAGE_NONE) {
        // 根据当前的L角点情况决定，取左(右)中线，进行斑马线的寻找
        if (Lpt0_found && !Lpt1_found) {
            // 仅左角点，则在右中线上找斑马线
            garage_rpts = rptsc1;
            garage_rpts_num = rptsc1_num;
        } else if (Lpt1_found && !Lpt0_found) {
            // 仅右角点，则在左中线上找斑马线
            garage_rpts = rptsc0;
            garage_rpts_num = rptsc0_num;
        } else {
            // 其余情况不找
            garage_rpts_num = 0;
        }
        int pt[2];
        // 没有能找的中线就退出
        if (garage_rpts_num == 0) return;
        // 在中线上一定范围内找斑马线
        for (int i = 10; i < MIN(80, garage_rpts_num); i++) {
            // 反变换后，超出图像范围则跳过
            if (!map_inv(garage_rpts[i], pt)) return;
            // 调试绘图
            //draw_x(&img_raw, pt[0], pt[1], 3, 0);

            zebra_cross_flag_begin = AT_IMAGE(&img_raw, pt[0], pt[1]) > thres;

            memset(zebra_cross_flag0, 0, sizeof(zebra_cross_flag0));
            zebra_cross_flag0_num = 0;
            for (int x = pt[0] - 1; x >= MAX(0, pt[0] - 50); x--) {
                if (zebra_cross_flag_begin == 0) { // even white, odd black
                    if (zebra_cross_flag0_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current even, current white
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    } else if (zebra_cross_flag0_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current even, current black
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    } else if (zebra_cross_flag0_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current odd, current white
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    } else if (zebra_cross_flag0_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current odd, current black
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    }
                } else { // even black, odd white
                    if (zebra_cross_flag0_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current even, current white
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    } else if (zebra_cross_flag0_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current even, current black
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    } else if (zebra_cross_flag0_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current odd, current white
                        zebra_cross_flag0[zebra_cross_flag0_num]++;
                    } else if (zebra_cross_flag0_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current odd, current black
                        zebra_cross_flag0[++zebra_cross_flag0_num]++;
                    }
                }
            }

            memset(zebra_cross_flag1, 0, sizeof(zebra_cross_flag1));
            zebra_cross_flag1_num = 0;
            for (int x = pt[0] + 1; x <= MIN(img_raw.width - 1, pt[0] + 50); x++) {
                if (zebra_cross_flag_begin == 0) { // even white, odd black
                    if (zebra_cross_flag1_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current even, current white
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    } else if (zebra_cross_flag1_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current even, current black
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    } else if (zebra_cross_flag1_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current odd, current white
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    } else if (zebra_cross_flag1_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current odd, current black
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    }
                } else { // even black, odd white
                    if (zebra_cross_flag1_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current even, current white
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    } else if (zebra_cross_flag1_num % 2 == 0 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current even, current black
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    } else if (zebra_cross_flag1_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) > thres) { // current odd, current white
                        zebra_cross_flag1[zebra_cross_flag1_num]++;
                    } else if (zebra_cross_flag1_num % 2 == 1 && AT_IMAGE(&img_raw, x, pt[1]) < thres) { // current odd, current black
                        zebra_cross_flag1[++zebra_cross_flag1_num]++;
                    }
                }
            }

            // 判断连续跳变的阈值条件以识别斑马线
            int i0 = 1;
            for (; i0 < zebra_cross_flag0_num - 1; i0++) {
                if (zebra_cross_flag0[i0] < 2 || zebra_cross_flag0[i0] >= 20 || abs(zebra_cross_flag0[i0 + 1] - zebra_cross_flag0[i0]) >= 10) break;
            }
            bool is_zebra0 = i0 > 6;

            int i1 = 1;
            for (; i1 < zebra_cross_flag1_num - 1; i1++) {
                if (zebra_cross_flag1[i1] < 2 || zebra_cross_flag1[i1] >= 20 || abs(zebra_cross_flag1[i1 + 1] - zebra_cross_flag1[i1]) >= 10) break;
            }
            bool is_zebra1 = i1 > 6;

            if (is_zebra0 && is_zebra1) {
                if (Lpt0_found && !Lpt1_found) {
                    if (++garage_num >= 2) {    // 第二次车库就入库
                        garage_type = GARAGE_IN_LEFT;
                        garage_yaw = eulerAngle.yaw;
                        servo_pid.kp *= 1.5;
                    } else {                    // 第一次车库就不入库
                        garage_type = GARAGE_PASS_LEFT;
                        garage_encoder = get_total_encoder();
                    }
                    break;
                } else if (!Lpt0_found && Lpt1_found) {
                    if (++garage_num >= 2) {    // 第二次车库就入库
                        garage_type = GARAGE_IN_RIGHT;
                        garage_yaw = eulerAngle.yaw;
                        servo_pid.kp *= 1.5;
                    } else {                    // 第一次车库就不入库
                        garage_type = GARAGE_PASS_RIGHT;
                        garage_encoder = get_total_encoder();
                    }
                    break;
                }
            }
        }
    }
}

void run_garage() {
    switch (garage_type) {
        case GARAGE_OUT_LEFT:
            aim_distance = 0.25;
            track_type = TRACK_LEFT;
            // 转向45度，则出库完毕
            if (angle_diff(eulerAngle.yaw, garage_yaw) > 45) {
                garage_type = GARAGE_NONE;
            }
            break;
        case GARAGE_OUT_RIGHT:
            aim_distance = 0.25;
            track_type = TRACK_RIGHT;
            // 转向45度，则出库完毕
            if (angle_diff(eulerAngle.yaw, garage_yaw) < -45) {
                garage_type = GARAGE_NONE;
            }
            break;
        case GARAGE_IN_LEFT:
            aim_distance = 0.5;
            track_type = TRACK_LEFT;
            // 转向45度且识别到双L角点，则入库完毕
            if (angle_diff(eulerAngle.yaw, garage_yaw) > 45 && Lpt0_found && Lpt0_rpts0s_id < 40 && Lpt1_found && Lpt1_rpts1s_id < 40) {
                garage_type = GARAGE_STOP;
                rt_mb_send(buzzer_mailbox, 2);
            }
            break;
        case GARAGE_IN_RIGHT:
            aim_distance = 0.5;
            track_type = TRACK_RIGHT;
            // 转向45度且识别到双L角点，则入库完毕
            if (angle_diff(eulerAngle.yaw, garage_yaw) < -45 && Lpt0_found && Lpt0_rpts0s_id < 40 && Lpt1_found && Lpt1_rpts1s_id < 40) {
                garage_type = GARAGE_STOP;
                rt_mb_send(buzzer_mailbox, 2);
            }
            break;
        case GARAGE_PASS_LEFT:
            track_type = TRACK_RIGHT;
            // 不入库，通过编码器使得小车走过车库后才退出车库模式
            if (get_total_encoder() - garage_encoder > ENCODER_PER_METER * 1.) {
                garage_type = GARAGE_NONE;
            }
            break;
        case GARAGE_PASS_RIGHT:
            track_type = TRACK_LEFT;
            // 不入库，通过编码器使得小车走过车库后才退出车库模式
            if (get_total_encoder() - garage_encoder > ENCODER_PER_METER * 1.) {
                garage_type = GARAGE_NONE;
            }
            break;
        default:
            (void) 0;
    }
}
