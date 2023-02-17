#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

#define SMCLK_FREQUENCY     3000000

void init_timer(void);

void delayMs(int n);

void debounce_button(void);

bool is_debouncing(void);

void init_GPIO();

void moveServo(float angle);

#endif
