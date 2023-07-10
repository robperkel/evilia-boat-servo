#include "PWM.h"

#include <xc.h>

//Initializes all PWM Instances
void PWM_init()
{
    //Turn off peripheral instances
    //(Shouldn't be required, but just in case)
    PWM1CON = 0x00;
    PWM2CON = 0x00;
    PWM3CON = 0x00;
    
    //No ERS
    PWM1ERS = 0x00;
    PWM2ERS = 0x00;
    PWM3ERS = 0x00;
    
    //LFINTOSC for base clock
    PWM1CLK = 0b0100;
    PWM2CLK = 0b0100;
    PWM3CLK = 0b0100;
    
    //No Clock Pre-Scaling
    PWM1CPRE = 0x00;
    PWM2CPRE = 0x00;
    PWM3CPRE = 0x00;
    
    //Disable Auto-Load
    PWM1LDS = 0x00;
    PWM2LDS = 0x00;
    PWM3LDS = 0x00;
    
    //Set Periods to 50 Hz (Normal Servo Frequency)
    //31 kHz / 50 Hz = 620
    PWM1PR = 620;
    PWM2PR = 620;
    PWM3PR = 620;
    
    //Set Duty Cycles to 0%
    PWM1S1P1 = 0x0000;
    PWM1S1P2 = 0x0000;
    PWM2S1P1 = 0x0000;
    PWM2S1P2 = 0x0000;
    PWM3S1P1 = 0x0000;
    PWM3S1P2 = 0x0000;
    
    //No PWM Interrupts
    PWM1GIE = 0x00;
    PWM2GIE = 0x00;
    PWM3GIE = 0x00;
    
    //Active-High Period, No "Push-Pull" Outputs, Left-Aligned
    PWM1S1CFG = 0x00;
    PWM2S1CFG = 0x00;
    PWM3S1CFG = 0x00;
    
    //Enable all PWM instances at the same time
    PWMEN = 0x03;
}

//Loads new PWM values - PWM instances are changed simutanously
//Must be called after PWMx_setPeriod
void PWM_loadNewPeriods(void)
{
    //Load new values into PWM1/2/3 at the same time
    PWMLOAD = 0x03;
}

//Sets the period of PWM outputs
void PWM1_setPeriod(uint16_t val)
{
    PWM1PR = val;
}

void PWM2_setPeriod(uint16_t val)
{
    PWM2PR = val;
}

void PWM3_setPeriod(uint16_t val)
{
    PWM3PR = val;
}

    