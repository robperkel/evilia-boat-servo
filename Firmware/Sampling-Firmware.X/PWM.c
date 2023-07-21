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
    
    //MFINTOSC (500 kHz) for base clock
    PWM1CLK = 0b0101;
    PWM2CLK = 0b0101;
    PWM3CLK = 0b0101;
    
    //No Clock Pre-Scaling
    PWM1CPRE = 0x00;
    PWM2CPRE = 0x00;
    PWM3CPRE = 0x00;
    
    //Disable Auto-Load
    PWM1LDS = 0x00;
    PWM2LDS = 0x00;
    PWM3LDS = 0x00;
    
    //Set Periods to 50 Hz (Normal Servo Frequency)
    //500 kHz / 50 Hz = 10,000
    PWM1PR = PWM_DEFAULT_FRQ_VALUE;
    PWM2PR = PWM_DEFAULT_FRQ_VALUE;
    PWM3PR = PWM_DEFAULT_FRQ_VALUE;
    
    //Set Periods to Default
    PWM1S1P1 = PWM_DEFAULT_DC_VALUE;
    PWM1S1P2 = PWM_DEFAULT_DC_VALUE;
    PWM2S1P1 = PWM_DEFAULT_DC_VALUE;
    PWM2S1P2 = PWM_DEFAULT_DC_VALUE;
    PWM3S1P1 = PWM_DEFAULT_DC_VALUE;
    PWM3S1P2 = PWM_DEFAULT_DC_VALUE;
    
    //No PWM Interrupts
    PWM1GIE = 0x00;
    PWM2GIE = 0x00;
    PWM3GIE = 0x00;
    
    //Active-High Period, No "Push-Pull" Outputs, Left-Aligned
    PWM1S1CFG = 0x00;
    PWM2S1CFG = 0x00;
    PWM3S1CFG = 0x00;
    
    //Enable all PWM instances at the same time
    PWMEN = 0x07;
}

//Loads new PWM values - PWM instances are changed simutanously
//Must be called after PWMx_setPeriod
void PWM_loadNewParameters(void)
{
    //Load new values into PWM1/2/3 at the same time
    PWMLOAD = 0x07;
}

//Sets the duty cycle of a specific PWM
void PWM_setDutyCycle(uint16_t dc, uint8_t servo)
{
    switch (servo)
    {
        case SERVO1_INDEX:
        {
            //Servo 1
            //PWM1, Phase 1
            SERVO1_DC = dc;
            break;
        }
        case SERVO2_INDEX:
        {
            //Servo 2
            //PWM1, Phase 2
            SERVO2_DC = dc;
            break;
        }
        case SERVO3_INDEX:
        {
            //Servo 3
            //PWM2, Phase 1
            SERVO3_DC = dc;
            break;
        }
        case SERVO4_INDEX:
        {
            //Servo 4
            //PWM2, Phase 2
            SERVO4_DC = dc;
            break;
        }
        case SERVO5_INDEX:
        {
            //Servo 5
            //PWM3, Phase 1
            SERVO5_DC = dc;
            break;
        }
        case SERVO6_INDEX:
        {
            //Servo 6
            //PWM3, Phase 2
            SERVO6_DC = dc;
            break;
        }
        default:
        {
            //Invalid index
        }
    }
}

//Gets the high byte of the duty cycle of a specific PWM
uint8_t PWM_getDC_H(uint8_t servo)
{
    uint8_t DC_H = 0xFF;
    switch (servo)
    {
        case SERVO1_INDEX:
        {
            //Servo 1
            //PWM1, Phase 1
            DC_H = SERVO1_DC_H;
            break;
        }
        case SERVO2_INDEX:
        {
            //Servo 2
            //PWM1, Phase 2
            DC_H = SERVO2_DC_H;
            break;
        }
        case SERVO3_INDEX:
        {
            //Servo 3
            //PWM2, Phase 1
            DC_H = SERVO3_DC_H;
            break;
        }
        case SERVO4_INDEX:
        {
            //Servo 4
            //PWM2, Phase 2
            DC_H = SERVO4_DC_H;
            break;
        }
        case SERVO5_INDEX:
        {
            //Servo 5
            //PWM3, Phase 1
            DC_H = SERVO5_DC_H;
            break;
        }
        case SERVO6_INDEX:
        {
            //Servo 6
            //PWM3, Phase 2
            DC_H = SERVO6_DC_H;
            break;
        }
        default:
        {
            //Invalid index
        }
    }
    return DC_H;
}

//Gets the high byte of the duty cycle of a specific PWM
uint8_t PWM_getDC_L(uint8_t servo)
{
    uint8_t DC_L = 0xFF;
    switch (servo)
    {
        case SERVO1_INDEX:
        {
            //Servo 1
            //PWM1, Phase 1
            DC_L = SERVO1_DC_L;
            break;
        }
        case SERVO2_INDEX:
        {
            //Servo 2
            //PWM1, Phase 2
            DC_L = SERVO2_DC_L;
            break;
        }
        case SERVO3_INDEX:
        {
            //Servo 3
            //PWM2, Phase 1
            DC_L = SERVO3_DC_L;
            break;
        }
        case SERVO4_INDEX:
        {
            //Servo 4
            //PWM2, Phase 2
            DC_L = SERVO4_DC_L;
            break;
        }
        case SERVO5_INDEX:
        {
            //Servo 5
            //PWM3, Phase 1
            DC_L = SERVO5_DC_L;
            break;
        }
        case SERVO6_INDEX:
        {
            //Servo 6
            //PWM3, Phase 2
            DC_L = SERVO6_DC_L;
            break;
        }
        default:
        {
            //Invalid index
        }
    }
    return DC_L;
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

uint8_t PWM1_getFrequency_H(void)
{
    return PWM1PRH;
}
uint8_t PWM1_getFrequency_L(void)
{
    return PWM1PRL;
}

uint8_t PWM2_getFrequency_H(void)
{
    return PWM2PRH;
}
uint8_t PWM2_getFrequency_L(void)
{
    return PWM2PRL;
}

uint8_t PWM3_getFrequency_H(void)
{
    return PWM3PRH;
}
uint8_t PWM3_getFrequency_L(void)
{
    return PWM3PRL;
}
    