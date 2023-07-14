#include "TMR2.h"

#include <xc.h>

static void (*TMR2Overflow)(void) = 0;

//Init TMR2
void TMR2_init(void)
{
    
}

//Start TMR2
void TMR2_start(void)
{
    T2CONbits.ON = 1;
}

//Stop TMR2
void TMR2_stop(void)
{
    T2CONbits.ON = 0;
}

//Set the period of TMR2
void TMR2_setPeriod(uint8_t period)
{
    T2PR = period;
}

//Get the period of TMR2
uint8_t TMR2_getPeriod(void)
{
    return T2PR;
}

//Sets the callback function for timer overflow
void TMR2_setCallback(void (*callback)(void))
{
    TMR2Overflow = callback;
}