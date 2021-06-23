/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		逐飞科技无线转串口模块
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-03-27
 * @note		
					接线定义：
					------------------------------------ 
					    无线转串口       单片机                        
    					RX              查看SEEKFREE_WIRELESS.h文件中的WIRELESS_UART_TX宏定义
    					TX              查看SEEKFREE_WIRELESS.h文件中的WIRELESS_UART_RX宏定义
    					RTS             查看SEEKFREE_WIRELESS.h文件中的RTS_PIN宏定义
    					CMD             悬空或者上拉
					------------------------------------ 
 ********************************************************************************************************************/

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "zf_systick.h"
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_uart.h"
#include "SEEKFREE_WIRELESS.h"





uint8               wireless_rx_buffer;
lpuart_transfer_t   wireless_receivexfer;
lpuart_handle_t     wireless_g_lpuartHandle;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口8中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        //接到一个字节后单片机将会进入串口中断，通过在此处读取wireless_rx_buffer可以取走数据
        
        
    }
    handle->rxDataSize = wireless_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = wireless_receivexfer.data;          //还原缓冲区地址
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块初始化
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void seekfree_wireless_init(void)
{
    //本函数使用的波特率为115200，为无线转串口模块的默认波特率，如需其他波特率请自行配置模块并修改串口的波特率
    gpio_init(RTS_PIN,GPI,0,GPIO_PIN_CONFIG);//初始化流控引脚
    
    uart_init (WIRELESS_UART, WIRELESS_UART_BAUD,WIRELESS_UART_TX,WIRELESS_UART_RX);	//初始换串口    
    uart_rx_irq(WIRELESS_UART,1);
    //配置串口接收的缓冲区及缓冲区长度
    wireless_receivexfer.dataSize = 1;
    wireless_receivexfer.data = &wireless_rx_buffer;
    
    uart_set_handle(WIRELESS_UART, &wireless_g_lpuartHandle, wireless_uart_callback, NULL, 0, wireless_receivexfer.data, 1);
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)(WIRELESS_UART) + LPUART1_IRQn),0);  //设置中断优先级 范围0-15 越小优先级越高
    //EnableGlobalIRQ(0);
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 发送函数
//  @param      buff        需要发送的数据地址
//  @param      len         发送长度
//  @return     uint32      剩余未发送的字节数   
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint32 seekfree_wireless_send_buff(uint8 *buff, uint32 len)
{
    while(len>30)
    {
        if(gpio_get(RTS_PIN))  
        {
            return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        }
        //while(gpio_get(RTS_PIN));  //如果RTS为低电平，则继续发送数据
        uart_putbuff(WIRELESS_UART,buff,30);

        buff += 30; //地址偏移
        len -= 30;//数量
    }
    
    if(gpio_get(RTS_PIN))  
    {
        return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
    }
    //while(gpio_get(RTS_PIN));  //如果RTS为低电平，则继续发送数据
    uart_putbuff(WIRELESS_UART,buff,len);//发送最后的数据
    
    return 0;
}