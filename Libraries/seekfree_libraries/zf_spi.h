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
 
#ifndef _zf_spi_h
#define _zf_spi_h


#include "common.h"
#include "fsl_lpspi.h"



//此枚举定义不允许用户修改
typedef enum
{            
    SPI1_SCK_D12  = 1*14+0*2, SPI1_SCK_E27,
    SPI1_MOSI_D14 = 1*14+1*2, SPI1_MOSI_E28,
    SPI1_MISO_D15 = 1*14+2*2, SPI1_MISO_E29,
    SPI1_CS0_D13  = 1*14+3*2, SPI1_CS0_E30,
    SPI1_CS1_E31  = 1*14+4*2,
    SPI1_CS2_D26  = 1*14+5*2,
    SPI1_CS3_D27  = 1*14+6*2,

    SPI2_SCK_D7   = 2*14+0*2, SPI2_SCK_E0,  
    SPI2_MOSI_D8  = 2*14+1*2, SPI2_MOSI_E2, 
    SPI2_MISO_D9  = 2*14+2*2, SPI2_MISO_E3, 
    SPI2_CS0_D6   = 2*14+3*2, SPI2_CS0_E1, 
    SPI2_CS1_E14  = 2*14+4*2,
    SPI2_CS2_D10  = 2*14+5*2,
    SPI2_CS3_D11  = 2*14+6*2,

    SPI3_SCK_B0   = 3*14+0*2, SPI3_SCK_B31, 
    SPI3_MOSI_B1  = 3*14+1*2, SPI3_MOSI_B30,
    SPI3_MISO_B2  = 3*14+2*2, SPI3_MISO_B29,
    SPI3_CS0_B3   = 3*14+3*2, SPI3_CS0_B28,
    SPI3_CS1_B4   = 3*14+4*2,
    SPI3_CS2_B5   = 3*14+5*2,
    SPI3_CS3_B6   = 3*14+6*2,

    SPI4_SCK_C3   = 4*14+0*2, SPI4_SCK_C23 ,
    SPI4_MOSI_C2  = 4*14+1*2, SPI4_MOSI_C22,
    SPI4_MISO_C1  = 4*14+2*2, SPI4_MISO_C21,
    SPI4_CS0_C0   = 4*14+3*2, SPI4_CS0_C20 ,
    SPI4_CS1_C19  = 4*14+4*2,
    SPI4_CS2_C18  = 4*14+5*2,
    SPI4_CS3_C27  = 4*14+6*2,
                           
    SPI_CS_NOT_USE,

}SPI_PIN_enum;

//此枚举定义不允许用户修改
typedef enum //枚举串口号
{
    SPI_0,//RT1064没有SPI0 这里仅用于占位
    SPI_1,
    SPI_2,
    SPI_3,
    SPI_4,
}SPIN_enum;

void spi_init(SPIN_enum spi_n, SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, SPI_PIN_enum cs_pin, uint8 mode, uint32 baud);
void spi_mosi(SPIN_enum spi_n, SPI_PIN_enum cs_pin, uint8 *modata, uint8 *midata, uint32 len, uint8 continuous);

#endif