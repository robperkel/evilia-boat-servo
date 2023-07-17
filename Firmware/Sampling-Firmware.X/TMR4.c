#include "TMR4.h"
#include "GPIO_Macros.h"

#include <xc.h>

static void (*TMR4Overflow)(void) = 0;

//Init TMR4
void TMR4_init(void)
{
    //No prescaler, no postscaler
    T4CON = 0x00;
    
    //Sync. to Fosc/4, Rising Edge Count, Sync. to ON, mode = one-shot
    T4HLT = 0x00;
//    T4HLTbits.CKSYNC = 1;
//    T4HLTbits.PSYNC = 1;
    T4HLTbits.MODE = 0b01000;
    
    //NCO1
    T4CLKCON = 0x00;
    T4CLKCONbits.CS = 0b1010;
    
    //No External Reset
    T4RST = 0x00;
    
    //Period of Timer4 
    T4PR = DEFAULT_TMR4_PERIOD;
    
    //Clear TMR4 Flag
    PIR10bits.TMR4IF = 0;
    
    //Enable TMR4 Interrupt
    PIE10bits.TMR4IE = 1;
}

//Start TMR4
void TMR4_start(void)
{
    //If set to 0x00 - disable timeout
    if (T4PR != 0x00)
        T4CONbits.ON = 1;
}

//Stop TMR4
void TMR4_stop(void)
{
    T4CONbits.ON = 0;
    T4TMR = 0x00;
}

//Set the period of TMR4
void TMR4_setPeriod(uint8_t period)
{
    T4PR = period;
}

//Get the period of TMR4
uint8_t TMR4_getPeriod(void)
{
    return T4PR;
}

//Sets the callback function for timer overflow
void TMR4_setCallback(void (*callback)(void))
{
    TMR4Overflow = callback;
}

void __interrupt(irq(IRQ_TMR4)) TMR4_onOverflow(void)
{
    if (TMR4Overflow)
    {
        TMR4Overflow();
    }
    
    //Clear TMR4 Interrupt
    PIR10bits.TMR4IF = 0;
}

