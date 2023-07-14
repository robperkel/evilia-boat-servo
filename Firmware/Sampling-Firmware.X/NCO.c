#include "NCO.h"
#include "interrupts.h"

#include <xc.h>

static void (*NCO_callback)(void) = 0;

//Init the NCO Peripheral
void NCO_init(void)
{
    //Fixed Duty Cycle Mode (FDC)
    NCO1CON = 0x00;
    
    //1 Clock Cycle Active, LFINTOSC (31 kHz)
    NCO1CLK = 0x00;
    NCO1CLKbits.CKS = 0b0010;
    
    //Increment Value
    //(0x01000000 (16,777,216) / 31,000 ) * 2 [Due to FDC] = ~1042
    //About 1s period
    NCO1INC = 1042;
    
    //Enable NCO Interrupt
    PIE6bits.NCO1IE = 1;
    
    //Enable NCO
    NCO1CONbits.EN = 0b1;
}

//Set the callback for the NCO
void NCO_setCallback(void (*callback)(void))
{
    NCO_callback = callback;
    
}

void __interrupt(irq(NCO1), base(INTERRUPT_BASE)) NCO_onOverflow(void)
{
    if (NCO_callback)
    {
        NCO_callback();
    }
    
    //Clear NCO Interrupt
    PIR6bits.NCO1IF = 0;
}
