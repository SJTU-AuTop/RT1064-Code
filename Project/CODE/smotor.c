#include "smotor.h"
#include "pid.h"


//pid_param_t servo_pid = PID_CREATE(30, 0, 0, 15, 5, 15);   


pid_param_t servo_pid = PID_CREATE(1.88, 0, 1.2, 15, 5, 15);   
pid_param_t adc_pid = PID_CREATE(20, 0, 0, 15, 5, 15);   


pid_param_t laser_pid = PID_CREATE(-0.12, 0, -0, 20, 20, 20);   

//转向角度
float laser_angle = SMOTOR2_CENTER;

void smotor_init(void)
{
    pwm_init(SMOTOR1_PIN, SERVO_FREQ, servo_duty(SMOTOR1_CENTER));
    pwm_init(SMOTOR2_PIN, SERVO_FREQ, servo_duty(SMOTOR2_CENTER));
    pwm_init(SMOTOR3_PIN, SERVO_FREQ, servo_duty(SMOTOR3_CENTER));
}


void smotor1_control(int16 duty)
{
    pwm_duty(SMOTOR1_PIN, (int16)duty);
}

//+左转, -右转
void smotor2_control(int16 duty)
{
    pwm_duty(SMOTOR2_PIN, (int16)MINMAX(duty,1250,6250));
}

//+低头, -抬头
void smotor3_control(int16 duty)
{
    pwm_duty(SMOTOR3_PIN, (int16)MINMAX(duty,3750,4850));
}


int16 servo_duty(float angle){
    return (angle * 2 / 180 + 0.5) * PWM_DUTY_MAX * SERVO_FREQ / 1000;
}