#include "apriltag.h"
#include "motor.h"
#include "buzzer.h"
#include "camera_param.h"
#include "main.h"
#include "openart_mini.h"

enum apriltag_type_e apriltag_type = APRILTAG_NONE;

const char *apriltag_type_name[APRILTAG_NUM] = {
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

// 采用中线反变换回原图的方式，保证找黑斑时，一定是在赛道中心上寻找
void check_apriltag() {
    if (apriltag_type == APRILTAG_NONE || apriltag_type == APRILTAG_MAYBE) {
        apriltag_type = APRILTAG_NONE;
        //存在L角点,区分车库与Apriltag
        if (Lpt0_found && Lpt0_rpts0s_id < 0.5 / sample_dist) return;
        if (Lpt1_found && Lpt1_rpts1s_id < 0.5 / sample_dist) return;
        // 选择当前在左中线还是右中线找黑斑
        apriltag_cnt = 1 - apriltag_cnt;
        if (apriltag_cnt == 0) {
            apriltag_rpts = rptsc0;
            apriltag_rpts_num = rptsc0_num;
        } else {
            apriltag_rpts = rptsc1;
            apriltag_rpts_num = rptsc1_num;
        }
        // 遍历0.1m~1m范围内的赛道中线
        int pt[2];
        for (int i = 0.1 / sample_dist; i < MIN(1. / sample_dist, apriltag_rpts_num); i++) {
            // 当前坐标反变换后在图像外，则跳过
            if (!map_inv(apriltag_rpts[i], pt)) continue;
            // 当前坐标反变换后在图像下侧，则跳过(否则会找到车头)
            if (pt[1] > MT9V03X_CSI_H - 120) continue;
            // 调试绘图
            //AT_IMAGE(&img_raw, pt[0], pt[1]) = 0;

            int total_cnt = (apriltag_half_size * 2 + 1) * (apriltag_half_size * 2 + 1);

            //自适应阈值
            int local_thres = 0;
            for (int dy = -apriltag_half_size; dy <= apriltag_half_size; dy++) {
                for (int dx = -apriltag_half_size; dx <= apriltag_half_size; dx++) {
                    local_thres += AT_IMAGE_CLIP(&img_raw, pt[0] + dx, pt[1] + dy);
                }
            }
            local_thres = local_thres / total_cnt - 5;

            //存储跳变点与黑色点个数
            int black_cnt = 0, bound_cnt = 0;
            for (int dy = -apriltag_half_size; dy <= apriltag_half_size; dy++) {
                for (int dx = -apriltag_half_size; dx <= apriltag_half_size; dx++) {
                    black_cnt += AT_IMAGE_CLIP(&img_raw, pt[0] + dx, pt[1] + dy) < local_thres;
                    bound_cnt += abs(AT_IMAGE_CLIP(&img_raw, pt[0] + dx, pt[1] + dy)
                                     - AT_IMAGE_CLIP(&img_raw, pt[0] + dx + 1, pt[1] + dy)) > 40;
                }
            }

            // 如果满足黑斑阈值和跳变阈值则认为是apriltag
            // 注意，由于会把斑马线误判。在main函数里，如果识别到车库则会清除黑斑apriltag的标志。
            if (black_cnt > total_cnt / 5 && bound_cnt > total_cnt / 20) {
                if (i < 0.5 / sample_dist) { // 如果识别到比较近，则直接准备停车
                    // 记录位置,用于位置环,存储第一次found的位置用于位置环停车(使得停车有倒车的效果，然而轮胎打滑还是没用)
                    if (apriltag_type != APRILTAG_MAYBE && apriltag_type != APRILTAG_FOUND) {
                        motor_l.target_encoder = motor_l.total_encoder;
                        motor_r.target_encoder = motor_r.total_encoder;
                    }
                    apriltag_type = APRILTAG_FOUND;

                    // 记录当前时间和编码器值，用于避免重复触发，以及一些误触发
                    // 即第一次识别到黑斑apriltag后，需要小车前进一段距离才会做别的事
                    apriltag_encoder = get_total_encoder();
                    apriltag_time = rt_tick_get_millisecond();

                    // 蜂鸣器叫一声，用于调试
                    rt_mb_send(buzzer_mailbox, 1);

                    // draw circle, 用于调试
                    draw_o(&img_raw, pt[0], pt[1], 8, 0);
                } else {    // 如果识别的比较远，则可能误判，故仅会减速，而不是直接停车。
                    if (apriltag_type != APRILTAG_MAYBE) {
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
    } else if (apriltag_type == APRILTAG_LEAVE) {
        // 距离第一次识别的位置至少前进1m后，才会清除黑斑apriltag标志。
        // 防止横向扫描起始点时，扫到apriltag上，从而导致其他模式的误判。
        if (get_total_encoder() - apriltag_encoder > 1. * ENCODER_PER_METER) {
            apriltag_type = APRILTAG_NONE;
        }
    }
}
