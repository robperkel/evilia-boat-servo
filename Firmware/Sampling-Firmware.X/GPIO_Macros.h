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
    
//I2C Address I/O
#define ADDR0_GET_VALUE() PORTCbits.RC0
#define ADDR1_GET_VALUE() PORTBbits.RB4
    
#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_MACROS_H */

