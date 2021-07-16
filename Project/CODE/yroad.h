#ifndef YROAD_H
#define YROAD_H

enum yroad_type_e {
    YROAD_NONE = 0,
    YROAD_FOUND, YROAD_NEAR,
    YROAD_LEFT_RUN, YROAD_RIGHT_RUN,
    YROAD_LEFT_OUT, YROAD_RIGHT_OUT,
    YROAD_NUM,
};

extern enum yroad_type_e yroad_type;

extern const char* yroad_type_name[YROAD_NUM];

void check_yroad();

void run_yroad();

void draw_yroad();

#endif // YROAD_H