#ifndef CORSS_H
#define CORSS_H

enum cross_type_e {
    CROSS_NONE = 0,
    CROSS_BEGIN, CROSS_IN,
    CROSS_NUM,
};

extern enum cross_type_e cross_type;

extern const char* cross_type_name[CROSS_NUM];


void check_cross();

void run_cross();

void draw_cross();

void cross_farline();

#endif // CORSS_H