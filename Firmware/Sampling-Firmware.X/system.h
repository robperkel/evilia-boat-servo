#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
    
#define I2C_BASE_ADDRESS 0x40
    
//Sets the number of ms the I2C bus can stall for before resetting the peripheral
#define I2C_TIMEOUT_TIME 1
    
    //Initializes all HW Peripherals
    //DOES NOT INIT SW FEATURES
    void System_init(void);
    
    //This function indicates the Watchdog Timer (WDT) needs be cleared
    void System_setWDTFlag(void);
    
    //Returns true if the WDT needs to be cleared
    bool System_getWDTFlag(void);
    
    //Resets the WDT
    //Only called from Main
    void System_clearWDT(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

