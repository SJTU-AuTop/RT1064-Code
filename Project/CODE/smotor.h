#ifndef _smotor_h
#define _smotor_h

#include "headfile.h"
#include "pid.h"

#define SMOTOR1_CENTER  (88)
#define SMOTOR2_CENTER  (92)
#define SMOTOR3_CENTER  (106)

extern pid_param_t servo_pid;

void smotor_init(void);
void smotor1_control(int16 duty);
void smotor2_control(int16 duty);
void smotor3_control(int16 duty);
int16 servo_duty(float angle);

#endif
