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
 
 
#include "fsl_iomuxc.h"
#include "zf_gpio.h"

GPIO_Type * PORTPTR[] = GPIO_BASE_PTRS;




//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO初始化
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @param      dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
//  @param      pinconf     引脚配置（可设置参数由zf_iomuxc.h文件内PINCONF_enum枚举值确定，多个条件使用 | 相或）
//  @return     void
//  Sample usage:           gpio_init(D0, GPO, 1, GPIO_PIN_CONFIG);//D0初始化为GPIO功能、输出模式、输出高电平、上拉47K IO速度100MHZ 驱动强度R0
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, uint32 pinconf)
{
    gpio_pin_config_t gpio_config;

    if(GPO == dir)      gpio_config.direction = kGPIO_DigitalOutput; 
    else if(GPI == dir) gpio_config.direction = kGPIO_DigitalInput;
    
    if(dat)     gpio_config.outputLogic =  1;
    else        gpio_config.outputLogic =  0;

    gpio_config.interruptMode = (gpio_interrupt_mode_t)NO_INT; //不使用中断
    iomuxc_pinconf(pin,ALT5,pinconf);

    GPIO_PinInit(PORTPTR[pin>>5], pin&0x1f, &gpio_config);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           gpio_set(D0,1);//D0 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set(PIN_enum pin, uint8 dat)
{
    if(dat) GPIO_SetPinsOutput(PORTPTR[pin>>5],1<<(pin&0x1f));
    else    GPIO_ClearPinsOutput(PORTPTR[pin>>5],1<<(pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO状态获取
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = gpio_get(D0);//获取D0引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get(PIN_enum pin)
{
    return (GPIO_ReadPadStatus(PORTPTR[pin>>5],pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO方向设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @return     void        
//  Sample usage:           gpio_dir(D0,GPO);//设置D0为输出模式
//-------------------------------------------------------------------------------------------------------------------
void gpio_dir(PIN_enum pin, GPIODIR_enum dir)
{
    if (GPI == dir) PORTPTR[pin>>5]->GDIR &= ~(1U << (pin&0x1f));
    else            PORTPTR[pin>>5]->GDIR |= (1U << (pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO 翻转
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     void        
//  Sample usage:           gpio_toggle(D0);//D0引脚电平翻转
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle(PIN_enum pin)
{
    GPIO_PortToggle(PORTPTR[pin>>5],1<<(pin&0x1f));
}






//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO 外部中断初始化
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      trigger     中断触发方式 选择范围参见h文件TRIGGER_enum枚举
//  @param      pinconf     引脚配置 （可设置参数由zf_iomuxc.h文件内PINCONF_enum枚举值确定，多个条件使用 | 相或）
//  @return     void        
//  Sample usage:           gpio_interrupt_init(D0,RISING,GPIO_INT_CONFIG);//D0上升沿中断
//-------------------------------------------------------------------------------------------------------------------
void gpio_interrupt_init(PIN_enum pin, TRIGGER_enum trigger, uint32 pinconf)
{
    gpio_pin_config_t gpio_config;

    iomuxc_pinconf(pin,ALT5,pinconf);                           //设置引脚复用
    gpio_config.direction = kGPIO_DigitalInput;
    gpio_config.interruptMode = (gpio_interrupt_mode_t)trigger;
    GPIO_PinInit(PORTPTR[pin>>5], pin&0x1f, &gpio_config);      //初始化GPIO
    GPIO_PortEnableInterrupts(PORTPTR[pin>>5],1<<(pin&0x1f));   //打开GPIO的中断

    EnableIRQ((IRQn_Type)((IRQn_Type)((pin>>4)-2) + GPIO1_Combined_0_15_IRQn));//使用IRQ
    
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)((pin>>4)-2) + GPIO1_Combined_0_15_IRQn),0);//优先级设置 范围0-15 越小优先级越高
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO初始化
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @param      dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
//  @param      pinconf     引脚配置（可设置参数由zf_iomuxc.h文件内PINCONF_enum枚举值确定，多个条件使用 | 相或）
//  @return     void
//  Sample usage:           fast_gpio_init(D0, GPO, 1, FAST_GPIO_PIN_CONFIG);//D0初始化为GPIO功能、输出模式、输出高电平、上拉47K IO速度2000MHZ 驱动强度R0
//                          快速GPIO 最高可达150M的翻转输出，需要达到最高速度不能使用库函数来输出电平，需要直接操作寄存器来控制引脚，具体可以查看h文件中有宏定义
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, uint32 pinconf)
{
    iomuxc_pinconf(pin,ALT5,pinconf);
    
    switch(pin>>5)
    {
        case 1:
        {
            IOMUXC_GPR->GPR26 |= 1<<(pin&0x1f);
        }break;
        case 2:
        {
            IOMUXC_GPR->GPR27 |= 1<<(pin&0x1f);
        }break;
        case 3:
        {
            IOMUXC_GPR->GPR28 |= 1<<(pin&0x1f);
        }break;
    }
    
    pin = (PIN_enum)(pin + F0);

    PORTPTR[pin>>5]->IMR &= ~(1U << (pin&0x1f));

    if (GPI == dir)
    {
        PORTPTR[pin>>5]->GDIR &= ~(1U << (pin&0x1f));
    }
    else
    {
        GPIO_PinWrite(PORTPTR[pin>>5], (pin&0x1f), dat);
        PORTPTR[pin>>5]->GDIR |= (1U << (pin&0x1f));
    }

    GPIO_SetPinInterruptConfig(PORTPTR[pin>>5], (pin&0x1f), kGPIO_NoIntmode);
    
    
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           fast_gpio_set(D0,1);//D0 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_set(PIN_enum pin, uint8 dat)
{
    if(dat) GPIO_SetPinsOutput(PORTPTR[(pin+F0)>>5],1<<(pin&0x1f));
    else    GPIO_ClearPinsOutput(PORTPTR[(pin+F0)>>5],1<<(pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = fast_gpio_get(D0);//获取D0引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 fast_gpio_get(PIN_enum pin)
{
    return (GPIO_ReadPinInput(PORTPTR[(pin+F0)>>5],pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO方向设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @return     void        
//  Sample usage:           fast_gpio_dir(D0,GPO);//设置D0为输出模式
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_dir(PIN_enum pin, GPIODIR_enum dir)
{
    if (GPI == dir) PORTPTR[(pin+F0)>>5]->GDIR &= ~(1U << (pin&0x1f));
    else            PORTPTR[(pin+F0)>>5]->GDIR |= (1U << (pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO 翻转
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     void        
//  Sample usage:           fast_gpio_toggle(D0);//D0引脚电平翻转
//  @note                   使用本函数进行翻转IO，最多只能达到20多M的IO翻转速率，如果使用h文件的寄存器宏定义可以达到最高150M
//                          但是需要注意，如果使用while(1)+宏定义寄存器来翻转IO，会发现频率最多只有100M，那是因为while(1)也占用了指令
//                          想达到最高频率，需要牺牲代码大小来增加速度，也就是写很多宏定义寄存器来翻转IO，这样就没有while(1)指令了
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_toggle(PIN_enum pin)
{
    GPIO_PortToggle(PORTPTR[(pin+F0)>>5],1<<(pin&0x1f));
}
