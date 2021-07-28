#ifndef YROAD_H
#define YROAD_H

enum yroad_type_e {
    YROAD_NONE = 0,                     // 非三岔路
    YROAD_FOUND,                        // 找到三岔，即两个Y角点
    YROAD_NEAR,                         // 三岔距离较近，即两个Y角点较近
    YROAD_LEFT_RUN, YROAD_RIGHT_RUN,    // 三岔内部
    YROAD_LEFT_OUT, YROAD_RIGHT_OUT,    // 出三岔路，即在三岔内部识别到两个Y角点
    YROAD_NUM,
};

extern enum yroad_type_e yroad_type;

extern const char *yroad_type_name[YROAD_NUM];

void check_yroad();

void run_yroad();

void draw_yroad();

#endif // YROAD_H