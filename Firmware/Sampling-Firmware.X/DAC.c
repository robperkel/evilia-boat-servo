#include "DAC.h"

#include <stdint.h>
#include <xc.h>

//Init DAC2
void DAC2_init(void)
{
    //FVR Reference, with VSS as negative reference
    DAC2CON = 0x00;
    DAC2CONbits.PSS = 0b10;
    
    DAC2DAT = 0x00;
    
    //Enable the DAC
    DAC2CONbits.EN = 1;
}

//Set the output of DAC2
void DAC2_setValue(uint8_t val)
{
    DAC2DAT = val;
}

//Get the value of DAC2
uint8_t DAC2_getValue(void)
{
    return DAC2DAT;
}
