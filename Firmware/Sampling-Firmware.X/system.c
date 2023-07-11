#include "system.h"

#include "GPIO.h"
#include "i2c_client.h"
#include "interrupts.h"
#include "PWM.h"
#include "NCO.h"
#include "GPIO_Macros.h"

//Initializes all HW Peripherals
//DOES NOT INIT SW FEATURES
void System_init(void)
{
    //Init GPIO
    GPIO_init();
    
    //Calculate I2C Address on PoR
    uint8_t addr = I2C_BASE_ADDRESS;
    addr |= (ADDR1_GET_VALUE() << 1);
    addr |= ADDR0_GET_VALUE();
    
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
}
