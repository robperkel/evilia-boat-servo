#include "TMR2.h"
#include "GPIO_Macros.h"

#include <xc.h>

static void (*TMR2Overflow)(void) = 0;

//Init TMR2
void TMR2_init(void)
{
    //No prescaler, no postscaler
    T2CON = 0x00;
    
    //Sync. to Fosc/4, Rising Edge Count, Sync. to ON, mode = one-shot
    T2HLT = 0x00;
//    T2HLTbits.CKSYNC = 1;
//    T2HLTbits.PSYNC = 1;
    T2HLTbits.MODE = 0b01000;
    
    //NCO1
    T2CLKCON = 0x00;
    T2CLKCONbits.CS = 0b1010;
    
    //No External Reset
    T2RST = 0x00;
    
    //Period of Timer2 
    T2PR = DEFAULT_TMR2_PERIOD;
    
    //Clear TMR2 Flag
    PIR3bits.TMR2IF = 0;
    
    //Enable TMR2 Interrupt
    PIE3bits.TMR2IE = 1;
}

//Start TMR2
void TMR2_start(void)
{
    //If set to 0x00 - disable timeout
    if (T2PR != 0x00)
        T2CONbits.ON = 1;
}

//Stop TMR2
void TMR2_stop(void)
{
    T2CONbits.ON = 0;
    T2TMR = 0x00;
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

void __interrupt(irq(IRQ_TMR2)) TMR2_onOverflow(void)
{
    if (TMR2Overflow)
    {
        TMR2Overflow();
    }
    
    //Clear TMR2 Interrupt
    PIR3bits.TMR2IF = 0;
}
