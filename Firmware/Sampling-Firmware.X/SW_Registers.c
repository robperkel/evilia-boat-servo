#include "SW_Registers.h"
#include "SW_Registers_Types.h"
#include "PWM.h"
#include "TMR2.h"
#include "GPIO.h"
#include "system.h"
#include "TMR4.h"
#include "ADCC.h"
#include "OPAMP.h"
#include "DAC.h"

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
#ifndef HW_SELF_TEST
    regIndex = 0x0000;
#endif
    tempVal = 0x0000;
    
    //Load new parameters, if changed
    PWM_loadNewParameters();
}

//Sets the address to read/write to. Returns false if address is invalid
bool Registers_setRegisterAddress(uint8_t addr)
{
    //Returns true if matches to a valid address
    
    bool isGood = true;
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
        case REG_ANALOG_CONFIG:
        case REG_GAIN_CONFIG:
        case REG_DAC2_OUTPUT:
        {
            isGood = true;
            break;
        }
        default:
        {
            //Not defined / implemented
            isGood = false;
        }
    }
    
    if (isGood)
    {
        regIndex = addr;
    }
    
    return isGood;
}

//Reads a byte of data from the defined register address. Automatically increments on valid address.
//Returns 0xFF if invalid (and does not increment to the next position).
uint8_t Registers_getByte(void)
{
    bool isGood = true;
    uint8_t rtnVal = 0xFF;
    switch (regIndex)
    {
        case REG_STATUS:
        {
            //Clear error flag
            System_clearError();
            
            rtnVal = GPIO_getOutputState();
            rtnVal |= (System_getErrorStatus() << 1);
            rtnVal |= ADCC_isResultReady();
            break;
        }
        case REG_OUTPUT:
        {
            rtnVal = GPIO_getOutputState();
            break;
        }
        case REG_SAMPLE:
        {
            rtnVal = ADCC_getSampleChannel();
            break;
        }
        case REG_ADC_H:
        {
            rtnVal = ADCC_getResult_H();
            break;
        }
        case REG_ADC_L:
        {
            rtnVal = ADCC_getResult_L();
            break;
        }
        case REG_PUMP_TIME:
        {
            rtnVal = PUMP_TIMEOUT_GET_PERIOD();
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
        case REG_ANALOG_CONFIG:
        {
            rtnVal = ADCC_getAnalogConfig();
            break;
        }
        case REG_GAIN_CONFIG:
        {
            rtnVal = OPAMP_getGainSettings();
            break;
        }
        case REG_DAC2_OUTPUT:
        {
            rtnVal = DAC2_getValue();
            break;
        }
        default:
        {
            //Not defined / implemented
            isGood = false;
        }
    }
    
    //Increment index if no issues occurred
    if (isGood)
    {
        regIndex++;
    }

    return rtnVal;
}

//Writes a byte of data to the defined register address. Automatically increments on valid address.
//Returns false if invalid (and does not increment to the next position)
bool Registers_setByte(uint8_t val)
{
    bool isGood = true;
    
    switch (regIndex)
    {
        case REG_STATUS:
        {
            //Read Only
#ifndef HW_SELF_TEST
            return false;
#endif
            break;
        }
        case REG_OUTPUT:
        {
            System_setGPIO(val);
            break;
        }
        case REG_SAMPLE:
        {
            ADCC_setChannelAndGo(val);
            break;
        }
        case REG_ADC_H:
        case REG_ADC_L:
        {
            //Read Only
            isGood = false;
            break;
        }
        case REG_PUMP_TIME:
        {
            PUMP_TIMEOUT_SET_PERIOD(val);
            break;
        }
        case REG_LED_TIME:
        {
            LED_TIMEOUT_SET_PERIOD(val);
            break;
        }
        case REG_DC1_H:
        {
            tempVal = val;
            break;
        }
        case REG_DC1_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM_setDutyCycle(tempVal, SERVO1_INDEX);
            break;
        }
        case REG_DC2_H:
        {
            tempVal = val;
            break;
        }
        case REG_DC2_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM_setDutyCycle(tempVal, SERVO2_INDEX);
            break;
        }
        case REG_DC3_H:
        {
            tempVal = val;
            break;
        }
        case REG_DC3_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM_setDutyCycle(tempVal, SERVO3_INDEX);
            break;
        }
        case REG_DC4_H:
        {
            tempVal = val;
            break;
        }
        case REG_DC4_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM_setDutyCycle(tempVal, SERVO4_INDEX);
            break;
        }
        case REG_DC5_H:
        {
            tempVal = val;
            break;
        }
        case REG_DC5_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM_setDutyCycle(tempVal, SERVO5_INDEX);
            break;
        }
        case REG_DC6_H:
        {
            tempVal = val;
            break;
        }
        case REG_DC6_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM_setDutyCycle(tempVal, SERVO6_INDEX);
            break;
        }
        case REG_FRQ1_H:
        {
            tempVal = val;
            break;
        }
        case REG_FRQ1_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM1_setPeriod(tempVal);
            break;
        }
        case REG_FRQ2_H:
        {
            tempVal = val;
            break;
        }
        case REG_FRQ2_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM2_setPeriod(tempVal);
            break;
        }
        case REG_FRQ3_H:
        {
            tempVal = val;
            break;
        }
        case REG_FRQ3_L:
        {
            tempVal <<= 8;
            tempVal |= val;
            PWM3_setPeriod(tempVal);
            break;
        }
        case REG_ANALOG_CONFIG:
        {
            ADCC_loadAnalogConfig(val);
            break;
        }
        case REG_GAIN_CONFIG:
        {
            OPAMP_setGainSettings(val);
            break;
        }
        case REG_DAC2_OUTPUT:
        {
            DAC2_setValue(val);
            break;
        }
        default:
        {
            //Not defined / implemented
            isGood = false;
        }
    }
    
    //Increment index if no issues occurred
    if (isGood)
    {
        regIndex++;
    }
    
    return isGood;
}
