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




#ifndef _SEEKFREE_NRF24L01_h
#define _SEEKFREE_NRF24L01_h





// SPI命令字   SPI Commands
#define NRF_CMD_R_REGISTER          0x00    // 读寄存器             Read command and status registers
#define NRF_CMD_W_REGISTER          0x20    // 写寄存器             Write command and status registers
#define NRF_CMD_R_RX_PAYLOAD        0x61    // 读RXFIFO             Read RX-payload
#define NRF_CMD_W_TX_PAYLOAD        0xA0    // 读TXFIFO             Write TX-payload
#define NRF_CMD_FLUSH_TX            0xE1    // 清TXFIFO             Flush TX FIFO
#define NRF_CMD_FLUSH_RX            0xE2    // 清RXFIFO             Flush RX FIFO
#define NRF_CMD_REUSE_TX_PL         0xE3    // 重发TX数据           Used for a PTX device Reuse last transmitted payload.
#define NRF_CMD_R_RX_PL_WID         0x60    // 读RX数据宽           Read RX payload width for the top R_RX_PAYLOAD in the RX FIFO
#define NRF_CMD_W_ACK_PAYLOAD       0xA8    // 带ACK的数据          Write Payload to be transmitted together with ACK packet on PIPE
#define NRF_CMD_W_TX_PAYLOAD_NOACK  0xB0    // 无ACK的数据          Disables AUTOACK on this specific packet.
#define NRF_CMD_NOP                 0xFF    // 空操作"命令字        No Operation.Might be used to read the STATUS register

// SPI寄存器地址     Registers Addresses
#define NRF_REG_CONFIG              0x00    // 配置寄存器           Configuration Register
#define NRF_REG_EN_AA               0x01    // 使能自动应答         Enable ‘Auto Acknowledgment’
#define NRF_REG_EN_RXADDR           0x02    // 使能RX数据通道       Enabled RX Addresses
#define NRF_REG_SETUP_AW            0x03    // 设置地址宽度         Setup of Address Widths
#define NRF_REG_SETUP_RETR          0x04    // 设置自动重发         Setup of Automatic Retransmission
#define NRF_REG_RF_CH               0x05    // 频道设置             RF Channel
#define NRF_REG_RF_SETUP            0x06    // RF设置               RF Setup Register
#define NRF_REG_STATUS              0x07    // 状态                 Status Register
#define NRF_REG_OBSERVE_TX          0x08    // 发送监测             Transmit observe register
#define NRF_REG_RPD                 0x09    // 接收功率监测         Received Power Detector (nRF24L01+ only),Carrier Detect(nRF24L01 only)
#define NRF_REG_RX_ADDR_P0          0x0A    // 接收通道0地址        Receive address data pipe 0
#define NRF_REG_RX_ADDR_P1          0x0B    // 接收通道1地址        Receive address data pipe 1
#define NRF_REG_RX_ADDR_P2          0x0C    // 接收通道2地址        Receive address data pipe 2
#define NRF_REG_RX_ADDR_P3          0x0D    // 接收通道3地址        Receive address data pipe 3
#define NRF_REG_RX_ADDR_P4          0x0E    // 接收通道4地址        Receive address data pipe 4
#define NRF_REG_RX_ADDR_P5          0x0F    // 接收通道5地址        Receive address data pipe 5
#define NRF_REG_TX_ADDR             0x10    // 发送地址             Transmit address
#define NRF_REG_RX_PW_P0            0x11    // 接收通道0数据宽度    Number of bytes in RX payload in data pipe 0
#define NRF_REG_RX_PW_P1            0x12    // 接收通道1数据宽度    Number of bytes in RX payload in data pipe 1
#define NRF_REG_RX_PW_P2            0x13    // 接收通道2数据宽度    Number of bytes in RX payload in data pipe 2
#define NRF_REG_RX_PW_P3            0x14    // 接收通道3数据宽度    Number of bytes in RX payload in data pipe 3
#define NRF_REG_RX_PW_P4            0x15    // 接收通道4数据宽度    Number of bytes in RX payload in data pipe 4
#define NRF_REG_RX_PW_P5            0x16    // 接收通道5数据宽度    Number of bytes in RX payload in data pipe 5
#define NRF_REG_FIFO_STATUS         0x17    // FIFO状态             FIFO Status Register
#define NRF_REG_DYNPD               0x1C    // 允许动态数据包长度   Enable dynamic payload length
#define NRF_REG_FEATURE             0x1D    // 特征寄存器           Feature Register

// SPI寄存器配置     Registers Config

// 0x00 CONFIG  配置寄存器
#define NRF_RCD_RX_DR_EN            0<<6    // bit6=MASK_RX_DR=0=映射RX_DR中断(数据接收完成时IRQ输出L)
#define NRF_RCD_RX_DR_DI            1<<6    // bit6=MASK_RX_DR=1=屏蔽RX_DR中断
#define NRF_RCD_TX_DS_EN            0<<5    // bit5=MASK_TX_DR=0=映射TX_DR中断(数据发送完成时IRQ输出L)
#define NRF_RCD_TX_DS_DI            1<<5    // bit5=MASK_TX_DR=1=屏蔽TX_DR中断
#define NRF_RCD_MAX_RT_EN           0<<4    // bit4=MASK_MAX_RT=0=映射MASK_MAX_RT中断(超过重发上限时IRQ输出L)
#define NRF_RCD_MAX_RT_DI           1<<4    // bit4=MASK_MAX_RT=1=屏蔽MASK_MAX_RT中断
#define NRF_RCD_CRC_DI              0<<3    // bit3=EN_CRC=0=禁用CRC
#define NRF_RCD_CRC_EN              1<<3    // bit3=EN_CRC=1=启用CRC
#define NRF_RCD_CRC8                0<<2    // bit2=CRCO=0=CRC-8=1byte
#define NRF_RCD_CRC16               1<<2    // bit2=CRCO=1=CRC-16=2byte
#define NRF_RCD_PWR_DOWN            0<<1    // bit1=PWR_UP=0=电源关闭模式
#define NRF_RCD_PWR_UP              1<<1    // bit1=PWR_UP=1=电源开启模式
#define NRF_RCD_PRIM_PRX            1       // bit0=PRIM_RX=1=接收模式
#define NRF_RCD_PRIM_PTX            0       // bit0=PRIM_RX=0=发送模式

// 0x01 EN_AA   使能自动应答
#define NRF_RCD_ALL_PIPE_AA_DI      0       // bit5:0=000000=禁用全部通道的AA
#define NRF_RCD_PIPE5_AA_DI         0<<5    // bit5=ENAA_P5=0=禁用通道5的AA(Auto Ack自动应答)
#define NRF_RCD_PIPE5_AA_EN         1<<5    // bit5=ENAA_P5=1=启用通道5的AA
#define NRF_RCD_PIPE4_AA_DI         0<<4    // bit4=ENAA_P4=0=禁用通道4的AA
#define NRF_RCD_PIPE4_AA_EN         1<<4    // bit4=ENAA_P4=1=启用通道4的AA
#define NRF_RCD_PIPE3_AA_DI         0<<3    // bit3=ENAA_P3=0=禁用通道3的AA
#define NRF_RCD_PIPE3_AA_EN         1<<3    // bit3=ENAA_P3=1=启用通道3的AA
#define NRF_RCD_PIPE2_AA_DI         0<<2    // bit2=ENAA_P2=0=禁用通道2的AA
#define NRF_RCD_PIPE2_AA_EN         1<<2    // bit2=ENAA_P2=1=启用通道2的AA
#define NRF_RCD_PIPE1_AA_DI         0<<1    // bit1=ENAA_P1=0=禁用通道1的AA
#define NRF_RCD_PIPE1_AA_EN         1<<1    // bit1=ENAA_P1=1=启用通道1的AA
#define NRF_RCD_PIPE0_AA_DI         0       // bit0=ENAA_P0=0=禁用通道0的AA
#define NRF_RCD_PIPE0_AA_EN         1       // bit0=ENAA_P0=1=启用通道0的AA

// 0x02 EN_RXADDR   使能RX数据通道
#define NRF_RCD_PIPE5_RX_DI         0<<5    // bit5=ERX_P5=0=禁用通道5
#define NRF_RCD_PIPE5_RX_EN         1<<5    // bit5=ERX_P5=1=启用通道5
#define NRF_RCD_PIPE4_RX_DI         0<<4    // bit4=ERX_P4=0=禁用通道4
#define NRF_RCD_PIPE4_RX_EN         1<<4    // bit4=ERX_P4=1=启用通道4
#define NRF_RCD_PIPE3_RX_DI         0<<3    // bit3=ERX_P3=0=禁用通道3
#define NRF_RCD_PIPE3_RX_EN         1<<3    // bit3=ERX_P3=1=启用通道3
#define NRF_RCD_PIPE2_RX_DI         0<<2    // bit2=ERX_P2=0=禁用通道2
#define NRF_RCD_PIPE2_RX_EN         1<<2    // bit2=ERX_P2=1=启用通道2
#define NRF_RCD_PIPE1_RX_DI         0<<1    // bit1=ERX_P1=0=禁用通道1
#define NRF_RCD_PIPE1_RX_EN         1<<1    // bit1=ERX_P1=1=启用通道1
#define NRF_RCD_PIPE0_RX_DI         0       // bit0=ERX_P0=0=禁用通道0
#define NRF_RCD_PIPE0_RX_EN         1       // bit0=ERX_P0=1=启用通道0

// 0x03 SETUP_AW    设置地址宽度
#define NRF_RCD_AW_3byte            1       // bit1:0=01=地址宽度为3byte
#define NRF_RCD_AW_4byte            2       // bit1:0=10=地址宽度为4byte
#define NRF_RCD_AW_5byte            3       // bit1:0=11=地址宽度为5byte

// 0x04 SETUP_RETR  设置自动重发
#define NRF_RCD_ARD_250us           0<<4    // bit7:4=0000=自动重发延时为250us
#define NRF_RCD_ARD_500us           1<<4    // bit7:4=0001=自动重发延时为500us
#define NRF_RCD_ARD_750us           2<<4    // bit7:4=0010=自动重发延时为750us
#define NRF_RCD_ARD_1000us          3<<4    // bit7:4=0011=自动重发延时为1000us
#define NRF_RCD_ARD_1250us          4<<4    // bit7:4=0100=自动重发延时为1250us
#define NRF_RCD_ARD_1500us          5<<4    // bit7:4=0101=自动重发延时为1500us
#define NRF_RCD_ARD_1750us          6<<4    // bit7:4=0110=自动重发延时为1750us
#define NRF_RCD_ARD_2000us          7<<4    // bit7:4=0111=自动重发延时为2000us
#define NRF_RCD_ARD_2250us          8<<4    // bit7:4=1000=自动重发延时为2250us
#define NRF_RCD_ARD_2500us          9<<4    // bit7:4=1001=自动重发延时为2500us
#define NRF_RCD_ARD_2750us          10<<4   // bit7:4=1010=自动重发延时为2750us
#define NRF_RCD_ARD_3000us          11<<4   // bit7:4=1011=自动重发延时为3000us
#define NRF_RCD_ARD_3250us          12<<4   // bit7:4=1100=自动重发延时为3250us
#define NRF_RCD_ARD_3500us          13<<4   // bit7:4=1101=自动重发延时为3500us
#define NRF_RCD_ARD_3750us          14<<4   // bit7:4=1110=自动重发延时为3750us
#define NRF_RCD_ARD_4000us          15<<4   // bit7:4=1111=自动重发延时为4000us
#define NRF_RCD_ARC_DI              0       // bit3:0=0000=禁用自动重发
#define NRF_RCD_ARC_1               1       // bit3:0=0001=自动重发1次
#define NRF_RCD_ARC_2               2       // bit3:0=0010=自动重发2次
#define NRF_RCD_ARC_3               3       // bit3:0=0011=自动重发3次
#define NRF_RCD_ARC_4               4       // bit3:0=0100=自动重发4次
#define NRF_RCD_ARC_5               5       // bit3:0=0101=自动重发5次
#define NRF_RCD_ARC_6               6       // bit3:0=0110=自动重发6次
#define NRF_RCD_ARC_7               7       // bit3:0=0111=自动重发7次
#define NRF_RCD_ARC_8               8       // bit3:0=1000=自动重发8次
#define NRF_RCD_ARC_9               9       // bit3:0=1001=自动重发9次
#define NRF_RCD_ARC_10              10      // bit3:0=1010=自动重发10次
#define NRF_RCD_ARC_11              11      // bit3:0=1011=自动重发11次
#define NRF_RCD_ARC_12              12      // bit3:0=1100=自动重发12次
#define NRF_RCD_ARC_13              13      // bit3:0=1101=自动重发13次
#define NRF_RCD_ARC_14              14      // bit3:0=1110=自动重发14次
#define NRF_RCD_ARC_15              15      // bit3:0=1111=自动重发15次

// 0x05 RF_CH   频道设置    (Freq=2400+RF_CH[MHz],2400~2525MHz)
#define NRF_RCD_RF_CH_max           125     // bit6:0   工作频率最大值
#define NRF_RCD_RF_CH_min           0       // bit6:0   工作频率最小值

// 0x06 RF_SETUP    RF设置
#define NRF_RCD_CONT_WAVE_DI        0<<7    // bit7=CONT_WAVE=0=禁用连续载波传送
#define NRF_RCD_CONT_WAVE_EN        1<<7    // bit7=CONT_WAVE=1=启用连续载波传送
#define NRF_RCD_RF_DR_250kbps       4<<3    // bit5&bit3=10=250kbps
#define NRF_RCD_RF_DR_1Mbps         0<<3    // bit5&bit3=00=1Mbps
#define NRF_RCD_RF_DR_2Mbps         1<<3    // bit5&bit3=01=2Mbps
#define NRF_RCD_PLL_LOCK_DI         0<<4    // bit4=PLL_LOCK=0=不锁定PLL
#define NRF_RCD_PLL_LOCK_EN         1<<4    // bit4=PLL_LOCK=1=锁定PLL
#define NRF_RCD_RF_PWR_0dBm         3<<1    // bit2:1=RF_PWR=11=0dBm
#define NRF_RCD_RF_PWR_n6dBm        2<<1    // bit2:1=RF_PWR=10=-6dBm
#define NRF_RCD_RF_PWR_n12dBm       1<<1    // bit2:1=RF_PWR=01=-12dBm
#define NRF_RCD_RF_PWR_n18dBm       0<<1    // bit2:1=RF_PWR=00=-18dBm

// 0x07 STATUS  状态
#define NRF_RCD_RX_DR               1<<6    // bit6=1=RX_DR=数据接收完成中断(写1清除)
#define NRF_RCD_TX_DR               1<<5    // bit5=1=TX_DR=数据发送完成中断(写1清除)
#define NRF_RCD_MAX_RT              1<<4    // bit4=1=MAX_RT=重发上限中断(写1清除)
#define NRF_RCD_RX_PIPE0_DR         0<<1    // bit3:1=000=接收到的数据包为通道0
#define NRF_RCD_RX_PIPE1_DR         1<<1    // bit3:1=001=接收到的数据包为通道1
#define NRF_RCD_RX_PIPE2_DR         2<<1    // bit3:1=010=接收到的数据包为通道2
#define NRF_RCD_RX_PIPE3_DR         3<<1    // bit3:1=011=接收到的数据包为通道3
#define NRF_RCD_RX_PIPE4_DR         4<<1    // bit3:1=100=接收到的数据包为通道4
#define NRF_RCD_RX_PIPE5_DR         5<<1    // bit3:1=101=接收到的数据包为通道5
#define NRF_RCD_RX_FIFO_EMPTY       7<<1    // bit3:1=111=RX FIFO为空
#define NRF_RCD_TX_FIFO_FULL        1       // bit0=1=TX FIFO已满

// 0x08 OBSERVE_TX  发送监测
#define NRF_RCD_PLOS_CNT_MAX        15      // bit7:4   丢包计数器最大值    
#define NRF_RCD_PLOS_CNT_MIN        0       // bit7:4   丢包计数器最小值
#define NRF_RCD_ARC_CNT_MAX         15      // bit3:0   重发计数器最大值    
#define NRF_RCD_ARC_CNT_MIN         0       // bit3:0   重发计数器最小值

// 0x09 RPD 接收功率监测
#define NRF_RCD_RPD_n64dBm_UP       1       // bit0=1=接收功率>=-64dBm
#define NRF_RCD_RPD_n64dbm_DOWN     0       // bit0=0=接收功率<-64dBm

// 0x11 RX_PW_PX    接收通道X数据宽度
#define NRF_RCD_RX_PW_PX_MAX        32      // bit5:0    通道X数据宽度最大值
#define NRF_RCD_RX_PW_PX_MIN        1       // bit5:0    通道X数据宽度最小值
#define NRF_RCD_RX_PW_PX_DI         0       // bit5:0    通道X未使用

// 0x17 FIFO_STATUS FIFO状态
#define NRF_RCD_TX_REUSE            1<<6    // bit6=1=设备处于重发模式
#define NRF_RCD_TX_FIFO_S_FULL      1<<5    // bit5=1=TX FIFO已满
#define NRF_RCD_TX_FIFO_S_EMPTY     1<<4    // bit4=1=TX FIFO无数据
#define NRF_RCD_RX_FIFO_S_FULL      1<<1    // bit1=1=RX FIFO已满
#define NRF_RCD_RX_FIFO_S_EMPTY     1       // bit0=1=RX FIFO无数据

// 0x1C Enable dynamic payload length   使能动态数据包长度
#define NRF_RCD_PIPE5_DPL_EN        1<<5    // bit5=1=开启通道5的动态数据包长度
#define NRF_RCD_PIPE5_DPL_DI        0<<5    // bit5=0=关闭通道5的动态数据包长度
#define NRF_RCD_PIPE4_DPL_EN        1<<4    // bit4=1=开启通道4的动态数据包长度
#define NRF_RCD_PIPE4_DPL_DI        0<<4    // bit4=0=关闭通道4的动态数据包长度
#define NRF_RCD_PIPE3_DPL_EN        1<<3    // bit3=1=开启通道3的动态数据包长度
#define NRF_RCD_PIPE3_DPL_DI        0<<3    // bit3=0=关闭通道3的动态数据包长度
#define NRF_RCD_PIPE2_DPL_EN        1<<2    // bit2=1=开启通道2的动态数据包长度
#define NRF_RCD_PIPE2_DPL_DI        0<<2    // bit2=0=关闭通道2的动态数据包长度
#define NRF_RCD_PIPE1_DPL_EN        1<<1    // bit1=1=开启通道1的动态数据包长度
#define NRF_RCD_PIPE1_DPL_DI        0<<1    // bit1=0=关闭通道1的动态数据包长度
#define NRF_RCD_PIPE0_DPL_EN        1       // bit0=1=开启通道0的动态数据包长度
#define NRF_RCD_PIPE0_DPL_DI        0       // bit0=0=关闭通道0的动态数据包长度

// 0x1D Feature Register    特征寄存器
#define NRF_RCD_DPL_EN              1<<2    // bit2=1=允许动态数据包长度
#define NRF_RCD_DPL_DI              0<<2    // bit2=0=禁止动态数据包长度
#define NRF_RCD_ACK_PAY_EN          1<<1    // bit1=1=允许带ACK的数据
#define NRF_RCD_ACK_PAY_DI          0<<1    // bit1=0=禁止带ACK的数据
#define NRF_RCD_DYN_ACK_PAY_EN      1       // bit1=1=允许无ACK的数据
#define NRF_RCD_DYN_ACK_PAY_DI      0       // bit1=0=禁止无ACK的数据





#define NRF_RF_CH       0                   // RF射频通道 0~125
#define	NRF_ADDR_WIDTH  5                   // RF地址宽度 1~5byte
#define NRF_DATA_WIDTH  32                  // RF数据宽度 1~32byte


//-------宏定义引脚--------
//使用的是模拟SPI，引脚可以在这里随意更换
#define NRF_CE_PIN          B17
#define NRF_CSN_PIN         B21
#define NRF_MOSI_PIN        B29
#define NRF_SCK_PIN         B22
                            
#define NRF_MISO_PIN        B14
#define NRF_IRQ_PIN         B15



// 用户变量 
extern uint8 nrf_rx_buff[];                 // 接收数据缓冲区
extern uint8 nrf_tx_buff[];                 // 发送数据缓冲区


// 用户函数
void  nrf_init(void);
void  nrf_send_packet(uint8*);
uint8 nrf_rece_packet(uint8*);


#endif

