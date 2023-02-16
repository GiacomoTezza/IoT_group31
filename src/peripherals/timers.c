#include "include/peripherals.h"

void init_timer(void)
{
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
}

bool is_debouncing(void)
{
    return Timer32_getValue(TIMER32_0_BASE) != 0;
}

void debounce_button(void)
{
    Timer32_setCount(TIMER32_0_BASE, SMCLK_FREQUENCY / 4);
    Timer32_startTimer(TIMER32_0_BASE, true);
}
