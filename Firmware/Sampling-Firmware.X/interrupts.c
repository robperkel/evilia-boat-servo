#include "interrupts.h"

#include <xc.h>

//Initializes vector interrupts on the devices
void Interrupts_init(void)
{
    
}

//Enables interrupts on the device
void Interrupts_enable(void)
{
    INTCON0bits.GIE = 1;
}

void __interrupt(irq(default)) DEFAULT_ISR(void)
{

}
