#include "GPIO.h"
#include "GPIO_Macros.h"
#include "i2c_client.h"

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
    
}