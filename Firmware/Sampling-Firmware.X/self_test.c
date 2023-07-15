#include "self_test.h"
#include "PWM.h"

//Runs all self-tests
void selfTest_runAll(void)
{
    selfTest_configurePWM();
}

//Sets the PWM to 1ms/1.5ms/2ms/1ms/1.5ms/2ms
void selfTest_configurePWM(void)
{
    //640 = 100% @ 50 Hz
    PWM_setDutyCycle(31, SERVO1_INDEX);
    PWM_setDutyCycle(47, SERVO2_INDEX);
    PWM_setDutyCycle(62, SERVO3_INDEX);
    PWM_setDutyCycle(31, SERVO4_INDEX);
    PWM_setDutyCycle(47, SERVO5_INDEX);
    PWM_setDutyCycle(62, SERVO6_INDEX);
    
    PWM_loadNewPeriods();
}