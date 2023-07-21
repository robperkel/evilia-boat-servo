#ifndef SW_REGISTERS_TYPES_H
#define	SW_REGISTERS_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

    //Register Addresses
    typedef enum {
        REG_STATUS = 0x00, REG_OUTPUT, REG_SAMPLE, 
        REG_ADC_H = 0x04, REG_ADC_L, 
        REG_PUMP_TIME = 0x06, REG_LED_TIME,
        REG_RESET = 0x0A, 
        REG_DC1_H = 0x10, REG_DC1_L, REG_DC2_H, REG_DC2_L, REG_DC3_H, REG_DC3_L,
            REG_DC4_H, REG_DC4_L, REG_DC5_H, REG_DC5_L, REG_DC6_H, REG_DC6_L,
        REG_FRQ1_H = 0x20, REG_FRQ1_L, REG_FRQ2_H, REG_FRQ2_L, REG_FRQ3_H, REG_FRQ3_L,
        REG_ANALOG_CONFIG = 0x30, REG_GAIN_CONFIG, REG_DAC2_OUTPUT
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
        UNUSED = 0x00, ANALOG_INPUT1, ANALOG_INPUT2, ANALOG_VSS_INPUT, ANALOG_DAC2_INPUT
    } AnalogInput;
    
    //Averaging Configurations
    typedef enum {
        ADC_1_SAMPLE = 0b0000, ADC_2_SAMPLES, ADC_4_SAMPLES, ADC_8_SAMPLES, ADC_16_SAMPLES
    } AveragingConfiguration;
    
    //Voltage Reference Configurations
    typedef enum {
        VDD = 0b00, FVR_1V, FVR_2V, FVR_4V
    } VoltageReferenceConfiguration;
    
    //Analog Config Bitfield
    typedef union {
        struct {
            unsigned averagingConfig : 4;
            unsigned : 2;
            unsigned voltageRefConfig : 2;
        };
        uint8_t value;
    } AnalogConfigRegister;
    
    //OPAMP Gain Configuration
    typedef enum {
        GAIN_16_OVER_15 = 0b000, GAIN_8_OVER_7, GAIN_4_OVER_3, GAIN_2, 
                GAIN_8_OVER_3, GAIN_4, GAIN_8, GAIN_16
    } GainConfiguration;
    
    //Unity Gain Macros
#define UNITY_GAIN_ENABLED 0b1
#define UNITY_GAIN_DISABLED 0b0
    
    //Gain Config Bitfield
    typedef union {
        struct {
            unsigned gainConfig : 3;
            unsigned unityGain : 1;
            unsigned : 4;
        };
        uint8_t value;
    } GainConfigureRegister;

#ifdef	__cplusplus
}
#endif

#endif	/* SW_REGISTERS_TYPES_H */

