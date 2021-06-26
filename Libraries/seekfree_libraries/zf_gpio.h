/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		gpio
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#ifndef _zf_gpio_h
#define _zf_gpio_h

#include "common.h"
#include "MIMXRT1064.h"
#include "fsl_gpio.h"
#include "zf_iomuxc.h"

extern GPIO_Type * PORTPTR[];

#define GPIO_PIN_CONFIG         SPEED_100MHZ | DSE_R0 | PULLUP_47K | PULL_EN	//宏定义GPIO引脚的默认配置，便于初始化GPIO时快速填写参数，如果需要其他参数可自行修改
#define FAST_GPIO_PIN_CONFIG    SPEED_200MHZ | DSE_R0 | PULLUP_47K | PULL_EN    //宏定义快速GPIO引脚的默认配置，便于初始化GPIO时快速填写参数，如果需要其他参数可自行修改
#define GPIO_INT_CONFIG         SPEED_100MHZ | HYS_EN | PULLUP_22K | PULL_EN    //宏定义GPIO中断引脚的默认配置，便于初始化GPIO中断时快速填写参数，如果需要其他参数可自行修改

typedef enum    // 枚举触发方式
{
    NO_INT,     //关闭中断模式
    LOW,
    HIGH,
    RISING,
    FALLING,
    BOTH,       //仅PINT模块 可用此触发方式
}TRIGGER_enum;



//------------------------------------------------------
//通用GPIO操作
void gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, uint32 pinconf);
void gpio_set(PIN_enum pin, uint8 dat);
uint8 gpio_get(PIN_enum pin);
void gpio_dir(PIN_enum pin, GPIODIR_enum dir);
void gpio_toggle(PIN_enum pin);

#define PORTB_DR           		GPIO1->DR                   //B端口数据输出寄存器
#define PORTC_DR           		GPIO2->DR                   //C端口数据输出寄存器
#define PORTD_DR           		GPIO3->DR                   //D端口数据输出寄存器



//GPIO中断初始化
void gpio_interrupt_init(PIN_enum pin, TRIGGER_enum trigger, uint32 pinconf);


//中断标志位获取 
#define GET_GPIO_FLAG(pin)      ((GPIO_GetPinsInterruptFlags(PORTPTR[pin>>5]) >> (pin&0x1f)) & 0x01)
//中断标志位清除   
#define CLEAR_GPIO_FLAG(pin)    GPIO_ClearPinsInterruptFlags(PORTPTR[pin>>5], (uint32)1<<(pin&0x1f));


//------------------------------------------------------
//以下函数用于实现快速GPIO的操作，快速GPIO最高可达150M的IO翻转速度

void fast_gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, uint32 pinconf);
void fast_gpio_set(PIN_enum pin, uint8 dat);
uint8 fast_gpio_get(PIN_enum pin);
void fast_gpio_dir(PIN_enum pin, GPIODIR_enum dir);
void fast_gpio_toggle(PIN_enum pin);

#define PORTB_FAST_DR           GPIO6->DR                   //B端口数据输出寄存器
#define PORTC_FAST_DR           GPIO7->DR                   //C端口数据输出寄存器
#define PORTD_FAST_DR           GPIO8->DR                   //D端口数据输出寄存器

#define PORTB_FAST_PSR          GPIO6->PSR                  //B端口数据输入寄存器
#define PORTC_FAST_PSR          GPIO7->PSR                  //C端口数据输入寄存器
#define PORTD_FAST_PSR          GPIO8->PSR                  //D端口数据输入寄存器

#define PORTB_FAST_SET(X)       GPIO6->DR_SET    = 1<<X     //B端口快速GPIO置一寄存器     X选择端口号 5：表示B5
#define PORTC_FAST_SET(X)       GPIO7->DR_SET    = 1<<X     //C端口快速GPIO置一寄存器     X选择端口号 5：表示C5
#define PORTD_FAST_SET(X)       GPIO8->DR_SET    = 1<<X     //D端口快速GPIO置一寄存器     X选择端口号 5：表示D5
                                                                                          
#define PORTB_FAST_CLR(X)       GPIO6->DR_CLEAR  = 1<<X     //B端口快速GPIO置低寄存器     X选择端口号 5：表示B5
#define PORTC_FAST_CLR(X)       GPIO7->DR_CLEAR  = 1<<X     //C端口快速GPIO置低寄存器     X选择端口号 5：表示C5
#define PORTD_FAST_CLR(X)       GPIO8->DR_CLEAR  = 1<<X     //D端口快速GPIO置低寄存器     X选择端口号 5：表示D5
                                                                                          
#define PORTB_FAST_TOGGLE(X)    GPIO6->DR_TOGGLE = 1<<X     //B端口快速GPIO取反寄存器     X选择端口号 5：表示B5
#define PORTC_FAST_TOGGLE(X)    GPIO7->DR_TOGGLE = 1<<X     //C端口快速GPIO取反寄存器     X选择端口号 5：表示C5
#define PORTD_FAST_TOGGLE(X)    GPIO8->DR_TOGGLE = 1<<X     //D端口快速GPIO取反寄存器     X选择端口号 5：表示D5






#endif
