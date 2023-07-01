#ifndef I2C_REGISTERS_H
#define	I2C_REGISTERS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    //Init the SW Registers
    void Registers_init(void);
    
    //Handles Bytes from I2C Interface
    bool Registers_handleWrite(uint8_t val);
    
    //Sends Bytes to I2C Interface
    uint8_t Registers_handleRead(void);
    
    //I2C Stop Event
    void Registers_handleStop(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* I2C_REGISTERS_H */

