#ifndef GPIO_MACROS_H
#define	GPIO_MACROS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
//Register Macros
    
//LAT - Latched Output Values
#define LAT_HIGH 1
#define LAT_LOW 0    
    
//TRIS - Tristate Control (I/O Direction)
#define TRIS_INPUT 1
#define TRIS_OUTPUT 0
    
//ANSEL - Analog Select
#define ANSEL_ANALOG 1
#define ANSEL_DIGITAL 0
    
//WPU - Weak Pull-Ups
#define WPU_ENABLED 1
#define WPU_DISABLED 0
    
//INLVL - Input Levels
#define INLVL_ST 1 //Schmitt Trigger Levels
#define INLVL_TTL 0 //TTL Logic Levels
    
//SLRCON - Slew Rate Limiters
#define SLRCON_LIMITED 1
#define SLRCON_NO_LIMIT 0
    
//ODCON - Open Drain Enable
#define ODCON_OPEN_DRAIN 1
#define ODCON_PUSH_PULL 0

//I/O Macros
    
//PUMP_EN Output - RC1
#define PUMP_EN_LAT LATC1
#define PUMP_EN_TRIS TRISC1
#define PUMP_EN_ANSEL ANSELC1
#define PUMP_EN_SetHigh() PUMP_EN_LAT = 1
#define PUMP_EN_SetLow() PUMP_EN_LAT = 0
#define PUMP_EN_GetValue() PUMP_EN_LAT
    
//EXT_LED Output - RB6
#define EXT_LED_LAT LATB6
#define EXT_LED_TRIS TRISB6
#define EXT_LED_ANSEL ANSELB6
#define EXT_LED_SetHigh() EXT_LED_LAT = 1
#define EXT_LED_SetLow() EXT_LED_LAT = 0
#define EXT_LED_GetValue() EXT_LED_LAT
    
//DEBUG1 Output - RA1
#define DEBUG1_LAT LATA1
#define DEBUG1_TRIS TRISA1
#define DEBUG1_ANSEL ANSELA1
#define DEBUG1_SetHigh() DEBUG1_LAT = 1
#define DEBUG1_SetLow() DEBUG1_LAT = 0
#define DEBUG1_GetValue() DEBUG1_LAT

//DEBUG0 Output - RA0
#define DEBUG0_LAT LATA0
#define DEBUG0_TRIS TRISA0
#define DEBUG0_ANSEL ANSELA0
#define DEBUG0_SetHigh() DEBUG0_LAT = 1
#define DEBUG0_SetLow() DEBUG0_LAT = 0
#define DEBUG0_GetValue() DEBUG0_LAT
    
//I2C Address I/O
    
//ADDR1 - RB4
#define ADDR1_TRIS TRISB4
#define ADDR1_ANSEL ANSELB4
#define ADDR1_GetValue() PORTBbits.RB4
    
//ADDR0 - RC0
#define ADDR0_TRIS TRISC0
#define ADDR0_ANSEL ANSELC0
#define ADDR0_GetValue() PORTCbits.RC0
    
#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_MACROS_H */

