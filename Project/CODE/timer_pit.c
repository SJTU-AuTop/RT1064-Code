#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"
#include "elec.h"
#include "cross.h"
#include "main.h"
#include "attitude_solution.h"



int64_t ramp_time = -20000;

void timer1_pit_entry(void *parameter)
{     
    //采集陀螺仪数据
    ICM_getEulerianAngles();
    
    //陀螺仪判坡道
    if(eulerAngle.pitch < -10){
      //记录ramp时刻,误触2s清除
      if(enable_adc==0) ramp_time = pit_get_ms(TIMER_PIT);
        enable_adc = 1;
    }else if((eulerAngle.pitch > 10 || pit_get_ms(TIMER_PIT)-ramp_time>2000 )&& enable_adc == 1){
        enable_adc = 0;
    }
    
    //采集电磁数据
    elec_get();
    
    //采集编码器数据
    encoder_get();
    
    //控制电机转动
    motor_control();
    
    //
    if(enable_adc) {
//        elec_calculate();
    }
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //创建一个定时器 周期运行
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    
    //启动定时器
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }

    
}