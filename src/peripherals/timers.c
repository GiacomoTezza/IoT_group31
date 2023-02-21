#include "include/peripherals.h"

void init_timer(void) {
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Initializes Clock System */
//    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
//    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
//    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
//    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
//    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Debouncer */
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, SMCLK_FREQUENCY / 4);
    Timer32_startTimer(TIMER32_0_BASE, true);

    /* configure TimerA0.4 as PWM */
    TIMER_A0->CCR[0] = 60000 - 1;   /* PWM Period (3Mhz/60k=50hz) */
    TIMER_A0->CCTL[4] = 0xE0;       /* CCR4 reset/set mode */
    TIMER_A0->CTL = 0x0214;         /* use SMCLK, count up, clear TA0R register */
}

bool is_debouncing(void) {
    return Timer32_getValue(TIMER32_0_BASE) != 0;
}

void debounce_button(void) {
    Timer32_setCount(TIMER32_0_BASE, SMCLK_FREQUENCY / 4);
    Timer32_startTimer(TIMER32_0_BASE, true);
}

/* system clock at 3 MHz, MSP432P401R Rev. C, Start-up v2.2.1 */
void delayMs(int n) {
    int  i, j;

    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      /* Delay */
}
