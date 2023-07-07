#include "SW_Registers.h"
#include "SW_Registers_Types.h"

#include <stdint.h>
#include <stdbool.h>

static volatile uint8_t regIndex = 0x00;
static volatile uint16_t tempVal = 0x0000;

//Initializes the SW-defined registers and state machines
void Registers_init(void)
{

}

//Cleans up variables on an I2C Stop
void Registers_finish(void)
{
    regIndex = 0x0000;
    tempVal = 0x0000;
}

//Sets the address to read/write to. Returns false if address is invalid
bool Registers_setRegisterAddress(uint8_t addr)
{
    //Returns true if matches to a valid address
    switch (addr)
    {
        case REG_STATUS:
        {
            break;
        }
        case REG_OUTPUT:
        {
            break;
        }
        case REG_SAMPLE:
        {
            break;
        }
        case REG_ADC_H:
        {
            break;
        }
        case REG_ADC_L:
        {
            break;
        }
        case REG_PUMP_TIME:
        {
            break;
        }
        case REG_LED_TIME:
        {
            break;
        }
        case REG_DC1_H:
        {
            break;
        }
        case REG_DC1_L:
        {
            break;
        }
        case REG_DC2_H:
        {
            break;
        }
        case REG_DC2_L:
        {
            break;
        }
        case REG_DC3_H:
        {
            break;
        }
        case REG_DC3_L:
        {
            break;
        }
        case REG_DC4_H:
        {
            break;
        }
        case REG_DC4_L:
        {
            break;
        }
        case REG_DC5_H:
        {
            break;
        }
        case REG_DC5_L:
        {
            break;
        }
        case REG_DC6_H:
        {
            break;
        }
        case REG_DC6_L:
        {
            break;
        }
        case REG_FRQ1_H:
        {
            break;
        }
        case REG_FRQ1_L:
        {
            break;
        }
        case REG_FRQ2_H:
        {
            break;
        }
        case REG_FRQ2_L:
        {
            break;
        }
        case REG_FRQ3_H:
        {
            break;
        }
        case REG_FRQ3_L:
        {
            break;
        }
        case REG_ANALOG_CONFIG1:
        {
            break;
        }
        case REG_GAIN_CONFIG1:
        {
            break;
        }
        case REG_ANALOG_CONFIG2:
        {
            break;
        }
        case REG_GAIN_CONFIG2:
        {
            break;
        }
        default:
        {
            //Not defined / implemented
            return false;
        }
    }
    return true;
}

//Reads a byte of data from the defined register address. Automatically increments on valid address.
//Returns 0xFF if invalid (and does not increment to the next position).
uint8_t Registers_getByte(void)
{
    switch (regIndex)
    {
        case REG_STATUS:
        {
            break;
        }
        case REG_OUTPUT:
        {
            break;
        }
        case REG_SAMPLE:
        {
            break;
        }
        case REG_ADC_H:
        {
            break;
        }
        case REG_ADC_L:
        {
            break;
        }
        case REG_PUMP_TIME:
        {
            break;
        }
        case REG_LED_TIME:
        {
            break;
        }
        case REG_DC1_H:
        {
            break;
        }
        case REG_DC1_L:
        {
            break;
        }
        case REG_DC2_H:
        {
            break;
        }
        case REG_DC2_L:
        {
            break;
        }
        case REG_DC3_H:
        {
            break;
        }
        case REG_DC3_L:
        {
            break;
        }
        case REG_DC4_H:
        {
            break;
        }
        case REG_DC4_L:
        {
            break;
        }
        case REG_DC5_H:
        {
            break;
        }
        case REG_DC5_L:
        {
            break;
        }
        case REG_DC6_H:
        {
            break;
        }
        case REG_DC6_L:
        {
            break;
        }
        case REG_FRQ1_H:
        {
            break;
        }
        case REG_FRQ1_L:
        {
            break;
        }
        case REG_FRQ2_H:
        {
            break;
        }
        case REG_FRQ2_L:
        {
            break;
        }
        case REG_FRQ3_H:
        {
            break;
        }
        case REG_FRQ3_L:
        {
            break;
        }
        case REG_ANALOG_CONFIG1:
        {
            break;
        }
        case REG_GAIN_CONFIG1:
        {
            break;
        }
        case REG_ANALOG_CONFIG2:
        {
            break;
        }
        case REG_GAIN_CONFIG2:
        {
            break;
        }
        default:
        {
            //Not defined / implemented
            return 0xFF;
        }
    }

    return 0xFF;
}

//Writes a byte of data to the defined register address. Automatically increments on valid address.
//Returns false if invalid (and does not increment to the next position)
bool Registers_setByte(uint8_t val)
{
    switch (regIndex)
    {
        case REG_STATUS:
        {
            //Read Only
            return false;
            break;
        }
        case REG_OUTPUT:
        {
            break;
        }
        case REG_SAMPLE:
        {
            break;
        }
        case REG_ADC_H:
        {
            break;
        }
        case REG_ADC_L:
        {
            break;
        }
        case REG_PUMP_TIME:
        {
            break;
        }
        case REG_LED_TIME:
        {
            break;
        }
        case REG_DC1_H:
        {
            break;
        }
        case REG_DC1_L:
        {
            break;
        }
        case REG_DC2_H:
        {
            break;
        }
        case REG_DC2_L:
        {
            break;
        }
        case REG_DC3_H:
        {
            break;
        }
        case REG_DC3_L:
        {
            break;
        }
        case REG_DC4_H:
        {
            break;
        }
        case REG_DC4_L:
        {
            break;
        }
        case REG_DC5_H:
        {
            break;
        }
        case REG_DC5_L:
        {
            break;
        }
        case REG_DC6_H:
        {
            break;
        }
        case REG_DC6_L:
        {
            break;
        }
        case REG_FRQ1_H:
        {
            break;
        }
        case REG_FRQ1_L:
        {
            break;
        }
        case REG_FRQ2_H:
        {
            break;
        }
        case REG_FRQ2_L:
        {
            break;
        }
        case REG_FRQ3_H:
        {
            break;
        }
        case REG_FRQ3_L:
        {
            break;
        }
        case REG_ANALOG_CONFIG1:
        {
            break;
        }
        case REG_GAIN_CONFIG1:
        {
            break;
        }
        case REG_ANALOG_CONFIG2:
        {
            break;
        }
        case REG_GAIN_CONFIG2:
        {
            break;
        }
        default:
        {
            //Not defined / implemented
            return false;
        }
    }
    return false;
}
