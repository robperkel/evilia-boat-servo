#include "FVR.h"

#include <xc.h>

//Initializes the FVR
void FVR_init(void)
{
    FVRCON = 0x00;
    
    //Enable the FVR
    FVRCONbits.EN = 1;
}

//Sets the FVR output to the ADC
void FVR_setADCRef(VoltageReferenceConfiguration config)
{
    FVRCONbits.ADFVR = config;
}