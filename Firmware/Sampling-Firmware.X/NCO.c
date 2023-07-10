#include "NCO.h"

#include <xc.h>

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
    
    NCO1CONbits.EN = 0b1;
}
