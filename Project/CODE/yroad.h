#ifndef YROAD_H
#define YROAD_H

enum yroad_type_e {
    YROAD_NONE,
    YROAD_FOUND,
    YROAD_NEAR,
    YROAD_LEFT_RUN,
    YROAD_RIGHT_RUN,
    YROAD_LEFT_OUT,
    YROAD_RIGHT_OUT,
};

extern enum yroad_type_e yroad_type;

void check_yroad();

void run_yroad();

void draw_yroad();

#endif // YROAD_H