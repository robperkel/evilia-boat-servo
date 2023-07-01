#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

static volatile uint8_t regIndex = 0x00;

//Init the SW Registers
void Registers_init(void)
{
    
}

//Handles Bytes from I2C Interface
bool Registers_handleWrite(uint8_t val)
{
    return false;
}

//Sends Bytes to I2C Interface
uint8_t Registers_handleRead(void)
{
    return 0xFF;
}

//I2C Stop Event
void Registers_handleStop(void)
{
    regIndex = 0x00;
}

