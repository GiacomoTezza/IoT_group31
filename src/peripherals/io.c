#include "include/peripherals.h"

void init_GPIO() {
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    /* P1.0 as output led */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /* P1.6 as input */
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P1, GPIO_PIN6);
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN6);

    /* P1.4 as input for button DEBUG ONLY*/
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
}

void moveServo(float angle) {
    if (angle >= 0 && angle <= 180) {
        int value = angle/180 * (7500-1500) + 1500;
        TIMER_A0->CCR[4] = value;
    } else {
        printf("Not a valid angle\n");
    }
}
