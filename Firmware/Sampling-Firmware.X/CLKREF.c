#include "CLKREF.h"

#include <xc.h>

//Init CLKREF
void CLKREF_init(void)
{
    //Select 16x divider, 50% duty cycle
    CLKRCON = 0x00;
    CLKRCONbits.DIV = 0b100;
    CLKRCONbits.DC = 0b10;
    
    //Select MFINTOSC (32 kHz)
    CLKRCLK = 0b0100;
    
    //Enable Module
    CLKRCONbits.EN = 1;
}
