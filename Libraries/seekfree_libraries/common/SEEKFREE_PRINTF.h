/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 鎶�鏈璁篞Q缇わ細涓�缇わ細179029047(宸叉弧)  浜岀兢锛�244861897 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		printf
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#ifndef _SEEKFREE_PRINTF_h
#define _SEEKFREE_PRINTF_h
#include "common.h"

//void    printf(const char *format, ...);
uint32  zf_sprintf(char *buf, const char *fmt, ...);





#endif
