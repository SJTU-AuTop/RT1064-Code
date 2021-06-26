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


#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_csi.h"
#include "zf_systick.h"
#include "zf_pit.h"
#include "zf_camera.h"
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_csi.h"
#include "fsl_cache.h"
#include "seekfree_iic.h"
#include "SEEKFREE_SCC8660_CSI.h"
#include "SEEKFREE_SCC8660.h"


//定义图像缓冲区  如果用户需要访问图像数据 最好通过scc8660_image来访问数据，最好不要直接访问缓冲区
//AT_DTCM_SECTION_ALIGN(uint16 scc8660_flexio1_image[SCC8660_PIC_H][SCC8660_PIC_W],64);
//AT_DTCM_SECTION_ALIGN(uint16 scc8660_flexio2_image[SCC8660_PIC_H][SCC8660_PIC_W],64);
AT_OCRAM_SECTION_ALIGN(uint16 scc8660_flexio1_image[SCC8660_PIC_H][SCC8660_PIC_W],64);
AT_OCRAM_SECTION_ALIGN(uint16 scc8660_flexio2_image[SCC8660_PIC_H][SCC8660_PIC_W],64);

uint16 (*flexio_color_camera_buffer_addr1)[SCC8660_PIC_W];//摄像头数组地址
uint16 (*flexio_color_camera_buffer_addr2)[SCC8660_PIC_W];//摄像头数组地址

//用户访问图像数据直接访问这个指针变量就可以
//访问方式非常简单，可以直接使用下标的方式访问
//例如访问第10行 50列的点，scc8660_image[10][50]就可以了
uint16 (*scc8660_image)[SCC8660_PIC_W];


//需要配置到摄像头的数据
uint16 SCC8660_CFG[SCC8660_CONFIG_FINISH][2]=
{
    {SCC8660_AUTO_EXP,          0},                     //自动曝光     默认：0     可选参数为：0 1。      0：手动曝光  1：自动曝光
    {SCC8660_BRIGHT,            800},                   //亮度设置     手动曝光默认：800	手动曝光时：参数范围0-65535   自动曝光推荐值：100 自动曝光时参数设置范围0-255
														//需要注意SCC8660_BRIGHT的参数固定时，不同的SCC8660_PCLK_DIV参数会影响图像的亮度。
														//假设SCC8660_BRIGHT的参数为800，SCC8660_PCLK_DIV的参数为0时 和 SCC8660_PCLK_DIV的参数为2时 
														//参数为2的时候图像明显要比为0的时候亮，在使用双摄的时候感觉两个摄像头亮度不一致时需要注意这个问题。
														
    {SCC8660_FPS,               50},                    //图像帧率     默认：50    可选参数为：60 50 30 25。 实际帧率还需要看SCC8660_PCLK_DIV参数的设置
    {SCC8660_SET_COL,           SCC8660_PIC_W},         //图像列数     默认：160   请在.h的宏定义处修改
    {SCC8660_SET_ROW,           SCC8660_PIC_H},         //图像行数     默认：120   请在.h的宏定义处修改
    {SCC8660_PCLK_DIV,          2},                     //PCLK分频系数 默认：0     可选参数为：0:1/1 1:2/3 2:1/2 3:1/3 4:1/4 5:1/8。  
                                                       //分频系数越大，PCLK频率越低，降低PCLK可以减轻DVP接口的干扰，但降低PCLK频率则会影响帧率。若无特殊需求请保持默认。
                                                       //例如设置FPS为50帧，但是pclk分频系数选择的为5，则摄像头输出的帧率为50*（1/8）=6.25帧
                                                       //其他参数不变的情况下，SCC8660_PCLK_DIV参数越大图像会越亮
													   //FLEXIO不能接受过大的频率，因此这里最好设置为2或者以上
													   
    
    {SCC8660_PCLK_MODE,         0},                     //PCLK模式     默认：0     可选参数为：0 1。        0：不输出消隐信号，1：输出消隐信号。(通常都设置为0，如果使用STM32的DCMI接口采集需要设置为1)
    {SCC8660_COLOR_MODE,        0},                     //图像色彩模式 默认：0     可选参数为：0 1。        0：正常彩色模式  1：鲜艳模式（色彩饱和度提高）
    {SCC8660_DATA_FORMAT,       0},                     //输出数据格式 默认：0	   可选参数为：0 1 2 3。    0:RGB565 1:RGB565(字节交换) 2:YUV422(YUYV) 3:YUV422(UYVY)
    {SCC8660_MANUAL_WB,         0},                     //手动白平衡   默认：0     可选参数为：0 0x65-0xa0。0:关闭手动白平衡，启用自动白平衡    其他：手动白平衡 手动白平衡时 参数范围0x65-0xa0
    
    {SCC8660_INIT,              0}                      //摄像头开始初始化
};



//从摄像头内部获取到的配置数据
uint16 SCC8660_GET_CFG[SCC8660_CONFIG_FINISH-1][2]=
{
    {SCC8660_AUTO_EXP,          0},
    {SCC8660_BRIGHT,            0}, //亮度设置          
    {SCC8660_FPS,               0}, //图像帧率           
    {SCC8660_SET_COL,           0}, //图像列数           
    {SCC8660_SET_ROW,           0}, //图像行数          
    {SCC8660_PCLK_DIV,          0}, //PCLK分频系数      
    {SCC8660_PCLK_MODE,         0}, //PCLK模式      
    {SCC8660_COLOR_MODE,        0}, //图像色彩模式
    {SCC8660_DATA_FORMAT,       0}, //输出数据格式 	
    {SCC8660_MANUAL_WB,         0}, //白平衡设置
};


uint8               scc8660_rx_buffer;
lpuart_transfer_t   scc8660_receivexfer;
lpuart_handle_t     scc8660_g_lpuartHandle;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在SDK底层fsl_lpuart文件中的串口3中断函数内调用
//-------------------------------------------------------------------------------------------------------------------
void scc8660_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        scc8660_uart_receive[scc8660_uart_receive_num] = scc8660_rx_buffer;
        scc8660_uart_receive_num++;
    
        if(1==scc8660_uart_receive_num && 0XA5!=scc8660_uart_receive[0])  scc8660_uart_receive_num = 0;
        if(3 == scc8660_uart_receive_num)
        {
            scc8660_uart_receive_num = 0;
            scc8660_uart_receive_flag = 1;
        }
    }
    handle->rxDataSize = scc8660_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = scc8660_receivexfer.data;          //还原缓冲区地址
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)配置串口初始化
//  @param      NULL
//  @return     void                    
//  @since      v1.0
//  Sample usage:       内部调用，无需用户调用。
//-------------------------------------------------------------------------------------------------------------------
void scc8660_cof_uart_init(void)
{
    //初始化串口 配置摄像头
    uart_init (SCC8660_COF_UART, 9600,SCC8660_COF_UART_TX,SCC8660_COF_UART_RX);      
    uart_rx_irq(SCC8660_COF_UART,1);
    //配置串口接收的缓冲区及缓冲区长度
    scc8660_receivexfer.dataSize = 1;
    scc8660_receivexfer.data = &scc8660_rx_buffer;
    //配置串口中断
    uart_set_handle(SCC8660_COF_UART, &scc8660_g_lpuartHandle, scc8660_uart_callback, NULL, 0, scc8660_receivexfer.data, 1);
    
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)初始化
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	使用FLEXIO接口采集摄像头	
//-------------------------------------------------------------------------------------------------------------------
void scc8660_init(void)
{
    flexio_camera_type = CAMERA_COLOR;//设置flexio接口连接摄像头类型
    flexio_color_camera_buffer_addr1 = scc8660_flexio1_image;
    flexio_color_camera_buffer_addr2 = scc8660_flexio2_image;
    //摄像头开始初始化之前务必将场信号拉高
    gpio_init(SCC8660_VSYNC_PIN,GPO,1,GPIO_PIN_CONFIG);
    
    //初始化摄像头配置串口
    scc8660_cof_uart_init();
	//开总中断
	EnableGlobalIRQ(0);
    //等待摄像头上电初始化成功 方式有两种：延时或者通过获取配置的方式 二选一
    //systick_delay_ms(500);//延时方式
    scc8660_get_all_config(SCC8660_COF_UART,SCC8660_GET_CFG);//获取配置的方式
    
    scc8660_uart_receive_flag = 0;
    //向摄像头发送配置信息
    scc8660_set_all_config(SCC8660_COF_UART,SCC8660_CFG);
    //获取配置便于查看配置是否正确
    scc8660_get_all_config(SCC8660_COF_UART,SCC8660_GET_CFG);
    //为方便使用，获取配置信息后并未对数据进行校验，如果需要确认配置是否成功，请自行进行数据比对。
	//关总中断
    DisableGlobalIRQ();

    scc8660_image = scc8660_flexio2_image;//设置双缓冲首地址
    
    dma_mux_init();
    flexio_camera(SCC8660_DATA_PIN, SCC8660_PCLK_PIN, SCC8660_HREF_PIN, SCC8660_W, SCC8660_H);
    flexio_dma_init((uint8 *)scc8660_image[0], SCC8660_W*SCC8660_H, scc8660_dma);
    flexio_enable_rxdma();
    NVIC_SetPriority(DMA0_DMA16_IRQn,1);            //设置DMA中断优先级 范围0-15 越小优先级越高
    
    //设置场中断
    gpio_interrupt_init(SCC8660_VSYNC_PIN, FALLING, GPIO_INT_CONFIG);
    NVIC_SetPriority(SCC8660_VSYNC_IRQN,0);         //设置场中断优先级 范围0-15 越小优先级越高
	//EnableGlobalIRQ(0);
}


uint8 scc8660_finish_flag;       //一场图像采集完成标志位
//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)场中断
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:       在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void scc8660_vsync(void)
{
    CLEAR_GPIO_FLAG(SCC8660_VSYNC_PIN);
    
    if(scc8660_image==flexio_color_camera_buffer_addr1)
    {
        dma_restart((uint8 *)flexio_color_camera_buffer_addr2[0]);
    }
    else if(scc8660_image==flexio_color_camera_buffer_addr2)
    {
        dma_restart((uint8 *)flexio_color_camera_buffer_addr1[0]);
    }
    

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)DMA完成中断
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void scc8660_dma(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if(scc8660_image==flexio_color_camera_buffer_addr1)
    {
        scc8660_image = flexio_color_camera_buffer_addr1;
    }
    else if(scc8660_image==flexio_color_camera_buffer_addr2)
    {
        scc8660_image = flexio_color_camera_buffer_addr2;
    }
    L1CACHE_CleanInvalidateDCacheByRange((uint32)scc8660_image[0],SCC8660_W*SCC8660_H);//如果数据存放在TCM则可以不需要这句话
	scc8660_finish_flag = 1;//一副图像从采集开始到采集结束耗时18MS左右(50FPS)
}
