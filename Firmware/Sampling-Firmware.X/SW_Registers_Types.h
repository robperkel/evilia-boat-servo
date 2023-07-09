#ifndef SW_REGISTERS_TYPES_H
#define	SW_REGISTERS_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

    //Register Addresses
    typedef enum {
        REG_STATUS = 0x00, REG_OUTPUT, REG_SAMPLE, REG_ADC_H, REG_ADC_L, 
        REG_PUMP_TIME = 0x06, REG_LED_TIME,
        REG_RESET = 0x0A, 
        REG_DC1_H = 0x10, REG_DC1_L, REG_DC2_H, REG_DC2_L, REG_DC3_H, REG_DC3_L,
            REG_DC4_H, REG_DC4_L, REG_DC5_H, REG_DC5_L, REG_DC6_H, REG_DC6_L,
        REG_FRQ1_H = 0x20, REG_FRQ1_L, REG_FRQ2_H, REG_FRQ2_L, REG_FRQ3_H, REG_FRQ3_L,
        REG_ANALOG_CONFIG1 = 0x33, REG_GAIN_CONFIG1, REG_ANALOG_CONFIG2, REG_GAIN_CONFIG2
    } SWRegisterAddress;
    
    //Status Register Bitfield
    typedef union {
        struct{
            unsigned sampleReady : 1;
            unsigned pumpState : 1;
            unsigned ledState : 1;
            unsigned : 5;
        };
        uint8_t value;
    } StatusRegister;
    
    //Output Register Bitfield
    typedef union{
        struct {
            unsigned debugLED0 : 1;
            unsigned debugLED1 : 1;
            unsigned extLED : 1;
            unsigned : 4;
            unsigned pump : 1;
        };
        uint8_t value;
    } OutputRegister;
    
    //Sample Register Options
    typedef enum {
        UNUSED = 0x00, ANALOG_INPUT1, ANALOG_INPUT2
    } AnalogInput;
    
    //Analog Config Bitfield
    typedef union {
        struct {
            unsigned averagingConfig : 4;
            unsigned : 2;
            unsigned voltageRefConfig : 2;
        };
        uint8_t value;
    } AnalogConfigRegister;
    
    //Gain Config Bitfield
    typedef union {
        struct {
            unsigned gainConfig : 4;
            unsigned : 4;
        };
        uint8_t value;
    } GainConfigureRegister;

#ifdef	__cplusplus
}
#endif

#endif	/* SW_REGISTERS_TYPES_H */

