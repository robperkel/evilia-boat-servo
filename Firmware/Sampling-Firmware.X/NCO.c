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
    //2^20 / 31000 * 2 = ~68
    //About 1s period
    NCO1INC = 68;
    
    //Clear flag
    PIR6bits.NCO1IF = 0;
    
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

//Note: Do not use IRQ_NCO1 with PIC18F-Q_DFP v1.17.379
//The wrong IRQ number is assigned to this macro
void __interrupt(irq(51)) NCO_onOverflow(void)
{
    if (NCO_callback)
    {
        NCO_callback();
    }
    
    //Clear NCO Interrupt
    PIR6bits.NCO1IF = 0;
}
