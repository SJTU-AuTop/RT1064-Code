/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		adc
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#ifndef _zf_adc_h
#define _zf_adc_h


#include "common.h"
#include "fsl_adc.h"



//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
    ADC1_CH0_B27,    
    ADC1_CH1_B12,    
    ADC1_CH2_B13,    
    ADC1_CH3_B14,    
    ADC1_CH4_B15,    
    ADC1_CH5_B16,    
    ADC1_CH6_B17,    
    ADC1_CH7_B18,        
    ADC1_CH8_B19,        
    ADC1_CH9_B20,        
    ADC1_CH10_B21,       
    ADC1_CH11_B22,
    ADC1_CH12_B23,
    ADC1_CH13_B24,
    ADC1_CH14_B25,
    ADC1_CH15_B26,
    
    ADC2_CH0_B27,    
    ADC2_CH1_B28,    
    ADC2_CH2_B29,    
    ADC2_CH3_B30,    
    ADC2_CH4_B31,    
    ADC2_CH5_B16,    
    ADC2_CH6_B17,    
    ADC2_CH7_B18,        
    ADC2_CH8_B19,        
    ADC2_CH9_B20,        
    ADC2_CH10_B21,       
    ADC2_CH11_B22,
    ADC2_CH12_B23,
    ADC2_CH13_B24,
    ADC2_CH14_B25,
    ADC2_CH15_B26,
}ADCCH_enum;

//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
    ADC_8BIT,     //8位分辨率
    ADC_10BIT,    //10位分辨率
    ADC_12BIT,    //12位分辨率

}ADCRES_enum;

//此枚举定义不允许用户修改
typedef enum    // 枚举ADC编号
{
    ADC_0,      //RT1064没有ADC0 这里仅用于占位
    ADC_1,     
    ADC_2,  

}ADCN_enum;





void adc_init(ADCN_enum adcn, ADCCH_enum ch, ADCRES_enum resolution);
uint16 adc_convert(ADCN_enum adcn, ADCCH_enum ch);
uint16 adc_mean_filter(ADCN_enum adcn, ADCCH_enum ch, uint8 count);





#endif