#ifndef _FLASH_PARAM_H_
#define _FLASH_PARAM_H_

// 可调参数写入flash

#include <stdint.h>
#include <stdbool.h>


//
extern float thres;
extern float block_size;
extern float clip_value;
extern float begin_x;
extern float begin_y;
extern float line_blur_kernel;
extern float pixel_per_meter;
extern float sample_dist;
extern float angle_dist;
extern float aim_distance;          // ???????
extern float far_rate;



void flash_param_init();

bool flash_param_check();

void flash_param_load();

void flash_param_write();

#endif /* _FLASH_PARAM_H_ */