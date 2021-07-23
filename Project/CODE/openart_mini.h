#ifndef _openartart_mini_h
#define _openartart_mini_h

#include "headfile.h"


typedef struct openart_param_t
{
    int8_t rx_array[5];     //存储串口接受数据
    int8_t openart_result;  //结果
    int32_t receiver_time; 
    
    int8_t fa_num[2];
    int32_t animaltime;     //识别到动物时间，停车计时
    int32_t aprilencoder;
    int32_t aprilwaitencoder;
    enum{
        NONE,ANIMAL,FRUIT,
    } fa_type;
    
    enum{
        OFF_MODE,TAG_MODE, NUM_MODE, OBJ_MODE,FA_MODE,
    } openart_mode;
    
} openart_param_t;


extern openart_param_t openart;


void openart_send(void);
void openart_mini(void);
void check_openart(void);

#endif

