#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdint.h>

enum timeIds {HOURS = 4, MINUTES= 2, SECONDS= 0};

extern uint8_t getCurrentTime(enum timeIds id);

#endif