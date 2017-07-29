#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__


#include "common.h"
#include "include.h"

#define US_ECHO PTD2
#define US_TRIG PTD1

void ultrasonic_init();
void ultrasonic_start();
void PORTD_IRQHandler(void);

extern uint32 UltraSonicDistance;

#endif