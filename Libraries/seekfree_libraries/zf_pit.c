/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		pit
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#include "fsl_common.h"
#include "zf_pit.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      周期定时器模块初始化
//  @param      void
//  @param      void     
//  @return     void
//  Sample usage:           如果需要使用周期中断、延时、计时等功能都需要对PIT进行初始化之后才能调用相应功能函数
//-------------------------------------------------------------------------------------------------------------------
void pit_init(void)
{
    pit_config_t pitConfig;
    
    PIT_GetDefaultConfig(&pitConfig);   //默认配置为false
              
    PIT_Init(PIT, &pitConfig);          //第一次初始化便于打开时钟
    PIT_Deinit(PIT);                    //复位外设
    PIT_Init(PIT, &pitConfig);          //重新初始化设置正确的参数
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      周期中断 时间设置
//  @param      pit_ch      选择模块的通道 (选择范围 由PIT_enum枚举值的内容确定)
//  @param      count       计数器值
//  @return     void
//  Sample usage:           本函数通常用户无需关心，如果需要使用周期中断功能，应该调用h文件的宏定义函数（带有时间单位）
//-------------------------------------------------------------------------------------------------------------------
void pit_interrupt(PIT_enum pit_ch, uint32 count)
{
    PIT_SetTimerPeriod(PIT, (pit_chnl_t)pit_ch, count);
    PIT_EnableInterrupts(PIT, (pit_chnl_t)pit_ch, kPIT_TimerInterruptEnable);//打开PIT通道0中断
	PIT_SetTimerChainMode(PIT, (pit_chnl_t)pit_ch,false);
    PIT_StartTimer(PIT, (pit_chnl_t)pit_ch);
    EnableIRQ(PIT_IRQn);
    
    //NVIC_SetPriority(PIT_IRQn,0);//优先级设置 范围0-15 越小优先级越高
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      延时 时间设置
//  @param      pit_ch      选择模块的通道 (选择范围 由PIT_enum枚举值的内容确定)
//  @param      count       计数器值
//  @return     void
//  Sample usage:           本函数通常用户无需关心，如果需要使用延时功能，应该调用h文件的宏定义函数（带有时间单位）
//-------------------------------------------------------------------------------------------------------------------
void pit_delay(PIT_enum pit_ch, uint32 count)
{
    PIT_SetTimerPeriod(PIT, (pit_chnl_t)pit_ch, count);
	PIT_SetTimerChainMode(PIT, (pit_chnl_t)pit_ch,false);
    PIT_StartTimer(PIT, (pit_chnl_t)pit_ch);
    
    while(!PIT_GetStatusFlags(PIT, (pit_chnl_t)pit_ch));//等待计时结束
    PIT_StopTimer(PIT, (pit_chnl_t)pit_ch);
    PIT_ClearStatusFlags(PIT, (pit_chnl_t)pit_ch, kPIT_TimerFlag);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      计时器开始
//  @param      pit_ch      选择模块的通道 (选择范围 由PIT_enum枚举值的内容确定)
//  @return     void
//  Sample usage:           pit_start(PIT_CH0); //0通道 开始计数
//-------------------------------------------------------------------------------------------------------------------
void pit_start(PIT_enum pit_ch)
{
    PIT_SetTimerPeriod(PIT, (pit_chnl_t)pit_ch, 0xFFFFFFFF);
	PIT_SetTimerChainMode(PIT, (pit_chnl_t)pit_ch,false);
    PIT_StartTimer(PIT, (pit_chnl_t)pit_ch);
    
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取计时器值
//  @param      pit_ch      选择模块的通道 (选择范围 由PIT_enum枚举值的内容确定)
//  @return     uint32      计数值
//  Sample usage:           本函数通常用户无需关心，如果需要获取计数值，应该调用h文件的宏定义函数（带有时间单位）
//-------------------------------------------------------------------------------------------------------------------
uint32 pit_get(PIT_enum pit_ch)
{
    if(PIT_GetStatusFlags(PIT, (pit_chnl_t)pit_ch))
    {
        PIT_ClearStatusFlags(PIT, (pit_chnl_t)pit_ch, kPIT_TimerFlag);
        return 0XFFFFFFFF;
        //计时溢出 返回最大值
    }
    return (0XFFFFFFFF - PIT_GetCurrentTimerCount(PIT, (pit_chnl_t)pit_ch));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      关闭PIT定时器
//  @param      pit_ch      选择模块的通道 (选择范围 由PIT_enum枚举值的内容确定)
//  @return     void      
//  Sample usage:           关闭定时器并清除标志位
//-------------------------------------------------------------------------------------------------------------------
void pit_close(PIT_enum pit_ch)
{
    PIT_StopTimer(PIT, (pit_chnl_t)pit_ch);
    PIT_ClearStatusFlags(PIT, (pit_chnl_t)pit_ch, kPIT_TimerFlag);
}

