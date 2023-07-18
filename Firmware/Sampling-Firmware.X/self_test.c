#include "self_test.h"
#include "PWM.h"
#include "ADCC.h"

//Runs all self-tests
void selfTest_runAll(void)
{
    selfTest_configurePWM();
    
    selfTest_runADC();
}

//Sets the PWM
void selfTest_configurePWM(void)
{
    //10,000 counts per period
    //500us - 2500us pulse width
    //1 bit = 2 us
    PWM_setDutyCycle(250, SERVO1_INDEX);
    PWM_setDutyCycle(500, SERVO2_INDEX);
    PWM_setDutyCycle(750, SERVO3_INDEX);
    PWM_setDutyCycle(1000, SERVO4_INDEX);
    PWM_setDutyCycle(1250, SERVO5_INDEX);
    PWM_setDutyCycle(250, SERVO6_INDEX);
    
    PWM_loadNewParameters();
}

//Test the ADC
void selfTest_runADC(void)
{
    ADCC_setChannelAndGo(ANALOG_INPUT1);
}