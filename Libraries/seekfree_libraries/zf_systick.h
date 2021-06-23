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
 
 
 
 
#ifndef _zf_systick_h
#define _zf_systick_h

#include "common.h"
#include "fsl_lpspi.h"

#define DELAY_TIMER_TYPE            1		//0：适用systick进行延时(不能选择此项 已经被RTOS占用)   1：适用GPT进行延时
    
    
#define DELAY_GPT 					GPT2	//选择使用的GPT定时器
#define GPT_DIV   					2		//设置GPT输入时钟分频
    
#if(0==DELAY_TIMER_TYPE)    
    #define DELAY_CLK               CLOCK_GetFreq(kCLOCK_CpuClk)//定义SYSTICK定时器的输入时钟
#else   
    #define DELAY_CLK               (CLOCK_GetFreq(kCLOCK_PerClk)/(GPT_DIV))//定义GPT模块时钟
#endif



void systick_delay(uint32 time);
void systick_timing(uint32 time);
void systick_start(void);
uint32 systick_getval(void);


//------------------------------------以下宏定义用于延时------------------------------------
void systick_delay_ms(uint32 ms);                                                        //毫秒级延时函数 由于滴答定时器最大只有24位，因此用函数实现，这样延时时间范围较宽
#define systick_delay_us(time)      systick_delay(USEC_TO_COUNT(time, DELAY_CLK))        //设置延时时间  单位us   范围0  -  16777215(0xffffff)/(DELAY_CLK*1000)ms   主频500M systick最大延时时间大约为33ms
#define systick_delay_ns(time)      systick_delay(USEC_TO_COUNT(time, DELAY_CLK/1000))   //设置延时时间  单位ns   范围0  -  16777215(0xffffff)*1000/(DELAY_CLK)ns   主频500M systick最大延时时间大约为33ms
//以上延时函数可以DELAY_TIMER_TYPE宏定义选择  延时所使用的定时器类型，当使用库里面的文件系统时请将宏定义设置为1，因为文件系统需要占用systick定时器


    
//------------------------------------以下宏定义用于定时------------------------------------  
#define systick_timing_ms(time)     systick_timing(MSEC_TO_COUNT(time, DELAY_CLK))       //设置定时时间  单位ms   范围0  -  16777215(0xffffff)/(DELAY_CLK*1000)ms   主频500M 最大定时时间大约为33ms
#define systick_timing_us(time)     systick_timing(USEC_TO_COUNT(time, DELAY_CLK))       //设置定时时间  单位us   范围0  -  16777215(0xffffff)/(DELAY_CLK)us        主频500M 最大定时时间大约为33ms
#define systick_timing_ns(time)     systick_timing(USEC_TO_COUNT(time, DELAY_CLK/1000))  //设置定时时间  单位ns   范围0  -  16777215(0xffffff)*1000/(DELAY_CLK)ns   主频500M 最大定时时间大约为33ms


//------------------------------------以下宏定义用于获取当前时间------------------------------------
#define systick_getval_ms()         COUNT_TO_MSEC(systick_getval(),DELAY_CLK)            //获取当前计时时间  单位ms
#define systick_getval_us()         COUNT_TO_USEC(systick_getval(),DELAY_CLK)            //获取当前计时时间  单位us
#define systick_getval_ns()         COUNT_TO_USEC(systick_getval()*1000,DELAY_CLK)       //获取当前计时时间  单位ns

#endif