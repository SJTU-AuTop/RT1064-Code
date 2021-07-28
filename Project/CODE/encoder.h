#ifndef _encoder_h
#define _encoder_h

#include "headfile.h"

extern int16 speed_l, speed_r;

void encoder_init(void);
void encoder_get(void);
#endif