/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		pwm
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#ifndef _zf_pwm_h
#define _zf_pwm_h

#include "common.h"
#include "fsl_pwm.h"

//此枚举定义不允许用户修改
typedef enum
{
    //同一个子模块不同通道只能输出相同频率的PWM，占空比可设置不同
    //例如PWM1_MODULE0_CHB与PWM1_MODULE0_CHA属于同一个子模块，频率只能一样，但是占空比可以不一样
    //PWM1_MODULE0_CHA_D12与PWM1_MODULE1_CHA_D14虽然是同一个PWM模块但是属于不同的子模块可以输出不同频率的PWM
    
    PWM1_MODULE0_CHB_D13=1*40+5*0,  PWM1_MODULE0_CHB_E24,   //PWM1 子模块0 通道B  引脚可选范围
    PWM1_MODULE0_CHA_D12=1*40+5*1,  PWM1_MODULE0_CHA_E23,   //PWM1 子模块0 通道A  引脚可选范围 
    
    PWM1_MODULE1_CHB_D15=1*40+5*2,  PWM1_MODULE1_CHB_E26,   //PWM1 子模块1 通道B  引脚可选范围
    PWM1_MODULE1_CHA_D14=1*40+5*3,  PWM1_MODULE1_CHA_E25,   //PWM1 子模块1 通道A  引脚可选范围
    
    PWM1_MODULE2_CHB_D17=1*40+5*4,  PWM1_MODULE2_CHB_E28,   //PWM1 子模块2 通道B  引脚可选范围
    PWM1_MODULE2_CHA_D16=1*40+5*5,  PWM1_MODULE2_CHA_E27,   //PWM1 子模块2 通道A  引脚可选范围

    PWM1_MODULE3_CHB_B11=1*40+5*6,  PWM1_MODULE3_CHB_C17,   PWM1_MODULE3_CHB_D1,    PWM1_MODULE3_CHB_D25,   PWM1_MODULE3_CHB_E13,//PWM1 子模块3 通道B  引脚可选范围
    PWM1_MODULE3_CHA_B10=1*40+5*7,  PWM1_MODULE3_CHA_C16,   PWM1_MODULE3_CHA_D0,    PWM1_MODULE3_CHA_D24,   PWM1_MODULE3_CHA_E12,//PWM1 子模块3 通道A  引脚可选范围
    
    //-----------------------------------------------------------------------------
    PWM2_MODULE0_CHB_C7 =2*40+5*0,  PWM2_MODULE0_CHB_E7,    //PWM2 子模块0 通道B  引脚可选范围
    PWM2_MODULE0_CHA_C6 =2*40+5*1,  PWM2_MODULE0_CHA_E6,    //PWM2 子模块0 通道A  引脚可选范围
                                
    PWM2_MODULE1_CHB_C9 =2*40+5*2,  PWM2_MODULE1_CHB_E9,    //PWM2 子模块1 通道B  引脚可选范围
    PWM2_MODULE1_CHA_C8 =2*40+5*3,  PWM2_MODULE1_CHA_E8,    //PWM2 子模块1 通道A  引脚可选范围
                        
    PWM2_MODULE2_CHB_C11=2*40+5*4,  PWM2_MODULE2_CHB_E11,   //PWM2 子模块2 通道B  引脚可选范围
    PWM2_MODULE2_CHA_C10=2*40+5*5,  PWM2_MODULE2_CHA_E10,   //PWM2 子模块2 通道A  引脚可选范围
                        
    PWM2_MODULE3_CHB_B1 =2*40+5*6,  PWM2_MODULE3_CHB_C19,   PWM2_MODULE3_CHB_D3,    PWM2_MODULE3_CHB_E20,                       //PWM2 子模块3 通道B  引脚可选范围
    PWM2_MODULE3_CHA_B0 =2*40+5*7,  PWM2_MODULE3_CHA_C18,   PWM2_MODULE3_CHA_D2,    PWM2_MODULE3_CHA_E19,   PWM2_MODULE3_CHA_B9,//PWM2 子模块3 通道A  引脚可选范围
    
    //-----------------------------------------------------------------------------
    //PWM3模块的引脚全部被SDRAM所占用
    PWM3_MODULE0_CHB_E30=3*40+5*0,                          //PWM3 子模块0 通道B  引脚可选范围
    PWM3_MODULE0_CHA_E29=3*40+5*1,                          //PWM3 子模块0 通道A  引脚可选范围
                        
    PWM3_MODULE1_CHB_D18=3*40+5*2,                          //PWM3 子模块1 通道B  引脚可选范围
    PWM3_MODULE1_CHA_E31=3*40+5*3,                          //PWM3 子模块1 通道A  引脚可选范围
                        
    PWM3_MODULE2_CHB_D20=3*40+5*4,                          //PWM3 子模块2 通道B  引脚可选范围
    PWM3_MODULE2_CHA_D19=3*40+5*5,                          //PWM3 子模块2 通道A  引脚可选范围
                        
    PWM3_MODULE3_CHB_E22=3*40+5*6,                          //PWM3 子模块3 通道B  引脚可选范围
    PWM3_MODULE3_CHA_E21=3*40+5*7,                          //PWM3 子模块3 通道A  引脚可选范围
    
    //-----------------------------------------------------------------------------
    PWM4_MODULE0_CHB_E1 =4*40+5*0,                          //PWM4 子模块0 通道B  引脚可选范围
    PWM4_MODULE0_CHA_B24=4*40+5*1,   PWM4_MODULE0_CHA_E0,   //PWM4 子模块0 通道A  引脚可选范围
                                
    PWM4_MODULE1_CHB_E3 =4*40+5*2,                          //PWM4 子模块1 通道B  引脚可选范围
    PWM4_MODULE1_CHA_B25=4*40+5*3,   PWM4_MODULE1_CHA_E2,   //PWM4 子模块1 通道A  引脚可选范围
                            
    PWM4_MODULE2_CHB_E5 =4*40+5*4,                          //PWM4 子模块2 通道B  引脚可选范围
    PWM4_MODULE2_CHA_C30=4*40+5*5,   PWM4_MODULE2_CHA_E4,   //PWM4 子模块2 通道A  引脚可选范围
                            
    PWM4_MODULE3_CHB_E18=4*40+5*6,                          //PWM4 子模块3 通道B  引脚可选范围
    PWM4_MODULE3_CHA_C31=4*40+5*7,   PWM4_MODULE3_CHA_E17   //PWM4 子模块3 通道A  引脚可选范围
    
}PWMCH_enum;




void pwm_init(PWMCH_enum pwmch, uint32 freq, uint32 duty);
void pwm_duty(PWMCH_enum pwmch, uint32 duty);
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint32 duty);



#endif