#ifndef SW_REGISTERS_H
#define	SW_REGISTERS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
    
    //Initializes the SW-defined registers and state machines
    void Registers_init(void);
    
    //Cleans up variables on an I2C Stop
    void Registers_finish(void);
    
    //Sets the address to read/write to. Returns false if address is invalid
    bool Registers_setRegisterAddress(uint8_t addr);
    
    //Reads a byte of data from the defined register address. Automatically increments on valid address.
    //Returns 0xFF if invalid (and does not increment to the next position).
    uint8_t Registers_getByte(void);
    
    //Writes a byte of data to the defined register address. Automatically increments on valid address.
    //Returns false if invalid (and does not increment to the next position)
    bool Registers_setByte(uint8_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* SW_REGISTERS_H */

