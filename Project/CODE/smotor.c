#include "smotor.h"
#include "pid.h"

#define SMOTOR1_PIN   PWM4_MODULE2_CHA_C30       //定义车模寻迹舵机引脚
#define SMOTOR2_PIN   PWM1_MODULE0_CHA_D12       //定义云台舵机1引脚
#define SMOTOR3_PIN   PWM1_MODULE0_CHB_D13       //定义云台舵机2引脚

#define SERVO_FREQ    (50)

//pid_param_t servo_pid = PID_CREATE(30, 0, 0, 15, 5, 15);   


pid_param_t servo_pid = PID_CREATE(0.85, 0, 0, 15, 5, 15);   

void smotor_init(void)
{
    pwm_init(SMOTOR1_PIN, SERVO_FREQ, servo_duty(SMOTOR1_CENTER));
    pwm_init(SMOTOR2_PIN, SERVO_FREQ, servo_duty(SMOTOR2_CENTER));
    pwm_init(SMOTOR3_PIN, SERVO_FREQ, servo_duty(SMOTOR3_CENTER));
}


//下 2300-
void smotor1_control(int16 duty)
{
    pwm_duty(SMOTOR1_PIN, (int16)duty);
}

//+左转, -右转
void smotor2_control(int16 duty)
{
    pwm_duty(SMOTOR2_PIN, (int16)(MINMAX(duty,-2500,2500)));
}

//+低头, -抬头
void smotor3_control(int16 duty)
{
    pwm_duty(SMOTOR3_PIN, (int16)(MINMAX(duty,-100,600)));
}

int16 servo_duty(float angle){
    return (angle * 2 / 180 + 0.5) * PWM_DUTY_MAX * SERVO_FREQ / 1000;
}