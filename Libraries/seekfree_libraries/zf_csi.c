/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		CSI
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#include "zf_iomuxc.h"
#include "zf_csi.h"

#define CSI_PIN_CONF        SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置CSI引脚默认配置   

csi_handle_t csi_handle;        //csi事务结构体
uint32 fullCameraBufferAddr;    //采集完成的缓冲区地址    用户无需关心

void csi_iomuxc(VSYNCPIN_enum vsync, PIXCLKPIN_enum pixclk)
{
    //数据端口引脚复用设置
    iomuxc_pinconf(B24,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B25,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B26,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B27,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B28,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B29,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B30,ALT4,CSI_PIN_CONF);
    iomuxc_pinconf(B31,ALT4,CSI_PIN_CONF);
    
    if      (CSI_VSYNC_B14 == vsync)    iomuxc_pinconf(B14,ALT4,CSI_PIN_CONF);
    else if (CSI_VSYNC_B22 == vsync)    iomuxc_pinconf(B22,ALT4,CSI_PIN_CONF);
    else if (CSI_VSYNC_C29 == vsync)    iomuxc_pinconf(C29,ALT2,CSI_PIN_CONF);
    
    if      (CSI_PIXCLK_B20 == pixclk)  iomuxc_pinconf(B20,ALT4,CSI_PIN_CONF);
    else if (CSI_PIXCLK_C28 == pixclk)  iomuxc_pinconf(C28,ALT2,CSI_PIN_CONF);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI初始化
//  @param      width       图像的列
//  @param      height      图像的行
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @param      callback    中断的时候的回调函数
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_init(uint16 width, uint16 height, csi_handle_t *handle, csi_transfer_callback_t callback, VSYNCPIN_enum vsync, PIXCLKPIN_enum pixclk)
{
    uint16 i;
    uint32 pixel_num;
    uint16 temp_width;
    uint16 temp_height=0;
    csi_config_t csi_config;

    csi_iomuxc(vsync,pixclk);
    
    //CSI 采集初始化
    CLOCK_SetMux(kCLOCK_CsiMux, 8);
    CLOCK_SetDiv(kCLOCK_CsiDiv, 0);
        
    //摄像头采集初始化
    DisableGlobalIRQ();
    pixel_num = width*height;
    if(pixel_num%8) assert(0);//像素点不是8的倍数 无法采集
    if(width%8)
    {
        temp_width = width - width%8;//储存临时宽度
        i=1;
        while(pixel_num>(temp_width+(i*8)))
        {
            if(!(pixel_num%((temp_width+(i*8))))) 
            {
                temp_width += (i*8);//储存临时宽度
                temp_height = pixel_num/temp_width;
                break;
            }
            i++;
        }
        if(!temp_height)
        {
            //如果没有找到则从临时宽度往下找
            i=1;
            while((temp_width-(i*8)))
            {
                if(!(pixel_num%((temp_width-(i*8))))) 
                {
                    temp_width -= (i*8);//储存临时宽度
                    temp_height = pixel_num/temp_width;
                    break;
                }
                i++;
            }
        }
        if(!temp_height)
        {
            //如果还是没有找到
            temp_width = pixel_num;
            temp_height = 1;
        }
    }
    else
    {
        temp_width = width;
        temp_height = height;
    }
    
    CSI_GetDefaultConfig(&csi_config);
    csi_config.width = temp_width;
    csi_config.height = temp_height;
    csi_config.polarityFlags = kCSI_DataLatchOnRisingEdge;
    csi_config.bytesPerPixel = 1U;
    csi_config.linePitch_Bytes = temp_width;
    csi_config.workMode = kCSI_NonGatedClockMode;
    csi_config.dataBus = kCSI_DataBus8Bit;
    csi_config.useExtVsync = true;
    CSI_Init(CSI, &csi_config);
    CSI_TransferCreateHandle(CSI,handle,callback,NULL);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI添加空缓冲区地址
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @param      *buff       缓冲区的首地址
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_add_empty_buffer(csi_handle_t *handle, uint8 *buff)
{
    CSI_TransferSubmitEmptyBuffer(CSI,handle,(uint32_t)buff);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI获取采集完成的缓冲区地址
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @param      buffaddr    获取到的地址
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
uint8 csi_get_full_buffer(csi_handle_t *handle, uint32 *buffaddr)
{
    if(kStatus_Success == CSI_TransferGetFullBuffer(CSI,handle,(uint32_t *)buffaddr))
    {
        return 1;//获取到采集完成的BUFFER
    }
    return 0;    //未采集完成
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI启动
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_start(csi_handle_t *handle)
{
    CSI_TransferStart(CSI,handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI停止
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_stop(csi_handle_t *handle)
{
    CSI_TransferStop(CSI,handle);
}



