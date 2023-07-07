#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "SW_Registers.h"

static volatile bool isFirst = true;

//Init the I2C Interface State Machine
void I2C_FSM_init(void)
{
    
}

//Handles Bytes from I2C Interface
bool I2C_FSM_handleWrite(uint8_t val)
{
    bool isGood = false;
    if (isFirst)
    {
        //Load Register Address
        isFirst = false;
        isGood = Registers_setRegisterAddress(val);
    }
    else
    {
        //Every byte after is a register write
        isGood = Registers_setByte(val);
    }
    
    return isGood;
}

//Sends Bytes to I2C Interface
uint8_t I2C_FSM_handleRead(void)
{
    return Registers_getByte();
}

//I2C Stop Event
void I2C_FSM_handleStop(void)
{
    isFirst = true;
    Registers_finish();
}

