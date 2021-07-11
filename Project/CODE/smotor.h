#ifndef _smotor_h
#define _smotor_h

#include "headfile.h"
#include "pid.h"

#define SMOTOR1_CENTER  (88)
#define SMOTOR2_CENTER  (90)
#define SMOTOR3_CENTER  (115)

#define SMOTOR2_LEFT_CENTER  (160)
#define SMOTOR2_RIGHT_CENTER  (20)

#define SMOTOR1_PIN   PWM4_MODULE2_CHA_C30       //定义车模寻迹舵机引脚
#define SMOTOR3_PIN   PWM1_MODULE0_CHA_D12       //定义云台舵机1引脚
#define SMOTOR2_PIN   PWM1_MODULE0_CHB_D13       //定义云台舵机2引脚


#define SERVO_FREQ      (50)

// 前轮转角和方向舵机转角的比例关系
#define SMOTOR_RATE     (2.4)

extern pid_param_t servo_pid;

void smotor_init(void);
void smotor1_control(int16 duty);
void smotor2_control(int16 duty);
void smotor3_control(int16 duty);
int16 servo_duty(float angle);

#endif
