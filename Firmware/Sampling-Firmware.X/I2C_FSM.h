#ifndef I2C_FSM_H
#define	I2C_FSM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    //Init the I2C Interface State Machine
    void I2C_FSM_init(void);
    
    //Handles Bytes from I2C Interface
    bool I2C_FSM_handleWrite(uint8_t val);
    
    //Sends Bytes to I2C Interface
    uint8_t I2C_FSM_handleRead(void);
    
    //I2C Stop Event
    void I2C_FSM_handleStop(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* I2C_REGISTERS_H */

