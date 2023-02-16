#include "include/peripherals.h"

void init_GPIO() {
    /* P1.0 as output led */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /* P1.6 as input */
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P1, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN6);

    /* P1.4 as input for button DEBUG ONLY*/
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
}
