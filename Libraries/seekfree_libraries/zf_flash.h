/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		flash(内置) 
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#ifndef _zf_flash_h
#define _zf_flash_h

#include "common.h"



#define FLASH_BASE_ADDR             0x70000000
#define FLASH_SIZE                  4096    //4M
#define FLASH_SECTOR_SIZE           4096    //4KB
#define FLASH_SECTOR_NUM            1024

#define FLASH_PAGE_SIZE             256
#define FLASH_SECTOR_PAGE_NUM       (FLASH_SECTOR_SIZE/FLASH_PAGE_SIZE)



//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      sector_num 		需要写入的扇区编号
//  @param      offset	 		地址偏移 偏移1个点 为四个字节
//  @param      type		 	读取的数据类型
//  @return     				返回给定地址的数据
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//读取20号扇区偏移0数据类型为uint32
//  @note       需要特别注意的是 RT系列有cache，因此在每次读取flash之前建议SCB_InvalidateDCache();执行改语句清空cache
//              并不是说没读一个数据清空一下，
//-------------------------------------------------------------------------------------------------------------------
#define     flash_read(sector_num,offset,type)      (*(type *)((uint32)((FLASH_BASE_ADDR + (sector_num)*FLASH_SECTOR_SIZE) + (offset*4))))


#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)

#define     uint32_conversion_float(uint32_data)    (*(float *)&uint32_data)


uint8 flash_init(void);
uint8 flash_check(uint32 sector_num, uint32 page_num);
uint8 flash_erase_sector(uint32 sector_num);
uint8 flash_page_program(uint32 sector_num, uint32 page_num, const uint32 *buf, uint8 len);
void  flash_read_page(uint32 sector_num, uint32 page_num, uint32 *buf, uint8 len);


#endif