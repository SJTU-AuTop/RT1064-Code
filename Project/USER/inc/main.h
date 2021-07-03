#ifndef MAIN_H
#define MAIN_H

#include "headfile.h"
#include "imgproc.h"
#include <stdbool.h>
#include <stdint.h>

int clip(int x, int low, int up);
float fclip(float x, float low, float up);

extern image_t img_raw;
extern image_t img_thres;
extern image_t img_line;
extern float thres;
extern float delta;
extern float begin_x;
extern float begin_y;
extern float line_blur_kernel;
extern float pixel_per_meter;
extern float sample_dist;
extern float angle_dist;
extern float aim_distance;          // 纯跟踪前视距离
extern bool line_show_sample;
extern bool line_show_blur;
extern bool track_left;

extern float angle;

#define TIMER_PIT       PIT_CH3
#define ROAD_WIDTH  (0.45)
#define POINTS_MAX_LEN  (MT9V03X_CSI_H)

#define FAR_POINTS_MAX_LEN  (POINTS_MAX_LEN / 2)

// 原图左右边线
extern int ipts0[POINTS_MAX_LEN][2];
extern int ipts1[POINTS_MAX_LEN][2];
extern int ipts0_num, ipts1_num;
// 变换后左右边线
extern float rpts0[POINTS_MAX_LEN][2];
extern float rpts1[POINTS_MAX_LEN][2];
extern int rpts0_num, rpts1_num;
// 变换后左右边线+滤波
extern float rpts0b[POINTS_MAX_LEN][2];
extern float rpts1b[POINTS_MAX_LEN][2];
extern int rpts0b_num, rpts1b_num;
// 变换后左右边线+等距采样
extern float rpts0s[POINTS_MAX_LEN][2];
extern float rpts1s[POINTS_MAX_LEN][2];
extern int rpts0s_num, rpts1s_num;
// 左右边线局部角度变化率
extern float rpts0a[POINTS_MAX_LEN];
extern float rpts1a[POINTS_MAX_LEN];
extern int rpts0a_num, rpts1a_num;
// 左右边线局部角度变化率+非极大抑制
extern float rpts0an[POINTS_MAX_LEN];
extern float rpts1an[POINTS_MAX_LEN];
extern int rpts0an_num, rpts1an_num;
// 中线
extern float rpts[POINTS_MAX_LEN][2];
extern int rpts_num;
// 归一化中线
extern float rptsn[POINTS_MAX_LEN][2];
extern int rptsn_num;

// Y角点
extern int Ypt0_rpts0s_id, Ypt1_rpts1s_id;
extern bool Ypt0_found, Ypt1_found;

// L角点
extern int Lpt0_rpts0s_id, Lpt1_rpts1s_id;
extern bool Lpt0_found, Lpt1_found;

extern bool far_Lpt0_found,far_Lpt1_found;
extern int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;
// ԶПԭͼسԒҟП
extern int far_ipts0[FAR_POINTS_MAX_LEN][2];
extern int far_ipts1[FAR_POINTS_MAX_LEN][2];
extern int far_ipts0_num, far_ipts1_num;
// ԶПҤۻ۳سԒҟП
extern float far_rpts0[FAR_POINTS_MAX_LEN][2];
extern float far_rpts1[FAR_POINTS_MAX_LEN][2];
extern int far_rpts0_num, far_rpts1_num;
// ԶПҤۻ۳سԒҟП+ËҨ
extern float far_rpts0b[FAR_POINTS_MAX_LEN][2];
extern float far_rpts1b[FAR_POINTS_MAX_LEN][2];
extern int far_rpts0b_num, far_rpts1b_num;
// ԶПҤۻ۳سԒҟП+ֈߠӉҹ
extern float far_rpts0s[FAR_POINTS_MAX_LEN][2];
extern float far_rpts1s[FAR_POINTS_MAX_LEN][2];
extern int far_rpts0s_num, far_rpts1s_num;
// ԶПسԒҟПߖҿއ׈ҤۯÊ
extern float far_rpts0a[FAR_POINTS_MAX_LEN];
extern float far_rpts1a[FAR_POINTS_MAX_LEN];
extern int far_rpts0a_num, far_rpts1a_num;
// ԶПسԒҟПߖҿއ׈ҤۯÊ+؇ܫճӖ׆
extern float far_rpts0an[FAR_POINTS_MAX_LEN];
extern float far_rpts1an[FAR_POINTS_MAX_LEN];
extern int far_rpts0an_num, far_rpts1an_num;

extern bool is_straight0, is_straight1;

enum track_type_e{
    TRACK_LEFT,
    TRACK_RIGHT,
};
extern enum track_type_e track_type;


#endif // MAIN_H