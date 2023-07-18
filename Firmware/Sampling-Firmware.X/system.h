#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
#define I2C_BASE_ADDRESS 0x40
  
//If defined, ADDR1/0 are not used in address calculation
//#define I2C_DISABLE_ADDR
    
//Sets the number of ms the I2C bus can stall for before resetting the peripheral
#define I2C_TIMEOUT_TIME 5
    
//If set, LED1 will blink at 0.5 Hz while running
#define HEARTBEAT_LED
    
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
    
    //Sets the GPIO outputs of the system
    void System_setGPIO(uint8_t state);
    
    //Set the error flag
    void System_setError(void);
    
    //Clears the error flag
    void System_clearError(void);
    
    //Returns the state of the error flag
    bool System_getErrorStatus(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

