#ifndef CIRCLE_H
#define CIRCLE_H

enum circle_type_e {
    CIRCLE_LEFT_BEGIN,  CIRCLE_LEFT_IN,  CIRCLE_LEFT_RUNNING,  CIRCLE_LEFT_OUT, CIRCLE_LEFT_END,
    CIRCLE_RIGHT_BEGIN, CIRCLE_RIGHT_IN, CIRCLE_RIGHT_RUNNING, CIRCLE_RIGHT_OUT, CIRCLE_RIGHT_END,
    CIRCLE_NONE
};

extern enum circle_type_e circle_type;

void check_circle();

void run_circle();

void draw_circle();


#endif // CIRCLE_H