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
 

#include "zf_iomuxc.h"
#include "zf_qtimer.h"


#define QTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_IpgClk)
#define QTIMER_PIN_CONF  SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置QTIMER引脚默认配置

TMR_Type * QTIMERN[] = TMR_BASE_PTRS;

void qtimer_iomuxc(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA, QTIMER_PIN_enum phaseB)
{
    switch(qtimern)
    {
        case QTIMER_1:
        {
            if((phaseA/3) == (phaseB/3))            assert(0);  //引脚设置错误,不允许设置为同一个定时器 断言失败
            if      (QTIMER1_TIMER0_C0  == phaseA)  iomuxc_pinconf(C0 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER1_TIMER1_C1  == phaseA)  iomuxc_pinconf(C1 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER1_TIMER2_C2  == phaseA)  iomuxc_pinconf(C2 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER1_TIMER3_C24 == phaseA)  iomuxc_pinconf(C24,ALT1,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
            
            if      (QTIMER1_TIMER0_C0  == phaseB)  iomuxc_pinconf(C0 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER1_TIMER1_C1  == phaseB)  iomuxc_pinconf(C1 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER1_TIMER2_C2  == phaseB)  iomuxc_pinconf(C2 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER1_TIMER3_C24 == phaseB)  iomuxc_pinconf(C24,ALT1,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
            
        }break;
        case QTIMER_2:
        {
            if((phaseA/3) == (phaseB/3))            assert(0);  //引脚设置错误,不允许设置为同一个定时器 断言失败
            if      (QTIMER2_TIMER0_C3  == phaseA)  iomuxc_pinconf(C3 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER0_E19 == phaseA)  iomuxc_pinconf(E19,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER1_C4  == phaseA)  iomuxc_pinconf(C4 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER1_E20 == phaseA)  iomuxc_pinconf(E20,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER2_C5  == phaseA)  iomuxc_pinconf(C5 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER2_E21 == phaseA)  iomuxc_pinconf(E21,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER3_C25 == phaseA)  iomuxc_pinconf(C25,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER3_E22 == phaseA)  iomuxc_pinconf(E22,ALT4,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
            
            if      (QTIMER2_TIMER0_C3  == phaseB)  iomuxc_pinconf(C3 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER0_E19 == phaseB)  iomuxc_pinconf(E19,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER1_C4  == phaseB)  iomuxc_pinconf(C4 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER1_E20 == phaseB)  iomuxc_pinconf(E20,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER2_C5  == phaseB)  iomuxc_pinconf(C5 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER2_E21 == phaseB)  iomuxc_pinconf(E21,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER3_C25 == phaseB)  iomuxc_pinconf(C25,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER2_TIMER3_E22 == phaseB)  iomuxc_pinconf(E22,ALT4,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
        }break;
        
        case QTIMER_3:
        {
            if((phaseA/3) == (phaseB/3))            assert(0);  //引脚设置错误,不允许设置为同一个定时器 断言失败
            if      (QTIMER3_TIMER0_B16 == phaseA)  iomuxc_pinconf(B16,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER0_C6  == phaseA)  iomuxc_pinconf(C6 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER0_E15 == phaseA)  iomuxc_pinconf(E15,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER1_B17 == phaseA)  iomuxc_pinconf(B17,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER1_C7  == phaseA)  iomuxc_pinconf(C7 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER1_E16 == phaseA)  iomuxc_pinconf(E16,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER2_B18 == phaseA)  iomuxc_pinconf(B18,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER2_C8  == phaseA)  iomuxc_pinconf(C8 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER2_E17 == phaseA)  iomuxc_pinconf(E17,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER3_B19 == phaseA)  iomuxc_pinconf(B19,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER3_C26 == phaseA)  iomuxc_pinconf(C26,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER3_E18 == phaseA)  iomuxc_pinconf(E18,ALT4,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
            
            if      (QTIMER3_TIMER0_B16 == phaseB)  iomuxc_pinconf(B16,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER0_C6  == phaseB)  iomuxc_pinconf(C6 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER0_E15 == phaseB)  iomuxc_pinconf(E15,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER1_B17 == phaseB)  iomuxc_pinconf(B17,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER1_C7  == phaseB)  iomuxc_pinconf(C7 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER1_E16 == phaseB)  iomuxc_pinconf(E16,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER2_B18 == phaseB)  iomuxc_pinconf(B18,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER2_C8  == phaseB)  iomuxc_pinconf(C8 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER2_E17 == phaseB)  iomuxc_pinconf(E17,ALT4,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER3_B19 == phaseB)  iomuxc_pinconf(B19,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER3_C26 == phaseB)  iomuxc_pinconf(C26,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER3_TIMER3_E18 == phaseB)  iomuxc_pinconf(E18,ALT4,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
        }break;
        
        case QTIMER_4:
        {
            if((phaseA/3) == (phaseB/3))            assert(0);  //引脚设置错误,不允许设置为同一个定时器 断言失败
            if      (QTIMER4_TIMER0_C9  == phaseA)  iomuxc_pinconf(C9 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER4_TIMER1_C10 == phaseA)  iomuxc_pinconf(C10,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER4_TIMER2_C11 == phaseA)  iomuxc_pinconf(C11,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER4_TIMER3_C27 == phaseA)  iomuxc_pinconf(C27,ALT1,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
            
            if      (QTIMER4_TIMER0_C9  == phaseB)  iomuxc_pinconf(C9 ,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER4_TIMER1_C10 == phaseB)  iomuxc_pinconf(C10,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER4_TIMER2_C11 == phaseB)  iomuxc_pinconf(C11,ALT1,QTIMER_PIN_CONF);
            else if (QTIMER4_TIMER3_C27 == phaseB)  iomuxc_pinconf(C27,ALT1,QTIMER_PIN_CONF);
            else    assert(0);  //引脚设置错误 断言失败
        }break;
        default:assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      QTIMER正交解码初始化
//  @param      qtimern         选择QTIMER模块(QTIMER_1、QTIMER_2)
//  @param      phaseA          选择正交解码 A端口
//  @param      phaseB          选择正交解码 B端口
//  @return     void
//  Sample usage:				qtimer_quad_init(QTIMER_1, QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
//-------------------------------------------------------------------------------------------------------------------
void qtimer_quad_init(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA, QTIMER_PIN_enum phaseB)
{
    uint8 qtimer_Ach;
    uint8 qtimer_Bch;
    qtmr_config_t qtmrConfig;
    qtimer_iomuxc(qtimern, phaseA, phaseB);

    qtimer_Ach = (phaseA%12)/3;//计算A通道
    qtimer_Bch = (phaseB%12)/3;//计算B通道
    
    QTMR_GetDefaultConfig(&qtmrConfig);
    qtmrConfig.primarySource = (qtmr_primary_count_source_t)(qtimer_Ach);
    qtmrConfig.secondarySource = (qtmr_input_source_t)(qtimer_Bch);
    QTMR_Init(QTIMERN[qtimern], (qtmr_channel_selection_t)(qtimer_Ach), &qtmrConfig);//第一次初始化便于打开时钟
    QTMR_Deinit(QTIMERN[qtimern], (qtmr_channel_selection_t)(qtimer_Ach));           //复位外设
    QTMR_Init(QTIMERN[qtimern], (qtmr_channel_selection_t)(qtimer_Ach), &qtmrConfig);//重新初始化设置正确的参数
    
    QTMR_StartTimer(QTIMERN[qtimern], (qtmr_channel_selection_t)(qtimer_Ach), kQTMR_PriSrcRiseEdgeSecDir);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      QTIMER正交解码计数获取
//  @param      qtimern         选择QTIMER模块(QTIMER_1、QTIMER_2)
//  @param      phaseA          选择正交解码 A端口 这个参数需要与qtimer_quad_init函数第二个参数一致 
//  @return     int16			返回脉冲数
//  Sample usage:				qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0);
//-------------------------------------------------------------------------------------------------------------------
int16 qtimer_quad_get(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA)
{
    uint8 qtimer_Ach;
    qtimer_Ach = (phaseA%12)/3;//计算A通道
    return QTMR_GetCurrentTimerCount(QTIMERN[qtimern], (qtmr_channel_selection_t)(qtimer_Ach));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      QTIMER正交解码计数清零
//  @param      qtimern         选择QTIMER模块(QTIMER_1、QTIMER_2)
//  @param      phaseA          选择正交解码 A端口 这个参数需要与qtimer_quad_init函数第二个参数一致 
//  @return     void
//  Sample usage:				qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0);
//-------------------------------------------------------------------------------------------------------------------
void qtimer_quad_clear(QTIMERN_enum qtimern, QTIMER_PIN_enum phaseA)
{
    uint8 qtimer_Ach;
    qtimer_Ach = (phaseA%12)/3;//计算A通道
    QTIMERN[qtimern]->CHANNEL[qtimer_Ach].CNTR = 0;
}

