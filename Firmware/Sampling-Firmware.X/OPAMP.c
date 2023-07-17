#include <xc.h>

#include <stdint.h>
#include <stdbool.h>

#include "OPAMP.h"
#include "SW_Registers_Types.h"

//Init the OPAMP
void OPAMP_init(void)
{
    //Default to Unity Gain, enable charge pump
    OPA1CON0 = 0x00;
    OPA1CON0bits.UG = 1;
    OPA1CON0bits.CPON = 1;
    
    //Disable Resistor Ladder, NSS = VSS
    OPA1CON1 = 0x00;
    OPA1CON1bits.NSS = 0b111;
    
    //Select OPAxIN+
    OPA1CON2 = 0x00;
    OPA1CON2bits.PCH = 0b010;
    
    //Disconnect FMS, Select Analog Input 1
    OPA1CON3 = 0x00;
    OPA1CON3bits.FMS = 0b00;
    OPA1CON3bits.PSS = OPAMP_ANALOG_INPUT1;
    
    //Disable Hardware Override
    OPA1HWC = 0x00;
    
    //Enable the OPAMP
    OPA1CON0bits.EN = 1;
}
    
//Set the gain of the OPAMP
void OPAMP_setGainSettings(uint8_t val)
{
    GainConfigureRegister gain;
    gain.value = val;
    
    //Disable OPAMP
    OPA1CON0bits.EN = 0;
    
    if (gain.unityGain)
    {
        //Unity gain is set
        //Deinit the resistor ladder
        
        //Turn on unity gain
        OPA1CON0bits.UG = 1;
        
        //Disable resistor ladder
        OPA1CON1bits.RESON = 0;
        
        //Disconnect from resistor ladder
        OPA1CON2bits.NCH = 0b000;
        
        //Disable FMS 
        OPA1CON3bits.FMS = 0b00;
    }
    else
    {
        //Not unity gain
        //Init the resistor ladder
        
        //Clear the unity gain
        OPA1CON0bits.UG = 0;
        
        //Set the gain
        OPA1CON1bits.GSEL = gain.gainConfig;
        
        //Enable resistor ladder
        OPA1CON1bits.RESON = 1;
        
        //Connect to resistor ladder
        OPA1CON2bits.NCH = 0b001;
        
        //Enable FMS 
        OPA1CON3bits.FMS = 0b10;

    }
    
    //Re-enable OPAMP
    OPA1CON0bits.EN = 1;
}
