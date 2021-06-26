/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		camera
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#include "fsl_flexio_camera.h"
#include "zf_iomuxc.h"
#include "zf_camera.h"

#define FLEXIO_PIN_CONF         SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置FLEXIO引脚默认配置


#define DMA_CHN                 0u
#define DMA_MUX_SRC             kDmaRequestMuxFlexIO2Request2Request3



uint8 flexio_shift_count;
static FLEXIO_CAMERA_Type s_FlexioCameraDevice;


void flexio_iomuxc(FLEXIO_PIN_enum dat_pin_start, FLEXIO_PIN_enum pclk_pin, FLEXIO_PIN_enum href_pin)
{
    uint8 pin[32]={C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18,C19,C20,C21,C22,C23,C24,C25,C26,C27,C28,C29,C30,C31};
    
    if(24<dat_pin_start)                                        assert(0);  //数据引脚参数错误  起始引脚不得大于24
    if(pclk_pin>=dat_pin_start && pclk_pin<=(dat_pin_start+7))  assert(0);  //像素时钟引脚不应该在数据引脚范围内
    if(href_pin>=dat_pin_start && href_pin<=(dat_pin_start+7))  assert(0);  //行信号引脚不应该在数据引脚范围内
    if(href_pin == pclk_pin)                                    assert(0);  //行信号引脚不应该与像素时钟引脚一样
    
    iomuxc_pinconf((PIN_enum)pin[pclk_pin],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[href_pin],ALT4,FLEXIO_PIN_CONF);
    
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+0],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+1],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+2],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+3],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+4],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+5],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+6],ALT4,FLEXIO_PIN_CONF);
    iomuxc_pinconf((PIN_enum)pin[dat_pin_start+7],ALT4,FLEXIO_PIN_CONF);

}

static flexio_camera_config_t s_FlexioCameraConfig;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO初始化为CSI(摄像头)接口
//  @param      dat_pin_start   摄像头数据接口的起始位
//  @param      pclk_pin        像素时钟的引脚
//  @param      href_pin        行信号的引脚
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_camera(FLEXIO_PIN_enum dat_pin_start, FLEXIO_PIN_enum pclk_pin, FLEXIO_PIN_enum href_pin, uint16 col, uint16 row)
{
    flexio_iomuxc(dat_pin_start,pclk_pin,href_pin);
    
    if(col*row>=(376*240))  flexio_shift_count = 2;
    else                    flexio_shift_count = 1;
    
    s_FlexioCameraDevice.flexioBase = FLEXIO2;                  //设置基地址
    s_FlexioCameraDevice.datPinStartIdx = dat_pin_start;        //设置数据引脚起始位
    s_FlexioCameraDevice.pclkPinIdx = pclk_pin;                 //设置像素时钟引脚
    s_FlexioCameraDevice.hrefPinIdx = href_pin;                 //设置行信号引脚
    s_FlexioCameraDevice.shifterStartIdx = 4-flexio_shift_count;//设置环移器起始编号  由于1064的缓冲区只有四个因此这里写的是4-
    s_FlexioCameraDevice.shifterCount = flexio_shift_count;     //设置缓冲区数量
    s_FlexioCameraDevice.timerIdx = 3;                          //设置定时器编号
    
    CLOCK_EnableClock(kCLOCK_Flexio2);
    FLEXIO_Reset(FLEXIO2);
    FLEXIO_CAMERA_GetDefaultConfig(&s_FlexioCameraConfig);
    FLEXIO_CAMERA_Init(&s_FlexioCameraDevice, &s_FlexioCameraConfig);
    FLEXIO_CAMERA_ClearStatusFlags(&s_FlexioCameraDevice, kFLEXIO_CAMERA_RxDataRegFullFlag | kFLEXIO_CAMERA_RxErrorFlag);
    FLEXIO_CAMERA_Enable(&s_FlexioCameraDevice, true);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO 使能
//  @param      enable          1：使能FLEXIO   0：关闭FLEXIO
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_enable(uint8 enable)
{
    if(enable)
    {
        s_FlexioCameraDevice.flexioBase->CTRL |= FLEXIO_CTRL_FLEXEN_MASK;
    }
    else
    {
        s_FlexioCameraDevice.flexioBase->CTRL &= ~FLEXIO_CTRL_FLEXEN_MASK;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO RX启用DMA触发
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_enable_rxdma(void)
{
    FLEXIO_CAMERA_EnableRxDMA(&s_FlexioCameraDevice, true);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO 标志位清除
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_flag_clear(void)
{
    FLEXIO_CAMERA_ClearStatusFlags(&s_FlexioCameraDevice, kFLEXIO_CAMERA_RxDataRegFullFlag | kFLEXIO_CAMERA_RxErrorFlag);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMAMUX复用初始化
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void dma_mux_init(void)
{
    DMAMUX_Deinit(DMAMUX);
    DMAMUX_Init(DMAMUX);
    DMAMUX_SetSource(DMAMUX, DMA_CHN, DMA_MUX_SRC);
    DMAMUX_EnableChannel(DMAMUX, DMA_CHN);
}


edma_transfer_config_t transferConfig;
edma_config_t edma_config;
edma_handle_t g_EDMA_Handle;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA初始化
//  @param      dest_addr       目的地址
//  @param      count           DMA传输次数
//  @param      callback        DMA中断回调函数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_dma_init(uint8 *dest_addr, uint32 count, edma_callback callback)
{
    edma_modulo_t s_addr_modulo;
    
    EDMA_GetDefaultConfig(&edma_config);
    EDMA_Deinit(DMA0);
    EDMA_Init(DMA0, &edma_config);
    DMA0->CERR = DMA_CERR_CERR_MASK | DMA_CERR_CAEI_MASK;
    
    EDMA_CreateHandle(&g_EDMA_Handle, DMA0, DMA_CHN);
    EDMA_SetCallback(&g_EDMA_Handle, callback, NULL);
    EDMA_PrepareTransfer(&transferConfig, 
    (void *)FLEXIO_CAMERA_GetRxBufferAddress(&s_FlexioCameraDevice), 
    4,
    (void *)(dest_addr), 
    4,
    4*flexio_shift_count,
    count,
    kEDMA_MemoryToMemory);
    
    
    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);
    
    switch(4*flexio_shift_count)
    {
        case 4:     s_addr_modulo = kEDMA_Modulo4bytes;break;
        case 8:     s_addr_modulo = kEDMA_Modulo8bytes;break;
        case 16:    s_addr_modulo = kEDMA_Modulo16bytes;break;
        case 32:    s_addr_modulo = kEDMA_Modulo32bytes;break;
        default:assert(0);  //参数有误
    }
    
    
    EDMA_SetModulo(DMA0,DMA_CHN,s_addr_modulo,kEDMA_ModuloDisable);
    EDMA_StartTransfer(&g_EDMA_Handle);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA开启
//  @param      dest_addr       目的地址
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void dma_restart(uint8 *dest_addr)
{
    DMA0->TCD[DMA_CHN].DADDR = (uint32_t)(dest_addr);
    flexio_flag_clear();
    DMA0->SERQ = DMA_SERQ_SERQ(DMA_CHN);
}

