#include "FVR.h"

#include <xc.h>

//Initializes the FVR
void FVR_init(void)
{
    //1.024V reference for the DAC
    FVRCON = 0x00;
    FVRCONbits.CDAFVR = 0b01;
    
    //Enable the FVR
    FVRCONbits.EN = 1;
}

//Sets the FVR output to the ADC
void FVR_setADCRef(VoltageReferenceConfiguration config)
{
    FVRCONbits.ADFVR = config;
}