#include "system.h"

#include "GPIO.h"
#include "i2c_client.h"
#include "interrupts.h"
#include "PWM.h"
#include "NCO.h"
#include "GPIO_Macros.h"
#include "ADCC.h"
#include "TMR2.h"
#include "SW_Registers_Types.h"
#include "OPAMP.h"
#include "TMR4.h"
#include "FVR.h"
#include "DAC.h"

#include <stdbool.h>

static volatile bool WDTclear = true;
static volatile bool statusError = false;

//Initializes all HW Peripherals
//DOES NOT INIT SW FEATURES
void System_init(void)
{
    //Init GPIO
    GPIO_init();
    
    //Calculate I2C Address on PoR
    uint8_t addr = I2C_BASE_ADDRESS;
#ifndef I2C_DISABLE_ADDR
    addr |= (ADDR1_GetValue() << 1);
    addr |= ADDR0_GetValue();
#endif
    
    //Init I2C Client
    I2C_initClient(addr);
    
    //Reset I2C on Bus TimeOut (BTO), 1ms Bus Timeout
    //See section 36.3.7 in the Datasheet
    I2C_initBTO(true, true, I2C_TIMEOUT_TIME, I2C_BTO_LFINTOSC);
    
    //Configure Vector Interrupts
    //Does NOT enable interrupts
    Interrupts_init();
    
    //Init PWM Peripherals
    PWM_init();
    
    //Init NCO Peripheral
    NCO_init();
    
    //Setup 1s interrupts (to indicate WDT needs to be cleared)
    NCO_setCallback(&System_setWDTFlag);
    
    //Init the FVR
    FVR_init();
    
    //Init DAC2 (testing only)
    DAC2_init();
    
    //Init the ADC
    ADCC_init();
    
    //Init the OPAMP
    OPAMP_init();
    
    //Init TMR2
    TMR2_init();
    
    //Configure callback
    LED_TIMEOUT_SET_CALLBACK(&GPIO_LED_Timeout_Callback);
    
    //Init TMR4
    TMR4_init();
    
    //Configure callback
    PUMP_TIMEOUT_SET_CALLBACK(&GPIO_Pump_Timeout_Callback);
}

//This function indicates the Watchdog Timer (WDT) must be cleared
void System_setWDTFlag(void)
{
#ifdef HEARTBEAT_LED
    DEBUG1_Toggle();
#endif
    
    WDTclear = true;
    
    //Must read the WDT
    volatile uint8_t t = WDTCON0;
}

//Returns true if the WDT needs to be cleared
bool System_getWDTFlag(void)
{
    return WDTclear;
}

//Resets the WDT
//Only called from Main
void System_clearWDT(void)
{
    CLRWDT();
    
    //Clear flag
    WDTclear = false;
}

//Sets the GPIO outputs of the system
void System_setGPIO(uint8_t state)
{
    //Load into union datatype
    OutputRegister out;
    out.value = state;
    
    if (out.pump)
    {
        //Enable pump
        PUMP_EN_SetHigh();
        TMR4_start();
    }
    else
    {
        //Disable pump
        PUMP_EN_SetLow();
        TMR4_stop();
    }
    
    if (out.extLED)
    {
        //Enable EXT_LED
        EXT_LED_SetHigh();
        TMR2_start();
    }
    else
    {
        //Disable EXT_LED
        EXT_LED_SetLow();
        TMR2_stop();
    }
    
    if (out.debugLED1)
    {
        //Turn on DEBUG1 LED
        DEBUG1_SetHigh();
    }
    else
    {
        //Turn off DEBUG1 LED
        DEBUG1_SetLow();
    }
    
    if (out.debugLED0)
    {
        //Turn on DEBUG0 LED
        DEBUG0_SetHigh();
    }
    else
    {
        //Turn off DEBUG0 LED
        DEBUG0_SetLow();
    }
}

//Set the error flag
void System_setError(void)
{
    statusError = true;
}

//Clears the error flag
void System_clearError(void)
{
    statusError = false;
}

//Returns the state of the error flag
bool System_getErrorStatus(void)
{
    return statusError;
}