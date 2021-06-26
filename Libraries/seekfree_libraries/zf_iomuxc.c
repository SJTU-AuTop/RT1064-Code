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
 

#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "zf_iomuxc.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      IO复用设置与引脚配置
//  @param      pin         选择引脚（选择范围 详见common.h文件内 PIN_enum枚举中的值）
//  @param      alt         复用功能（ALT0-ALT7）
//  @param      pinconf     引脚配置（可设置参数由zf_iomuxc.h文件内PINCONF_enum枚举值确定，多个条件使用 | 相或）
//  @return     void
//  Sample usage:           iomuxc_pinconf(D5,ALT5,PULLUP_100K|SPEED_50MHZ|DSE_R0);     
//                          D5复用功能设置为ALT5，ALT5为GPIO功能，上拉100K IO速度50MHZ 驱动强度R0
//-------------------------------------------------------------------------------------------------------------------
void iomuxc_pinconf(PIN_enum pin, ALT_enum alt, uint32 pinconf)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);           /* iomuxc clock (iomuxc_clk_enable): 0x03u */
    if(B0<=pin && B31>=pin)//端口B
    {
        switch(pin)
        {
            case B0:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_FLEXPWM2_PWMA03,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_XBAR1_INOUT14,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_REF_CLK_32K,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_USB_OTG2_ID,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_LPI2C1_SCLS,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_GPIO1_IO00,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_USDHC1_RESET_B,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_LPSPI3_SCK,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_00_GPIO1_IO00,pinconf);
            }break;
            
            case B1:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_FLEXPWM2_PWMB03,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_XBAR1_INOUT15,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_REF_CLK_24M,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_USB_OTG1_ID,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_LPI2C1_SDAS,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_EWM_OUT_B,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_LPSPI3_SDO,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,pinconf);
            }break;
            
            case B2:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_FLEXCAN2_TX,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_XBAR1_INOUT16,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_USB_OTG1_PWR,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_FLEXPWM1_PWMX00,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPI2C1_HREQ,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPSPI3_SDI,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02,pinconf);
            }break;
            
            case B3:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_FLEXCAN2_RX,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_XBAR1_INOUT17,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_USB_OTG1_OC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_FLEXPWM1_PWMX01,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_GPIO1_IO03,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_REF_CLK_24M,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_LPSPI3_PCS0,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_03_GPIO1_IO03,pinconf);
            }break;
            
            //以下引脚核心板并未引出，这里屏蔽以减少代码大小
//            case B4:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_SRC_BOOT_MODE00,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_MQS_RIGHT,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_ENET_TX_DATA03,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_SAI2_TX_SYNC,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_CSI_DATA09,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_PIT_TRIGGER00,0);
//                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_LPSPI3_PCS1,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,pinconf);
//            }break;
//            
//            case B5:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_SRC_BOOT_MODE01,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_MQS_LEFT,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_ENET_TX_DATA02,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_SAI2_TX_BCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_CSI_DATA08,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_GPIO1_IO05,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_XBAR1_INOUT17,0);
//                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_05_LPSPI3_PCS2,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_05_GPIO1_IO05,pinconf);
//            }break;
//            
//            case B6:
//            {
//                assert(0);              //不允许使用SWD引脚，避免出现问题。
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_JTAG_TMS,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_GPT2_COMPARE1,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_ENET_RX_CLK,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_SAI2_RX_BCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_CSI_DATA07,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_GPIO1_IO06,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_XBAR1_INOUT18,0);
//                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_LPSPI3_PCS3,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_06_GPIO1_IO06,pinconf);
//            }break;
//            
//            case B7:
//            {
//                assert(0);              //不允许使用SWD引脚，避免出现问题。
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_JTAG_TCK,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_GPT2_COMPARE2,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_ENET_TX_ER,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_SAI2_RX_SYNC,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_CSI_DATA06,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_GPIO1_IO07,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_XBAR1_INOUT19,0);
//                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_ENET_1588_EVENT3_OUT,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_07_GPIO1_IO07,pinconf);
//            }break;
//            
//            case B8:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_JTAG_MOD,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_GPT2_COMPARE3,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_ENET_RX_DATA03,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_SAI2_RX_DATA,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_CSI_DATA05,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_GPIO1_IO08,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_XBAR1_IN20,0);
//                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_08_ENET_1588_EVENT3_IN,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_08_GPIO1_IO08,pinconf);
//            }break;
            
            case B9:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_JTAG_TDI,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_FLEXPWM2_PWMA03,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_ENET_RX_DATA02,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_SAI2_TX_DATA,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_CSI_DATA04,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_XBAR1_IN21,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPT2_CLK,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_SEMC_DQS4,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,pinconf);
            }break;
            
            case B10:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_JTAG_TDO,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_FLEXPWM1_PWMA03,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_ENET_CRS,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_SAI2_MCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_CSI_DATA03,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_XBAR1_IN22,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_ENET_1588_EVENT0_OUT,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_FLEXCAN3_TX,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_ARM_TRACE_SWO,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10,pinconf);
            }break;
            
            case B11:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_JTAG_TRSTB,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_FLEXPWM1_PWMB03,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_ENET_COL,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_WDOG1_WDOG_B,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_CSI_DATA02,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_XBAR1_IN23,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_ENET_1588_EVENT0_IN,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_FLEXCAN3_RX,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_SEMC_CLK6,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11,pinconf);
            }break;
            
            case B12:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPI2C4_SCL,1);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_CCM_PMIC_READY,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_WDOG2_WDOG_B,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_FLEXPWM1_PWMX02,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_GPIO1_IO12,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_ENET_1588_EVENT1_OUT,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_NMI_GLUE_NMI,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_GPIO1_IO12,pinconf);
            }break;
            
            case B13:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPI2C4_SDA,1);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_GPT1_CLK,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_EWM_OUT_B,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_FLEXPWM1_PWMX03,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_GPIO1_IO13,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_ENET_1588_EVENT1_IN,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_REF_CLK_24M,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_GPIO1_IO13,pinconf);
            }break;
            
            case B14:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_USB_OTG2_OC,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_XBAR1_IN24,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_LPUART1_CTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_ENET_1588_EVENT0_OUT,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_CSI_VSYNC,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_FLEXCAN2_TX,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_FLEXCAN3_TX,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14,pinconf);
            }break;
            
            case B15:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_USB_OTG2_PWR,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_XBAR1_IN25,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_LPUART1_RTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_ENET_1588_EVENT0_IN,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_CSI_HSYNC,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_GPIO1_IO15,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_FLEXCAN2_RX,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_WDOG1_WDOG_RST_B_DEB,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_FLEXCAN3_RX,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_15_GPIO1_IO15,pinconf);
            }break;
            
            case B16:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_USB_OTG2_ID,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_QTIMER3_TIMER0,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_LPUART2_CTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL,1);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_WDOG1_B,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_USDHC1_WP,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_KPP_ROW07,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_ENET2_1588_EVENT0_OUT,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_FLEXIO3_FLEXIO00,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16,pinconf);
            }break;
            
            case B17:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_USB_OTG1_PWR,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_QTIMER3_TIMER1,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_LPUART2_RTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA,1);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_CCM_PMIC_READY,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_USDHC1_VSELECT,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_KPP_COL07,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_ENET2_1588_EVENT0_IN,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_FLEXIO3_FLEXIO01,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17,pinconf);
            }break;
            
            case B18:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_USB_OTG1_ID,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_QTIMER3_TIMER2,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_SPDIF_OUT,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_ENET_1588_EVENT2_OUT,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_GPIO1_IO18,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_USDHC1_CD_B,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_KPP_ROW06,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_GPT2_CLK,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_FLEXIO3_FLEXIO02,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_02_GPIO1_IO18,pinconf);
            }break;
            
            case B19:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_USB_OTG1_OC,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_QTIMER3_TIMER3,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_SPDIF_IN,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_ENET_1588_EVENT2_IN,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_GPIO1_IO19,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_USDHC2_CD_B,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_KPP_COL06,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_GPT2_CAPTURE1,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_FLEXIO3_FLEXIO03,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_03_GPIO1_IO19,pinconf);
            }break;
            
            case B20:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_FLEXSPIB_DATA03,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_ENET_MDC,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_LPUART3_CTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_SPDIF_SR_CLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_CSI_PIXCLK,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_GPIO1_IO20,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_USDHC2_DATA0,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_KPP_ROW05,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_GPT2_CAPTURE2,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_FLEXIO3_FLEXIO04,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_04_GPIO1_IO20,pinconf);
            }break;
            
            case B21:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_FLEXSPIB_DATA02,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_ENET_MDIO,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_LPUART3_RTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_SPDIF_OUT,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_CSI_MCLK,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_GPIO1_IO21,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_USDHC2_DATA1,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_KPP_COL05,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_GPT2_COMPARE1,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_FLEXIO3_FLEXIO05,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_05_GPIO1_IO21,pinconf);
            }break;
            
            case B22:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_FLEXSPIB_DATA01,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA,1);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_SPDIF_LOCK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_CSI_VSYNC,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_GPIO1_IO22,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_USDHC2_DATA2,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_KPP_ROW04,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_GPT2_COMPARE2,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_FLEXIO3_FLEXIO06,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_06_GPIO1_IO22,pinconf);
            }break;
            
            case B23:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_FLEXSPIB_DATA00,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL,1);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_SPDIF_EXT_CLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_CSI_HSYNC,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_GPIO1_IO23,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_USDHC2_DATA3,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_KPP_COL04,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_GPT2_COMPARE3,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_FLEXIO3_FLEXIO07,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_07_GPIO1_IO23,pinconf);
            }break;
            
            case B24:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_FLEXSPIA_SS1_B,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_FLEXPWM4_PWMA00,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_FLEXCAN1_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_CCM_PMIC_READY,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_CSI_DATA09,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_USDHC2_CMD,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_KPP_ROW03,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_FLEXIO3_FLEXIO08,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24,pinconf);
            }break;
            
            case B25:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_FLEXSPIA_DQS,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_FLEXPWM4_PWMA01,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_FLEXCAN1_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_SAI1_MCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_CSI_DATA08,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_USDHC2_CLK,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_KPP_COL03,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_FLEXIO3_FLEXIO09,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25,pinconf);
            }break;
            
            case B26:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_FLEXSPIA_DATA03,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_WDOG1_B,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_LPUART8_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_SAI1_RX_SYNC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_CSI_DATA07,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_USDHC2_WP,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_KPP_ROW02,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_ENET2_1588_EVENT1_OUT,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_FLEXIO3_FLEXIO10,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26,pinconf);
            }break;
            
            case B27:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_FLEXSPIA_DATA02,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_EWM_OUT_B,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_LPUART8_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_SAI1_RX_BCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_CSI_DATA06,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_USDHC2_RESET_B,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_KPP_COL02,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_ENET2_1588_EVENT1_IN,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_FLEXIO3_FLEXIO11,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27,pinconf);
            }break;
            
            case B28:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_FLEXSPIA_DATA01,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_ACMP_OUT00,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_LPSPI3_PCS0,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_SAI1_RX_DATA00,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_CSI_DATA05,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_USDHC2_DATA4,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_KPP_ROW01,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_ENET2_1588_EVENT2_OUT,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_FLEXIO3_FLEXIO12,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28,pinconf);
            }break;
            
            case B29:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_FLEXSPIA_DATA00,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_ACMP_OUT01,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_LPSPI3_SDI,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_SAI1_TX_DATA00,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_CSI_DATA04,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_GPIO1_IO29,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_USDHC2_DATA5,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_KPP_COL01,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_ENET2_1588_EVENT2_IN,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_FLEXIO3_FLEXIO13,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_13_GPIO1_IO29,pinconf);
            }break;
            
            case B30:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_FLEXSPIA_SCLK,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_ACMP_OUT02,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_LPSPI3_SDO,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_SAI1_TX_BCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_CSI_DATA03,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_GPIO1_IO30,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_USDHC2_DATA6,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_KPP_ROW00,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_ENET2_1588_EVENT3_OUT,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_FLEXIO3_FLEXIO14,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_14_GPIO1_IO30,pinconf);
            }break;
            
            case B31:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_FLEXSPIA_SS0_B,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_ACMP_OUT03,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_LPSPI3_SCK,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_SAI1_TX_SYNC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_CSI_DATA02,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_GPIO1_IO31,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_USDHC2_DATA7,0);
                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_KPP_COL00,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_ENET2_1588_EVENT3_IN,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_FLEXIO3_FLEXIO15,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_15_GPIO1_IO31,pinconf);
            }break;
            
            default: break;
        }
    }
    
    else if(C0<=pin && C31>=pin)//端口C
    {
        switch(pin)
        {
            case C0:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_LCD_CLK,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_QTIMER1_TIMER0,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_MQS_RIGHT,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_LPSPI4_PCS0,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_FLEXIO2_FLEXIO00,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_GPIO2_IO00,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_SEMC_CSX01,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_ENET2_MDC,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_00_GPIO2_IO00,pinconf);
            }break;
            
            case C1:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_LCD_ENABLE,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_QTIMER1_TIMER1,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_MQS_LEFT,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_LPSPI4_SDI,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_FLEXIO2_FLEXIO01,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_GPIO2_IO01,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_SEMC_CSX02,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_ENET2_MDIO,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_01_GPIO2_IO01,pinconf);
            }break;
            
            case C2:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_LCD_HSYNC,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_QTIMER1_TIMER2,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_FLEXCAN1_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_LPSPI4_SDO,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_FLEXIO2_FLEXIO02,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_GPIO2_IO02,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_SEMC_CSX03,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_ENET2_1588_EVENT0_OUT,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_02_GPIO2_IO02,pinconf);
            }break;
            
            case C3:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_LCD_VSYNC,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_QTIMER2_TIMER0,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_FLEXCAN1_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_LPSPI4_SCK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_FLEXIO2_FLEXIO03,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_GPIO2_IO03,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_WDOG2_RESET_B_DEB,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_ENET2_1588_EVENT0_IN,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_03_GPIO2_IO03,pinconf);
            }break;
            
            case C4:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_LCD_DATA00,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_QTIMER2_TIMER1,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_LPI2C2_SCL,1);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_ARM_TRACE0,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_FLEXIO2_FLEXIO04,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_GPIO2_IO04,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_SRC_BOOT_CFG00,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_ENET2_TDATA03,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_04_GPIO2_IO04,pinconf);
            }break;
            
            case C5:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_LCD_DATA01,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_QTIMER2_TIMER2,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_LPI2C2_SDA,1);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_ARM_TRACE1,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_FLEXIO2_FLEXIO05,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_GPIO2_IO05,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_SRC_BOOT_CFG01,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_ENET2_TDATA02,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_05_GPIO2_IO05,pinconf);
            }break;
            
            case C6:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_LCD_DATA02,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_QTIMER3_TIMER0,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_FLEXPWM2_PWMA00,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_ARM_TRACE2,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_FLEXIO2_FLEXIO06,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_GPIO2_IO06,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_SRC_BOOT_CFG02,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_ENET2_RX_CLK,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_06_GPIO2_IO06,pinconf);
            }break;
            
            case C7:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_LCD_DATA03,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_QTIMER3_TIMER1,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_FLEXPWM2_PWMB00,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_ARM_TRACE3,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_FLEXIO2_FLEXIO07,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_GPIO2_IO07,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_SRC_BOOT_CFG03,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_ENET2_TX_ER,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_07_GPIO2_IO07,pinconf);
            }break;
            
            case C8:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LCD_DATA04,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_QTIMER3_TIMER2,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_FLEXPWM2_PWMA01,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LPUART3_TX,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_FLEXIO2_FLEXIO08,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_GPIO2_IO08,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_SRC_BOOT_CFG04,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_ENET2_RDATA03,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_GPIO2_IO08,pinconf);
            }break;
            
            case C9:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LCD_DATA05,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_QTIMER4_TIMER0,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_FLEXPWM2_PWMB01,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LPUART3_RX,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_FLEXIO2_FLEXIO09,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_GPIO2_IO09,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_SRC_BOOT_CFG05,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_ENET2_RDATA02,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_GPIO2_IO09,pinconf);
            }break;
            
            case C10:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_LCD_DATA06,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_QTIMER4_TIMER1,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_FLEXPWM2_PWMA02,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_SAI1_TX_DATA03,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_FLEXIO2_FLEXIO10,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_GPIO2_IO10,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_SRC_BOOT_CFG06,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_ENET2_CRS,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_10_GPIO2_IO10,pinconf);
            }break;
            
            case C11:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_LCD_DATA07,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_QTIMER4_TIMER2,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_FLEXPWM2_PWMB02,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_SAI1_TX_DATA02,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_FLEXIO2_FLEXIO11,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_GPIO2_IO11,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_SRC_BOOT_CFG07,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_ENET2_COL,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_11_GPIO2_IO11,pinconf);
            }break;
            
            case C12:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_LCD_DATA08,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_XBAR1_INOUT10,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_ARM_TRACE_CLK,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_SAI1_TX_DATA01,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_FLEXIO2_FLEXIO12,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_GPIO2_IO12,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_SRC_BOOT_CFG08,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_ENET2_TDATA00,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_12_GPIO2_IO12,pinconf);
            }break;
            
            case C13:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_LCD_DATA09,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_XBAR1_INOUT11,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_ARM_TRACE_SWO,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_SAI1_MCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_FLEXIO2_FLEXIO13,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_GPIO2_IO13,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_SRC_BOOT_CFG09,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_ENET2_TDATA01,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_13_GPIO2_IO13,pinconf);
            }break;
            
            case C14:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_LCD_DATA10,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_XBAR1_INOUT12,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_ARM_TXEV,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_SAI1_RX_SYNC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_FLEXIO2_FLEXIO14,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_GPIO2_IO14,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_SRC_BOOT_CFG10,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_ENET2_TX_EN,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_14_GPIO2_IO14,pinconf);
            }break;
            
            case C15:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_LCD_DATA11,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_XBAR1_INOUT13,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_ARM_RXEV,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_SAI1_RX_BCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_FLEXIO2_FLEXIO15,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_GPIO2_IO15,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_SRC_BOOT_CFG11,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_ENET2_TX_CLK,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_ENET2_REF_CLK2,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_15_GPIO2_IO15,pinconf);
            }break;
            
            case C16:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_LCD_DATA12,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_XBAR1_INOUT14,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_LPUART4_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_SAI1_RX_DATA00,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_FLEXIO2_FLEXIO16,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_GPIO2_IO16,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_FLEXPWM1_PWMA03,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_ENET2_RX_ER,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_FLEXIO3_FLEXIO16,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_00_GPIO2_IO16,pinconf);
            }break;
            
            case C17:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_LCD_DATA13,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_XBAR1_INOUT15,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_LPUART4_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_SAI1_TX_DATA00,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_FLEXIO2_FLEXIO17,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_GPIO2_IO17,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_FLEXPWM1_PWMB03,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_ENET2_RDATA00,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_FLEXIO3_FLEXIO17,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_01_GPIO2_IO17,pinconf);
            }break;
            
            case C18:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_LCD_DATA14,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_XBAR1_INOUT16,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_LPSPI4_PCS2,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_SAI1_TX_BCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_FLEXIO2_FLEXIO18,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_GPIO2_IO18,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_FLEXPWM2_PWMA03,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_ENET2_RDATA01,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_FLEXIO3_FLEXIO18,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_02_GPIO2_IO18,pinconf);
            }break;
            
            case C19:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_LCD_DATA15,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_XBAR1_INOUT17,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_LPSPI4_PCS1,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_SAI1_TX_SYNC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_FLEXIO2_FLEXIO19,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_GPIO2_IO19,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_FLEXPWM2_PWMB03,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_ENET2_RX_EN,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_FLEXIO3_FLEXIO19,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_03_GPIO2_IO19,pinconf);
            }break;
            
            case C20:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_LCD_DATA16,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_LPSPI4_PCS0,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_CSI_DATA15,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_ENET_RX_DATA00,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_FLEXIO2_FLEXIO20,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_GPIO2_IO20,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_GPT1_CLK,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_FLEXIO3_FLEXIO20,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_04_GPIO2_IO20,pinconf);
            }break;
            
            case C21:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_LCD_DATA17,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_LPSPI4_SDI,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_CSI_DATA14,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_ENET_RX_DATA01,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_FLEXIO2_FLEXIO21,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_GPIO2_IO21,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_GPT1_CAPTURE1,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_FLEXIO3_FLEXIO21,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_05_GPIO2_IO21,pinconf);
            }break;
            
            case C22:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_LCD_DATA18,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_LPSPI4_SDO,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_CSI_DATA13,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_ENET_RX_EN,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_FLEXIO2_FLEXIO22,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPIO2_IO22,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPT1_CAPTURE2,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_FLEXIO3_FLEXIO22,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_GPIO2_IO22,pinconf);
            }break;
            
            case C23:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_LCD_DATA19,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_LPSPI4_SCK,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_CSI_DATA12,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_ENET_TX_DATA00,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_FLEXIO2_FLEXIO23,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_GPIO2_IO23,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_GPT1_COMPARE1,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_FLEXIO3_FLEXIO23,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_GPIO2_IO23,pinconf);
            }break;
            
            case C24:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_LCD_DATA20,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_QTIMER1_TIMER3,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_CSI_DATA11,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_ENET_TX_DATA01,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_FLEXIO2_FLEXIO24,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_GPIO2_IO24,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_FLEXCAN2_TX,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_GPT1_COMPARE2,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_FLEXIO3_FLEXIO24,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_08_GPIO2_IO24,pinconf);
            }break;
            
            case C25:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_LCD_DATA21,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_QTIMER2_TIMER3,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_CSI_DATA10,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_ENET_TX_EN,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_FLEXIO2_FLEXIO25,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_GPIO2_IO25,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_FLEXCAN2_RX,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_GPT1_COMPARE3,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_FLEXIO3_FLEXIO25,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_GPIO2_IO25,pinconf);
            }break;
            
            case C26:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_LCD_DATA22,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_QTIMER3_TIMER3,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_CSI_DATA00,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_ENET_TX_CLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_FLEXIO2_FLEXIO26,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_GPIO2_IO26,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_ENET_REF_CLK,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_FLEXIO3_FLEXIO26,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_10_GPIO2_IO26,pinconf);
            }break;
            
            case C27:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_LCD_DATA23,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_QTIMER4_TIMER3,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_CSI_DATA01,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_ENET_RX_ER,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_FLEXIO2_FLEXIO27,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_GPIO2_IO27,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_LPSPI4_PCS3,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_FLEXIO3_FLEXIO27,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_GPIO2_IO27,pinconf);
            }break;
            
            case C28:
            {
                //设置引脚复用
                if      (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_LPUART5_TX,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_CSI_PIXCLK,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_ENET_1588_EVENT0_IN,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_FLEXIO2_FLEXIO28,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_GPIO2_IO28,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_USDHC1_CD_B,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_FLEXIO3_FLEXIO28,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_12_GPIO2_IO28,pinconf);
            }break;
            
            case C29:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_WDOG1_B,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_LPUART5_RX,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_CSI_VSYNC,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_ENET_1588_EVENT0_OUT,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_FLEXIO2_FLEXIO29,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_GPIO2_IO29,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_USDHC1_WP,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_SEMC_DQS4,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_FLEXIO3_FLEXIO29,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_13_GPIO2_IO29,pinconf);
            }break;
            
            case C30:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_ENET_MDC,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_FLEXPWM4_PWMA02,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_CSI_HSYNC,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_XBAR1_IN02,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_FLEXIO2_FLEXIO30,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_GPIO2_IO30,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_USDHC1_VSELECT,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_ENET2_TDATA00,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_FLEXIO3_FLEXIO30,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_14_GPIO2_IO30,pinconf);
            }break;
            
            case C31:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_ENET_MDIO,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_FLEXPWM4_PWMA03,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_CSI_MCLK,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_XBAR1_IN03,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_FLEXIO2_FLEXIO31,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_GPIO2_IO31,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_USDHC1_RESET_B,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_ENET2_TDATA01,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_FLEXIO3_FLEXIO31,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_15_GPIO2_IO31,pinconf);
            }break;
            
            default: break;
        }
    }
    
    else if(D0<=pin && D31>=pin)//端口D
    {
        switch(pin)
        {
            case D0:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_USDHC2_DATA3,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_FLEXSPIB_DATA03,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_FLEXPWM1_PWMA03,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_SAI1_TX_DATA03,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_SAI3_RX_DATA,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,pinconf);
            }break;
            
            case D1:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_USDHC2_DATA2,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_FLEXSPIB_DATA02,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_FLEXPWM1_PWMB03,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_SAI1_TX_DATA02,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_GPIO3_IO01,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_SAI3_TX_DATA,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_GPIO3_IO01,pinconf);
            }break;
            
            case D2:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_USDHC2_DATA1,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_FLEXSPIB_DATA01,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_FLEXPWM2_PWMA03,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_SAI1_TX_DATA01,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_FLEXCAN1_TX,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_GPIO3_IO02,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_CCM_WAIT,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_SAI3_TX_SYNC,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_02_GPIO3_IO02,pinconf);
            }break;
            
            case D3:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_USDHC2_DATA0,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_FLEXSPIB_DATA00,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_FLEXPWM2_PWMB03,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_SAI1_MCLK,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_FLEXCAN1_RX,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_GPIO3_IO03,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_CCM_PMIC_READY,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_SAI3_TX_BCLK,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_03_GPIO3_IO03,pinconf);
            }break;
            
            case D4:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_USDHC2_CLK,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_FLEXSPIB_SCLK,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_LPI2C1_SCL,1);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_SAI1_RX_SYNC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_FLEXSPIA_SS1_B,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_CCM_STOP,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_SAI3_MCLK,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,pinconf);
            }break;
            
            //flash DQS引脚NXP官方建议不要使用该引脚
//            case D5:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_USDHC2_CMD,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_FLEXSPIA_DQS,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_LPI2C1_SDA,1);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_SAI1_RX_BCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_FLEXSPIB_SS0_B,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_GPIO3_IO05,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_SAI3_RX_SYNC,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_05_GPIO3_IO05,pinconf);
//            }break;
            
            //以下引脚核心板并未引出，这里屏蔽以减少代码大小
//            case D6:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_USDHC2_RESET_B,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_FLEXSPIA_SS0_B,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_LPUART7_CTS_B,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_SAI1_RX_DATA00,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_LPSPI2_PCS0,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_GPIO3_IO06,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_SAI3_RX_BCLK,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_06_GPIO3_IO06,pinconf);
//            }break;
//            
//            case D7:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_SEMC_CSX01,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_FLEXSPIA_SCLK,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_LPUART7_RTS_B,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_SAI1_TX_DATA00,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_LPSPI2_SCK,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_GPIO3_IO07,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_07_GPIO3_IO07,pinconf);
//            }break;
//            
//            case D8:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_USDHC2_DATA4,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_FLEXSPIA_DATA00,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_SAI1_TX_BCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_LPSPI2_SD0,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_GPIO3_IO08,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_SEMC_CSX02,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_08_GPIO3_IO08,pinconf);
//            }break;
//            
//            case D9:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_USDHC2_DATA5,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_FLEXSPIA_DATA01,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_SAI1_TX_SYNC,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_LPSPI2_SDI,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_GPIO3_IO09,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_09_GPIO3_IO09,pinconf);
//            }break;
//            
//            case D10:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_USDHC2_DATA6,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_FLEXSPIA_DATA02,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_LPUART2_RX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_LPI2C2_SDA,1);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_LPSPI2_PCS2,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_GPIO3_IO10,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_10_GPIO3_IO10,pinconf);
//            }break;
//            
//            case D11:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_USDHC2_DATA7,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_FLEXSPIA_DATA03,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_LPUART2_TX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_LPI2C2_SCL,1);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_LPSPI2_PCS3,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_GPIO3_IO11,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_11_GPIO3_IO11,pinconf);
//            }break;
            
            case D12:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_USDHC1_CMD,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_FLEXPWM1_PWMA00,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_LPI2C3_SCL,1);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_XBAR1_INOUT04,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_LPSPI1_SCK,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_GPIO3_IO12,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_FLEXSPIA_SS1_B,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_ENET2_TX_EN,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_SEMC_DQS4,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_GPIO3_IO12,pinconf);
            }break;
            
            case D13:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_USDHC1_CLK,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_FLEXPWM1_PWMB00,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_LPI2C3_SDA,1);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_XBAR1_INOUT05,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_LPSPI1_PCS0,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_GPIO3_IO13,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_FLEXSPIB_SS1_B,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_ENET2_TX_CLK,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_ENET2_REF_CLK2,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_GPIO3_IO13,pinconf);
            }break;
            
            case D14:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_FLEXPWM1_PWMA01,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_LPUART8_CTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_XBAR1_INOUT06,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_LPSPI1_SDO,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_GPIO3_IO14,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_ENET2_RX_ER,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_SEMC_CLK5,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_02_GPIO3_IO14,pinconf);
            }break;
            
            case D15:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_FLEXPWM1_PWMB01,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_LPUART8_RTS_B,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_XBAR1_INOUT07,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_LPSPI1_SDI,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_GPIO3_IO15,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_ENET2_RDATA00,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_SEMC_CLK6,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_03_GPIO3_IO15,pinconf);
            }break;
            
            case D16:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_FLEXPWM1_PWMA02,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_XBAR1_INOUT08,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_FLEXSPIB_SS0_B,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_GPIO3_IO16,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_CCM_CLKO1,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_ENET2_RDATA01,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_GPIO3_IO16,pinconf);
            }break;
            
            case D17:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_FLEXPWM1_PWMB02,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_XBAR1_INOUT09,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_FLEXSPIB_DQS,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_GPIO3_IO17,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_CCM_CLKO2,0);
                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_ENET2_RX_EN,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_GPIO3_IO17,pinconf);
            }break;
            
            //以下引脚核心板并未引出，这里屏蔽以减少代码大小
//            case D18:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_SEMC_DATA10,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_FLEXPWM3_PWMB01,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_LPUART7_RX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_CCM_PMIC_RDY,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_CSI_DATA21,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_GPIO3_IO18,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_ENET2_TX_EN,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_32_GPIO3_IO18,pinconf);
//            }break;
//            
//            case D19:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_SEMC_DATA11,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_FLEXPWM3_PWMA02,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_USDHC1_RESET_B,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_SAI3_RX_DATA,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_CSI_DATA20,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_GPIO3_IO19,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_ENET2_TX_CLK,0);
//                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_ENET2_REF_CLK2,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_33_GPIO3_IO19,pinconf);
//            }break;
//            
//            case D20:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_SEMC_DATA12,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_FLEXPWM3_PWMB02,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_USDHC1_VSELECT,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_SAI3_RX_SYNC,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_CSI_DATA19,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_GPIO3_IO20,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_34_ENET2_RX_ER,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_34_GPIO3_IO20,pinconf);
//            }break;
//            
//            case D21:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_SEMC_DATA13,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_XBAR1_INOUT18,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_GPT1_COMPARE1,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_SAI3_RX_BCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_CSI_DATA18,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_GPIO3_IO21,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_USDHC1_CD_B,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_35_ENET2_RDATA00,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_35_GPIO3_IO21,pinconf);
//            }break;
//            
//            case D22:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_SEMC_DATA14,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_XBAR1_IN22,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_GPT1_COMPARE2,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_SAI3_TX_DATA,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_CSI_DATA17,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_GPIO3_IO22,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_USDHC1_WP,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_ENET2_RDATA01,0);
//                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_FLEXCAN3_TX,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_36_GPIO3_IO22,pinconf);
//            }break;
//            
//            case D23:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_SEMC_DATA15,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_XBAR1_IN23,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_GPT1_COMPARE3,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_SAI3_MCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_CSI_DATA16,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_GPIO3_IO23,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_USDHC2_WP,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_ENET2_RX_EN,0);
//                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_FLEXCAN3_RX,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_37_GPIO3_IO23,pinconf);
//            }break;
//            
//            case D24:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_SEMC_DM01,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_FLEXPWM1_PWMA03,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_LPUART8_TX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_SAI3_TX_BCLK,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_CSI_FIELD,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_GPIO3_IO24,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_USDHC2_VSELECT,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_38_ENET2_MDC,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_38_GPIO3_IO24,pinconf);
//            }break;
//            
//            case D25:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_SEMC_DQS,0);
//                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_FLEXPWM1_PWMB03,0);
//                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_LPUART8_RX,0);
//                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_SAI3_TX_SYNC,0);
//                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_WDOG1_WDOG_B,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_GPIO3_IO25,0);
//                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_USDHC2_CD_B,0);
//                else if (ALT8 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_ENET2_MDIO,0);
//                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_39_SEMC_DQS4,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_39_GPIO3_IO25,pinconf);
//            }break;
            
            case D26:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_SEMC_RDY,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_GPT2_CAPTURE2,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_LPSPI1_PCS2,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_USB_OTG2_OC,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_ENET_MDC,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_GPIO3_IO26,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_USDHC2_RESET_B,0);
                else if (ALT9 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_SEMC_CLK5,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_GPIO3_IO26,pinconf);
            }break;
            
            case D27:
            {
                //设置引脚复用
                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_SEMC_CSX00,0);
                else if (ALT1 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_GPT2_CAPTURE1,0);
                else if (ALT2 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_LPSPI1_PCS3,0);
                else if (ALT3 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_USB_OTG2_PWR,0);
                else if (ALT4 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_ENET_MDIO,0);
                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_GPIO3_IO27,0);
                else if (ALT6 == alt)   IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_USDHC1_VSELECT,0);
                else                    assert(0);//复用错误 进入断言失败
                //配置引脚
                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_GPIO3_IO27,pinconf);
            }break;
            
//            case D28:
//            {
//                assert(0);//无此引脚
//                
//            }break;
//            
//            case D29:
//            {
//                assert(0);//无此引脚
//            }break;
//            
//            case D30:
//            {
//                assert(0);//无此引脚
//            }break;
//            
//            case D31:
//            {
//                assert(0);//无此引脚
//            }break;
            
            default: assert(0);break;//复用错误 进入断言失败
        }
    }

//    else if(E0<=pin && E31>=pin)//端口F
//    {
//        //端口E已经全部被SDRAM占用，因此这里不再编写E端口的引脚复用设置，如果有需要可以自行根据SDK进行实现
//    }
    
//    else if(F0<=pin && F31>=pin)//端口F
//    {
//        //核心板并未引出端口F因此，这里屏蔽以减少代码大小
//        switch(pin)
//        {
//            case F0:
//            {
//                //设置引脚复用
//                if      (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_GPIO5_IO00,0);
//                else if (ALT7 == alt)   IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_NMI_GLUE_NMI,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_SNVS_WAKEUP_GPIO5_IO00,pinconf);
//            }break;
//            
//            case F1:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_SNVS_PMIC_ON_REQ_SNVS_LP_PMIC_ON_REQ,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_SNVS_PMIC_ON_REQ_GPIO5_IO01,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_SNVS_PMIC_ON_REQ_GPIO5_IO01,pinconf);
//            }break;
//            
//            case F2:
//            {
//                //设置引脚复用
//                if      (ALT0 == alt)   IOMUXC_SetPinMux(IOMUXC_SNVS_PMIC_STBY_REQ_CCM_PMIC_VSTBY_REQ,0);
//                else if (ALT5 == alt)   IOMUXC_SetPinMux(IOMUXC_SNVS_PMIC_STBY_REQ_GPIO5_IO02,0);
//                else                    assert(0);//复用错误 进入断言失败
//                //配置引脚
//                if      (pinconf)       IOMUXC_SetPinConfig(IOMUXC_SNVS_PMIC_STBY_REQ_GPIO5_IO02,pinconf);
//            }break;
//            
//            default: assert(0);break;//复用错误 进入断言失败
//        }
//    }
}