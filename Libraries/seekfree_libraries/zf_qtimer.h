/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		qtimer
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#ifndef _zf_qtimer_h
#define _zf_qtimer_h



#include "common.h"
#include "fsl_qtmr.h"

//此枚举定义不允许用户修改
typedef enum    //QTIMER引脚枚举
{
    QTIMER1_TIMER0_C0 =1*12+3*0,											//定时器0 同一时间只能有一个引脚与定时器相关联
    QTIMER1_TIMER1_C1 =1*12+3*1,                                            //定时器1 同一时间只能有一个引脚与定时器相关联
    QTIMER1_TIMER2_C2 =1*12+3*2,                                            //定时器2 同一时间只能有一个引脚与定时器相关联
    QTIMER1_TIMER3_C24=1*12+3*3,                                            //定时器3 同一时间只能有一个引脚与定时器相关联
    
    QTIMER2_TIMER0_C3 =2*12+3*0, QTIMER2_TIMER0_E19,                        //定时器0 同一时间只能有一个引脚与定时器相关联
    QTIMER2_TIMER1_C4 =2*12+3*1, QTIMER2_TIMER1_E20,                        //定时器1 同一时间只能有一个引脚与定时器相关联
    QTIMER2_TIMER2_C5 =2*12+3*2, QTIMER2_TIMER2_E21,                        //定时器2 同一时间只能有一个引脚与定时器相关联
    QTIMER2_TIMER3_C25=2*12+3*3, QTIMER2_TIMER3_E22,                        //定时器3 同一时间只能有一个引脚与定时器相关联
    
    QTIMER3_TIMER0_B16=3*12+3*0, QTIMER3_TIMER0_C6,  QTIMER3_TIMER0_E15,    //定时器0 同一时间只能有一个引脚与定时器相关联
    QTIMER3_TIMER1_B17=3*12+3*1, QTIMER3_TIMER1_C7,  QTIMER3_TIMER1_E16,    //定时器1 同一时间只能有一个引脚与定时器相关联
    QTIMER3_TIMER2_B18=3*12+3*2, QTIMER3_TIMER2_C8,  QTIMER3_TIMER2_E17,    //定时器2 同一时间只能有一个引脚与定时器相关联
    QTIMER3_TIMER3_B19=3*12+3*3, QTIMER3_TIMER3_C26, QTIMER3_TIMER3_E18,    //定时器3 同一时间只能有一个引脚与定时器相关联
    
    QTIMER4_TIMER0_C9 =4*12+3*0,                                            //定时器0 同一时间只能有一个引脚与定时器相关联
    QTIMER4_TIMER1_C10=4*12+3*1,                                            //定时器1 同一时间只能有一个引脚与定时器相关联
    QTIMER4_TIMER2_C11=4*12+3*2,                                            //定时器2 同一时间只能有一个引脚与定时器相关联
    QTIMER4_TIMER3_C27=4*12+3*3,                                            //定时器3 同一时间只能有一个引脚与定时器相关联
    
}QTIMER_PIN_enum;

//此枚举定义不允许用户修改
typedef enum    //QTIMER编号枚举
{
    QTIMER_0,//RT1064没有QTIMER0 这里仅用于占位
    QTIMER_1,
    QTIMER_2,
    QTIMER_3,
    QTIMER_4,
}QTIMERN_enum;


void qtimer_quad_init(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA, QTIMER_PIN_enum phaseB);
int16 qtimer_quad_get(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA);
void qtimer_quad_clear(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA);

#endif
 
