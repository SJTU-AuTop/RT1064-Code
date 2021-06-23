/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		W25QXXJV 
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


#ifndef _SEEKFREE_W25QXXJV_h
#define _SEEKFREE_W25QXXJV_h


#include "common.h"

#define W25QXXJV_FLEXSPI                FLEXSPI
#define W25QXXJV_FLEXSPI_AMBA_BASE      FlexSPI_AMBA_BASE
#define W25QXXJV_FLEXSPI_CLOCK          kCLOCK_FlexSpi

#define W25QXXJV_BASE_ADDR              0x60000000
#define W25QXXJV_SIZE                   8192    //64Mbit 
#define W25QXXJV_SECTOR_SIZE            4096    //4KB
#define W25QXXJV_SECTOR_NUM             2048
    
#define W25QXXJV_PAGE_SIZE              256
#define W25QXXJV_SECTOR_PAGE_NUM        (W25QXXJV_SECTOR_SIZE/W25QXXJV_PAGE_SIZE)






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
#define     w25qxxjv_read(sector_num,offset,type)      (*(type *)((uint32)((W25QXXJV_BASE_ADDR + (sector_num)*W25QXXJV_SECTOR_SIZE) + (offset*4))))


//浮点转换宏定义在zf_flash.h文件中






void   w25qxxjv_init(void);
uint8  w25qxxjv_check(uint32 sector_num, uint32 page_num);
uint8  w25qxxjv_erase_sector(uint32 sector_num);
uint8  w25qxxjv_write_page(uint32 sector_num, uint32 page_num, const void *buf, uint8 len);
void   w25qxxjv_read_page(uint32 sector_num, uint32 page_num, void *buf, uint8 len);


#endif

