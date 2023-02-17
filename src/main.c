#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "include/peripherals.h"
#include <stdio.h>

void _hw_init(void) {
    init_timer();
    init_GPIO();

    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableMaster();
}

int main(void) {
    _hw_init();

    moveServo(30);
    delayMs(100);
    moveServo(0);

    while(1) {
        PCM_gotoLPM0();
    }
}
