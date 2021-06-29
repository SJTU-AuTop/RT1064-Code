#ifndef CORSS_H
#define CORSS_H

enum cross_type_e {
  CROSS_RUNNING, CROSS_BEGIN, CROSS_IN, CROSS_OUT,
  CROSS_NONE
};


extern enum cross_type_e cross_type;



void check_cross();

void run_cross();

void draw_cross();

void cross_farline();

#endif // CORSS_H