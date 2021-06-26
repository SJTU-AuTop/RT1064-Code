/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		总钻风 RT CSI接口
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-02-18
 * @note		
					接线定义：
					------------------------------------ 
                        模块管脚            单片机管脚
						SDA(51的RX)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_COF_UART_TX宏定义
						SCL(51的TX)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_COF_UART_RX宏定义
						场中断(VSY)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_VSYNC_PIN宏定义
						行中断(HREF)	    不需要使用
						像素中断(PCLK)      查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_PCLK_PIN宏定义
						数据口(D0-D7)		B31-B24 B31对应摄像头接口D0
					------------------------------------ 
	
					默认分辨率是            188*120
					默认FPS                 50帧
 ********************************************************************************************************************/



#ifndef _SEEKFREE_MT9V03X_CSI_h
#define _SEEKFREE_MT9V03X_CSI_h


#include "common.h"
#include "zf_uart.h"

//配置摄像头参数
#define MT9V03X_CSI_W               376             //图像宽度  范围1-752      RT105X RT106X 采集时列宽度必须为4的倍数
#define MT9V03X_CSI_H               240             //图像高度	范围1-480



//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define MT9V03X_CSI_COF_UART        USART_5         //配置摄像头所使用到的串口     
#define MT9V03X_CSI_COF_UART_TX     UART5_TX_C28
#define MT9V03X_CSI_COF_UART_RX     UART5_RX_C29


#define MT9V03X_CSI_PCLK_PIN        CSI_PIXCLK_B20  //定义像素时钟引脚
#define MT9V03X_CSI_VSYNC_PIN       CSI_VSYNC_B22   //定义场信号引脚
//对于数据引脚这里不提供设置到其他引脚的定义
//由于第二组引脚由部分没有引出所以程序直接固定使用B31-B24连接摄像头的数据引脚

                            

extern uint8 mt9v03x_csi_finish_flag;               //一场图像采集完成标志位
extern uint8 (*mt9v03x_csi_image)[MT9V03X_CSI_W];          //图像数据

void mt9v03x_csi_init(void);
void csi_seekfree_sendimg_03x(UARTN_enum uartn, uint8 *image, uint16 width, uint16 height);










#endif
