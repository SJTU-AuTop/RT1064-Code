/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		TFT
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		
					接线定义：
					------------------------------------ 
						模块管脚            单片机管脚
						SCL                 查看TFT_SCL宏定义的引脚     硬件SPI引脚不可随意切换
						SDA                 查看TFT_SDA宏定义的引脚     硬件SPI引脚不可随意切换
						RES                 查看REST_PIN宏定义的引脚    
						DC                  查看DC_PIN宏定义的引脚  
						CS                  查看TFT_CS宏定义的引脚      硬件SPI引脚不可随意切换
						
						电源引脚
						BL  3.3V电源（背光控制引脚，也可以接PWM来控制亮度）
						VCC 3.3V电源
						GND 电源地
						最大分辨率128*160
					------------------------------------ 

 ********************************************************************************************************************/



#ifndef _SEEKFREE_18TFT_h
#define _SEEKFREE_18TFT_h

#include "common.h"
#include "SEEKFREE_FONT.h"


//-----------------引脚定义------------------------------
#define TFT_SPIN    SPI_3           //定义使用的SPI号
#define TFT_SCL     SPI3_SCK_B0    //定义SPI_SCK引脚
#define TFT_SDA     SPI3_MOSI_B1   //定义SPI_MOSI引脚
#define TFT_SDA_IN  SPI3_MISO_B2   //定义SPI_MISO引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#define TFT_CS      SPI3_CS0_B3    //定义SPI_CS引脚
                    
#define BL_PIN		C18	            //液晶背光引脚定义  
#define REST_PIN	B2              //液晶复位引脚定义 由于实际通讯未使用D15因此 这里复用为GPIO
#define DC_PIN		C19	            //液晶命令位引脚定义



     
#define DC(x)   	gpio_set(DC_PIN,x)
#define REST(x) 	gpio_set(REST_PIN,x)




//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	    0xF800	//红色
//#define BLUE         	    0x001F  //蓝色
//#define YELLOW       	    0xFFE0	//黄色
//#define GREEN        	    0x07E0	//绿色
//#define WHITE        	    0xFFFF	//白色
//#define BLACK        	    0x0000	//黑色 
//#define GRAY  			0X8430 	//灰色
//#define BROWN 			0XBC40 	//棕色
//#define PURPLE    		0XF81F	//紫色
//#define PINK    		    0XFE19	//粉色



//定义写字笔的颜色
#define TFT_PENCOLOR    RED

//定义背景颜色
#define TFT_BGCOLOR	    WHITE

     
     
//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define TFT_DISPLAY_DIR 3

#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
#define	TFT_X_MAX	128	//液晶X方宽度
#define TFT_Y_MAX	160 //液晶Y方宽度
     
#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
#define	TFT_X_MAX	160	//液晶X方宽度
#define TFT_Y_MAX	128 //液晶Y方宽度
     
#else
#error "TFT_DISPLAY_DIR 定义错误"
     
#endif


void lcd_init(void);
void lcd_clear(int color);
void lcd_drawpoint(uint16 x,uint16 y,uint16 color);
void lcd_showchar(uint16 x,uint16 y,const int8 dat);
void lcd_showstr(uint16 x,uint16 y,const int8 dat[]);
void lcd_showint8(uint16 x,uint16 y,int8 dat);
void lcd_showuint8(uint16 x,uint16 y,uint8 dat);
void lcd_showint16(uint16 x,uint16 y,int16 dat);
void lcd_showuint16(uint16 x,uint16 y,uint16 dat);
void lcd_showint32(uint16 x,uint16 y,int32 dat,uint8 num);
void lcd_showfloat(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);
void showimage(const unsigned char *p);
void lcd_displayimage032(uint8 *p, uint16 width, uint16 height);
void lcd_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void lcd_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void lcd_displayimage7725(uint8 *p, uint16 width, uint16 height);
void lcd_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);


#endif
