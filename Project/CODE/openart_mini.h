#ifndef _openartart_mini_h
#define _openartart_mini_h

#include "headfile.h"


typedef struct openart_param_t
{
    int8_t openart_result;   
    int32_t number_time;
    int32_t tag_time;
    int16_t openart_buff[2];   
    int32_t animaltime;
    int32_t numencoder;     
    int32_t apriltime;      
    int32_t aprilencoder;  
    enum{
        OFF_MODE,TAG_MODE, NUM_MODE, OBJ_MODE,FA_MODE,
    } openart_mode;
    
} openart_param_t;


extern openart_param_t openart;


void openart_send(void);
void openart_mini(void);
void check_openart(void);
void openart_putbuff(int32_t *array,int32_t input_dat);

#endif
