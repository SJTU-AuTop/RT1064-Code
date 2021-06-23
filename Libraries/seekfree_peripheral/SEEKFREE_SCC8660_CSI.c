/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		凌瞳摄像头(SCC8660) RT CSI接口
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
						SDA(摄像头的RX)     查看SEEKFREE_SCC8660_CSI.h文件中的SCC8660_CSI_COF_UART_TX宏定义
						SCL(摄像头的TX)     查看SEEKFREE_SCC8660_CSI.h文件中的SCC8660_CSI_COF_UART_RX宏定义
						场中断(VSY)         查看SEEKFREE_SCC8660_CSI.h文件中的SCC8660_CSI_VSYNC_PIN宏定义
						行中断(HREF)        不与核心板连接（悬空）
						像素中断(PCLK)      查看SEEKFREE_SCC8660_CSI.h文件中的SCC8660_CSI_PCLK_PIN宏定义
						数据口(D0-D7)       B31-B24 B31对应摄像头接口D0
					------------------------------------ 
	
					默认分辨率               160*120
					默认FPS                  50帧
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
#include "zf_usb_cdc.h"
#include "seekfree_iic.h"
#include "SEEKFREE_SCC8660_CSI.h"


//定义图像缓冲区  如果用户需要访问图像数据 最好通过scc8660_csi_image来访问数据，最好不要直接访问缓冲区
//由于默认分辨率160*120数据量较小，所以默认将图像数组放置于DTCM区域，访问速度更快。
//以下注释的两句是将图像数组定义在SDRAM内，如果图像分辨率超过160*120，请将这两句解注并注释掉位于DTCM的两句。
//AT_SDRAM_SECTION_ALIGN(uint16 scc8660_csi1_image[SCC8660_CSI_PIC_H][SCC8660_CSI_PIC_W],64);
//AT_SDRAM_SECTION_ALIGN(uint16 scc8660_csi2_image[SCC8660_CSI_PIC_H][SCC8660_CSI_PIC_W],64);
AT_DTCM_SECTION_ALIGN(uint16 scc8660_csi1_image[SCC8660_CSI_PIC_H][SCC8660_CSI_PIC_W],64);
AT_DTCM_SECTION_ALIGN(uint16 scc8660_csi2_image[SCC8660_CSI_PIC_H][SCC8660_CSI_PIC_W],64);

//用户访问图像数据直接访问这个指针变量就可以
//访问方式非常简单，可以直接使用下标的方式访问
//例如访问第10行 50列的点，scc8660_csi_image[10][50]就可以了
uint16 (*scc8660_csi_image)[SCC8660_CSI_PIC_W];

uint8   scc8660_uart_receive[3];
uint8   scc8660_uart_receive_num = 0;
vuint8  scc8660_uart_receive_flag;

//需要配置到摄像头的数据
uint16 SCC8660_CFG_CSI[SCC8660_CONFIG_FINISH][2]=
{
    {SCC8660_AUTO_EXP,          0},                     //自动曝光     默认：0     	可选参数为：0 1。      0：手动曝光  1：自动曝光
    {SCC8660_BRIGHT,            800},                   //亮度设置     手动曝光默认：800	手动曝光时：参数范围0-65535   自动曝光推荐值：100 自动曝光时参数设置范围0-255
														//需要注意SCC8660_BRIGHT的参数固定时，不同的SCC8660_PCLK_DIV参数会影响图像的亮度。
														//假设SCC8660_BRIGHT的参数为800，SCC8660_PCLK_DIV的参数为0时 和 SCC8660_PCLK_DIV的参数为2时 
														//参数为2的时候图像明显要比为0的时候亮，在使用双摄的时候感觉两个摄像头亮度不一致时需要注意这个问题。
														
    {SCC8660_FPS,               50},                    //图像帧率     默认：50    	可选参数为：60 50 30 25。 实际帧率还需要看SCC8660_PCLK_DIV参数的设置
    {SCC8660_SET_COL,           SCC8660_CSI_PIC_W},     //图像列数     默认：160   	请在.h的宏定义处修改
    {SCC8660_SET_ROW,           SCC8660_CSI_PIC_H},     //图像行数     默认：120   	请在.h的宏定义处修改
    {SCC8660_PCLK_DIV,          0},                     //PCLK分频系数 默认：0     	可选参数为：0:1/1 1:2/3 2:1/2 3:1/3 4:1/4 5:1/8。  
                                                       //分频系数越大，PCLK频率越低，降低PCLK可以减轻DVP接口的干扰，但降低PCLK频率则会影响帧率。若无特殊需求请保持默认。
                                                       //例如设置FPS为50帧，但是pclk分频系数选择的为5，则摄像头输出的帧率为50*（1/8）=6.25帧
													   //其他参数不变的情况下，SCC8660_PCLK_DIV参数越大图像会越亮
    
    {SCC8660_PCLK_MODE,         0},                     //PCLK模式     默认：0		可选参数为：0 1。         0：不输出消隐信号，1：输出消隐信号。(通常都设置为0，如果使用STM32的DCMI接口采集需要设置为1)
    {SCC8660_COLOR_MODE,        0},                     //图像色彩模式 默认：0		可选参数为：0 1。         0：正常彩色模式    1：鲜艳模式（色彩饱和度提高）
    {SCC8660_DATA_FORMAT,       0},                     //输出数据格式 默认：0		可选参数为：0 1 2 3。     0：RGB565 1：RGB565(字节交换) 2：YUV422(YUYV) 3：YUV422(UYVY)
    {SCC8660_MANUAL_WB,         0},                     //手动白平衡   默认：0		可选参数为：0 0x65-0xa0。 0：关闭手动白平衡，启用自动白平衡    其他：手动白平衡 手动白平衡时 参数范围0x65-0xa0
    
    {SCC8660_INIT,              0}                      //摄像头开始初始化
};

//从摄像头内部获取到的配置数据
uint16 SCC8660_GET_CFG_CSI[SCC8660_CONFIG_FINISH-1][2]= 
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

uint8               scc8660_csi_rx_buffer;
lpuart_transfer_t   scc8660_csi_receivexfer;
lpuart_handle_t     scc8660_csi_g_lpuartHandle;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在SDK底层fsl_lpuart文件中的串口3中断函数内调用
//-------------------------------------------------------------------------------------------------------------------
void csi_scc8660_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        scc8660_uart_receive[scc8660_uart_receive_num] = scc8660_csi_rx_buffer;
        scc8660_uart_receive_num++;
    
        if(1==scc8660_uart_receive_num && 0XA5!=scc8660_uart_receive[0])  scc8660_uart_receive_num = 0;
        if(3 == scc8660_uart_receive_num)
        {
            scc8660_uart_receive_num = 0;
            scc8660_uart_receive_flag = 1;
        }
    }
    handle->rxDataSize = scc8660_csi_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = scc8660_csi_receivexfer.data;          //还原缓冲区地址
}

uint8 scc8660_csi_finish_flag;  //图像采集完成的标志位    


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)CSI中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数由isr.c中的CSI_IRQHandler函数调用
//-------------------------------------------------------------------------------------------------------------------
void scc8660_csi_isr(CSI_Type *base, csi_handle_t *handle, status_t status, void *userData)
{
    if(csi_get_full_buffer(&csi_handle,&fullCameraBufferAddr))
    {
        csi_add_empty_buffer(&csi_handle,(uint8 *)fullCameraBufferAddr);
        if(fullCameraBufferAddr == (uint32)scc8660_csi1_image[0])
        {
            scc8660_csi_image = scc8660_csi1_image;//采集完成
            L1CACHE_CleanInvalidateDCacheByRange((uint32)scc8660_csi1_image[0],SCC8660_CSI_W*SCC8660_CSI_H);
        }
        else if(fullCameraBufferAddr == (uint32)scc8660_csi2_image[0])
        {
            scc8660_csi_image = scc8660_csi2_image;//采集完成
            L1CACHE_CleanInvalidateDCacheByRange((uint32)scc8660_csi2_image[0],SCC8660_CSI_W*SCC8660_CSI_H);
        }
        scc8660_csi_finish_flag = 1;//采集完成标志位置一
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      摄像头配置串口初始化
//  @param      NULL
//  @return     void                    
//  @since      v1.0
//  Sample usage:       内部调用，无需用户调用。
//-------------------------------------------------------------------------------------------------------------------
void scc8660_csi_cof_uart_init(void)
{
    //初始化串口 配置摄像头
    uart_init (SCC8660_CSI_COF_UART, 9600,SCC8660_CSI_COF_UART_TX,SCC8660_CSI_COF_UART_RX);      
    uart_rx_irq(SCC8660_CSI_COF_UART,1);
    //配置串口接收的缓冲区及缓冲区长度
    scc8660_csi_receivexfer.dataSize = 1;
    scc8660_csi_receivexfer.data = &scc8660_csi_rx_buffer;
    //配置串口中断
    uart_set_handle(SCC8660_CSI_COF_UART, &scc8660_csi_g_lpuartHandle, csi_scc8660_uart_callback, NULL, 0, scc8660_csi_receivexfer.data, 1);
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      配置摄像头内部配置信息
//  @param      uartn       选择使用的串口
//  @param      buff        发送配置信息的地址
//  @return     void
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
void scc8660_set_all_config(UARTN_enum uartn, uint16 buff[SCC8660_CONFIG_FINISH-1][2])
{
    uint16 temp, i;
    uint8  send_buffer[4];

    scc8660_uart_receive_flag = 0;
    
    //设置参数  具体请参看问题锦集手册
    //开始配置摄像头并重新初始化
    for(i=0; i<SCC8660_CONFIG_FINISH; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = buff[i][0];
        temp           = buff[i][1];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(uartn,send_buffer,4);
        systick_delay_ms(2);
    }
    
    //等待摄像头初始化成功
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    while((0xff != scc8660_uart_receive[1]) || (0xff != scc8660_uart_receive[2]));
    //以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    //利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头内部全部配置信息
//  @param      uartn       选择使用的串口
//  @param      buff        接收配置信息的地址
//  @return     void
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化摄像头配置串口
//-------------------------------------------------------------------------------------------------------------------
void scc8660_get_all_config(UARTN_enum uartn, uint16 buff[SCC8660_CONFIG_FINISH-1][2])
{
    uint16 temp, i;
    uint8  send_buffer[4];
    
    for(i=0; i<SCC8660_CONFIG_FINISH-1; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = SCC8660_GET_STATUS;
        temp           = buff[i][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(uartn,send_buffer,4);
        
        //等待接受回传数据
        while(!scc8660_uart_receive_flag);
        scc8660_uart_receive_flag = 0;
        
        buff[i][1] = scc8660_uart_receive[1]<<8 | scc8660_uart_receive[2];
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头固件版本
//  @param      uartn               选择使用的串口
//  @return     (uint16)camera_id   返回摄像头ID
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化摄像头配置串口
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_id(UARTN_enum uartn)
{
    uint16 temp;
    uint8  send_buffer[4];
	
    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_GET_WHO_AM_I;
    temp           = 0;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
        
    //等待接受回传数据
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    
    return ((uint16)(scc8660_uart_receive[1]<<8) | scc8660_uart_receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头某一个参数配置信息
//  @param      uartn               选择使用的串口
//  @return     (uint16)config      返回参数值
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化摄像头配置串口
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_config(UARTN_enum uartn, uint8 config)
{
    uint8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_GET_WHO_AM_I;
    send_buffer[2] = 0x00;
    send_buffer[3] = config;
    
    uart_putbuff(uartn,send_buffer,4);
        
    //等待接受回传数据
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    
    return ((uint16)(scc8660_uart_receive[1]<<8) | scc8660_uart_receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取彩色摄像头固件版本
//  @param      uartn       选择使用的串口
//  @return     uint16      版本号
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化摄像头配置串口
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_version(UARTN_enum uartn)
{
    uint16 temp;
    uint8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_GET_STATUS;
    temp           = SCC8660_GET_VERSION;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
        
    //等待接受回传数据
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    
    return ((uint16)(scc8660_uart_receive[1]<<8) | scc8660_uart_receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单独设置图像亮度
//  @param      uartn       选择使用的串口
//  @param      data        需要设置的亮度值
//  @return     uint16      返回设置的亮度值
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化摄像头配置串口
//  @note                   通过该函数设置的参数，不会被51单片机保存
//-------------------------------------------------------------------------------------------------------------------
uint16  scc8660_set_bright(UARTN_enum uartn, uint16 data)
{
    uint8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_SET_BRIGHT;
    send_buffer[2] = data>>8;
    send_buffer[3] = (uint8)data;
    
    uart_putbuff(uartn,send_buffer,4);
    
    //等待接受回传数据
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    
    data = scc8660_uart_receive[1]<<8 | scc8660_uart_receive[2];
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单独设置白平衡
//  @param      uartn       选择使用的串口
//  @param      data        需要设置的亮度值
//  @return     uint16      返回设置的亮度值
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化摄像头配置串口
//  @note                   通过该函数设置的参数，不会被51单片机保存
//-------------------------------------------------------------------------------------------------------------------
uint16  scc8660_set_maunal_wb(UARTN_enum uartn, uint16 data)
{
    uint8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_SET_MANUAL_WB;
    send_buffer[2] = data>>8;
    send_buffer[3] = (uint8)data;
    
    uart_putbuff(uartn,send_buffer,4);
    
    //等待接受回传数据
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    
    data = scc8660_uart_receive[1]<<8 | scc8660_uart_receive[2];
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单独设置摄像头寄存器
//  @param      uartn       选择使用的串口
//  @param      reg         寄存器地址
//  @param      data        需要写入寄存器的数值
//  @return     uint16      回传写入寄存器的值
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_set_reg_addr(UARTN_enum uartn, uint8 reg, uint16 data)
{
    uint16 temp;
    uint8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_SET_REG_ADDR;
    send_buffer[2] = 0x00;
    send_buffer[3] = (uint8)reg;
    
    uart_putbuff(uartn,send_buffer,4);
    
    systick_delay_ms(2);
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SCC8660_SET_REG_DATA;
    temp           = data;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
    
    //等待接受回传数据
    while(!scc8660_uart_receive_flag);
    scc8660_uart_receive_flag = 0;
    
    
    temp = scc8660_uart_receive[1]<<8 | scc8660_uart_receive[2];

    return temp;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)初始化 使用CSI接口
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
void scc8660_csi_init(void)
{
    //摄像头开始初始化之前务必将场信号拉高
    if      (SCC8660_CSI_VSYNC_PIN == CSI_VSYNC_B14)  gpio_init(B14,GPO,1,GPIO_PIN_CONFIG);
    else if (SCC8660_CSI_VSYNC_PIN == CSI_VSYNC_B22)  gpio_init(B22,GPO,1,GPIO_PIN_CONFIG);
    else if (SCC8660_CSI_VSYNC_PIN == CSI_VSYNC_C29)  gpio_init(C29,GPO,1,GPIO_PIN_CONFIG);
    
    //初始化摄像头配置串口
    scc8660_csi_cof_uart_init();
	//开总中断
	EnableGlobalIRQ(0);
    //等待摄像头上电初始化成功 方式有两种：延时或者通过获取配置的方式 二选一
    //systick_delay_ms(500);//延时方式
    scc8660_get_all_config(SCC8660_CSI_COF_UART,SCC8660_GET_CFG_CSI);//获取配置的方式
    
    scc8660_uart_receive_flag = 0;
    //向摄像头发送配置信息
    scc8660_set_all_config(SCC8660_CSI_COF_UART,SCC8660_CFG_CSI);
    //获取配置便于查看配置是否正确
    scc8660_get_all_config(SCC8660_CSI_COF_UART,SCC8660_GET_CFG_CSI);
    //为方便使用，获取配置信息后并未对数据进行校验，如果需要确认配置是否成功，请自行进行数据比对。
	//关总中断
    DisableGlobalIRQ();
    //CSI 采集初始化
    csi_init(SCC8660_CSI_W, SCC8660_CSI_H, &csi_handle, scc8660_csi_isr, SCC8660_CSI_VSYNC_PIN, SCC8660_CSI_PCLK_PIN);
    csi_add_empty_buffer(&csi_handle, (uint8 *)&scc8660_csi1_image[0][0]);
	csi_add_empty_buffer(&csi_handle, (uint8 *)&scc8660_csi2_image[0][0]);
    csi_start(&csi_handle);
    //设置图像地址初值，务必保留
    scc8660_csi_image = scc8660_csi1_image;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)图像上传至上位机
//  @param      uartn	需要发送的串口
//  @param      image	图像数组地址
//  @param      width	图像高度
//  @param      height	图像宽度
//  @return     void                    
//  @since      v1.0
//  Sample usage:       csi_seekfree_sendimg_scc8660(USART_1,(uint8 *)scc8660_csi_image[0],SCC8660_CSI_PIC_W,SCC8660_CSI_PIC_H);
//-------------------------------------------------------------------------------------------------------------------
void csi_seekfree_sendimg_scc8660(UARTN_enum uartn, uint8 *image, uint16 width, uint16 height)
{
    uart_putchar(uartn,0x00);uart_putchar(uartn,0xff);uart_putchar(uartn,0x01);uart_putchar(uartn,0x01);//发送命令
    uart_putbuff(uartn, image, 2*width*height);  //发送图像 因为彩色图像 一个像素点占用两个字节 因此这里字节数需要乘以2
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)图像上传至上位机（使用USB虚拟串口发送）
//  @param      uartn	需要发送的串口
//  @param      image	图像数组地址
//  @param      width	图像高度
//  @param      height	图像宽度
//  @return     void                    
//  @since      v1.0
//  Sample usage:       seekfree_sendimg_scc8660_usb_cdc((uint8 *)scc8660_csi_image[0],SCC8660_CSI_PIC_W,SCC8660_CSI_PIC_H);
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_scc8660_usb_cdc(uint8 *image, uint16 width, uint16 height)
{
	uint8 cmd[4];
	cmd[0] = 0x00; cmd[1] = 0xff; cmd[2] = 0x01; cmd[3] = 0x01; 
	usb_cdc_send_buff(cmd,4);					//发送命令
    usb_cdc_send_buff(image, width*height*2);  	//发送图像 因为彩色图像 一个像素点占用两个字节 因此这里字节数需要乘以2
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660(凌瞳摄像头)获取像素点RGB分量
//  @param      *dat    图像数组的地址
//  @param      x       需要获取的像素所在列
//  @param      y       需要获取的像素所在行
//  @param      z       图像宽度
//  @param      *r      接收r分量地址 返回值范围0-31
//  @param      *g      接收g分量地址 返回值范围0-63
//  @param      *b      接收b分量地址 返回值范围0-31
//  @return     void					
//  @since      v1.0
//  Sample usage:		color_camera_take_point(scc8660_csi_image[0],0, 0, SCC8660_CSI_PIC_W, &r_value,&g_value,&b_value);//获取第0列 第0行像素的RGB分量  摄像头的数据格式必须设置为0
//	@note				此函数主要目的是为了让大家能够清晰的了解RGB数据是如何存储的
//-------------------------------------------------------------------------------------------------------------------
void inline color_camera_take_point(uint16 *dat, uint16 x, uint16 y, uint16 z, uint8 *r, uint8 *g, uint8 *b)
{
    uint16 pixel;
    
    //获取指定坐标的像素数据
    pixel = dat[x+y*z];
    
    //因为R5G3是存储在低八位 G3B5是存储在高八位
    //因为我们先将位置进行交换，便于获取每个分量的数据
    pixel = ((pixel&0xff)<<8) |(pixel>>8);
    
    *r = pixel>>11;
    *g = (pixel>>5)&0x3f;
    *b = pixel&0x1f;
}



