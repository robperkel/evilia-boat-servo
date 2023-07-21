#include "ADCC.h"
#include "SW_Registers_Types.h"
#include "FVR.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

static volatile AnalogConfigRegister config;
static volatile bool sampleReady = false; 

//Init the ADC
void ADCC_init(void)
{
    //Clock for ADC for ADCRC, right justified data
    ADCON0 = 0x00;
    ADCON0bits.CS = 1;
    ADCON0bits.FM = 1;
    
    //CVD is not used
    ADCON1 = 0x00;
    
    //Configured by ADCC_loadAnalogConfiguration
    ADCON2 = 0x00;
    
    //Always interrupt on threshold test
    ADCON3 = 0x00;
    ADCON3bits.TMD = 0b111;
    
    //Default VREF (configured later)
    ADREF = 0x00;
    
    //Set input channel to AN1 (after OPAMP)
    ADPCH = ADC_AN1_INPUT;
    
    //Pre-charge time (part of CVD)
    ADPRE = 0x00;
    
    //AQ Time
    //Min. OPAMP Output = 85%
    //OPAMP Output Impedance = 4.25V/10mA (max output current) = 425 ohms
    //To get AQ time, see Equation 40-1.. assume 60C temp max
    //2us (settling time) + 0.107us (charge time) + 1.75us (temp coeff.) = ~4us
    //ADCRC clock period is about 2us
    ADACQ = 2;

    //No extra capacitance
    ADCAP = 0x00;
    
    //Software Writes to ADPCH will trigger a conversion
    ADACT = 0b11001;
    
    //Charge pump is not needed (due to +5V supply)
    ADCP = 0x00;
    
    //Update Configuration Variables
    config.value = 0x00;
    config.averagingConfig = ADC_1_SAMPLE;
    config.voltageRefConfig = FVR_2V;
    
    //Load config settings
    ADCC_loadAnalogConfig(config.value);
    
    //Clear AD Threshold
    PIR2bits.ADTIF = 0;
    
    //Enable AD Threshold Interrupt
    PIE2bits.ADTIE = 1;
}

//Loads a new analog configuration
void ADCC_loadAnalogConfig(uint8_t nConfig)
{
    config.value = nConfig;
    
    //Turn off the ADC
    ADCON0bits.ON = 0;
    
    switch (config.averagingConfig)
    {
        case ADC_1_SAMPLE:
        {
            //Basic Mode - No Averaging
            ADRPT = 0x00;
            ADCON2bits.MD = 0b000;
            break;
        }
        case ADC_2_SAMPLES:
        {
            ADRPT = 2;
            ADCON2bits.MD = 0b011;
            ADCON2bits.CRS = 1;
            break;
        }
        case ADC_4_SAMPLES:
        {
            ADRPT = 4;
            ADCON2bits.MD = 0b011;
            ADCON2bits.CRS = 2;
            break;
        }
        case ADC_8_SAMPLES:
        {
            ADRPT = 8;
            ADCON2bits.MD = 0b011;
            ADCON2bits.CRS = 3;
            break;
        }
        case ADC_16_SAMPLES:
        {
            ADRPT = 16;
            ADCON2bits.MD = 0b011;
            ADCON2bits.CRS = 4;
            break;
        }
        default:
        {
            //Unknown Value
        }
    }
    
    //Modify the FVR settings
    FVR_setADCRef(config.voltageRefConfig);
    
    switch (config.voltageRefConfig)
    {
        case VDD:
        {
            //Select VDD
            ADREFbits.PREF = 0b00;
            break;
        }
        case FVR_1V:
        case FVR_2V:
        case FVR_4V:
        {
            //Select FVR for VREF 
            ADREFbits.PREF = 0b11;
            break;
        }
    }
    
    //Re-enable the ADC
    ADCON0bits.ON = 1;
}

//Gets the analog configuration of the ADCC
uint8_t ADCC_getAnalogConfig(void)
{
    return config.value;
}

//Sets the sampling channel and begins a conversion
void ADCC_setChannelAndGo(AnalogInput input)
{
    switch (input)
    {
        case ANALOG_INPUT1:
        {
            ADPCH = ADC_AN1_INPUT;
            break;
        }
        case ANALOG_INPUT2:
        {
            ADPCH = ADC_AN2_INPUT;
            break;
        }
        case ANALOG_VSS_INPUT:
        {
            ADPCH = ADC_VSS_INPUT;
            break;
        }
        case ANALOG_DAC2_INPUT:
        {
            ADPCH = ADC_DAC2_INPUT;
            break;
        }
        default:
        {
            //Invalid value
        }
    }
}

//Returns true if data is ready
//Cleared automatically on read
bool ADCC_isResultReady(void)
{
    return sampleReady;
}

//Returns the sampling channel
uint8_t ADCC_getSampleChannel(void)
{
    if (ADPCH == ADC_AN1_INPUT)
    {
        return ANALOG_INPUT1;
    }
    else if (ADPCH == ADC_AN2_INPUT)
    {
        return ANALOG_INPUT2;
    }
    else if (ADPCH == ADC_VSS_INPUT)
    {
        return ANALOG_VSS_INPUT;
    }
    else if (ADPCH == ADC_DAC2_INPUT)
    {
        return ANALOG_DAC2_INPUT;
    }
    return UNUSED;
}

//Returns the high byte of the result
uint8_t ADCC_getResult_H(void)
{
    sampleReady = false;
    if (config.averagingConfig == ADC_1_SAMPLE)
    {
        return ADRESH;
    }
    return ADFLTRH;
}

//Returns the low byte of the result
uint8_t ADCC_getResult_L(void)
{
    sampleReady = false;
    if (config.averagingConfig == ADC_1_SAMPLE)
    {
        return ADRESL;
    }
    return ADFLTRL;
}

void __interrupt(irq(IRQ_ADT)) ADCC_onConversion(void)
{
    sampleReady = true;
    
    //Clear AD Threshold
    PIR2bits.ADTIF = 0;
}
