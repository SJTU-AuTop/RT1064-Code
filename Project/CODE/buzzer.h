#ifndef _buzzer_h
#define _buzzer_h

#include "headfile.h"

extern rt_mailbox_t buzzer_mailbox;

void buzzer_init(void);

#endif