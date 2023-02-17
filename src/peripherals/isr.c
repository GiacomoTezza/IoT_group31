#include "include/peripherals.h"

void PORT1_IRQHandler(void) {
    /* Check which pins generated the interrupts */
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    /* clear interrupt flag (to clear pending interrupt indicator) */
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (is_debouncing()) {
        return;
    }

    /* check if we received P1.6 or P1.4 interrupt */
    if(((status & GPIO_PIN6)) || (status & GPIO_PIN4)) {
        debounce_button();
        /* Toggling the output on the LED */
        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN6) == GPIO_INPUT_PIN_HIGH) {
            printf("up\n");
        }
        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN6) == GPIO_INPUT_PIN_LOW) {
            printf("down\n");
        }
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

        moveServo(90);
        delayMs(500);
        moveServo(0);
    }
}
