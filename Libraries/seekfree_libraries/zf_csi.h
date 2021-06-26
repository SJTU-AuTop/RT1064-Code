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

#ifndef _zf_csi_h
#define _zf_csi_h

#include "common.h"
#include "fsl_csi.h"

extern uint32 fullCameraBufferAddr;    //采集完成的缓冲区地址    用户无需关心
extern csi_handle_t csi_handle;        //csi事务结构体

//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
    CSI_VSYNC_B14,
    CSI_VSYNC_B22,
    CSI_VSYNC_C29,
}VSYNCPIN_enum;

//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
    CSI_PIXCLK_B20,
    CSI_PIXCLK_C28,
}PIXCLKPIN_enum;


void csi_init(uint16 width, uint16 height, csi_handle_t *handle, csi_transfer_callback_t callback, VSYNCPIN_enum vsync, PIXCLKPIN_enum pixclk);
void csi_add_empty_buffer(csi_handle_t *handle, uint8 *buff);
uint8 csi_get_full_buffer(csi_handle_t *handle, uint32 *buffaddr);
void csi_start(csi_handle_t *handle);
void csi_stop(csi_handle_t *handle);







#endif