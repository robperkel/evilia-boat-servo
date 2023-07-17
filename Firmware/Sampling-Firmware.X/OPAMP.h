#ifndef OPAMP_H
#define	OPAMP_H

#include "SW_Registers_Types.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
//RA2 - IN2+
#define OPAMP_ANALOG_INPUT1 0b10
    
//RB5 - IN0+
#define OPAMP_ANALOG_INPUT2 0b00
    
    //Init the OPAMP
    void OPAMP_init(void);
    
    //Set the gain of the OPAMP
    void OPAMP_setGainSettings(uint8_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* OPAMP_H */

