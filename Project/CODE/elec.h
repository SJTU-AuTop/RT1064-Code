#ifndef _elec_h
#define _elec_h

#include "headfile.h"

extern int enable_adc;
extern uint16 elec_data[2];

void elec_init(void);

void elec_get(void);

void elec_calculate(void);

#endif