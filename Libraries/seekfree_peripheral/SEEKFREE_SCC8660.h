/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		凌瞳摄像头(SCC8660) RT FLEXIO接口
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598 & QQ2380006440)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.32.4 or MDK 5.24 或更高
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-09-04
 * @note		
					接线定义：
					------------------------------------ 
						模块管脚            单片机管脚
						SDA(摄像头的RX)     查看SEEKFREE_SCC8660.h文件中的SCC8660_COF_UART_TX宏定义
						SCL(摄像头的TX)     查看SEEKFREE_SCC8660.h文件中的SCC8660_COF_UART_RX宏定义
                        场中断(VSY)         查看SEEKFREE_SCC8660.h文件中的SCC8660_VSYNC_PIN宏定义
						行中断(HREF)		查看SEEKFREE_SCC8660.h文件中的SCC8660_HREF_PIN宏定义
						像素中断(PCLK)      查看SEEKFREE_SCC8660.h文件中的SCC8660_PCLK_PIN宏定义
						数据口(D0-D7)		查看SEEKFREE_SCC8660.h文件中的SCC8660_DATA_PIN宏定义
					------------------------------------ 
	
					默认分辨率               160*120
					默认FPS                  25帧
 ********************************************************************************************************************/



#ifndef _SEEKFREE_SCC8660_h
#define _SEEKFREE_SCC8660_h


#include "common.h"
#include "fsl_edma.h"
#include "zf_uart.h"



//使用flexio采集时主要推荐两个分辨率一个是160*120 另一个是320*240
#define SCC8660_PIC_W           160		            //实际图像分辨率宽度	可选参数为：160 320。
#define SCC8660_PIC_H           120		            //实际图像分辨率高度	可选参数为：120 240。

#define SCC8660_W		        SCC8660_PIC_W*2		//此参数为图像数据存储宽度 请勿修改
#define SCC8660_H		        SCC8660_PIC_H       //此参数为图像数据存储高度 请勿修改

//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define SCC8660_COF_UART        USART_4             //配置摄像头所使用到的串口     
#define SCC8660_COF_UART_TX     UART4_TX_C16
#define SCC8660_COF_UART_RX     UART4_RX_C17

#define SCC8660_VSYNC_PIN       C7                  //场中断引脚
#define SCC8660_VSYNC_IRQN      GPIO2_Combined_0_15_IRQn   //中断号


#define SCC8660_DATA_PIN        FLEXIO2_D08_C8      //定义D0数据引脚  假设D0定义为FLEXIO2_D08_C8 那么D1所使用的引脚则为FLEXIO2_D09_C9，依次类推
#define SCC8660_PCLK_PIN        FLEXIO2_D05_C5      //定义像素时钟引脚
#define SCC8660_HREF_PIN        FLEXIO2_D06_C6      //定义行信号引脚



extern uint16 scc8660_flexio1_image[SCC8660_PIC_H][SCC8660_PIC_W];
extern uint16 scc8660_flexio2_image[SCC8660_PIC_H][SCC8660_PIC_W];
extern uint16 (*scc8660_image)[SCC8660_PIC_W];
extern uint8  scc8660_finish_flag;                  //一场图像采集完成标志位



void scc8660_init(void);
void scc8660_vsync(void);
void scc8660_dma(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);


#endif
