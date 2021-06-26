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
 
#ifndef _zf_camera_h
#define _zf_camera_h

#include "common.h"
#include "fsl_flexio.h"
#include "fsl_dmamux.h"
#include "fsl_edma.h"




//此枚举定义不允许用户修改
typedef enum    //FLEXIO 引脚定义
{
    FLEXIO2_D00_C0,
    FLEXIO2_D01_C1,
    FLEXIO2_D02_C2,
    FLEXIO2_D03_C3,
    FLEXIO2_D04_C4,
    FLEXIO2_D05_C5,
    FLEXIO2_D06_C6,
    FLEXIO2_D07_C7,
    FLEXIO2_D08_C8,
    FLEXIO2_D09_C9,
    FLEXIO2_D10_C10,
    FLEXIO2_D11_C11,
    FLEXIO2_D12_C12,
    FLEXIO2_D13_C13,
    FLEXIO2_D14_C14,
    FLEXIO2_D15_C15,
    FLEXIO2_D16_C16,
    FLEXIO2_D17_C17,
    FLEXIO2_D18_C18,
    FLEXIO2_D19_C19,
    FLEXIO2_D20_C20,
    FLEXIO2_D21_C21,
    FLEXIO2_D22_C22,
    FLEXIO2_D23_C23,
    FLEXIO2_D24_C24,
    FLEXIO2_D25_C25,
    FLEXIO2_D26_C26,
    FLEXIO2_D27_C27,
    FLEXIO2_D28_C28,
    FLEXIO2_D29_C29,
    FLEXIO2_D30_C30,
    FLEXIO2_D31_C31,
}FLEXIO_PIN_enum;





void flexio_camera(FLEXIO_PIN_enum dat_pin_start, FLEXIO_PIN_enum pclk_pin, FLEXIO_PIN_enum href_pin, uint16 col, uint16 row);
void flexio_enable(uint8 enable);
void flexio_enable_rxdma(void);
void flexio_flag_clear(void);

void dma_mux_init(void);
void flexio_dma_init(uint8 *dest_addr, uint32 count, edma_callback callback);
void dma_restart(uint8 *dest_addr);


#endif