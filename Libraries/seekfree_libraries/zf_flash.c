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

#include "fsl_cache.h"
#include "zf_rom_api.h"
#include "zf_flash.h"

flexspi_nor_config_t config;
serial_nor_config_option_t option;
uint32 instance = 1;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      校验FLASH是否有数据
//  @param      sector_num 		需要写入的扇区编号   参数范围0-1023
//  @param      page_num	 	当前扇区页的编号     参数范围0-15
//  @return     				返回1有数据，返回0没有数据，如果需要对有数据的区域写入新的数据则应该对所在扇区进行擦除操作
//  @since      v1.0
//  Sample usage:               flash_check(500,0);//校验500号扇区，第0页是否有数据
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check(uint32 sector_num, uint32 page_num)
{
    uint8 i;
    
    assert(FLASH_SECTOR_NUM>sector_num);                //校验参数合法性
    assert(FLASH_SECTOR_PAGE_NUM>page_num);             //校验参数合法性
    
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE, 256);//读取flash前，最好先清空缓存
    for(i=0; i<FLASH_PAGE_SIZE/4; i++)
    {
        if(0xFFFFFFFF != flash_read(sector_num,page_num*FLASH_PAGE_SIZE/4+i,uint32))
        {
            return kStatus_Fail;//flash需要擦除
        }
    }
    
    return kStatus_Success;//flash不需要擦除
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      擦除扇区
//  @param      sector_num 		需要写入的扇区编号   参数范围0-1023
//  @return     				返回1有表示失败  返回0表示成功
//  @since      v1.0
//  Sample usage:               flash_erase_sector(500);
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_erase_sector(uint32 sector_num)
{
    status_t status;
    
    assert(FLASH_SECTOR_NUM>sector_num);                //校验参数合法性
    
    status = rom_api_flexspi_nor_flash_erase(instance, &config, sector_num*FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
    if(status != kStatus_Success)
    {
        return kStatus_Fail;
    }
    
    
    
    return kStatus_Success;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编程一页
//  @param      sector_num 		需要写入的扇区编号   参数范围0-1023
//  @param      page_num 		需要写入的页编号     参数范围0-15
//  @param      buf 		    需要写入的数据地址   传入的数组类型必须为uint32
//  @param      len 		    需要写入的数据长度   参数范围1-64
//  @return     				返回1有表示失败  返回0表示成功
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_page_program(uint32 sector_num, uint32 page_num, const uint32 *buf, uint8 len)
{
    uint16 i=0;
    status_t status;
    uint8 page_buffer[256];
    
    assert(FLASH_SECTOR_NUM>sector_num);                //校验参数合法性
    assert(FLASH_SECTOR_PAGE_NUM>page_num);             //校验参数合法性
    assert(FLASH_PAGE_SIZE>=(len*4));                   //校验参数合法性
    
    while(i<(len*4))
    {
        page_buffer[i] = ((uint8 *)buf)[i];
        i++;
    }
    while(i<FLASH_PAGE_SIZE)
    {
        page_buffer[i] = 0xff;
        i++;
    }
    
    status = rom_api_flexspi_nor_flash_page_program(instance,&config,sector_num*FLASH_SECTOR_SIZE+page_num*FLASH_PAGE_SIZE,(const uint32_t *)page_buffer);
    if(status != kStatus_Success)
    {
        return kStatus_Fail;
    }
    
    
    
    return kStatus_Success;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编程一页
//  @param      sector_num 		需要读取的扇区编号       参数范围0-1023
//  @param      page_num 		需要读取的页编号         参数范围0-15
//  @param      buf 		    需要读取的数据地址       传入的数组类型必须为uint32
//  @param      len 		    需要读取的数据长度       参数范围1-64
//  @return     				返回1有表示失败  返回0表示成功
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page(uint32 sector_num, uint32 page_num, uint32 *buf, uint8 len)
{
    uint8 i;
    
    assert(FLASH_SECTOR_NUM>sector_num);                //校验参数合法性
    assert(FLASH_SECTOR_PAGE_NUM>page_num);             //校验参数合法性
    assert(FLASH_PAGE_SIZE>=(len*4));                   //校验参数合法性
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE, len*4);//读取flash前，最好先清空缓存
    
    for(i=0; i<len; i++)
    {
        *(buf + i) = flash_read(sector_num,page_num*FLASH_PAGE_SIZE+i,uint32);
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      flash初始化
//  @param      void 		
//  @return     				返回1有表示失败  返回0表示成功
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_init(void)
{
    option.option0.U = 0xC0000008; // QuadSPI NOR, Frequency: 133MHz
    
    rom_api_init();
    if(rom_api_flexspi_nor_get_config(instance, &config, &option) !=  kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}


