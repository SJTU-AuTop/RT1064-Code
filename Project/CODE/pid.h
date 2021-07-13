#ifndef _PID_H_
#define _PID_H_

#include "headfile.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)

typedef struct
{
    float kp;    //P
    float ki;    //I
    float kd;    //D
    float i_max; //integrator_max
    float p_max; //integrator_max
    float d_max; //integrator_max
    
    float low_pass;
    
    float out_p;
    float out_i;
    float out_d;
    
    float error;
    float pre_error;
    float pre_pre_error;
} pid_param_t;


#define PID_CREATE(_kp, _ki, _kd, _low_pass, max_p , max_i ,max_d) \
    {                                    \
        .kp = _kp,                       \
        .ki = _ki,                       \
        .kd = _kd,                       \
        .low_pass = _low_pass,           \
        .out_p = 0,                      \
        .out_i = 0,                      \
        .out_d = 0,                      \
        .p_max = max_p,                  \
        .i_max = max_i,                  \
        .d_max = max_d,                  \
    }

    
float pid_solve(pid_param_t *pid, float error);
float increment_pid_solve(pid_param_t *pid, float error);
float expert_pid_solve(pid_param_t *pid, float error);

float bangbang_pid_solve(pid_param_t *pid, float error);
float changable_pid_solve(pid_param_t *pid, float error);

#endif /* _PID_H_ */
