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
    float total_encoder;
    float target_encoder;
    float encoder_raw;
    float encoder_speed; //Measured speed
    float target_speed;
    int32_t duty;         //Motor PWM duty
    
    enum{
        MODE_NORMAL, MODE_BANGBANG, MODE_SOFT,MODE_POSLOOP,
    } motor_mode;
    
    pid_param_t pid;      //Motor PID param
    pid_param_t brake_pid;      //Motor PID param
} motor_param_t;


#define MOTOR_CREATE(ts, kp, ki, kd, brake_kp , brake_ki ,brake_kd, low_pass, p_max ,i_max ,d_max)       \
    {                                           \
        .total_encoder = 0,                     \
        .encoder_speed = 0,                     \
        .target_speed = ts,                     \
        .motor_mode = MODE_NORMAL,              \
        .pid = PID_CREATE(kp, ki, kd, low_pass, p_max ,i_max ,d_max), \
        .brake_pid = PID_CREATE(brake_kp, brake_ki, brake_kd, low_pass, p_max ,i_max ,d_max), \
    }

extern motor_param_t motor_l, motor_r; 



#define ENCODER_PER_METER   (5800)

void wireless_show(void);
void motor_init(void);
void motor_control(void);
int64_t get_total_encoder();        

    
#endif