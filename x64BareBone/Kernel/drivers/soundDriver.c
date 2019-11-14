#include <soundDriver.h>
#include <stdint.h>
#include <lib.h>
#include <timerTick.h>
#include <interrupts.h>

static void timer_wait(int waitTime);
//Source: https://wiki.osdev.org/PC_Speaker
//Play sound using built in speaker
 
//Make a beep
void beep(){
 	playSound(1000);
 	timer_wait(2);
 	noSound();
}

static void timer_wait(int waitTime){
	int initialTime = ticks_elapsed();
	while (ticks_elapsed() < (initialTime + waitTime));
}