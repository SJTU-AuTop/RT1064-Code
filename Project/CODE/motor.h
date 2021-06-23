#ifndef _motor_h
#define _motor_h

#include "headfile.h"
#include "pid.h"



#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

typedef struct motor_param_t
{
    int32_t encoder_speed; //Measured speed
    int32_t target_speed;
    int32_t duty;         //Motor PWM duty
    pid_param_t pid;      //Motor PID param
} motor_param_t;


#define MOTOR_CREATE(kp, ki, kd, p_max ,i_max ,d_max)       \
    {                                         \
        .encoder_speed = 0,                   \
        .target_speed = 0,                     \
        .pid = PID_CREATE(kp, ki, kd, p_max ,i_max ,d_max), \
    }

    
void wireless_show(void);
void motor_init(void);
void motor_control(void);
    
#endif