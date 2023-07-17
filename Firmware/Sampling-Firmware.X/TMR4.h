#ifndef TMR4_H
#define	TMR4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
#define PUMP_TIMEOUT_START TMR4_start
#define PUMP_TIMEOUT_STOP TMR4_stop
#define PUMP_TIMEOUT_SET_PERIOD TMR4_setPeriod
#define PUMP_TIMEOUT_GET_PERIOD TMR4_getPeriod
#define PUMP_TIMEOUT_SET_CALLBACK TMR4_setCallback
    
//Default timeout
#define DEFAULT_TMR4_PERIOD 0
    
    //Init TMR4
    void TMR4_init(void);
    
    //Start TMR4
    void TMR4_start(void);
    
    //Stop TMR4
    void TMR4_stop(void);
    
    //Set the period of TMR4
    void TMR4_setPeriod(uint8_t period);
    
    //Get the period of TMR4
    uint8_t TMR4_getPeriod(void);
    
    //Sets the callback function for timer overflow
    void TMR4_setCallback(void (*callback)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* TMR4_H */

