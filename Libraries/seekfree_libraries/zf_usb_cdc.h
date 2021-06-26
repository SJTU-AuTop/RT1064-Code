/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		USB虚拟串口
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-11-04
 ********************************************************************************************************************/
 
#ifndef _zf_usb_cdc_h
#define _zf_usb_cdc_h

#include "common.h"


void  usb_cdc_init(void);
uint8 usb_check_busy(void);
void  usb_cdc_send_char(uint8 dat);
void  usb_cdc_send_str(const int8 *str);
void  usb_cdc_send_buff(uint8 *p, uint32 length);
void  usb_cdc_recv_callback(uint8_t* buffer, uint32 length);

#endif
