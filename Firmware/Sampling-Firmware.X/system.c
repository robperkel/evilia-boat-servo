#include "system.h"

#include "GPIO.h"
#include "i2c_client.h"
#include "interrupts.h"
#include "PWM.h"
#include "NCO.h"
#include "GPIO_Macros.h"
#include "ADCC.h"
#include "TMR2.h"

#include <stdbool.h>

static bool WDTclear = true;

//Initializes all HW Peripherals
//DOES NOT INIT SW FEATURES
void System_init(void)
{
    //Init GPIO
    GPIO_init();
    
    //Calculate I2C Address on PoR
    uint8_t addr = I2C_BASE_ADDRESS;
    addr |= (ADDR1_GetValue() << 1);
    addr |= ADDR0_GetValue();
    
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
    
    //Init the ADC
    ADCC_init();
    
    //Init the OPAMP
    
    //Init TMR2
    TMR2_init();
    
    //Configure callback
    LED_TIMEOUT_SET_CALLBACK(&GPIO_LED_Timeout_Callback);
    
    //Init TMR4
    
    //Configure callback
    
}

//This function indicates the Watchdog Timer (WDT) must be cleared
void System_setWDTFlag(void)
{
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
}