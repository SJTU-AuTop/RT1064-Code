/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		spi
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 

#include "zf_iomuxc.h"
#include "zf_spi.h"


#define LPSPI_PIN_CONF  SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置SPI引脚默认配置
#define LPSPI_CLK_DIV   3
#define LPSPI_CLK_SRC   2



LPSPI_Type * SPIN[] = LPSPI_BASE_PTRS;

void spi_iomuxc(SPIN_enum spi_n, SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, SPI_PIN_enum cs_pin)
{
    switch(spi_n)
    {
        case SPI_1:
        {
            if      (SPI1_SCK_D12  == sck_pin)  iomuxc_pinconf(D12,ALT4,LPSPI_PIN_CONF);
            else if (SPI1_SCK_E27  == sck_pin)  iomuxc_pinconf(E27,ALT3,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI1_MOSI_D14 == mosi_pin) iomuxc_pinconf(D14,ALT4,LPSPI_PIN_CONF);
            else if (SPI1_MOSI_E28 == mosi_pin) iomuxc_pinconf(E28,ALT3,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
                                                               
            if      (SPI1_MISO_D15 == miso_pin) iomuxc_pinconf(D15,ALT4,LPSPI_PIN_CONF);
            else if (SPI1_MISO_E29 == miso_pin) iomuxc_pinconf(E29,ALT3,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI1_CS0_D13  == cs_pin)   iomuxc_pinconf(D13,ALT4,LPSPI_PIN_CONF);
            else if (SPI1_CS0_E30  == cs_pin)   iomuxc_pinconf(E30,ALT3,LPSPI_PIN_CONF);
            else if (SPI1_CS1_E31  == cs_pin)   iomuxc_pinconf(E31,ALT3,LPSPI_PIN_CONF);
            else if (SPI1_CS2_D26  == cs_pin)   iomuxc_pinconf(D26,ALT2,LPSPI_PIN_CONF);
            else if (SPI1_CS3_D27  == cs_pin)   iomuxc_pinconf(D27,ALT2,LPSPI_PIN_CONF);
            else if (SPI_CS_NOT_USE  == cs_pin)   ;//不使用片选引脚
            else                                assert(0);//引脚错误 进入断言失败
        }break;
        
        case SPI_2:
        {
            if      (SPI2_SCK_D7   == sck_pin)  iomuxc_pinconf(D7 ,ALT4,LPSPI_PIN_CONF);
            else if (SPI2_SCK_E0   == sck_pin)  iomuxc_pinconf(E0 ,ALT2,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI2_MOSI_D8  == mosi_pin) iomuxc_pinconf(D8 ,ALT4,LPSPI_PIN_CONF);
            else if (SPI2_MOSI_E2  == mosi_pin) iomuxc_pinconf(E2 ,ALT2,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
                                                               
            if      (SPI2_MISO_D9  == miso_pin) iomuxc_pinconf(D9 ,ALT4,LPSPI_PIN_CONF);
            else if (SPI2_MISO_E3  == miso_pin) iomuxc_pinconf(E3 ,ALT2,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI2_CS0_D6   == cs_pin)   iomuxc_pinconf(D6 ,ALT4,LPSPI_PIN_CONF);
            else if (SPI2_CS0_E1   == cs_pin)   iomuxc_pinconf(E1 ,ALT2,LPSPI_PIN_CONF);
            else if (SPI2_CS1_E14  == cs_pin)   iomuxc_pinconf(E14,ALT4,LPSPI_PIN_CONF);
            else if (SPI2_CS2_D10  == cs_pin)   iomuxc_pinconf(D10,ALT4,LPSPI_PIN_CONF);
            else if (SPI2_CS3_D11  == cs_pin)   iomuxc_pinconf(D11,ALT4,LPSPI_PIN_CONF);
            else if (SPI_CS_NOT_USE  == cs_pin)   ;//不使用片选引脚
            else                                assert(0);//引脚错误 进入断言失败
        }break;
        
        case SPI_3:
        {
            if      (SPI3_SCK_B0   == sck_pin)  iomuxc_pinconf(B0 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI3_SCK_B31  == sck_pin)  iomuxc_pinconf(B31,ALT2,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI3_MOSI_B1  == mosi_pin) iomuxc_pinconf(B1 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI3_MOSI_B30 == mosi_pin) iomuxc_pinconf(B30,ALT2,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
                                                               
            if      (SPI3_MISO_B2  == miso_pin) iomuxc_pinconf(B2 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI3_MISO_B29 == miso_pin) iomuxc_pinconf(B29,ALT2,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI3_CS0_B3   == cs_pin)   iomuxc_pinconf(B3 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI3_CS0_B28  == cs_pin)   iomuxc_pinconf(B28,ALT2,LPSPI_PIN_CONF);
            else if (SPI3_CS1_B4   == cs_pin)   iomuxc_pinconf(B4 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI3_CS2_B5   == cs_pin)   iomuxc_pinconf(B5 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI3_CS3_B6   == cs_pin)   iomuxc_pinconf(B6 ,ALT7,LPSPI_PIN_CONF);
            else if (SPI_CS_NOT_USE  == cs_pin)   ;//不使用片选引脚
            else                                assert(0);//引脚错误 进入断言失败
        }break;
        
        case SPI_4:
        {
            if      (SPI4_SCK_C3   == sck_pin)  iomuxc_pinconf(C3 ,ALT3,LPSPI_PIN_CONF);
            else if (SPI4_SCK_C23  == sck_pin)  iomuxc_pinconf(C23,ALT1,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI4_MOSI_C2  == mosi_pin) iomuxc_pinconf(C2 ,ALT3,LPSPI_PIN_CONF);
            else if (SPI4_MOSI_C22 == mosi_pin) iomuxc_pinconf(C22,ALT1,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
                                                               
            if      (SPI4_MISO_C1  == miso_pin) iomuxc_pinconf(C1 ,ALT3,LPSPI_PIN_CONF);
            else if (SPI4_MISO_C21 == miso_pin) iomuxc_pinconf(C21,ALT1,LPSPI_PIN_CONF);
            else                                assert(0);//引脚错误 进入断言失败
            
            if      (SPI4_CS0_C0   == cs_pin)   iomuxc_pinconf(C0 ,ALT3,LPSPI_PIN_CONF);
            else if (SPI4_CS0_C20  == cs_pin)   iomuxc_pinconf(C20,ALT1,LPSPI_PIN_CONF);
            else if (SPI4_CS1_C19  == cs_pin)   iomuxc_pinconf(C19,ALT2,LPSPI_PIN_CONF);
            else if (SPI4_CS2_C18  == cs_pin)   iomuxc_pinconf(C18,ALT2,LPSPI_PIN_CONF);
            else if (SPI4_CS3_C27  == cs_pin)   iomuxc_pinconf(C27,ALT6,LPSPI_PIN_CONF);
            else if (SPI_CS_NOT_USE  == cs_pin)   ;//不使用片选引脚
            else                                assert(0);//引脚错误 进入断言失败
        }break;
        
        default:assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI初始化
//  @param      spi_n           选择SPI模块(SPI_1-SPI_4)
//  @param      cs_pin          选择SPI片选引脚
//  @param      sck_pin         选择SPI时钟引脚
//  @param      mosi_pin        选择SPI MOSI引脚
//  @param      miso_pin        选择SPI MISO引脚
//  @param      mode            SPI模式 0：CPOL=0 CPHA=0    1：CPOL=0 CPHA=1   2：CPOL=1 CPHA=0   3：CPOL=1 CPHA=1 //具体细节可自行百度
//  @param      baud            设置SPI的波特率
//  @return     void
//  Sample usage:               spi_init(SPI_1, SPI1_SCK_D12, SPI1_MOSI_D14, SPI1_MISO_D15, SPI1_CS0_D13, 0, 1*1000*1000);//硬件SPI初始化  模式0 波特率为1Mhz   
//-------------------------------------------------------------------------------------------------------------------
void spi_init(SPIN_enum spi_n, SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, SPI_PIN_enum cs_pin, uint8 mode, uint32 baud)
{
    lpspi_master_config_t masterConfig;
    uint32 src_clock;
    
    spi_iomuxc(spi_n, sck_pin, mosi_pin, miso_pin, cs_pin);

    CLOCK_SetMux(kCLOCK_LpspiMux, LPSPI_CLK_SRC);    //选择PLL2作为LPSPI时钟源
    CLOCK_SetDiv(kCLOCK_LpspiDiv, LPSPI_CLK_DIV);
    
    LPSPI_MasterGetDefaultConfig(&masterConfig);

    masterConfig.baudRate = baud;
    masterConfig.bitsPerFrame = 8;
    masterConfig.whichPcs = (lpspi_which_pcs_t)(cs_pin%14/2-3);
    
    switch(mode)
    {
        case 0:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh; 
            masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge; 
        }break;
        
        case 1:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh; 
            masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge; 
        }break;
        
        case 2:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveLow; 
            masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge; 
        }break;
        
        case 3:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveLow; 
            masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge; 
        }break;
    }

    masterConfig.pcsToSckDelayInNanoSec = 1000000000 / masterConfig.baudRate;
    masterConfig.lastSckToPcsDelayInNanoSec = 1000000000 / masterConfig.baudRate;
    masterConfig.betweenTransferDelayInNanoSec = 1000000000 / masterConfig.baudRate;
    src_clock = (CLOCK_GetFreq(kCLOCK_SysPllClk) / (LPSPI_CLK_DIV + 1U));
    
    LPSPI_MasterInit(SPIN[spi_n], &masterConfig, src_clock);//第一次初始化便于打开时钟
    LPSPI_Reset(SPIN[spi_n]);                               //复位外设
    LPSPI_MasterInit(SPIN[spi_n], &masterConfig, src_clock);//重新初始化设置正确的参数
    
    LPSPI_Enable(SPIN[spi_n], false);
    SPIN[spi_n]->CFGR1 &= (~LPSPI_CFGR1_NOSTALL_MASK);
    LPSPI_Enable(SPIN[spi_n], true);

    LPSPI_FlushFifo(SPIN[spi_n], true, true);                       //刷新FIFO
    LPSPI_ClearStatusFlags(SPIN[spi_n], kLPSPI_AllStatusFlag);      //清除状态标志
    LPSPI_DisableInterrupts(SPIN[spi_n], kLPSPI_AllInterruptEnable);//关闭中断
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI发送接收函数
//  @param      spi_n           选择SPI模块   (SPI_1-SPI_4)
//  @param      cs_pin          选择SPI片选引脚
//  @param      modata          发送的数据缓冲区地址
//  @param      midata          发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
//  @param      len             发送的字节数
//  @param      continuous      本次通信是CS是否持续保持有效状态 1:持续保持  0:每传输完一个字节关闭CS(一般设置为1 即可)
//  @return     void				
//  @since      v2.0
//  Sample usage:       		spi_mosi(SPI_1,SPI1_CS0_D13,buf,buf,1,1);    //发送buff的内容，并接收到buf里，长度为1字节 通信期间CS持续拉低
//-------------------------------------------------------------------------------------------------------------------
void spi_mosi(SPIN_enum spi_n, SPI_PIN_enum cs_pin, uint8 *modata, uint8 *midata, uint32 len, uint8 continuous)
{
    lpspi_transfer_t transfer;

    assert(0 != len);               //断言字节数不为0
    
    if(continuous)  transfer.configFlags = ((cs_pin%14/2-3)<<LPSPI_MASTER_PCS_SHIFT) | kLPSPI_MasterPcsContinuous;
    else            transfer.configFlags = ((cs_pin%14/2-3)<<LPSPI_MASTER_PCS_SHIFT);
    transfer.txData = modata;
    transfer.rxData = midata;
    transfer.dataSize = len;
    LPSPI_MasterTransferBlocking(SPIN[spi_n], &transfer);
}



