#include "system.h"

#include "GPIO.h"
#include "i2c_client.h"
#include "interrupts.h"
#include "PWM.h"
#include "NCO.h"

//Initializes all HW Peripherals
//DOES NOT INIT SW FEATURES
void System_init(void)
{
    //Init GPIO
    GPIO_init();
    
    //Init I2C Client
    I2C_initClient();
    
    //Reset I2C on Bus TimeOut (BTO), 1ms Bus Timeout
    //See Note 2 for I2CxBTO Register in the Datasheet for Details
    I2C_initBTO(true, true, 0, I2C_BTO_LFINTOSC);
    
    //Configure Vector Interrupts
    //Does NOT enable interrupts
    Interrupts_init();
    
    //Init PWM Peripherals
    PWM_init();
    
    //Init NCO Peripheral
    NCO_init();
}
