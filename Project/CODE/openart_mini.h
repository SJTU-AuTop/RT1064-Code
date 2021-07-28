#ifndef _openartart_mini_h
#define _openartart_mini_h

#include "headfile.h"


typedef struct openart_param_t {
    int8_t rx_array[5];     //存储串口接受数据
    int8_t openart_result;  //结果
    int32_t receiver_time;

    float fruit_delta;      // 水果打靶的角度偏差

    enum {
        TAG_NONE, TAG_SEARCH, TAG_STOP, TAG_SHOOTING
    } tag_type;

    int8_t fa_num[2];
    int32_t animaltime;     // 识别到动物时间，停车计时
    int32_t fruittime;      // 识别到水果计时，避免无限制的尝试打靶
    int32_t aprilencoder;
    int32_t aprilwaitencoder;
    enum {
        NONE, ANIMAL, FRUIT,
    } fa_type;              // 靶牌分类结果

    enum {
        OFF_MODE, TAG_MODE, NUM_MODE, OBJ_MODE, FA_MODE,
    } openart_mode;         // openart识别模式

} openart_param_t;


extern openart_param_t openart;

void openart_send(void);

void openart_mini(void);

void check_openart(void);

#endif

