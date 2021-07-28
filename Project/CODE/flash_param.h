#ifndef _FLASH_PARAM_H_
#define _FLASH_PARAM_H_

// 可调参数写入flash

#include <stdint.h>
#include <stdbool.h>


//
extern float thres;                 // 二值化阈值，主要用于找起始点(边线使用自适应阈值，不使用该阈值)
extern float block_size;            // 自适应阈值的block大小
extern float clip_value;            // 自适应阈值的阈值裁减量
extern float begin_x;               // 起始点距离图像中心的左右偏移量
extern float begin_y;               // 起始点距离图像底部的上下偏移量
extern float line_blur_kernel;      // 边线三角滤波核的大小
extern float pixel_per_meter;       // 俯视图中，每个像素对应的长度
extern float sample_dist;           // 边线等距采样的间距
extern float angle_dist;            // 计算边线转角时，三个计算点的距离
extern float aim_distance;          // 预锚点长度
extern float far_rate;              //
extern bool adc_cross;              // 是否启用电感过十字


void flash_param_init();

bool flash_param_check();

void flash_param_load();

void flash_param_write();

#endif /* _FLASH_PARAM_H_ */