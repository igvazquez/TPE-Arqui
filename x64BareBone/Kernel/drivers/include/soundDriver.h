#ifndef __SOUND_DRIVER__
#define __SOUND_DRIVER__
#include <stdint.h>
void beep();

extern void noSound();
 
extern void playSound(uint32_t nFrequence);

#endif