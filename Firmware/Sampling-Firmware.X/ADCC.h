#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
//(Positive) Analog Inputs
#define ADC_AN1_INPUT 0b10000010
#define ADC_AN2_INPUT 0b10001101
#define ADC_VSS_INPUT 0b00111011

#include <stdint.h>
#include <stdbool.h>
    
#include "SW_Registers_Types.h"
    
    //Init the ADC
    void ADCC_init(void);
    
    //Loads a new analog configuration
    void ADCC_loadAnalogConfig(uint8_t nConfig);

    //Gets the analog configuration of the ADCC
    uint8_t ADCC_getAnalogConfig(void);
    
    //Sets the sampling channel and begins a conversion
    void ADCC_setChannelAndGo(AnalogInput input);
    
    //Returns true if data is ready
    //Cleared automatically on read
    bool ADCC_isResultReady(void);
    
    //Returns the sampling channel
    uint8_t ADCC_getSampleChannel(void);
    
    //Returns the high byte of the result
    uint8_t ADCC_getResult_H(void);
    
    //Returns the low byte of the result
    uint8_t ADCC_getResult_L(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

