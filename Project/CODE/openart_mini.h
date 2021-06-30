#ifndef _openartart_mini_h
#define _openartart_mini_h

#include "headfile.h"


typedef struct openart_param_t
{
    int8_t openart_result;
    int16_t openart_buff[2];
    enum{
        OFF_MODE,TAG_MODE, NUM_MODE, OBJ_MODE,FA_MODE,
    } openart_mode;
} openart_param_t;




void openart_send(void);
void openart_mini(void);

#endif
