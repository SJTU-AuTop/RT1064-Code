#include "laser.h"
#include "zf_pwm.h"

#define LASER_PWM   PWM2_MODULE2_CHA_C10
#define LASER_FREQ  (125)

void laser_init(){
    pwm_init(LASER_PWM, LASER_FREQ, 0);
}

void laser_on(){
    pwm_duty(LASER_PWM, 30000);
}

void laser_off(){
    pwm_duty(LASER_PWM, 0);
}
