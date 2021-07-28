#ifndef CIRCLE_H
#define CIRCLE_H

enum circle_type_e {
    CIRCLE_NONE = 0,                            // 非圆环模式
    CIRCLE_LEFT_BEGIN, CIRCLE_RIGHT_BEGIN,      // 圆环开始，识别到单侧L角点另一侧长直道。
    CIRCLE_LEFT_IN, CIRCLE_RIGHT_IN,            // 圆环进入，即走到一侧直道，一侧圆环的位置。
    CIRCLE_LEFT_RUNNING, CIRCLE_RIGHT_RUNNING,  // 圆环内部。
    CIRCLE_LEFT_OUT, CIRCLE_RIGHT_OUT,          // 准备出圆环，即识别到出环处的L角点。
    CIRCLE_LEFT_END, CIRCLE_RIGHT_END,          // 圆环结束，即再次走到单侧直道的位置。
    CIRCLE_NUM,                                 //
};

extern const char *circle_type_name[CIRCLE_NUM];

extern enum circle_type_e circle_type;

void check_circle();

void run_circle();

void draw_circle();

#endif // CIRCLE_H