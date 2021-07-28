#ifndef GARAGE_H
#define GARAGE_H

enum garage_type_e {
    GARAGE_NONE = 0,                        // 非车库模式
    GARAGE_OUT_LEFT, GARAGE_OUT_RIGHT,      // 出库，陀螺仪转过45°，即出库完毕
    GARAGE_FOUND_LEFT, GARAGE_FOUND_RIGHT,  // 发现车库，即斑马线+单侧L角点(未使用)
    GARAGE_IN_LEFT, GARAGE_IN_RIGHT,        // 进库，发现车库后判断第几次，从而决定是否进库
    GARAGE_PASS_LEFT, GARAGE_PASS_RIGHT,    // 不进库，发现车库后判断第几次，从而决定是否进库
    GARAGE_STOP,                            // 进库完毕，停车
    GARAGE_NUM,
};

extern enum garage_type_e garage_type;

extern const char *garage_type_name[GARAGE_NUM];

void check_garage();

void run_garage();

void draw_garage();

#endif // GARAGE_H