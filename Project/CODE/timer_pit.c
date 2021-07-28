#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"
#include "elec.h"
#include "cross.h"
#include "main.h"
#include "smotor.h"
#include "attitude_solution.h"


int64_t ramp_time = -20000;

void timer1_pit_entry(void *parameter) {
    //采集陀螺仪数据
    ICM_getEulerianAngles();

    // 陀螺仪判坡道
    // 先抬头再低头最后水平，退出坡道模式
    // 超时退出坡道模式
    if (eulerAngle.pitch < -10 && enable_adc == 0) {
        //记录ramp时刻,误触2s清除
        ramp_time = rt_tick_get_millisecond();
        enable_adc = 1;
    } else if (eulerAngle.pitch > 10 && enable_adc == 1) {
        enable_adc = 2;
    } else if (fabs(eulerAngle.pitch) < 5 && enable_adc == 2) {
        enable_adc = 0;
    } else if (rt_tick_get_millisecond() - ramp_time > 1000) {
        enable_adc = 0;
    }

    //采集电磁数据
    elec_get();

    //采集编码器数据
    encoder_get();

    //控制电机转动
    motor_control();

    //电磁控制
    if (enable_adc) {
        elec_calculate();
    } else if (adc_cross && cross_type == CROSS_IN) {
        elec_calculate();
    }
}


void timer_pit_init(void) {
    rt_timer_t timer;

    //创建一个定时器 周期运行
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);

    //启动定时器
    if (RT_NULL != timer) {
        rt_timer_start(timer);
    }
}