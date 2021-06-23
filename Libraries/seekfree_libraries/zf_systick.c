/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		systick
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#include "fsl_gpt.h"
#include "zf_systick.h"
#include "rtthread.h"

static uint8 gpt_init_flag;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      gpt初始化
//  @param      void            
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void gpt_init(void)
{
    if(!gpt_init_flag)
    {
        gpt_config_t gptConfig;
        
        gpt_init_flag = 1;
        GPT_GetDefaultConfig(&gptConfig);           //获取默认配置
        GPT_Init(DELAY_GPT, &gptConfig);            //GPT初始化 便于打开时钟
        GPT_Deinit(DELAY_GPT);                      //GPT反初始化
        GPT_Init(DELAY_GPT, &gptConfig);            //GPT初始化
        GPT_SetClockDivider(DELAY_GPT, GPT_DIV);    //设置分频系数
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick延时函数
//  @param      time            需要延时的时间
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void systick_delay(uint32 time)
{
#if(0==DELAY_TIMER_TYPE)
    if(time == 0)   return;
    assert(SysTick_LOAD_RELOAD_Msk >= time);//断言   延时时间必须小于或等于SysTick_LOAD_RELOAD_Msk
    SysTick->CTRL = 0x00;                   //先关了 systick ,清标志位
    SysTick->LOAD = time;                   //设置延时时间
    SysTick->VAL = 0x00;                    //清空计数器
    SysTick->CTRL = ( 0 | SysTick_CTRL_ENABLE_Msk     //使能 systick
                  //| SysTick_CTRL_TICKINT_Msk        //使能中断 (注释了表示关闭中断)
                    | SysTick_CTRL_CLKSOURCE_Msk      //时钟源选择 (core clk)
                );
    while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//等待时间到
    
#elif(1==DELAY_TIMER_TYPE)
    
    
    gpt_init();
    GPT_SetOutputCompareValue(DELAY_GPT, kGPT_OutputCompare_Channel1, time);//设置定时时间
    GPT_StartTimer(DELAY_GPT);                      //启动定时器
    while(!GPT_GetStatusFlags(DELAY_GPT,kGPT_OutputCompare1Flag));
    GPT_ClearStatusFlags(DELAY_GPT,kGPT_OutputCompare1Flag);
    GPT_StopTimer(DELAY_GPT);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      毫秒级systick延时函数
//  @param      ms              延时多少毫秒
//  @return     void
//  Sample usage:               systick_delay_ms(1000);   //延时1000毫秒
//-------------------------------------------------------------------------------------------------------------------
void systick_delay_ms(uint32 ms)
{
    //get_clk();//获取内核时钟便于后面设置
	//while(ms--) systick_delay(MSEC_TO_COUNT(1, DELAY_CLK));
    rt_thread_mdelay(ms);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick定时器
//  @param      time            定时时间(0-0x00ffffff)
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void systick_timing(uint32 time)
{
#if(0==DELAY_TIMER_TYPE)
    assert(SysTick_LOAD_RELOAD_Msk >= time);//断言   延时时间必须小于或等于SysTick_LOAD_RELOAD_Msk
    SysTick->LOAD = time;                   //设置延时时间
    SysTick->VAL = 0x00;       	            //清空计数器
    SysTick->CTRL = ( 0 
					| SysTick_CTRL_ENABLE_Msk       //使能 systick
                    | SysTick_CTRL_TICKINT_Msk      //使能中断
                    | SysTick_CTRL_CLKSOURCE_Msk    //时钟源选择 (core clk) 
                );
#elif(1==DELAY_TIMER_TYPE)
    
    gpt_init();
    GPT_SetOutputCompareValue(DELAY_GPT, kGPT_OutputCompare_Channel1, time);//设置定时时间
    GPT_StartTimer(DELAY_GPT);                      //启动定时器
    GPT_EnableInterrupts(DELAY_GPT,GPT_IR_OF1IE_MASK);//使能中断
    EnableIRQ(GPT2_IRQn);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick定时器启动
//  @param      void
//  @return     void
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void systick_start(void)
{
#if(0==DELAY_TIMER_TYPE)
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;//设置延时时间
    SysTick->VAL = 0x00;       	            //清空计数器
    SysTick->CTRL = ( 0 
					| SysTick_CTRL_ENABLE_Msk       //使能 systick
                    //| SysTick_CTRL_TICKINT_Msk      //使能中断
                    | SysTick_CTRL_CLKSOURCE_Msk    //时钟源选择 (core clk) 
                );
#elif(1==DELAY_TIMER_TYPE)
    
    gpt_init();
    GPT_SetOutputCompareValue(DELAY_GPT, kGPT_OutputCompare_Channel1, 0xffffffff);//设置定时时间
    GPT_StartTimer(DELAY_GPT);                      //启动定时器
#endif
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获得当前System tick timer的值
//  @return     返回当前System tick timer的值
//  Sample usage:               uint32 tim = systick_getval();   
//-------------------------------------------------------------------------------------------------------------------
uint32 systick_getval(void)
{
#if(0==DELAY_TIMER_TYPE)
    return (SysTick_LOAD_RELOAD_Msk - SysTick->VAL);
#elif(1==DELAY_TIMER_TYPE)
    return (GPT_GetCurrentTimerCount(DELAY_GPT));
#endif
}