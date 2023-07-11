#include "GPIO.h"
#include "GPIO_Macros.h"
#include "i2c_client.h"
#include "SW_Registers_Types.h"

#include <xc.h>

void GPIO_init()
{
    //Init Discrete I/O
    {
        //ADDR0 - RC0
        //ADDR1 - RC1
        TRISC0 = TRIS_INPUT;
        TRISC1 = TRIS_INPUT;
        
        ANSELC0 = ANSEL_DIGITAL;
        ANSELC1 = ANSEL_DIGITAL;
        
        //EXT_LED - RB6
        //PUMP_EN - RC1
        TRISB6 = TRIS_OUTPUT;
        TRISC1 = TRIS_OUTPUT;
        
        ANSELB6 = ANSEL_DIGITAL;
        ANSELC1 = ANSEL_DIGITAL;
        
        LATB6 = LAT_LOW;
        LATC1 = LAT_LOW;
        
        //Debug 0 - RA0
        //Debug 1 - RA1
        TRISA0 = TRIS_OUTPUT;
        TRISA1 = TRIS_OUTPUT;
        
        ANSELA0 = ANSEL_DIGITAL;
        ANSELA1 = ANSEL_DIGITAL;
        
        LATA0 = LAT_LOW;
        LATA1 = LAT_LOW;
        
        //Analog Input 1 - RA2
        //Analog Input 2 - RB5
        TRISA2 = TRIS_INPUT;
        TRISB5 = TRIS_INPUT;
        
        ANSELA2 = ANSEL_ANALOG;
        ANSELB5 = ANSEL_ANALOG;
        
        //OPAMP Out - RC2
        //Note - Peripheral takes control of I/O once active
        ANSELC2 = ANSEL_ANALOG;
    }

    
    //Init I2C
    {
        //RA5 - SDA
        //RA4 - SCL
    
        //Disable Analog Inputs
        ANSELAbits.ANSELA5 = ANSEL_DIGITAL;
        ANSELAbits.ANSELA4 = ANSEL_DIGITAL;

        //Configure as Open-Drain
        ODCONAbits.ODCA5 = ODCON_OPEN_DRAIN;
        ODCONAbits.ODCA4 = ODCON_OPEN_DRAIN;

        //Set as Outputs
        TRISA5 = TRIS_OUTPUT;
        TRISA4 = TRIS_OUTPUT;

        //Set PPS Outputs
        I2C1SDAPPS = 0b000101;
        I2C1SCLPPS = 0b000100;

        //Set PPS Inputs
        RA5PPS = 0x22;
        RA4PPS = 0x21;

        //Standard Slew Rate
        SLRCONAbits.SLRA5 = SLRCON_NO_LIMIT;
        SLRCONAbits.SLRA4 = SLRCON_NO_LIMIT;

        //Input Levels
        INLVLAbits.INLVLA5 = INLVL_ST;
        INLVLAbits.INLVLA4 = INLVL_ST;
    }
    
    //Init PWM
    {
        //PWM1S1P1 - RB7 (Servo 1)
        //PWM1S1P2 - RC7 (Servo 2)
        //PWM1S2P1 - RC6 (Servo 3)
        //PWM1S2P2 - RC3 (Servo 4)
        //PWM1S3P1 - RC4 (Servo 5)
        //PWM1S3P2 - RC5 (Servo 6)
        
        TRISB7 = TRIS_OUTPUT;
        LATB7 = LAT_LOW;
        RB7PPS = 0x0A;
        
        TRISC7 = TRIS_OUTPUT;
        LATC7 = LAT_LOW;
        RC7PPS = 0x0B;
        
        TRISC6 = TRIS_OUTPUT;
        LATC6 = LAT_LOW;
        RC6PPS = 0x0C;
        
        TRISC3 = TRIS_OUTPUT;
        LATC3 = LAT_LOW;
        RC3PPS = 0x0D;
        
        TRISC4 = TRIS_OUTPUT;
        LATC4 = LAT_LOW;
        RC4PPS = 0x0E;
        
        TRISC5 = TRIS_OUTPUT;
        LATC5 = LAT_LOW;
        RC5PPS = 0x0F;
    }
    
    //Init OPAMP
    {
        //Analog Input 1 - RA2
        //Analog Input 2 - RB5
        //Inputs configured in discrete I/O section
        
        //OPAMP Output - RC2
        
        ANSELCbits.ANSELC2 = ANSEL_ANALOG; //This probably un-necessary, but better safe than sorry
    }
}

//Sets the outputs from the OUTPUT register
void GPIO_setOutputState(uint8_t state)
{
    //Load into union datatype
    OutputRegister out;
    out.value = state;
    
    
}
    
//Gets the current output state of the I/O for the OUTPUT register
uint8_t GPIO_getOutputState(void)
{
    OutputRegister out;
    out.value = 0x00;
    
    
    
    return out.value;
}

//Callback for TMR2 ISR - LED Timeout
void GPIO_LED_Timeout_Callback(void)
{
    
}

//Callback for TMR4 ISR - Pump Timeout
void GPIO_Pump_Timeout_Callback(void)
{
    
}
