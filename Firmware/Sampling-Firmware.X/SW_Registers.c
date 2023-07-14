#include "SW_Registers.h"
#include "SW_Registers_Types.h"
#include "PWM.h"
#include "TMR2.h"

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
        case REG_OUTPUT:
        case REG_SAMPLE:
        case REG_ADC_H:
        case REG_ADC_L:
        case REG_PUMP_TIME:
        case REG_LED_TIME:
        case REG_DC1_H:
        case REG_DC1_L:
        case REG_DC2_H:
        case REG_DC2_L:
        case REG_DC3_H:
        case REG_DC3_L:
        case REG_DC4_H:
        case REG_DC4_L:
        case REG_DC5_H:
        case REG_DC5_L:
        case REG_DC6_H:
        case REG_DC6_L:
        case REG_FRQ1_H:
        case REG_FRQ1_L:
        case REG_FRQ2_H:
        case REG_FRQ2_L:
        case REG_FRQ3_H:
        case REG_FRQ3_L:
        case REG_ANALOG_CONFIG1:
        case REG_GAIN_CONFIG1:
        case REG_ANALOG_CONFIG2:
        case REG_GAIN_CONFIG2:
        {
            return true;
        }
        default:
        {
            //Not defined / implemented
            return false;
        }
    }
    return false;
}

//Reads a byte of data from the defined register address. Automatically increments on valid address.
//Returns 0xFF if invalid (and does not increment to the next position).
uint8_t Registers_getByte(void)
{
    uint8_t rtnVal = 0xFF;
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
            rtnVal = LED_TIMEOUT_GET_PERIOD();
            break;
        }
        case REG_DC1_H:
        {
            rtnVal = PWM_getDC_H(SERVO1_INDEX);
            break;
        }
        case REG_DC1_L:
        {
            rtnVal = PWM_getDC_L(SERVO1_INDEX);
            break;
        }
        case REG_DC2_H:
        {
            rtnVal = PWM_getDC_H(SERVO2_INDEX);
            break;
        }
        case REG_DC2_L:
        {
            rtnVal = PWM_getDC_L(SERVO2_INDEX);
            break;
        }
        case REG_DC3_H:
        {
            rtnVal = PWM_getDC_H(SERVO3_INDEX);
            break;
        }
        case REG_DC3_L:
        {
            rtnVal = PWM_getDC_L(SERVO3_INDEX);
            break;
        }
        case REG_DC4_H:
        {
            rtnVal = PWM_getDC_H(SERVO4_INDEX);
            break;
        }
        case REG_DC4_L:
        {
            rtnVal = PWM_getDC_L(SERVO4_INDEX);
            break;
        }
        case REG_DC5_H:
        {
            rtnVal = PWM_getDC_H(SERVO5_INDEX);
            break;
        }
        case REG_DC5_L:
        {
            rtnVal = PWM_getDC_L(SERVO5_INDEX);
            break;
        }
        case REG_DC6_H:
        {
            rtnVal = PWM_getDC_H(SERVO6_INDEX);
            break;
        }
        case REG_DC6_L:
        {
            rtnVal = PWM_getDC_L(SERVO6_INDEX);
            break;
        }
        case REG_FRQ1_H:
        {
            rtnVal = PWM1_getFrequency_H();
            break;
        }
        case REG_FRQ1_L:
        {
            rtnVal = PWM1_getFrequency_L();
            break;
        }
        case REG_FRQ2_H:
        {
            rtnVal = PWM2_getFrequency_H();
            break;
        }
        case REG_FRQ2_L:
        {
            rtnVal = PWM2_getFrequency_L();
            break;
        }
        case REG_FRQ3_H:
        {
            rtnVal = PWM3_getFrequency_H();
            break;
        }
        case REG_FRQ3_L:
        {
            rtnVal = PWM3_getFrequency_L();
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
        }
    }

    return rtnVal;
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
