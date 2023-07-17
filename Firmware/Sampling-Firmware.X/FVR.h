#ifndef FVR_H
#define	FVR_H

#include "SW_Registers_Types.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Initializes the FVR
    void FVR_init(void);
    
    //Sets the FVR output to the ADC
    void FVR_setADCRef(VoltageReferenceConfiguration config);

#ifdef	__cplusplus
}
#endif

#endif	/* FVR_H */

