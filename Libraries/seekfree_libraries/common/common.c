/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		common
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#include "common.h"


CAMERA_TYPE_enum flexio_camera_type;     //摄像头型号
uint8 *flexio_camera_buffer_addr;        //摄像头数组地址


void NMI_Handler(void)
{
	while(1);
}
//void HardFault_Handler(void)
//{
//	//硬件上访  可能是数组越界或者使用了未初始化的设备
//	//这里提示大家一个问题，经常有人说我的外设初始化了怎么就是要进HardFault呢
//	//很多是因为自己开了中断，然后在中断里面使用了外设，然后他的初始化顺序是先初始化中断然后再初始化外设
//	//那么问题就来了，中断初始化完成之后会部分中断直接进入中断函数或者满足调节也会进入中断函数，那么就会造成中断里面使用到的外设还没被初始化
//	//所以大家需要注意这个问题
//	while(1);
//}

void BusFault_Handler(void)
{
	while(1);
}
void UsageFault_Handler(void)
{
	while(1);
}
void SVC_Handler(void)
{
	while(1);
}
void DebugMon_Handler(void)
{
	while(1);
}


//此函数已经在fsl_sdmmc_event.c文件中定义
//void SysTick_Handler(void)
//{
//	while(1);
//}