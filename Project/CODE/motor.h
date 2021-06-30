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
    int64_t total_encoder;
    int32_t encoder_speed; //Measured speed
    int32_t target_speed;
    int32_t duty;         //Motor PWM duty
    
    enum{
        MODE_NORMAL, MODE_STOP, MODE_BEGIN,
    } motor_mode;
    
    pid_param_t pid;      //Motor PID param
} motor_param_t;


#define MOTOR_CREATE(ts, kp, ki, kd, p_max ,i_max ,d_max)       \
    {                                           \
        .total_encoder = 0,                     \
        .encoder_speed = 0,                     \
        .target_speed = ts,                     \
        .motor_mode = MODE_NORMAL,              \
        .pid = PID_CREATE(kp, ki, kd, p_max ,i_max ,d_max), \
    }

extern motor_param_t motor_l, motor_r;    

#define ENCODER_PER_METER   (5800)

void wireless_show(void);
void motor_init(void);
void motor_control(void);
int64_t get_total_encoder();        

    
#endif