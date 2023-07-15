#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //Init the GPIO
    void GPIO_init(void);
        
    //Gets the current output state of the I/O for the OUTPUT register
    uint8_t GPIO_getOutputState(void);
    
    //Callback for TMR2 ISR - LED Timeout
    void GPIO_LED_Timeout_Callback(void);
    
    //Callback for TMR4 ISR - Pump Timeout
    void GPIO_Pump_Timeout_Callback(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

