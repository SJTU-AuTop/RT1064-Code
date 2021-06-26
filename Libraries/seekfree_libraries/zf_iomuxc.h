/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		iomuxc
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
 
#ifndef _zf_iomuxc_h
#define _zf_iomuxc_h

#include "MIMXRT1064.h"
#include "common.h"

typedef enum
{
    ALT0,
    ALT1,
    ALT2,
    ALT3,
    ALT4,
    ALT5,
    ALT6,
    ALT7,
    ALT8,
    ALT9,
    ALT_MAX,
}ALT_enum;



typedef enum
{
    HYS_EN          = 1<<IOMUXC_SW_PAD_CTL_PAD_HYS_SHIFT,   //滞后使能
    
    PULLDOWN_100K   = 0<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,   //端口为输入时有效
    PULLUP_47K      = 1<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,   //端口为输入时有效
    PULLUP_100K     = 2<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,   //端口为输入时有效
    PULLUP_22K      = 3<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,   //端口为输入时有效
    
    PULL_EN         = 1<<IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT | 1<<IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT,
    KEEPER_EN       = 1<<IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT,   //保持器使能
    
    OD_EN           = 1<<IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT,   //开漏使能
    
    SPEED_50MHZ     = 0<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    SPEED_100MHZ    = 1<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    SPEED_200MHZ    = 3<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    
    DSE_DIS         = 0<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //禁用输出强度设置
    DSE_R0          = 1<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //3.3V时150ohm  1.8V时260ohm
    DSE_R0_2        = 2<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //R/2
    DSE_R0_3        = 3<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //R/3
    DSE_R0_4        = 4<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //R/4
    DSE_R0_5        = 5<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //R/5
    DSE_R0_6        = 6<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //R/6
    DSE_R0_7        = 7<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,   //R/7
        
    SRE_SLOW        = 0<<IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT,
    SRE_FAST        = 1<<IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT,
    
}PINCONF_enum;




void iomuxc_pinconf(PIN_enum pin, ALT_enum alt, uint32 pinconf);


#endif