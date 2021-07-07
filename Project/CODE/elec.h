#ifndef _elec_h
#define _elec_h

#include "headfile.h"

extern bool enable_adc;

void elec_init(void);
void elec_get(void);
void elec_calculate(void);

#endif