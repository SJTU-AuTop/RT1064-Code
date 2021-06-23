/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		NRF24L01无线模块
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		
					接线定义：
					------------------------------------ 
					    NRF24L01    单片机            
					    CE          查看SEEKFREE_NRF24L01文件内的NRF_CE_PIN   宏定义
					    CSN         查看SEEKFREE_NRF24L01文件内的NRF_CSN_PIN  宏定义
					    MOSI        查看SEEKFREE_NRF24L01文件内的NRF_MOSI_PIN 宏定义
					    SCK         查看SEEKFREE_NRF24L01文件内的NRF_SCK_PIN  宏定义
					                                   
					    MISO        查看SEEKFREE_NRF24L01文件内的NRF_MISO_PIN 宏定义
					    IRQ         查看SEEKFREE_NRF24L01文件内的NRF_IRQ_PIN  宏定义
					------------------------------------ 
 ********************************************************************************************************************/


#include "common.h"
#include "zf_iomuxc.h"
#include "zf_gpio.h"
#include "zf_systick.h"
#include "SEEKFREE_NRF24L01.h"





#define NRF_CE(x)   gpio_set(NRF_CE_PIN,x)
#define NRF_CSN(x)  gpio_set(NRF_CSN_PIN,x)
#define NRF_MOSI(x) gpio_set(NRF_MOSI_PIN,x)
#define NRF_SCK(x)  gpio_set(NRF_SCK_PIN,x)

#define NRF_MISO    gpio_get(NRF_MISO_PIN)
#define NRF_IRQ     gpio_get(NRF_IRQ_PIN)


uint8 NRF_RF_Addr[NRF_ADDR_WIDTH]={0xff,0xff,0xff,0xff,0xff};   // TX,RX地址,可自行更改

uint8 nrf_rx_buff[NRF_DATA_WIDTH];                      	// 接收数据缓冲区
uint8 nrf_tx_buff[NRF_DATA_WIDTH];                      	// 发送数据缓冲区



// 函数: nrf_spi_wr_byte()
// 描述: 通过SPI写一个byte到nRF24L01+,同时从nRF24L01+读取一个byte
// 参数: byte   待写入字节数据
//       return 读取到的字节数据
//		内部使用用户无需调用
uint8 nrf_spi_wr_byte(uint8 byte)
{
    uint8 i;
        for(i=0; i<8; i++){                            		// 循环8次
            NRF_MOSI(byte & 0x80);               			// 将byte最高位输出到NRF_MOSI_PIN
            byte <<= 1;                                		// 低一位移位到最高位
            NRF_SCK (1);                            		// 拉高NRF_SCK_PIN,nRF24L01从NRF_MOSI_PIN读入1位数据,同时从NRF_MISO_PIN输出1位数据
            byte |= NRF_MISO;                       		// 读NRF_MISO_PIN到byte最低位
            NRF_SCK (0);                            		// NRF_SCK_PIN置低
        }	
    return(byte);                                      		// 返回读出的一字节
}

// 函数: nrf_spi_w_cmd_byte()
// 描述: 将命令字写入nRF24L01+,同时返回status字节
// 参数: cmd    命令字
//       return 返回status状态
//		内部使用用户无需调用
uint8 nrf_spi_w_cmd_byte(uint8 cmd)
{
    uint8 status;
    NRF_CSN (0);                                    		// NRF_CSN_PIN置低,开始传输数据
    status = nrf_spi_wr_byte(cmd);                      	// 写入寄存器地址,同时返回状态字
    NRF_CSN (1);                                    		// NRF_CSN_PIN拉高,结束数据传输
    return(status);                                     	// 返回状态寄存器    
}

// 函数: nrf_spi_w_reg_byte()
// 描述: 将val写入addr对应的寄存器地址,同时返回status字节
// 参数: cmd    命令字
//       val    待写入寄存器的数值
//       return 返回status状态
//		内部使用用户无需调用
uint8 nrf_spi_w_reg_byte(uint8 cmd, uint8 val)
{
    uint8 status;
    NRF_CSN (0);                                    		// NRF_CSN_PIN置低,开始传输数据
    status = nrf_spi_wr_byte(cmd);                      	// 写入寄存器地址,同时返回状态字
    nrf_spi_wr_byte(val);                               	// 然后写数据到该寄存器
    NRF_CSN (1);                                    		// NRF_CSN_PIN拉高,结束数据传输
    return(status);                                     	// 返回状态寄存器    
}

// 函数: nrf_spi_r_reg_byte()
// 描述: 读取addr所对应的寄存器地址
// 参数: cmd    命令字
//       return 返回寄存器内的数值
//		内部使用用户无需调用
uint8 nrf_spi_r_reg_byte(uint8 cmd)
{
    uint8 val;
    NRF_CSN (0);                                    		// NRF_CSN_PIN置低,开始传输数据
    nrf_spi_wr_byte(cmd);                               	// 写入寄存器地址
    val = nrf_spi_wr_byte(0);                           	// 然后从该寄存器读数据
    NRF_CSN (1);                                    		// NRF_CSN_PIN拉高,结束数据传输
    return(val);                                        	// 返回寄存器数据
}

// 函数: nrf_spi_w_reg_burst()
// 描述: 连续写入len个字节到addr指定的寄存器中,同时返回status状态字
// 参数: cmd    命令字
//       *p     待写入数据指针
//       len    待写入数据长度
//       return 返回status状态
//		内部使用用户无需调用
uint8 nrf_spi_w_reg_burst(uint8 cmd, uint8 *p, uint8 len)
{
    uint8 status, i;
    NRF_CSN (0);                                    		// NRF_CSN_PIN置低,开始传输数据
    status = nrf_spi_wr_byte(cmd);                      	// 选择寄存器,同时返回状态字
    for(i=0; i<len; i++)	
        nrf_spi_wr_byte(p[i]);                          	// 逐个字节写入nRF24L01+
    NRF_CSN (1);                                    		// NRF_CSN_PIN拉高,结束数据传输
    return(status);                                     	// 返回状态寄存器    
}

// 函数: nrf_spi_r_reg_burst()
// 描述: 连续读取len个字节到addr指定的寄存器中,同时返回status状态字
// 参数: cmd     命令字
//       *p     待读取数据指针
//       len    待读取数据长度
//       return 返回status状态
//		内部使用用户无需调用
uint8 nrf_spi_r_reg_burst(uint8 cmd, uint8 *p, uint8 len)
{
    uint8 status, i;
    NRF_CSN (0);                                    		// NRF_CSN_PIN置低,开始传输数据
    status = nrf_spi_wr_byte(cmd);                      	// 选择寄存器,同时返回状态字
    for(i=0; i<len; i++)	
        p[i] = nrf_spi_wr_byte(0);                      	// 逐个字节从nRF24L01+读出
    NRF_CSN (1);                                    		// NRF_CSN_PIN拉高,结束数据传输
    return(status);                                     	// 返回状态寄存器    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      NRF检查函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void nrf_self_check(void)
{
    uint8 temp=0;

    while(NRF_DATA_WIDTH != temp)
	{
		nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_RX_PW_P0,   NRF_DATA_WIDTH);    // 设置RX通道0数据宽度
		temp = nrf_spi_r_reg_byte(NRF_CMD_R_REGISTER | NRF_REG_RX_PW_P0);               // 读取RX通道0数据宽度
	}
    //如果程序卡死在while这里，则有以下几种情况
    //1.nrf未连接
    //2.nrf与单片机连接不可靠，大多数无法通信都是因为这个
    //3.nrf是坏的,如果NRF是新的，坏的可能性极低
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      NRF无线模块初始化
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void nrf_init(void)
{
    gpio_init(NRF_CE_PIN  ,GPO,0,GPIO_PIN_CONFIG);
    gpio_init(NRF_CSN_PIN ,GPO,0,GPIO_PIN_CONFIG);
    gpio_init(NRF_MOSI_PIN,GPO,0,GPIO_PIN_CONFIG);
    gpio_init(NRF_SCK_PIN ,GPO,0,GPIO_PIN_CONFIG);
              
    gpio_init(NRF_MISO_PIN,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(NRF_IRQ_PIN ,GPI,0,GPIO_PIN_CONFIG);

    
    NRF_CE  (0);                                    		// 进入待机模式
    NRF_CSN (1);                                    		// SPI禁止
    NRF_SCK (0);                                    		// SPI时钟置低
    
    NRF_CE (0);                                             // NRF_CE_PIN置低,进入待机模式
    nrf_self_check();                                            // NRF检查
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_CONFIG,     NRF_RCD_TX_DS_DI        // 禁用发送完成中断
                                                              | NRF_RCD_MAX_RT_DI       // 禁用发送超时中断
                                                              | NRF_RCD_CRC_EN          // 启用CRC
                                                              | NRF_RCD_CRC16           // CRC16
                                                              | NRF_RCD_PWR_UP          // 上电模式
                                                              | NRF_RCD_PRIM_PRX);      // RX模式
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_EN_AA,      NRF_RCD_PIPE0_AA_EN);   // 使能通道0自动应答
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_EN_RXADDR,  NRF_RCD_PIPE0_RX_EN);   // 使能接收通道0
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_SETUP_AW,   NRF_RCD_AW_5byte);      // 设置RX地址宽度
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_SETUP_RETR, NRF_RCD_ARC_10|NRF_RCD_ARD_250us);        // 使能自动重发  间隔时间250US
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_RF_CH,      NRF_RF_CH);             // 设置射频通道
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_RF_SETUP,   NRF_RCD_RF_DR_2Mbps     // 设置传输速率为2Mbps
                                                              | NRF_RCD_RF_PWR_0dBm);   // 发射功率为0dBm
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_RX_PW_P0,   NRF_DATA_WIDTH);        // 设置RX通道0数据宽度

    nrf_spi_w_reg_burst(NRF_CMD_W_REGISTER | NRF_REG_RX_ADDR_P0, NRF_RF_Addr, NRF_ADDR_WIDTH);   // 设置RX通道0地址
    nrf_spi_w_cmd_byte(NRF_CMD_FLUSH_RX);                                               // 清空RXFIFO
    NRF_CE (1);                                                                     	// NRF_CE_PIN置高,进入运行模式
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      NRF无线模块数据发送函数
//  @param      *p			要发送的数据地址
//  @return     void
//  @since      v1.0
//  Sample usage:			初始化nRF24L01+,并将其转换为发送状态。发送数据缓冲区中的数据,发送完成后再转换为接收状态
//-------------------------------------------------------------------------------------------------------------------
void nrf_send_packet(uint8 *p)
{
    uint8 sta=0;
    
    NRF_CE (0);                                                                     	// NRF_CE_PIN置低,进入待机模式
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_CONFIG, NRF_RCD_TX_DS_DI            // 禁用发送完成中断
                                                          | NRF_RCD_MAX_RT_DI           // 禁用发送超时中断
                                                          | NRF_RCD_CRC_EN              // 启用CRC
                                                          | NRF_RCD_CRC16               // CRC16
                                                          | NRF_RCD_PWR_UP              // 上电模式
                                                          | NRF_RCD_PRIM_PTX);          // TX模式

    nrf_spi_w_reg_burst(NRF_CMD_W_REGISTER | NRF_REG_TX_ADDR, NRF_RF_Addr, NRF_ADDR_WIDTH);  // 设置TX地址
    nrf_spi_w_reg_burst(NRF_CMD_W_TX_PAYLOAD, p, NRF_DATA_WIDTH);                       // 写入发送数据
    NRF_CE (1);                                                                     	// NRF_CE_PIN置高,进入运行模式

    while(1)
    {
        sta = nrf_spi_r_reg_byte(NRF_CMD_R_REGISTER | NRF_REG_STATUS);
        if(sta&0x10)//发送失败
        {
            nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_STATUS, 0x10); 				// 写回TX_DR,重置NRF_IRQ_PIN中断
            nrf_spi_w_reg_byte(NRF_CMD_FLUSH_TX,0xff);
            break;
        }
        if(sta&0x20)//发送成功
        {
            nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_STATUS, NRF_RCD_TX_DR); 	// 写回TX_DR,重置NRF_IRQ_PIN中断
            break;   
        }
    }
    NRF_CE (0);                                                                     	// NRF_CE_PIN置低,进入待机模式
    nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_CONFIG,     NRF_RCD_TX_DS_DI        // 禁用发送完成中断
                                                              | NRF_RCD_MAX_RT_DI       // 禁用发送超时中断
                                                              | NRF_RCD_CRC_EN          // 启用CRC
                                                              | NRF_RCD_CRC16           // CRC16
                                                              | NRF_RCD_PWR_UP          // 上电模式
                                                              | NRF_RCD_PRIM_PRX);      // RX模式
    NRF_CE (1);                                                                     	// NRF_CE_PIN置高,进入运行模式
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      NRF无线模块数据接收函数
//  @param      *p			准备接收的数据的数组地址
//  @return     uint8		接收成功标志,为1时表明数据接收成功
//  @since      v1.0		
//  Sample usage:			检查nRF24L01+是否接收到数据,接收到数据时将数据读取到接收数据缓冲区中
//-------------------------------------------------------------------------------------------------------------------
uint8 nrf_rece_packet(uint8 *p)
{
    uint8 sta=0;
    if(NRF_IRQ==0){                                                                 	// 等待NRF_IRQ_PIN置低
        sta = nrf_spi_r_reg_byte(NRF_CMD_R_REGISTER | NRF_REG_STATUS);                  // 读取STATUS寄存器
        if(sta & NRF_RCD_RX_DR){                                                        // RX_DS为1时表明接收到数据
            nrf_spi_w_reg_byte(NRF_CMD_W_REGISTER | NRF_REG_STATUS, NRF_RCD_RX_DR);     // 写回RX_DS,重置NRF_IRQ_PIN中断
            nrf_spi_r_reg_burst(NRF_CMD_R_RX_PAYLOAD, p, NRF_DATA_WIDTH);               // 读取nRF24L01+中的接收数据
            return(1);                                                                  // 返回接收完成标志
        }
    }
    return(0);                                                                          // 返回接收检查失败标志
}





