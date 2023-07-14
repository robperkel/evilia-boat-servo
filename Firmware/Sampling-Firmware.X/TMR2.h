#ifndef TMR2_H
#define	TMR2_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
#define LED_TIMEOUT_START TMR2_start
#define LED_TIMEOUT_STOP TMR2_stop
#define LED_TIMEOUT_SET_PERIOD TMR2_setPeriod
#define LED_TIMEOUT_GET_PERIOD TMR2_getPeriod
#define LED_TIMEOUT_SET_CALLBACK TMR2_setCallback
    
    //Init TMR2
    void TMR2_init(void);
    
    //Start TMR2
    void TMR2_start(void);
    
    //Stop TMR2
    void TMR2_stop(void);
    
    //Set the period of TMR2
    void TMR2_setPeriod(uint8_t period);
    
    //Get the period of TMR2
    uint8_t TMR2_getPeriod(void);
    
    //Sets the callback function for timer overflow
    void TMR2_setCallback(void (*callback)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* TMR2_H */

