#ifndef CLC_H
#define	CLC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
    
    //Init the CLCs
    void CLCs_init(void);
    
    //Returns the output of CLC2
    bool CLC2_getOutputValue(void);
    
    //Set the callback function for a rising edge
    void CLC2_setRisingEdgeISR(void (*callback)(void));
    
    //Set the callback function for a falling edge
    void CLC2_setFallingEdgeISR(void (*callback)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* CLC_H */

