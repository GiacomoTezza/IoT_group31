#include "include/peripherals.h"

void PORT1_IRQHandler(void) {
    /* Check which pins generated the interrupts */
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    /* clear interrupt flag (to clear pending interrupt indicator) */
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
    /* check if we received P1.6 or P1.4 interrupt */
    if((status & GPIO_PIN6) || (status & GPIO_PIN4)){
        /* Toggling the output on the LED */
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
}
